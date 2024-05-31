#ifndef _KEYBOARD_HANDLER_H_
#define _KEYBOARD_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "project.h"

void keyboard_main_menu_handler ();
void keyboard_control_shell_handler ();
void keyboard_house_plant_handler ();
void keyboard_security_camera_handler ();
void keyboard_display_message_handler ();
void keyboard_settings_handler ();
void keyboard_help_handler ();
void translate_scancode(uint8_t scancode);
void handle_command(char* line_buffer);

#endif /*_KEYBOARD_HANDLER_H_*/


