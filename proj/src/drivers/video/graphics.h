#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "VBE.h"
#include "project.h"

vbe_mode_info_t vmi_p;

int(vg_set_graphics_mode)(uint16_t mode);
int(map_frame_buffer_page_flipping)(uint16_t mode);
int(map_frame_buffer_triple_buffering)(uint16_t mode);
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int(clear_back_buffer)();
int(set_display_start_page_flipping)();
int(set_display_start_triple_buffering)();
int(swap_buffers)();
int(change_resolution)(int res);
int(unmap_frame_buffer)();
int(triple_copy)();
int(map_frame_buffer)(int res);
int(buffering_method)();
int(wait_display_start_change)();

#endif
