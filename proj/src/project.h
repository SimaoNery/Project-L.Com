#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "drivers/timer/timer.h"
#include "drivers/mouse_keyboard/KBC.h"
#include "drivers/mouse_keyboard/keyboard.h"
#include "drivers/mouse_keyboard/mouse.h"
#include "drivers/video/graphics.h"
#include "visuals/sprite.h"

typedef enum {
    MAIN_MENU,
    HOUSE_PLANT,
    SECURITY_CAMERA,
    DISPLAY_MESSAGE,
    HELP,
} project_state;

//Sprites we will use
//extern Sprite *normalCursor;
//extern Sprite *clickCursor;
/*extern Sprite *titleText;
extern Sprite *controlShellText;
extern Sprite *housePlantText;
extern Sprite *securityCameraText;
extern Sprite *displayMessageText;*/
//extern Sprite *helpText;
//extern Sprite *numberZero;
extern Sprite *MainMenu;

//Will load the xpm, subscribe drivers and changes video mode to graphics mode 
//return 0 if successfull and 1 otherwise
int (project_start)();


//Will control the execution of the project through interrupts and driver processing
//return 0 if successfull and 1 otherwise
int (project_loop)();


//Clean memory, unsubscribe drivers and changes video mode to text mode
//return 0 if successfull and 1 otherwise
int (project_stop)();


//Will control the drawing of the different pages
//return 0 if successfull and 1 otherwise
int(draw_manager)();


//Will draw in the screen all the elements of the main menu page
//return 0 if successfull and 1 otherwise
int (draw_main_menu)();


//Will draw in the screen the house plant page elements 
//return 0 if successfull and 1 otherwise
int(draw_house_plant)();


//Will draw in the screen the security camera page elements
//return 0 if successfull and 1 otherwise
int(draw_security_camera)();


//Will draw in the scrren the display message page elements
//return 0 if successfull and 1 otherwise
int(draw_display_message)();


//Will draw in the screen the help page elements
//return 0 if successfull and 1 otherwise
int(draw_help)();


#endif
