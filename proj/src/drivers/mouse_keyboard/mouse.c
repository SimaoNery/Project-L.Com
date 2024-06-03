#include "mouse.h"

/**
 * @defgroup Mouse Mouse 
 * 
 */
int mouse_hook_id = 3;
uint8_t output_buffer;
uint8_t packet_bytes [3];
int packet_number = 0;
extern vbe_mode_info_t vmi_p;

/*!
 * @ingroup Mouse Mouse
 * @brief Subscribes to mouse interrupts.
 * 
 * @param bit_no Pointer to a variable where the bit will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (mouse_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;

    *bit_no = BIT(mouse_hook_id);

    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

/*!
 * @ingroup Mouse Mouse
 * @brief Unsubscribes from mouse interrupts.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

/*!
 * @ingroup Mouse Mouse
 * @brief Mouse interrupt handler.
 * 
 * Reads the output buffer from the kbc and processes the mouse packet bytes.
 */
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

/*!
 * @ingroup Mouse Mouse
 * @brief Parses the bytes read from the mouse into a mouse packet.
 * 
 * Updates the mouse packet structure with the button states and coordinates.
 */
void (parse_bytes_to_packet)() {
    mouse_packet.right_button = (packet_bytes[0] >> 1) & 0x01;
    mouse_packet.left_button = packet_bytes[0] & 0x01;

    if (packet_bytes[0] & BIT(6) || packet_bytes[0] & BIT(7)) return;
    int16_t x_coordinates = mouse_packet.x + ((packet_bytes[0] & BIT(4)) ? (0xFF00 | packet_bytes[1]) : packet_bytes[1]);
    int16_t y_coordinates = mouse_packet.y - ((packet_bytes[0] & BIT(5)) ? (0xFF00 | packet_bytes[2]) : packet_bytes[2]);
    
    if (x_coordinates < 0 || x_coordinates > vmi_p.XResolution || y_coordinates < 0 || y_coordinates > vmi_p.YResolution) return;

    mouse_packet.x = x_coordinates;
    mouse_packet.y = y_coordinates;
}

/*!
 * @ingroup Mouse Mouse
 * @brief Writes a command to the mouse.
 *
 * @param cmd The command to be written to the mouse.
 * @return int Returns 0 upon success and 1 upon failure.
 */
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
