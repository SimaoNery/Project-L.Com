#include <keyboard.h>

int hook_id = 1;
uint8_t out_buf;

int (kbc_subscribe_int)(uint8_t *bit_no) {

  if (bit_no == NULL) return 1;

  // irq_set to be used to identify the device 
  *bit_no = BIT(hook_id);

  // To avoid that the IH of the Minix takes the interrupt before us
  // Set IRQ_EXCLUSIVE which is a LCF flag, that will enable interrupts only for the most recent subscriber
  return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (kbc_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (kbc_int_handler)() {
    /* Before reading the KBC output buffer we must read the status of the kbc to check if bits 7 and 6 are active (invalid dada - ERROR)
    */

   uint8_t status;
   if (kbc_get_status(&status)) return;

   // Let´s check if bits 7 and 6 are active, bit 5 is 0 (keyboard) and that bit 0 is active - OUTPUT_BUF is full
   // To do that, we can do a bitwise AND with 1110 00001
   if ((status & 0xE1) != 0x01) return;

   // To be here, the status is ok, so we can read the OUT_BUF
   read_from_keyboard(OUT_BUF, &out_buf);
}


int (kbc_restore)() {
  // First we need to read the command byte to do that we must write on 0x64 the command 0x20
  uint8_t cmd;

  // Before sending the command we must tell KBC that we are going to write a cmd
  // To do that, we need to write the command 0x20 -> KBC_READ_CMD at port 0x64 -> Read Statu && Write Commands 
  if (write_in_keyboard(KBC_IN_BUF, READ_CMD_BYTE)) return 1;
  if (read_from_keyboard(OUT_BUF, &cmd)) return 1;

  // Now we need to activate the interrupt bit of the keyboard, which is bit 0
  cmd |= ENABLE_KBD_INT;

  // Now we need to warn KBC that we are going to write a command
  if (write_in_keyboard(KBC_IN_BUF, WRT_CMD_BYTE)) return 1;
  
  // Now we can perform the actual writting
  if (write_in_keyboard(0x60, cmd)) return 1;

  return 0;
}

