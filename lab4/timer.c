#include <stdint.h>
#include <lcom/lcf.h>
#include <lcom/timer.h>

#include "i8254.h"


int counter = 0;
int hook_id_timer = 0;


int (timer_subscribe_int)(uint8_t *bit_no) {

  if (bit_no == NULL) return 1;

  // irq_set to be used to identify the device 
  *bit_no = BIT(hook_id_timer);

  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id_timer);
}

void (timer_int_handler)() {
  counter++;
}
