#include <stddef.h>
#include "vga.h"
#include "panic.h"

#define VGABUF ((volatile uint8_t *) 0xA0000)
#define CHECK_X(x) \
	do { \
		if ((x) >= SCREEN_WIDTH) \
			panic(); \
	} while (0)
#define CHECK_Y(y) \
	do { \
		if ((y) >= SCREEN_HEIGHT) \
			panic(); \
	} while (0)

static uint8_t drawbuf[SCREEN_WIDTH * SCREEN_HEIGHT - 1];
static uint8_t drawcolor = 0;

void vga_clear_screen(uint8_t color)
{
	const uint32_t colorword = color | color<<8 | color<<16 | color<<24;
	for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(*drawbuf)/sizeof(colorword); ++i)
		((volatile uint32_t *)drawbuf)[i] = colorword;
}

void vga_set_draw_color(uint8_t color)
{
	drawcolor = color;
}

// (x, y) of top left corner
void vga_fill_rect(unsigned x, unsigned y, unsigned width, unsigned height)
{
	CHECK_X(x + width);
	CHECK_Y(y + height);

	for (unsigned cy = y; cy < y + height; ++cy) {
		for (unsigned cx = x; cx < x + width; ++cx) {
			drawbuf[cy*SCREEN_WIDTH + cx] = drawcolor;
		}
	}
}

void vga_present(void)
{
	for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(*drawbuf)/sizeof(uint32_t); ++i)
		((volatile uint32_t *)VGABUF)[i] = ((uint32_t *)drawbuf)[i];
}
