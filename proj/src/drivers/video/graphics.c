#include "graphics.h"


uint8_t *video_mem;

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
  unsigned int vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel + 7) / 8);

  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) {
    panic("sys_privctl (ADD_MEM) failed\n");
    return 1;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == NULL) {
    panic("couldn't map video memory");
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

  if (memcpy(&video_mem[idx], &color, bytes) == NULL){
    vg_exit();
    return 1;
  }
  

  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int col = 0; col < len; col++) {
    if (vg_draw_pixel(x + col, y, color))
      return 1;
  }

  return 0;
}

int(vg_draw_vline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int row = 0; row < len; row++) {
    if (vg_draw_pixel(x, y + row, color))
      return 1;
  }

  return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (int row = 0; row < height; row++) {
    if (vg_draw_hline(x, y + row, width, color)) {
      vg_exit();
      return 1;
    }
  }

  return 0;
}

int(mapped_draw_vline)(uint16_t x, uint16_t y, uint32_t len, uint32_t color) {

  if (vmi_p.MemoryModel == DIRECT_COLOR) {

    uint32_t red = (color >> vmi_p.RedFieldPosition) & (BIT(vmi_p.RedMaskSize) - 1);
    uint32_t green = (color >> vmi_p.GreenFieldPosition) & (BIT(vmi_p.GreenMaskSize) - 1);
    uint32_t blue = (color >> vmi_p.BlueFieldPosition) & (BIT(vmi_p.BlueMaskSize) - 1);

    color = 0;
    color = color | (red << vmi_p.RedFieldPosition) | (green << vmi_p.GreenFieldPosition) | (blue << vmi_p.BlueFieldPosition);
  }
  else {
    color &= 0xFF;
  }

  return vg_draw_vline(x, y, len, color);
}

int(vg_draw_no_rectangles)(uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint16_t h_res = vmi_p.XResolution;
  uint16_t v_res = vmi_p.YResolution;

  uint16_t rec_width = h_res / no_rectangles;
  uint16_t rec_height = v_res / no_rectangles;

  uint16_t width_left = h_res - (rec_width * no_rectangles);
  uint16_t height_left = v_res - (rec_height * no_rectangles);
  uint32_t color = 0;

  uint32_t new_color;

  if (normalize_color(first, &new_color))
    return 1;

  uint8_t red, green, blue, r, g, b;

  if (vmi_p.MemoryModel == DIRECT_COLOR) {
    red = (new_color >> vmi_p.RedFieldPosition) & (BIT(vmi_p.RedMaskSize) - 1);
    green = (new_color >> vmi_p.GreenFieldPosition) & (BIT(vmi_p.GreenMaskSize) - 1);
    blue = (new_color >> vmi_p.BlueFieldPosition) & (BIT(vmi_p.BlueMaskSize) - 1);
  }

  for (int row = 0; row < no_rectangles; row++) {
    for (int col = 0; col < no_rectangles; col++) {

      if (vmi_p.MemoryModel == DIRECT_COLOR) {
        r = (red + col * step) % (1 << vmi_p.RedMaskSize);
        g = (green + row * step) % (1 << vmi_p.GreenMaskSize);
        b = (blue + (col + row) * step) % (1 << vmi_p.BlueMaskSize);
        color = (r << vmi_p.RedFieldPosition) | (g << vmi_p.GreenFieldPosition) | (b << vmi_p.BlueFieldPosition);
      }
      else {
        color = (new_color + (row * no_rectangles + col) * step) % (1 << vmi_p.BitsPerPixel);
      }

      if (vg_draw_rectangle(col * rec_width, row * rec_height, rec_width, rec_height, color)) {
        return 1;
      }

      if (col == no_rectangles - 1) {
        if (vg_draw_rectangle((col * rec_width) + rec_width, row * rec_height, width_left, rec_height, 0xFFFFFFFF)) {
          return 1;
        }
      }
    }
  }

  if (height_left > 0) {
    if (vg_draw_rectangle(0, v_res - height_left, h_res, height_left, 0xFFFFFFFF)) {
      return 1;
    }
  }

  return 0;
}

int(print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  xpm_image_t xpm_image;
  uint8_t *xpm_loaded = xpm_load(xpm, XPM_INDEXED, &xpm_image);

  for (int row = 0; row < xpm_image.height; row++) {
    for (int col = 0; col < xpm_image.width; col++) {
      if (vg_draw_pixel(x + col, y + row, *xpm_loaded)) {
        return 1;
      }
      xpm_loaded++;
    }
  }

  return 0;
}

