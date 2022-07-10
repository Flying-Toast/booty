#ifndef __HAVE_VGA_H
#define __HAVE_VGA_H

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_MAGENTA,
	VGA_COLOR_BROWN,
	VGA_COLOR_LIGHT_GRAY,
	VGA_COLOR_DARK_GRAY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_MAGENTA,
	VGA_COLOR_YELLOW,
	VGA_COLOR_WHITE
};

void vga_clear_screen(enum vga_color clear_color);
void vga_putc(char c);
void vga_set_fg(enum vga_color color);
void vga_set_bg(enum vga_color color);
void vga_print(char *s);
void vga_println(char *s);

#endif
