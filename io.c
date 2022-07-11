#include "io.h"

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile (
		"inb %1, %%al\n"
		"mov %%al, %0\n"
		:"=g"(ret)
		:"r"(port)
		:"%al"
	);
	return ret;
}

void outb(uint16_t port, uint8_t value)
{
	asm volatile (
		"outb %1, %0\n"
		:
		:"d"(port), "a"(value)
	);
}
