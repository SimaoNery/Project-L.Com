#ifndef __SPRITE_H
#define __SPRITE_H

#include <lcom/lcf.h>

#include "../drivers/video/graphics.h"
#include "xpm_files/TitleText.xpm"

typedef struct {
    int x, y; //current position
    int width, height; //dimensions
    uint32_t *map; //the pixmap
} Sprite;

//Sprites we will use
//Sprite *normalCursor;
//Sprite *clickCursor;
Sprite *titleText;
//Sprite *controlShellText;
//Sprite *housePlantText;
//Sprite *securityCameraText;
//Sprite *displayMessageText;
//Sprite *helpText;

//Creates a new sprite drom XPM "pic" in the specified position
Sprite* (create_sprite)(xpm_map_t pic, int x, int y);

//Destroys a sprite
int (destroy_sprite)(Sprite *sp);

//Destroys all sprites used
int (destroy_all_sprites)();

//Draws a specific sprite
int (draw_sprite)(Sprite *sp);

//Loads the sprites
int (load_sprites)();

//Will animate the button when hover
int (animate_sprite)(Sprite *sp);


#endif
