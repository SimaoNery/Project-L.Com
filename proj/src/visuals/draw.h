#ifndef __DRAW_H
#define __DRAW_H

#include <lcom/lcf.h>

#include "sprite.h"

Sprite *mainMenu;
Sprite *controlShellButton;
Sprite *housePlantButton;
Sprite *securityCameraButton;
Sprite *displayMessageButton;
Sprite *helpButton;
Sprite *settingsButton;

int draw_main_menu();

int draw_control_shell();

int draw_display_message();

int draw_security_camera();

int draw_settings();

int draw_house_plant();

int draw_help();

int draw_main_buttons();



#endif
