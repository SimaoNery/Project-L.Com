// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "KBC.h"
#include "mouse.h"

extern int packet_number;
extern struct packet packet;

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
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

