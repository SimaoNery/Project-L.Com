#include "graphics.h"


uint8_t *video_mem;
uint8_t *back_buffer;

unsigned int vram_size;

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
  mr.mr_limit = mr.mr_base + vram_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) {
    panic("sys_privctl (ADD_MEM) failed\n");
    return 1;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size); 

  if(video_mem == NULL) {
    panic("couldn't map video memory");
    return 1;
  }

  back_buffer = (uint8_t*)malloc(vram_size);
  
  if (back_buffer == NULL) {
    printf("Error: Problems occured while trying to allocate memory! \n");
    
    return 1;
  }

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

int(back_buffer_to_video_mem)() {
  if(memcpy(video_mem, back_buffer, vram_size) != 0) return 1;

  return 0;
}
