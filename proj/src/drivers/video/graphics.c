#include "graphics.h"

extern uint8_t page_state;
extern uint16_t resolution;

uint8_t *video_mem;
uint8_t *front_buffer;
uint8_t *back_buffer;
uint8_t *extra_buffer;

unsigned int vram_size;

int buffer = 0;

int(normalize_color)(uint32_t color, uint32_t *normalized_color) {
  if (normalized_color == NULL)
    return 1;

  *normalized_color = color & (BIT(vmi_p.BitsPerPixel) - 1);

  return 0;
}

int(vg_set_graphics_mode)(uint16_t mode) {

  reg86_t r;
  memset(&r, 0, sizeof(r));
  r.intno = BIOS_VIDEOCARD_SERV;
  r.ax = VBE_MODE_SET;

  r.bx = mode | LINEAR_FB;

  if (sys_int86(&r)) {
    printf("vg_set_graphics_mode: sys_int86() failed\n");
    return 1;
  }

  return 0;
}


int(vg_set_text_mode)(uint16_t mode) {

  reg86_t r;
  memset(&r, 0, sizeof(r));
  r.intno = BIOS_VIDEOCARD_SERV;
  r.ax = VBE_MODE_SET;

  r.bx = mode | LINEAR_FB;

  if (sys_int86(&r)) {
    printf("vg_set_graphics_mode: sys_int86() failed\n");
    return 1;
  }

  return 0;
}

int(map_frame_buffer_page_flipping)(uint16_t mode) {
  memset(&vmi_p, 0, sizeof(vmi_p));

  int attempts = 10;
  while (attempts > 0 && vbe_get_mode_info(mode, &vmi_p)) {
    attempts--;
  }

  if (attempts < 0)
    return 1;

  struct minix_mem_range mr;
  unsigned int vram_base = vmi_p.PhysBasePtr;
  vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel + 7) / 8);

  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size * 2;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) {
    panic("sys_privctl (ADD_MEM) failed\n");
    return 1;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size * 2); 
  if(video_mem == NULL) {
    panic("couldn't map video memory");
    return 1;
  }

  front_buffer = video_mem;
  back_buffer = video_mem + vram_size;

  return 0;
}

int (map_frame_buffer_triple_buffering)(uint16_t mode) {
  memset(&vmi_p, 0, sizeof(vmi_p));

  int attempts = 10;
  while (attempts > 0 && vbe_get_mode_info(mode, &vmi_p)) {
    attempts--;
  }

  if (attempts < 0)
    return 1;

  struct minix_mem_range mr;
  unsigned int vram_base = vmi_p.PhysBasePtr;
  vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel + 7) / 8);

  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size * 3;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) {
    panic("sys_privctl (ADD_MEM) failed\n");
    return 1;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size * 3); 
  if(video_mem == NULL) {
    panic("couldn't map video memory");
    return 1;
  }

  front_buffer = video_mem;
  back_buffer = video_mem + vram_size;
  extra_buffer = video_mem + 2 * vram_size; 

  return 0;
}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x > vmi_p.XResolution || y > vmi_p.YResolution) {
    return 0;
  }
  
  unsigned int bytes = ((vmi_p.BitsPerPixel + 7) / 8);
  unsigned int idx = (vmi_p.XResolution * y + x) * bytes;

  if (memcpy(&back_buffer[idx], &color, bytes) == NULL){
    vg_exit();
    return 1;
  }
  
  return 0;
}

int (clear_back_buffer)() {
  if(memset(back_buffer, 0, vram_size) == NULL) return 1;

  return 0;
}

int (set_display_start_page_flipping)() {
  reg86_t r;
  memset(&r, 0, sizeof(r));

  r.intno = BIOS_VIDEOCARD_SERV;


  r.ax = 0x4F07;

  r.bh = 0x00;
  r.bl = 0x80;

  r.cx = 0x00;
  r.dx = buffer ? 0x00: vmi_p.YResolution;


  if (sys_int86(&r)) {
    printf("vg_set_graphics_mode: sys_int86() failed\n");
    return 1;
  }

  buffer = (buffer == 0 ? 1 : 0);

  return 0;
}

int (set_display_start_triple_buffering)() {
  reg86_t r;
  memset(&r, 0, sizeof(r));

  r.intno = BIOS_VIDEOCARD_SERV;


  r.ax = 0x4F07;

  r.bh = 0x00;
  r.bl = 0x00;

  r.cx = 0x00;
  
  if(buffer == 0) {
    r.dx = vmi_p.YResolution;
  }
  else if(buffer == 1) {
    r.dx = vmi_p.YResolution * 2;
  }
  else {
    r.dx = 0x00;
  }


  if (sys_int86(&r)) {
    printf("vg_set_graphics_mode: sys_int86() failed\n");
    return 1;
  }

  buffer = (buffer + 1) % 3;

  return 0;
}


int (swap_buffers)() {
  if(set_display_start_page_flipping() != 0) {
    printf("Error: Problems occured while trying to set display start! \n");
    return 1;
  } 

  uint8_t *temp = front_buffer;
  front_buffer = back_buffer;
  back_buffer = temp;

  if(clear_back_buffer() != 0) {
    printf("Error: Problems occured while trying to clean back buffer! \n");
    return 1;
  }

  return 0;
}

int (change_resolution)(int res) {
  if(res != (uint16_t)resolution) {

    if(unmap_frame_buffer(resolution) != 0) {
      printf("Error: Problems occured while trying to clear all buffers! (switch1) \n");
    }

    if(destroy_all_sprites() != 0) {
        printf("Error: A problem occured while destroying all sprites! (switch2)\n");
        return 1;
    }

    if (vg_exit() != 0) {
      printf("Error: Problems occurred while trying to exit the current video mode (switch3)!\n");
      return 1;
    }

    resolution = res;

    if(map_frame_buffer(resolution) != 0) {
       printf("Error: Problems occured while trying to switch resolutions! (switch4)\n");
    }

    if(vg_set_graphics_mode(resolution) != 0) {
      printf("Error: Problems occured while trying to switch resolutions! (switch5)\n");
      return 1;
    }

    if(load_sprites(resolution) != 0) {
       printf("Error: Problems occured while trying to switch resolutions! (switch6)\n");
       return 1;
    }

    buffer = 0;
    page_state = MAIN_MENU;
  }

  return 0;
}

int unmap_frame_buffer() {
  if (video_mem != NULL) {
    int r;

    if (resolution == (uint16_t)RES_1152_864) {
      r = vm_unmap_phys(SELF, video_mem, vram_size * 3);
    } 
    else {
      r = vm_unmap_phys(SELF, video_mem, vram_size * 2);
    }

    if (r != OK) {
        printf("unmap_frame_buffer: vm_unmap_phys failed: %d\n", r);
        return 1;
    }

  }

  if(front_buffer != NULL) {
    front_buffer = NULL;
  }

  if(back_buffer != NULL) {
    back_buffer = NULL;
  }

  if(extra_buffer != NULL) {
    extra_buffer = NULL;
  }

  return 0;
}

int (triple_copy)() {
  if(set_display_start_triple_buffering() != 0) {
    printf("Error: Problems occured while trying to set display start! \n");
    return 1;
  }

  while(wait_display_start_change() != 0){}

  uint8_t *temp = front_buffer;
  front_buffer = back_buffer;
  back_buffer = extra_buffer;
  extra_buffer = temp;

  if(clear_back_buffer() != 0) {
    printf("Error: Problems occured while trying to clear the back buffer! \n");
    return 1;
  }

  return 0;
}

int (map_frame_buffer)(int res) {
  if(resolution == (uint16_t)RES_1152_864) {
    if(map_frame_buffer_triple_buffering(resolution) != 0) {
      printf("Error: A problem occured while trying to map video memory! (triple_buffering\n");
      return 1;
    }
  }
    
  else {
    if(map_frame_buffer_page_flipping(resolution) != 0) {
      printf("Error: A problem occured while trying to map video memory! (page_flipping)\n");
      return 1;
    }
  }

  return 0;
}

int (buffering_method)() {
  if(resolution == (uint16_t)RES_1152_864) {
    if(triple_copy() != 0) {
      printf("Error: Problems occured while trying to copy buffers! \n");
      return 1;
    }
  }

  else {
    if(swap_buffers() != 0) {
      printf("Error: Problems occured while trying to swap buffers! \n");
      return 1;
    }
  }

  return 0;  
}

int (wait_display_start_change)() {
  reg86_t r;
  memset(&r, 0, sizeof(r));

  r.intno = BIOS_VIDEOCARD_SERV;
  r.ax = 0x4F07;
  r.bx = 0x04;

  if (sys_int86(&r)) {
    printf("wait_for_display_start_change: sys_int86() failed\n");
    return 1;
  }

  return (r.ax & 0x01) ? 1 : 0;
}
