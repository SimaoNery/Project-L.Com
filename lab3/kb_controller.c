#include "kb_controller.h"

int (kbc_get_status)(uint8_t *st) {
  // First check if st is not NULL
  if (st == NULL) return 1;

  return util_sys_inb(STATUS_REG, st);
}

int (kbc_get_out)(uint8_t *of) {
    if (of == NULL) return 1;

    return util_sys_inb(OUT_BUF, of);
}

int (kbc_write_cmd)(uint8_t port, uint8_t cmd) {
  // To write something, we must first read the status reg
  uint8_t status;
  if (kbc_get_status(&status)) return 1;

  // Before writting we need to check if buffer is full 
  // We can do that by checking that the bit(1) is 0
  if ((status & INB_FULL) == 0) {
    if (sys_outb(port, cmd)) return 1;

    return 0;
  }

  return 1;
}

/* WRITE in Keyboard
 * To write in keyboard, we need to check if the IBF is full or not
 */
int (write_in_keyboard)(uint8_t port, uint8_t cmd) {

  uint8_t status;
  int attempts = 0;

  while(attempts < ATTEMPTS) {
    if (kbc_get_status(&status)) return 1;

    // Check if BIT(1) is 0
    if ((status & BIT(1)) == 0) {
      return sys_outb(port, cmd);
    }
    
    tickdelay(micros_to_ticks(DELAY_US));
    attempts++;
  }

  return 1;
}

/* READ from Keyboard
 * To read from keyboard, we need to check if the parity and timout are 0 (bits 6 and 7)
 * We also need to check if the Output Buffeer is full and if the data comes from Mouse or from Keyboard (we can leave that for later)
 */
int (read_from_keyboard)(uint8_t port, uint8_t *of) {
  uint8_t status;
  int attemps = 0;

  // We need to verify that:
  // BIT(7) Parity is 0
  // BIT(6) Timeout is 0
  // BIT(5) AUX is 0 -> Keyboard
  // BIT(0) OBF is 1 -> Data is ready 
  // Mask = 1110 0001 Operation bitwise & if result is 0x01 it means that everything is ok to read
  while (attemps < ATTEMPTS) {
    if (kbc_get_status(&status)) return 1;

    if (status & BIT(0)) {
      if (status & BIT(7)) {
        printf("Parity bit is 1 -> ERROR\n");
        return 1;
      }
      if (status & BIT(6)) {
        printf("Timeout bit is 1 -> ERROR\n");
        return 1;
      }
      if (status & BIT(5)) {
        printf("Message to Mouse -> ERROR\n");
        return 1;
      }
      
      return util_sys_inb(port, of);
    }

    tickdelay(micros_to_ticks(DELAY_US));
    attemps++;
  }

  return 1;
}

