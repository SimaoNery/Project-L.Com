#ifndef _KEYBOARD_HANDLER_H_
#define _KEYBOARD_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

void keyboard_main_menu_handler (int irq_keyboard);
void keyboard_house_plant_handler (int irq_keyboard);
void keyboard_security_camera_handler (int irq_keyboard);
void keyboard_display_message_handler (int irq_keyboard);
void keyboard_settings_handler (int irq_keyboard);
void keyboard_help_handler (int irq_keyboard);

#endif /*_KEYBOARD_HANDLER_H_*/


