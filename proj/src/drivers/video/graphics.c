#include "graphics.h"


uint8_t *video_mem;
uint8_t *front_buffer;
uint8_t *back_buffer;

unsigned int vram_size;

bool buffer = false;

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

int(map_frame_buffer)(uint16_t mode) {

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

int (set_display_start)() {
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

  buffer = !buffer;

  return 0;
}

int (swap_buffers)() {
  if(set_display_start() != 0) {
    printf("Error: Problems occured while trying to set display start! \n");
    return 1;
  } 

  uint8_t *temp = front_buffer;
  front_buffer = back_buffer;
  back_buffer = temp;

  if(clear_back_buffer() != 0) {
    printf("Error: Problems occured whilr trying to clean back buffer! \n");
    return 1;
  }

  return 0;
}
