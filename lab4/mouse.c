#include "mouse.h"

int hook_id = 3;
uint8_t output_buffer;
uint8_t packet_bytes [3];
int packet_number = 0;
struct packet packet;

int (mouse_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;

    *bit_no = BIT(hook_id);

    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&hook_id);
}

void (mouse_ih)() {
    if (read_kbc_output(OUT_BUF, &output_buffer, MOUSE)) return;

    if (packet_number == 0) {
        if (output_buffer & BIT(3)) {
            packet_bytes[packet_number] = output_buffer;
            packet_number++;
        }
    }
    else {
        packet_bytes[packet_number] = output_buffer;
        packet_number++;
    }
    
}

void (parse_bytes_to_packet)() {
    packet.bytes[0] = packet_bytes[0];
    packet.bytes[1] = packet_bytes[1];
    packet.bytes[2] = packet_bytes[2];
    
    packet.mb = (packet_bytes[0] >> 2) & 0x01;
    packet.rb = (packet_bytes[0] >> 1) & 0x01;
    packet.lb = packet_bytes[0] & 0x01;

    packet.x_ov = (packet_bytes[0] >> 6) & 0x01;
    packet.y_ov = (packet_bytes[0] >> 7) & 0x01;

    packet.delta_y = ((packet_bytes[0] >> 5) & 0x01) ? 0xFF00 | packet_bytes[2] : 0x0000 | packet_bytes[2];
    packet.delta_x = ((packet_bytes[0] >> 4) & 0x01) ? 0xFF00 | packet_bytes[1] : 0x0000 | packet_bytes[1];
}

int (write_mouse_cmd)(uint8_t cmd) {
    // First we need to send the 0xD4 command to the KBC
    uint8_t ack;
    int attempts = ATTEMPTS;

    do {
        if (write_kbc_cmd(KBC_IN_BUF, 0xD4)) return 1;
        if (write_kbc_cmd(OUT_BUF, cmd)) return 1;

        tickdelay(micros_to_ticks(DELAY_US));

        if (util_sys_inb(OUT_BUF, &ack)) return 1;
        if (ack == ACK) return 0;

        attempts--;
    } while ((ack != ACK) && attempts);

    return 1;
    
}

