#include "interrupts.h"
#include "vga.h"
#include "keyboard.h"

void cmain(void)
{
	setup_interrupts();
	setup_keyboard();

	enable_interrupts();

	vga_clear_screen(123);
}
