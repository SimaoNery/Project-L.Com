#include "keyboard.h"


int keyboard_hook_id = 1;
uint8_t out_buf;

int (kbc_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == NULL) return 1;
  *bit_no = BIT(keyboard_hook_id);
  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

int (kbc_unsubscribe_int)() {
  return sys_irqrmpolicy(&keyboard_hook_id);
}

void (kbc_int_handler)() {
   uint8_t status;
   if (get_kbc_status(&status)) return;
   if ((status & 0xE1) != 0x01) return;
   read_kbc_output(OUT_BUF, &out_buf, false);
}


int (kbc_restore)() {
  uint8_t cmd;
  if (write_kbc_cmd(KBC_IN_BUF, READ_CMD_BYTE)) return 1;
  if (read_kbc_output(OUT_BUF, &cmd, false)) return 1;
  cmd |= ENABLE_KBD_INT;
  if (write_kbc_cmd(KBC_IN_BUF, WRT_CMD_BYTE)) return 1;
  if (write_kbc_cmd(0x60, cmd)) return 1;
  return 0;
}



