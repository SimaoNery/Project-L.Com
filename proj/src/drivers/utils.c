#include <lcom/lcf.h>
#include <stdint.h>

/*!
 * @brief Retrieves the least significant byte (LSB) of a 16-bit value.
 * 
 * @param val The 16-bit value from which to extract the LSB.
 * @param lsb Pointer to a variable where the LSB will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  if (lsb != NULL) {
    uint8_t mask = 0xFF;
    *lsb = val & mask;
    return 0;
  }

  return 1;
}

/*!
 * @brief Retrieves the most significant byte (MSB) of a 16-bit value.
 * 
 * @param val The 16-bit value from which to extract the MSB.
 * @param msb Pointer to a variable where the MSB will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  if (msb != NULL) {
    uint16_t mask = 0xFF00;
    *msb = (val & mask) >> 8;
    return 0;
  }

  return 1;
}

/*!
 * @brief Reads a byte from the specified port and store it in uint8_t variable.
 * 
 * @param port The port from which to read the byte.
 * @param value Pointer to a variable where the read byte will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (util_sys_inb)(int port, uint8_t *value) {

  if (value != NULL) {
    uint32_t temp;
    int res = sys_inb(port, &temp);

    if (res == 0) {
      *value = 0xFF & temp;
      return 0;
    }
  }

  return 1;
}
