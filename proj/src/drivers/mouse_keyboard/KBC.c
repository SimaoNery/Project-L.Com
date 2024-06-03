#include "KBC.h"
/**
 * @defgroup KBC KBC
 * 
 */


/*!
 * @ingroup KBC KBC
 * @brief Retrieves the status from the Keyboard Controller (KBC).
 * 
 * @param status Pointer to a variable where the status will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (get_kbc_status)(uint8_t *status) {
    if (status == NULL) return 1;

    return util_sys_inb(STATUS_REG, status);
}

/*!
  * @ingroup KBC KBC
 * @brief Writes a command to the specified port of the Keyboard Controller (KBC).
 * 
 * @param port The port to which the command will be written.
 * @param cmd The command to be written.
 * @return int Returns 0 upon success and 1 upon failure.
 */
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

/*!
  * @ingroup KBC KBC
 * @brief Reads the output from the specified port of the Keyboard Controller (KBC).
 * 
 * @param port The port from which the output will be read.
 * @param of Pointer to a variable where the output will be stored.
 * @param mouse Boolean indicating whether the output is from the mouse (true) or keyboard (false).
 * @return int Returns 0 upon success and 1 upon failure.
 */
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


