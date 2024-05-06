#ifndef _MOUSE_HANDLER_H_
#define _MOUSE_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

void mouse_main_menu_handler (int irq_mouse);
void mouse_house_plant_handler (int irq_mouse);
void mouse_security_camera_handler (int irq_mouse);
void mouse_display_message_handler (int irq_mouse);
void mouse_settings_handler (int irq_mouse);
void mouse_help_handler (int irq_mouse);

#endif /*_MOUSE_HANDLER_H_*/


