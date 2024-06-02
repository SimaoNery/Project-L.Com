#ifndef __DRAW_H
#define __DRAW_H

#include <lcom/lcf.h>

#include "sprite.h"
#include "../project.h"

int draw_page();

int draw_main_menu();

int draw_control_shell();

int draw_display_message();

int draw_resolution();

int draw_house_plant();

int draw_help();

int draw_main_buttons();

int draw_resolution_buttons();

int draw_housePlant_buttons();

int draw_sound_intensity();

int draw_temperature();

int draw_humidity();

int draw_date_time();

int draw_value_sprites(int val, int height, int width, int *x_counter);

#endif
