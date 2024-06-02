#include "keyboard_handler.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

extern uint8_t out_buf;
extern bool running;

/*!
 * @brief Handles keyboard input for the main menu.
 * 
 * Calls the keyboard controller interrupt handler and checks if the escape key (0x81) is pressed to stop the running flag.
 */
void keyboard_main_menu_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
}

/*!
 * @brief Handles keyboard input for the control shell.
 * 
 * Calls the keyboard controller interrupt handler, checks if the escape key (0x81) is pressed to stop the running flag, and processes the input to the command line.
 */
void keyboard_control_shell_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) {running = false;}
  input_to_command_line(out_buf);
}

void keyboard_house_plant_handler () {}

/*!
 * @brief Handles keyboard input for the settings menu.
 * 
 * Calls the keyboard controller interrupt handler and checks if the escape key (0x81) is pressed to stop the running flag.
 */
void keyboard_settings_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
}

void keyboard_help_handler () {}
