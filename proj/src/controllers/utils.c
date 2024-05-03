#include <lcom/lcf.h>
#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  if (lsb != NULL) {
    uint8_t mask = 0xFF;
    *lsb = val & mask;
    return 0;
  }

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  if (msb != NULL) {
    uint16_t mask = 0xFF00;
    *msb = (val & mask) >> 8;
    return 0;
  }

  return 1;
}

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
