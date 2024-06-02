#include "timer_handler.h"

extern uint8_t command;

extern uint32_t lights_counter[5];
extern bool count_time[5];
uint32_t counter_t[5];


extern uint32_t blink_counter[5];
extern bool blink_time[5];
uint32_t counter_b[5];

void timer_main_menu_handler () {}

void timer_control_shell_handler () {
  
  for (int i = 0; i < 5; i++) {
    
    if (count_time[i]) {
      counter_t[i]++;
      if (counter_t[i] / 60 == lights_counter[i]) {
        count_time[i] = false;
        blink_time[i] = false;
        counter_t[i] = 0;
        lights_counter[i] = 0;

        counter_b[i] = 0;
        blink_counter[i] = 0;

        command &= ~(BIT(i));
        send_serial_port_msg(command);
      }
    }
    if (blink_time[i]) {

      counter_b[i]++;
      if (counter_b[i] / 30 == blink_counter[i]) {

        counter_b[i] = 0;

        command ^= BIT(i);
        send_serial_port_msg(command);
      }

    }
  }


}

void timer_house_plant_handler () {}

void timer_security_camera_handler () {}

void timer_settings_handler () {}

void timer_help_handler () {}

