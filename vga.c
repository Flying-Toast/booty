#include <stdint.h>
#include "vga.h"

#define VGABUF ((volatile uint8_t *) 0xA0000)

void vga_color_demo(void)
{
	uint8_t a = 0;
	for (int i = 0; i < SCREEN_HEIGHT; ++i) {
		for (int j = 0; j < 256;j++){
			VGABUF[i*SCREEN_WIDTH + j] = a++;
		}
	}
}
