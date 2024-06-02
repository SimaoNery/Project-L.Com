#include "house_state.h"

bool asking_for_humidity_and_temp = false;
bool asking_for_sound = false;

void get_humidity_and_temperature() {
  asking_for_humidity_and_temp = true;
  send_serial_port_msg(HUMIDITY_AND_TEMPERATURE_ID);
}

void get_sound_intensity() {
  asking_for_sound = true;
  send_serial_port_msg(HUMIDITY_AND_TEMPERATURE_ID);
}