#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "drivers/timer/timer.h"
#include "drivers/mouse_keyboard/KBC.h"
#include "drivers/mouse_keyboard/keyboard.h"
#include "drivers/mouse_keyboard/mouse.h"
#include "drivers/real_time_clock/real_time_clock.h"
#include "drivers/serial_port/serial.h"
#include "handlers/timer_handler.h"
#include "handlers/keyboard_handler.h"
#include "handlers/mouse_handler.h"
#include "handlers/real_time_clock_handler.h"
#include "handlers/serial_port_handler.h"
#include "visuals/sprite.h"
#include "visuals/draw.h"

#define MAIN_MENU 0
#define CONTROL_SHELL 1
#define HOUSE_PLANT 2
#define SECURITY_CAMERA 3
#define DISPLAY_MESSAGE 4
#define SETTINGS 5
#define HELP 6

struct handler;
typedef struct handler handler_t;

int (project_start)();
int (project_loop)();
int (project_stop)();

#endif /*_PROJECT_H_*/
