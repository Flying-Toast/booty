#ifndef __HAVE_VGA_H
#define __HAVE_VGA_H

#include <stdint.h>

#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (200)

void vga_clear_screen(uint8_t color);

#endif
