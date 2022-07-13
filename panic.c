#include "vga.h"

void panic(void)
{
	vga_clear_screen(12);
	for (;;)
		;
}
