#include "interrupts.h"
#include "vga.h"
#include "keyboard.h"

void cmain(void)
{
	setup_interrupts();
	setup_keyboard();

	enable_interrupts();

	vga_clear_screen(VGA_COLOR_LIGHT_MAGENTA);
	vga_set_fg(VGA_COLOR_WHITE);
	vga_set_bg(VGA_COLOR_MAGENTA);

	for(;;) {
		if (keyboard_keystates[SCANCODE_Q]) {
			vga_println("Q key is down!");
		}
	}
}
