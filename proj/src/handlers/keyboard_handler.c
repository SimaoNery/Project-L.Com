#include "keyboard_handler.h"

extern uint8_t out_buf;
extern bool running;




void keyboard_main_menu_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
}

void keyboard_control_shell_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
  //printf("%d", out_buf);
  //kbd_print_scancode(!(out_buf & BIT(7)), out_buf == 0xE0 ? 2 : 1, &out_buf);
}

void keyboard_house_plant_handler () {}

void keyboard_security_camera_handler () {}

void keyboard_display_message_handler () {}

void keyboard_settings_handler () {}

void keyboard_help_handler () {}

