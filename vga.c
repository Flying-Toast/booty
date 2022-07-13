#include <stddef.h>
#include "vga.h"

#define VGABUF ((volatile uint8_t *) 0xA0000)

static uint8_t fillcolor = 0;

void vga_clear_screen(uint8_t color)
{
	const uint32_t colorword = color | color<<8 | color<<16 | color<<24;
	for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(*VGABUF)/sizeof(colorword); ++i)
		((volatile uint32_t *)VGABUF)[i] = colorword;
}

void vga_set_fill_color(uint8_t color)
{
	fillcolor = color;
}

// (x, y) of top left corner
void vga_fill_rect(unsigned x, unsigned y, unsigned width, unsigned height)
{
	// TODO: vaidate screen coords and don't overwrite video mem
	for (unsigned cy = y; cy < y + height; ++cy) {
		for (unsigned cx = x; cx < x + width; ++cx) {
			VGABUF[cy*SCREEN_WIDTH + cx] = fillcolor;
		}
	}
}
