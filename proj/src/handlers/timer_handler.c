#include "timer_handler.h"

extern uint8_t command;

extern uint32_t lights_counter[5];
extern bool count_time[5];
uint32_t counter_t[5] = {0};

extern uint32_t blink_counter[5];
extern bool blink_time[5];
uint32_t counter_b[5] = {0};

extern uint8_t command_fan;

extern uint32_t fan_counter;
extern bool fan_time;
uint32_t counter_fan = 0;

extern uint8_t command_horns;

extern uint32_t horns_counter[2];
extern bool count_time_horns[2];
uint32_t counter_horns_t[2] = {0};

extern uint32_t blink_counter_horns[2];
extern bool blink_time_horns[2];
uint32_t counter_horns_b[2] = {0};

void handle_alarm_int() {}

/*!
 * @brief Handles the update interrupt.
 * 
 * This function retrieves the current time from the RTC and updates the display.
 */
void handle_update_int() {
  rtc_get_time();
  draw_date_time();
}
void handle_periodic_int() {}

extern uint8_t config_RTC;
int count_rtc = 0;

/*!
 * @brief Handles timer interrupts for the main menu.
 * 
 * This function increments the RTC counter and updates the display every hour.
 */
void timer_main_menu_handler() {
  count_rtc++;
  if (count_rtc % 3600 == 0) {
    handle_update_int();
  }
}

/*!
 * @brief Handles timer interrupts for the control shell.
 * 
 * This function manages the countdown and blinking timers for lights, horns, and the fan.
 */
void timer_control_shell_handler() {

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
  for (int i = 0; i < 2; i++) {

    if (count_time_horns[i]) {
      counter_horns_t[i]++;
      if (counter_horns_t[i] / 60 == horns_counter[i]) {
        count_time_horns[i] = false;
        blink_time_horns[i] = false;
        counter_horns_t[i] = 0;
        horns_counter[i] = 0;

        counter_horns_b[i] = 0;
        blink_counter_horns[i] = 0;

        command_horns &= ~(BIT(i));
        send_serial_port_msg(command_horns);
      }
    }
    if (blink_time_horns[i]) {

      counter_horns_b[i]++;
      if (counter_horns_b[i] / 30 == blink_counter_horns[i]) {

        counter_horns_b[i] = 0;

        command_horns ^= BIT(i);
        send_serial_port_msg(command_horns);
      }
    }
  }

  if (fan_time) {
    counter_fan++;
    if (counter_fan / 60 == fan_counter) {

      fan_time = false;
      fan_counter = 0;
      counter_fan = 0;

      command_fan = FAN_ID;
      send_serial_port_msg(command_fan);
    }
  }
}

void timer_house_plant_handler() {}

void timer_security_camera_handler() {}

void timer_settings_handler () {}

void timer_help_handler () {}