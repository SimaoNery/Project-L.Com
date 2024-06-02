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
#include "xpm_files/RES_800_600/house_plant_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/adjust_fan_power_button_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/cam_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/fan_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/horn_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/humidity_and_temperature_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/light_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/light_vertical_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/read_humidity_button_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/read_sound_intensity_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/read_temperature_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/sound_intensity_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/degrees_celsius_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/percentage_800_600.xpm"
#include "xpm_files/RES_800_600/house_plant-buttons/db_800_600.xpm"
#include "xpm_files/RES_800_600/time/colon_800_600.xpm"
#include "xpm_files/RES_800_600/time/slash_800_600.xpm"
#include "xpm_files/RES_800_600/time/zero_800_600.xpm"
#include "xpm_files/RES_800_600/time/one_800_600.xpm"
#include "xpm_files/RES_800_600/time/two_800_600.xpm"
#include "xpm_files/RES_800_600/time/three_800_600.xpm"
#include "xpm_files/RES_800_600/time/four_800_600.xpm"
#include "xpm_files/RES_800_600/time/five_800_600.xpm"
#include "xpm_files/RES_800_600/time/six_800_600.xpm"
#include "xpm_files/RES_800_600/time/seven_800_600.xpm"
#include "xpm_files/RES_800_600/time/eight_800_600.xpm"
#include "xpm_files/RES_800_600/time/nine_800_600.xpm"


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
#include "xpm_files/RES_1152_864/time/colon_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/slash_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/zero_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/one_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/two_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/three_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/four_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/five_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/six_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/seven_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/eight_1152_864.xpm"
#include "xpm_files/RES_1152_864/time/nine_1152_864.xpm"


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
Sprite *exitButton;
Sprite *helpButton;
Sprite *resolutionButton;
Sprite *smallResolutionButton;
Sprite *bigResolutionButton;
Sprite *backArrow;

//HousePlant Buttons
Sprite *adjustFanPower;
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
Sprite *sound_int;


//time
Sprite *colon;
Sprite *slash;
Sprite *zero;
Sprite *one;
Sprite *two;
Sprite *three;
Sprite *four;
Sprite *five;
Sprite *six;
Sprite *seven;
Sprite *eight;
Sprite *nine;




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
