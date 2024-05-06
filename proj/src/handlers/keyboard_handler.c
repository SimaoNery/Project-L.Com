#include "keyboard_handler.h"

extern uint8_t out_buf;
extern bool running;

void keyboard_main_menu_handler (int irq_keyboard) {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
}

void keyboard_house_plant_handler (int irq_keyboard) {}

void keyboard_security_camera_handler (int irq_keyboard) {}

void keyboard_display_message_handler (int irq_keyboard) {}

void keyboard_settings_handler (int irq_keyboard) {}

void keyboard_help_handler (int irq_keyboard) {}

