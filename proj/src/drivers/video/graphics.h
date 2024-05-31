#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "VBE.h"

vbe_mode_info_t vmi_p;

int(vg_set_graphics_mode)(uint16_t mode);
int(map_frame_buffer)(uint16_t mode);
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int(clear_back_buffer)();
int(set_display_start)();
int(swap_buffers)();

#endif
