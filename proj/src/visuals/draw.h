#ifndef __DRAW_H
#define __DRAW_H

#include <lcom/lcf.h>

#include "sprite.h"

Sprite *MainMenu_1152x864;
Sprite *controlShellButton_1152x864;
Sprite *housePlantButton_1152x864;
Sprite *securityCameraButton_1152x864;
Sprite *displayMessageButton_1152x864;
Sprite *helpButton;

Sprite *MainMenu_800x600;
Sprite *controlShellButton_800x600;
Sprite *housePlantButton_800x600;
Sprite *securityCameraButton_800x600;
Sprite *displayMessageButton_800x600;
Sprite *helpButton_800x600;

int draw_mainMenu();

int draw_controlShell();

int draw_displayMessage();

int draw_securityCamera();

int draw_settings();

int draw_housePlant();

int draw_help();

int draw_buttons();



#endif
