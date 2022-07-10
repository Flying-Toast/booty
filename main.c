#include "interrupts.h"

void cmain(void)
{
	install_idt();
	enable_interrupts();
}
