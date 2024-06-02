#ifndef __SPRITE_H
#define __SPRITE_H

#include <lcom/lcf.h>

#include "../drivers/video/graphics.h"

#include "xpm_files/RES_800_600/main_menu_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/control_shell_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/exit_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/help_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/house_plant_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/security_camera_button_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/resolution_button_800_600.xpm"
#include "xpm_files/RES_800_600/mouse/mouse_pointer_800_600.xpm"
#include "xpm_files/RES_800_600/resolution_page_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/big_resolution_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/small_resolution_800_600.xpm"
#include "xpm_files/RES_800_600/buttons/back_arrow_800_600.xpm"

#include "xpm_files/RES_1152_864/main_menu_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/control_shell_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/exit_button_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/help_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/house_plant_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/security_camera_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/resolution_button_1152_864.xpm" 
#include "xpm_files/RES_1152_864/mouse/mouse_pointer_1152_864.xpm"
#include "xpm_files/RES_1152_864/resolution_page_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/big_resolution_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/small_resolution_1152_864.xpm"
#include "xpm_files/RES_1152_864/buttons/back_arrow_1152_864xpm.xpm"
#include "xpm_files/RES_1152_864/house_plant_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/adjust_fan_power_button_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/cam_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/db_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/degrees_celsius_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/fan_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/horn_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/humidity_and_temperature_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/light_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/light_vertical_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/percentage_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/read_humidity_button_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/read_sound_intensity_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/read_temperature_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/sound_intensity_1152_864.xpm"
#include "xpm_files/RES_1152_864/house_plant_buttons/take_picture_1152_864.xpm"

#define TRANSPARENT_COLOR 4


typedef struct {
    int x, y; //current position
    int width, height; //dimensions
    uint32_t *map; //the pixmap
    bool hover; //if mouse is hover  
    int xspeed, yspeed;
} Sprite;

extern vbe_mode_info_t vmi_p;

//Sprites we will use
Sprite *normalCursor;
//Sprite *clickCursor;

//Pages
Sprite *mainMenu;
Sprite *resolutionPage;
Sprite *housePlant;


//Buttons
Sprite *controlShellButton;
Sprite *housePlantButton;
Sprite *securityCameraButton;
Sprite *exitButton;
Sprite *helpButton;
Sprite *resolutionButton;
Sprite *smallResolutionButton;
Sprite *bigResolutionButton;
Sprite *backArrow;

//HousePlant Buttons
Sprite *adjustFanPower;
Sprite *cam;
Sprite *db;
Sprite *degrees_celcius;
Sprite *fan;
Sprite *horn1;
Sprite *horn2;
Sprite *humidity_and_temperature;
Sprite *light_horizontal1;
Sprite *light_horizontal2;
Sprite *light_vertical1;
Sprite *light_vertical2;
Sprite *light_vertical3;
Sprite *percentage;
Sprite *read_humidity;
Sprite *read_sound_intensity;
Sprite *read_temperature;
Sprite *sound_intensity;
Sprite *take_picture;



//Creates a new sprite drom XPM "pic" in the specified position
Sprite* (create_sprite)(xpm_map_t pic, int x, int y);

//Destroys a sprite
int (destroy_sprite)(Sprite *sp);

//Destroys all sprites used
int (destroy_all_sprites)();

//Draws a specific sprite
int (draw_sprite)(Sprite *sp);

//Loads the sprites
int (load_sprites)(int res);

int (load_sprites_1152x864)();
int (load_sprites_800x600)();


#endif
