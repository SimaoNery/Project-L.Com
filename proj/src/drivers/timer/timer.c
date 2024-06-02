#include <stdint.h>
#include <lcom/lcf.h>
#include <lcom/timer.h>

#include "i8254.h"

int counter = 0;
int timer_hook_id = 0;

/*!
 * @brief Sets the frequency of a specified timer.
 * 
 * @param timer The timer to configure (0, 1, or 2).
 * @param freq The desired frequency.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer > 2) return 1;
  if (freq < 19 || freq > TIMER_FREQ) return 1;

  uint8_t current_config;
  if (timer_get_conf(timer, &current_config) != 0) return 1;
  
  current_config = 0x0F & current_config;

  uint8_t mask = ((timer << 2) | 0x3) << 4;
 
  current_config = current_config | mask;

  if (sys_outb(TIMER_CTRL, current_config) != 0) return 1;

  uint32_t value = TIMER_FREQ / freq;

  uint8_t freq_lsb;
  uint8_t freq_msb;

  if (util_get_LSB(value, &freq_lsb) != 0) return 1;
  if (util_get_MSB(value, &freq_msb) != 0) return 1;
  
  if (sys_outb(TIMER_0 + timer, freq_lsb) != 0) return 1;
  if (sys_outb(TIMER_0 + timer, freq_msb) != 0) return 1;

  return 0;
}

/*!
 * @brief Subscribes to timer interrupts.
 * 
 * @param bit_no Pointer to a variable where the bit number will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (timer_subscribe_int)(uint8_t *bit_no) {

  if (bit_no == NULL) return 1;

  *bit_no = BIT(timer_hook_id);

  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);
}

/*!
 * @brief Unsubscribes from timer interrupts.
 * 
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&timer_hook_id);
}

/*!
 * @brief Timer interrupt handler.
 * 
 * Increments the global counter variable.
 */
void (timer_int_handler)() {
  counter++;
}

/*!
 * @brief Retrieves the configuration of a specified timer.
 * 
 * @param timer The timer to retrieve the configuration from (0, 1, or 2).
 * @param st Pointer to a variable where the configuration will be stored.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer > 2 || st == NULL) return 1;

  uint8_t readBackCmd;
  readBackCmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | BIT(timer + 1);

  int send = sys_outb(TIMER_CTRL, readBackCmd);
  if (send) return 1;

  return util_sys_inb(TIMER_0 + timer, st);
}

/*!
 * @brief Displays the configuration of a specified timer.
 * 
 * @param timer The timer to display the configuration for (0, 1, or 2).
 * @param st The status byte of the timer.
 * @param field The field of the status byte to display.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  if (timer > 2) return 1;

  union timer_status_field_val val;
  uint8_t bits5_4;
  uint8_t bits1_2_3;

  switch (field)
  {
  case tsf_all:
    val.byte = st;
    break;  

  case tsf_initial:
    bits5_4 = (st >> 4) & 0x03;

    if (bits5_4 == 1) {
      val.in_mode = LSB_only;
    }
    else if (bits5_4 == 2) {
      val.in_mode = MSB_only;
    } 
    else if (bits5_4 == 3) {
      val.in_mode = MSB_after_LSB;
    }
    else {
      val.in_mode = INVAL_val;
    }

    break;

  case tsf_mode:
    bits1_2_3 = (st >> 1) & 0x07;
    val.count_mode = (bits1_2_3 > 5) ? (bits1_2_3 % 2 == 0 ? 2 : 3) : bits1_2_3;
    break;

  case tsf_base:
    val.bcd = TIMER_BCD & st;
    break;

  default:
    return 1;
  }

  return timer_print_config(timer, field, val);
}

