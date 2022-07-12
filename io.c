#include "io.h"

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile (
		"inb %1, %0\n"
		:"=a"(ret)
		:"d"(port)
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
