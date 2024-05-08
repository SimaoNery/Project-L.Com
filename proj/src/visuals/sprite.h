#ifndef __SPRITE_H
#define __SPRITE_H

#include <lcom/lcf.h>

#include "../drivers/video/graphics.h"

#include "xpm_files/RES_800_600/main_menu_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/control_shell_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/display_message_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/help_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/house_plant_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/security_camera_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/settings_800_600.xpm"

#include "xpm_files/RES_1152_864/main_menu_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/control_shell_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/display_message_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/help_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/house_plant_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/security_camera_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/settings_1152_864.xpm"
#include "xpm_files/RES_1152_864/mouse/mouse_pointer_1152_864.xpm"

#define TRANSPARENT_COLOR 4


typedef struct {
    int x, y; //current position
    int width, height; //dimensions
    uint32_t *map; //the pixmap
    bool hover; //if mouse is hover  
} Sprite;

extern vbe_mode_info_t vmi_p;

//Sprites we will use
Sprite *normalCursor;
//Sprite *clickCursor;

Sprite *mainMenu;
Sprite *controlShellButton;
Sprite *housePlantButton;
Sprite *securityCameraButton;
Sprite *displayMessageButton;
Sprite *helpButton;
Sprite *settingsButton;

//Creates a new sprite drom XPM "pic" in the specified position
Sprite* (create_sprite)(xpm_map_t pic, int x, int y);

//Destroys a sprite
int (destroy_sprite)(Sprite *sp);

//Destroys all sprites used
int (destroy_all_sprites)();

//Draws a specific sprite
int (draw_sprite)(Sprite *sp);

//Loads the sprites
int (load_sprites_1152x864)();

int (load_sprites_800x600)();

//Will animate the button when hover
int (animate_sprite)(Sprite *sp);


#endif
