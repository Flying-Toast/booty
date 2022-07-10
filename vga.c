#include <stdint.h>
#include "kstd.h"
#include "vga.h"

#define VGABUF ((volatile uint16_t *) 0xB8000)
#define WIDTH (80)
#define HEIGHT (25)

void vga_clear_screen(enum vga_color clear_color)
{
	memset((void *)VGABUF, clear_color | clear_color << 4, sizeof(*VGABUF) * WIDTH * HEIGHT);
}
