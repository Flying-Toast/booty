#include "interrupts.h"
#include "vga.h"
#include "keyboard.h"

void vga_color_demo(void);

void cmain(void)
{
	setup_interrupts();
	setup_keyboard();

	enable_interrupts();
	vga_color_demo();
}
