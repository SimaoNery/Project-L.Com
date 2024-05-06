#ifndef _REAL_TIME_CLOCK_HANDLER_H_
#define _REAL_TIME_CLOCK_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

void real_time_clock_main_menu_handler (int irq_real_time_clock);
void real_time_clock_house_plant_handler (int irq_real_time_clock);
void real_time_clock_security_camera_handler (int irq_real_time_clock);
void real_time_clock_display_message_handler (int irq_real_time_clock);
void real_time_clock_settings_handler (int irq_real_time_clock);
void real_time_clock_help_handler (int irq_real_time_clock);

#endif /*_REAL_TIME_CLOCK_HANDLER_H_*/

