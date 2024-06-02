#include "keyboard_handler.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern uint8_t out_buf;
extern bool running;
extern uint8_t page_state;

void keyboard_main_menu_handler() {
  kbc_int_handler();
  if (out_buf == 0x81)
    running = false;
}

void keyboard_control_shell_handler() {
  kbc_int_handler();
  input_to_command_line(out_buf);
}

void keyboard_house_plant_handler() {}

<<<<<<< HEAD
void keyboard_security_camera_handler() {}

void keyboard_settings_handler() {
=======
void keyboard_settings_handler () {
>>>>>>> refs/remotes/origin/Project
  kbc_int_handler();
  if (out_buf == 0x81)
    running = false;
}

void keyboard_help_handler() {
  kbc_int_handler();
  if (out_buf == 0x81) {
    page_state = MAIN_MENU;
  }
  draw_page();
}