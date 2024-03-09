#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"
#include "kb_controller.c"

// This is the scancode readed from IH
extern uint8_t out_buf;
extern int counter;
int last_pressed = 0;

// Keep track of the number of sys_inb 
uint32_t cnt = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  //lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  /* Scan the scancode of a keyboard key both make and break code
  To do that, we first need to subscribe the interruptions in the IRQ1 */
  
  int kbc_status;
  message msg;
  uint8_t irq_set;
  int r;

  // Subscribe interrupt of kbc
  // irq_set is passed to kbc_subscribe_int
  if (kbc_subscribe_int(&irq_set) != 0) {
    return 1;
  }

  // It should fininsh as soon as the ESC key is released 
  while (out_buf != ESC_BRK)
  {
    if ((r = driver_receive(ANY, &msg, &kbc_status)) != 0)
    {
      printf("driver_receive failed with : %d", r);
      continue;
    }
    if (is_ipc_notify(kbc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_set)
        { /* subscribed interrupt */
          kbc_int_handler();

          // Print the make/break codes
          // It is a make code if the MSbit is 0 (and it is different from 0xE0)
          // It is a break code if the MSbit is 1 (and it is different from 0xE0)
          // It has 2 bytes if the first code is 0xE0
          bool make = ((out_buf & 0x80) == 0 && out_buf != 0xE0);
          if (kbd_print_scancode(make, (out_buf == 0xE0) ? 2 : 1, &out_buf)) return 1;
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      } 
    }
    else
    { /* received a standard message, not a notification*/
      /* no standard messages expected: do nothing */
    }
  }

  // Function provided to print the number of sys_inb calls
  if (kbd_print_no_sysinb(cnt)) return 1;

  return kbc_unsubscribe_int();
}

int(kbd_test_poll)() {
  
  while (out_buf != ESC_BRK) {
    if (read_from_keyboard(OUT_BUF, &out_buf) == 0) {
      bool make = ((out_buf & 0x80) == 0 && out_buf != 0xE0);
      kbd_print_scancode(make, (out_buf == 0xE0) ? 2 : 1, &out_buf);
    }
  }

  if (kbd_print_no_sysinb(cnt)) return 1;

  return kbc_restore();
}

int(kbd_test_timed_scan)(uint8_t n) {
  
  int kbc_status;
  message msg;
  uint8_t irq_set_timer;
  uint8_t irq_set_kbc;
  int r;

  // Subscribe interrupt of kbc
  // irq_set is passed to kbc_subscribe_int
  if (kbc_subscribe_int(&irq_set_kbc) != 0) {
    return 1;
  }

  if (timer_subscribe_int(&irq_set_timer)) return 1;

  // It should fininsh as soon as the ESC key is released or if the time since the last key pressed is higher then n
  while (out_buf != ESC_BRK && (counter - last_pressed) < n * 60)
  {
    if ((r = driver_receive(ANY, &msg, &kbc_status)) != 0)
    {
      printf("driver_receive failed with : %d", r);
      continue;
    }
    if (is_ipc_notify(kbc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_set_kbc)
        { /* subscribed interrupt */
          kbc_int_handler();

          // Print the make/break codes
          // It is a make code if the MSbit is 0 (and it is different from 0xE0)
          // It is a break code if the MSbit is 1 (and it is different from 0xE0)
          // It has 2 bytes if the first code is 0xE0
          bool make = ((out_buf & 0x80) == 0 && out_buf != 0xE0);
          if (kbd_print_scancode(make, (out_buf == 0xE0) ? 2 : 1, &out_buf)) return 1;
          last_pressed = counter;
        }
        if (msg.m_notify.interrupts & irq_set_timer) {
          timer_int_handler();
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      } 
    }
    else
    { /* received a standard message, not a notification*/
      /* no standard messages expected: do nothing */
    }
  }


  if (kbc_unsubscribe_int()) return 1;

  return timer_unsubscribe_int();
}

