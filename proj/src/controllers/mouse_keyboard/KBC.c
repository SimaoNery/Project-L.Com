#include "KBC.h"

int (get_kbc_status)(uint8_t *status) {
    if (status == NULL) return 1;

    return util_sys_inb(STATUS_REG, status);
}

int (write_kbc_cmd)(uint8_t port, uint8_t cmd) {

  uint8_t status;
  int attempts = 0;

  while(attempts < ATTEMPTS) {
    if (get_kbc_status(&status)) return 1;

    if ((status & BIT(1)) == 0) {
      return sys_outb(port, cmd);
    }
    
    tickdelay(micros_to_ticks(DELAY_US));
    attempts++;
  }

  return 1;
}

int (read_kbc_output)(uint8_t port, uint8_t *of, bool mouse) {
  uint8_t status;
  int attemps = 0;

  while (attemps < ATTEMPTS) {
    if (get_kbc_status(&status)) return 1;

    if (status & BIT(0)) {
      if (status & BIT(7)) {
        printf("Parity bit is 1 -> ERROR\n");
        return 1;
      }
      if (status & BIT(6)) {
        printf("Timeout bit is 1 -> ERROR\n");
        return 1;
      }
      if ((status & BIT(5)) && !mouse) {
        printf("Message to Mouse, wanted Keyboard -> ERROR\n");
        return 1;
      }
      if (!(status & BIT(5)) && mouse) {
       printf("Message to Keyboard, wanted Mouse -> ERROR\n");
       return 1;
      }

      return util_sys_inb(port, of);
    }

    tickdelay(micros_to_ticks(DELAY_US));
    attemps++;
  }

  return 1;
}


