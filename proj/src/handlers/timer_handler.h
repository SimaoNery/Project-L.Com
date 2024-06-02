#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "command_line/fan.h"
#include "command_line/horns.h"
#include "command_line/lights.h"
#include "project.h"

void timer_main_menu_handler ();
void timer_control_shell_handler ();
void timer_house_plant_handler ();
void timer_security_camera_handler ();
void timer_settings_handler ();
void timer_help_handler ();

#endif /*_TIMER_HANDLER_H_*/

