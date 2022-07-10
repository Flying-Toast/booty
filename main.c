#include "interrupts.h"
#include "vga.h"

void cmain(void)
{
	install_idt();
	enable_interrupts();
	vga_clear_screen(VGA_COLOR_LIGHT_MAGENTA);
}
