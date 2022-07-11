#include "interrupts.h"
#include "vga.h"

void cmain(void)
{
	setup_interrupts();
	enable_interrupts();
	vga_clear_screen(VGA_COLOR_LIGHT_MAGENTA);
	vga_set_fg(VGA_COLOR_RED);
	vga_set_bg(VGA_COLOR_WHITE);
	vga_putc('A');
	vga_set_fg(VGA_COLOR_BLUE);
	vga_set_bg(VGA_COLOR_YELLOW);
	vga_putc('b');
	vga_println("helloOOO");
	vga_print("YO");
}
