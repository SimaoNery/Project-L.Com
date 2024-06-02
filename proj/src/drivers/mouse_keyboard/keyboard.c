#include "keyboard.h"


int keyboard_hook_id = 1;
uint8_t out_buf;

/*!
 * @brief Subscribes to keyboard interrupts.
 * 
 * @param bit_no Pointer to a variable where the bit number will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (kbc_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == NULL) return 1;
  *bit_no = BIT(keyboard_hook_id);
  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}
/*!
 * @brief Unsubscribes from keyboard interrupts.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (kbc_unsubscribe_int)() {
  return sys_irqrmpolicy(&keyboard_hook_id);
}

/*!
 * @brief Keyboard interrupt handler.
 * 
 * Reads the status and output buffer from the Keyboard Controller (KBC).
 */
void (kbc_int_handler)() {
   uint8_t status;
   if (get_kbc_status(&status)) return;
   if ((status & 0xE1) != 0x01) return;
   read_kbc_output(OUT_BUF, &out_buf, false);
}

/*!
 * @brief Restores the keyboard controller to its default state.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (kbc_restore)() {
  uint8_t cmd;
  if (write_kbc_cmd(KBC_IN_BUF, READ_CMD_BYTE)) return 1;
  if (read_kbc_output(OUT_BUF, &cmd, false)) return 1;
  cmd |= ENABLE_KBD_INT;
  if (write_kbc_cmd(KBC_IN_BUF, WRT_CMD_BYTE)) return 1;
  if (write_kbc_cmd(0x60, cmd)) return 1;
  return 0;
}



