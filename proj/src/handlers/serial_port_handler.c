#include "serial_port_handler.h"

extern bool asking_for_humidity_and_temp;
extern bool asking_for_sound;

int humidity_temp[4] = {0};
int sound_intensity[2] = {0};
int counter_serial_port = 0;

extern bool lock;

<<<<<<< HEAD
void serial_port_main_menu_handler() {}

void serial_port_control_shell_handler() {
  serial_port_int_handler();
  if (asking_for_humidity_and_temp) {
    pop(get_queue(), &humidity_temp[counter_serial_port++]);
    if (counter_serial_port == 4) {
      counter_serial_port = 0;
      asking_for_humidity_and_temp = false;
      printf("Humidity: %d,%d%%\n", humidity_temp[0], humidity_temp[1]);
      printf("Temperature: %d,%dC", humidity_temp[2], humidity_temp[3]);
    }
    serial_port_clear_int();
  }
=======
void serial_port_settings_handler () {}
>>>>>>> refs/remotes/origin/Project

  if (asking_for_sound) {
    pop(get_queue(), &sound_intensity[counter_serial_port++]);
    if (counter_serial_port == 2) {
      counter_serial_port = 0;
      asking_for_sound = false;
      printf("Sound intensity: %d,%ddB\n", sound_intensity[0],
             sound_intensity[1]);
    }
    serial_port_clear_int();
  }
}

void serial_port_house_plant_handler() {}

void serial_port_security_camera_handler() {}

void serial_port_settings_handler() {}

void serial_port_help_handler() {}