#include "serial.h"

int serial_port_hook_id = SERIAL_PORT_HOOK_ID;
static queue_t *queue;

int serial_initial_config() {
  if ((queue = new_queue()) == NULL) {
    printf("Failed to create queue\n");
    return 1;
  }

  uint8_t ier;
  if (util_sys_inb(COM1_BASE_REG + IER, &ier)) {
    printf("Failed sys_inb IER\n");
    return 1;
  }

  ier &= IER_LS4B_MASK;

  if (sys_outb(COM1_BASE_REG + IER, ier | BIT(0))) {
    printf("Failed sys_outb IER\n");
    return 1;
  }

  return 0;
}

int serial_port_subscribe_int(uint8_t *bit_no) {
  if (bit_no == NULL)
    return 1;

  *bit_no = BIT(serial_port_hook_id);

  if (sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &serial_port_hook_id)) {
    printf("Failed to subscribe Serial Port Interrupts\n");
    return 1;
  }

  return 0;
}

int serial_port_unsubscribe_int() {
  return sys_irqrmpolicy(&serial_port_hook_id);
}

int get_serial_port_status(uint8_t *st) {
  if (st == NULL)
    return 1;

  return util_sys_inb(COM1_BASE_REG + LSR, st);
}

int send_serial_port_msg(uint8_t msg) {
  uint8_t st;
  uint8_t att = ATTEMPTS;

  do {
    if (get_serial_port_status(&st)) {
      printf("Failed to get status of the serial port\n");
      return 1;
    }

    if (st & TRANSMITTER_EMPTY) {
      return sys_outb(COM1_BASE_REG + THR, msg);
    }

  } while (att-- > 0);

  return 1;
}

int read_serial_port_msg() {
  uint8_t st;
  uint8_t msg;

  if (get_serial_port_status(&st)) {
    printf("Failed to get status of the serial port\n");
    return 1;
  }

  if (st & RECEIVER_READY) {
    if (util_sys_inb(COM1_BASE_REG + RBR, &msg)) {
      printf("Failed sys_inb RBR\n");
      return 1;
    }

    if (st & SER_OVERRUN_ERR) {
      printf("Error reading serial port Overrun Error\n");
      return 1;
    }

    if (st & SER_PARITY_ERR) {
      printf("Error reading serial port Parity Error\n");
      return 1;
    }

    if (st & SER_FRAME_ERR) {
      printf("Error reading serial port Frame Error\n");
      return 1;
    }

    while (push(queue, msg))
      ;
    return 0;
  }

  return 1;
}

void serial_port_int_handler() {
  uint8_t interrupt_ident;
  if (util_sys_inb(COM1_BASE_REG + IIR, &interrupt_ident))
    return;
  if ((interrupt_ident & NO_INT_PENDING)) {
    printf("No interrupt pending\n");
    return;
  }
  if (interrupt_ident & INT_PENDING == CHAR_TIMEOUT_FIFO) {
    while (read_serial_port_msg())
      ;
  }
}

int serial_port_clear_int() {
  if (sys_outb(COM1_BASE_REG + FCR, FIFO_CLEAR)) {
    printf("Failed sys_out FCR\n");
    return 1;
  }

  clear_queue(queue);

  return 0;
}

void serial_port_clear_all() {
  delete_queue(queue);
}

queue_t *get_queue() {
  return queue;
}
