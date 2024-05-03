#ifndef __SPRITE_H
#define __SPRITE_H

#include <lcom/lcf.h>

#include "../drivers/video/graphics.h"

typedef struct {
    int x, y; //current position
    int width, height; //dimensions
    int xspeed, yspeed; //current speed
    char *map; // the pixmap
} Sprite;

//Creates a new sprite drom XPM "pic" in the specified position and with the specified speed
Sprite (*create_sprite)(const char *pic[], int x, int y, int xspeed, int yspeed);

//Loads the sprites
int (load_sprites)();

//Destroys a sprite
int (destroy_sprite)();

//Draws a specific sprite
int (draw_sprite)(Sprite *sp);

//Will animate the button when hover
int (animate_sprite)(Sprite *sp);

#endif
