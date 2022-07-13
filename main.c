#include "interrupts.h"
#include "vga.h"
#include "keyboard.h"

void cmain(void)
{
	setup_interrupts();
	setup_keyboard();

	enable_interrupts();

	vga_clear_screen(123);
	vga_set_fill_color(3);
	panic();
	vga_fill_rect(10, 10, 30, 50);
}
