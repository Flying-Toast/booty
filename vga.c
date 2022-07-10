#include <stdint.h>
#include <stddef.h>
#include "kstd.h"
#include "vga.h"

#define VGABUF ((volatile uint16_t *) 0xB8000)
#define WIDTH (80)
#define HEIGHT (25)

static size_t cursorpos = 0;
static uint16_t upper_color_byte = (VGA_COLOR_BLACK << 4 | VGA_COLOR_WHITE) << 8;

void vga_clear_screen(enum vga_color clear_color)
{
	memset((void *)VGABUF, clear_color | clear_color << 4, sizeof(*VGABUF) * WIDTH * HEIGHT);
	cursorpos = 0;
}

void vga_putc(char c)
{
	if (c == '\n') {
		cursorpos += WIDTH;
		cursorpos -= cursorpos % WIDTH;
	} else {
		VGABUF[cursorpos++] = upper_color_byte | c;
	}
}

void vga_print(char *s)
{
	do {
		vga_putc(*s++);
	} while (*s);
}

void vga_println(char *s)
{
	vga_print(s);
	vga_putc('\n');
}

void vga_set_fg(enum vga_color color)
{
	uint8_t new_byte = upper_color_byte >> 8;
	new_byte &= 0xF0;
	new_byte |= color;
	upper_color_byte = new_byte << 8;
}

void vga_set_bg(enum vga_color color)
{
	uint8_t new_byte = upper_color_byte >> 8;
	new_byte &= 0x0F;
	new_byte |= color << 4;
	upper_color_byte = new_byte << 8;
}
