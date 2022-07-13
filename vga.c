#include <stddef.h>
#include "vga.h"

#define VGABUF ((volatile uint8_t *) 0xA0000)

void vga_clear_screen(uint8_t color)
{
	const uint32_t colorword = color | color<<8 | color<<16 | color<<24;
	for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(*VGABUF)/sizeof(colorword); ++i)
		((volatile uint32_t *)VGABUF)[i] = colorword;
}
