// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "KBC.h"
#include "mouse.h"

extern int packet_number;
extern struct packet packet;
extern int counter; 
int last_pressed = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  //lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    /* To be completed */
    uint8_t irq_set;
    message msg;
    int r;
    int kbc_status;

    if (mouse_subscribe_int(&irq_set)) return 1;

    if (write_mouse_cmd(ENABLE_DATA_REPORTING)) return 1;

    while (cnt) {
        if ((r = driver_receive(ANY, &msg, &kbc_status))) {
            printf("driver_receive failed with : %d", r);
            continue;
        }
        if (is_ipc_notify(kbc_status)) {
            switch (_ENDPOINT_P(msg.m_source))
            {
            case HARDWARE:
                {
                    if (msg.m_notify.interrupts & irq_set) {
                        mouse_ih();


                        if (packet_number == 3) {
                            packet_number = 0;
                        
                            parse_bytes_to_packet();
                            mouse_print_packet(&packet);
                            cnt--;
                        }
            
                    }
                }
                break;
            
            default:
                break;
            }
        }
    }

    if (write_mouse_cmd(DISABLE_DATA_REPORTING)) return 1;

    return mouse_unsubscribe_int();
}

int (mouse_test_async)(uint8_t idle_time) {
    uint8_t irq_mouse_set;
    uint8_t irq_timer_set;
    message msg;
    int r;
    int kbc_status;

    if (mouse_subscribe_int(&irq_mouse_set)) return 1;

    if (write_mouse_cmd(ENABLE_DATA_REPORTING)) return 1;

    if (timer_subscribe_int(&irq_timer_set)) return 1;

    while (counter - last_pressed < idle_time * 60) {
        if ((r = driver_receive(ANY, &msg, &kbc_status))) {
            printf("driver_receive failed with : %d", r);
            continue;
        }
        if (is_ipc_notify(kbc_status)) {
            switch (_ENDPOINT_P(msg.m_source))
            {
            case HARDWARE:
                {
                    if (msg.m_notify.interrupts & irq_timer_set) {
                        timer_int_handler();
                    }
                    if (msg.m_notify.interrupts & irq_mouse_set) {
                        mouse_ih();
                        

                        if (packet_number == 3) {
                            packet_number = 0;

                            parse_bytes_to_packet();
                            mouse_print_packet(&packet);
                            last_pressed = counter;
                        }
            
                    }
                }
                break;
            
            default:
                break;
            }
        }
    }

    if (write_mouse_cmd(DISABLE_DATA_REPORTING)) return 1;

    return timer_unsubscribe_int();

    return mouse_unsubscribe_int();
}


int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
