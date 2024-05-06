#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

void timer_main_menu_handler (int irq_timer);
void timer_house_plant_handler (int irq_timer);
void timer_security_camera_handler (int irq_timer);
void timer_display_message_handler (int irq_timer);
void timer_settings_handler (int irq_timer);
void timer_help_handler (int irq_timer);

#endif /*_TIMER_HANDLER_H_*/

