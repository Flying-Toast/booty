#ifndef __HAVE_VGA_H
#define __HAVE_VGA_H

#include <stdint.h>

#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (200)

void vga_clear_screen(uint8_t color);
void vga_set_draw_color(uint8_t color);
void vga_fill_rect(unsigned x, unsigned y, unsigned width, unsigned height);

#endif
