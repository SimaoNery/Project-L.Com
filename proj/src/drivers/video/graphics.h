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
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int(vg_draw_vline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int(mapped_draw_vline)(uint16_t x, uint16_t y, uint32_t len, uint32_t color);
int(vg_draw_no_rectangles)(uint8_t no_rectangles, uint32_t first, uint8_t step);
int(print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif
