#include <stdint.h>
#include <lcom/lcf.h>
#include <lcom/timer.h>

#include "i8254.h"

int counter = 0;
int hook_id = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer > 2 || timer < 0) return 1;

  // First, lets see what are the 4 LSB of the timer, making sure we dont change them
  uint8_t current_config;
  if (timer_get_conf(timer, &current_config) != 0) return 1;
  
  // We just want the 4 LSB
  current_config = 0x0F & current_config;

  // mask for the 4 MSB we need _ _ timer 00 01 10 
  // _ _ for LSB, MSB or LSB followed by MSB
  uint8_t mask = ((timer << 2) | 0x3) << 4;

  current_config = current_config | mask;

  // Tell controller which timer we want to configure
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

int (timer_subscribe_int)(uint8_t *bit_no) {

  if (bit_no == NULL) return 1;

  *bit_no = BIT(hook_id);

  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  // First check if the inputs are correct 3 timers and st not NULL
  if (timer > 2 || timer < 0 || st == NULL) return 1;

  // Build the Read-Back Command 1110___0 "_" to be filled with the respective timer 1 if it is the timer we want 0 otherwise
  uint8_t readBackCmd;
  readBackCmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | BIT(timer + 1);

  // Send command to control reg on port 0x43
  int send = sys_outb(TIMER_CTRL, readBackCmd);
  if (send) return 1;

  // Read from the timer port: 0x40 + timer
  int res = util_sys_inb(TIMER_0 + timer, st);
  return res;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  if (timer > 2 || timer < 0) return 1;

  union timer_status_field_val val;
  uint8_t bits5_4;
  uint8_t bits1_2_3;

  switch (field)
  {
  case tsf_all:
    val.byte = st;
    break;  

  case tsf_initial:
    // Just wants the initialization (bits 5 and 4) 01 - LSB / 10 - MSB / 11 - LSB followed by MSB
    // mask = 00000011 -> 0x03
    bits5_4 = (st >> 4) & 0x03;

    if (bits5_4 == 1) {
      // LSB
      val.in_mode = LSB_only;
    }
    else if (bits5_4 == 2) {
      // MSB
      val.in_mode = MSB_only;
    } 
    else if (bits5_4 == 3) {
      // LSB followed by MSB
      val.in_mode = MSB_after_LSB;
    }
    else {
      val.in_mode = INVAL_val;
    }

    break;

  case tsf_mode:
    // Just wants the mode of programming (bits 1,2,3) mask = 00000111 -> Ox07
    bits1_2_3 = (st >> 1) & 0x07;
    val.count_mode = (bits1_2_3 > 5) ? (bits1_2_3 % 2 == 0 ? 2 : 3) : bits1_2_3;
    break;

  case tsf_base:
    // Just want the BCD (bit 0) from status
    val.bcd = TIMER_BCD & st;
    break;

  default:
    return 1;
  }

  return timer_print_config(timer, field, val);
}
