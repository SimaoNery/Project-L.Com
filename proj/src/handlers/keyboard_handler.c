#include "keyboard_handler.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern uint8_t out_buf;
extern bool running;
extern uint8_t page_state;

/**
 * @brief Handles keyboard input for the main menu.
 * 
 * Calls the keyboard controller interrupt handler and checks if the escape key (0x81) is pressed to stop the running flag.
 */
void keyboard_main_menu_handler () {
  kbc_int_handler();
  if (out_buf == 0x81)
    running = false;
}

/**
 * @brief Handles keyboard input for the control shell.
 * 
 * Calls the keyboard controller interrupt handler and processes the input to the command line.
 */
void keyboard_control_shell_handler () {
  kbc_int_handler();
  input_to_command_line(out_buf);
}

/**
 * @brief Handles keyboard input for the house plant section.
 * 
 * Currently, this function does not perform any actions.
 */
void keyboard_house_plant_handler() {}

/**
 * @brief Handles keyboard input for the settings menu.
 * 
 * Calls the keyboard controller interrupt handler and checks if the escape key (0x81) is pressed to stop the running flag.
 */
void keyboard_settings_handler () {
  kbc_int_handler();
  if (out_buf == 0x81)
    running = false;
}

/**
 * @brief Handles keyboard input for the help section.
 * 
 * Calls the keyboard controller interrupt handler, checks if the escape key (0x81) is pressed to return to the main menu, and redraws the page.
 */
void keyboard_help_handler() {
  kbc_int_handler();
  if (out_buf == 0x81) {
    page_state = MAIN_MENU;
  }
  draw_page();
}

