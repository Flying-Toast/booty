#include <stdint.h>
#include <stddef.h>
#include "interrupts.h"

struct __attribute__((__packed__)) descriptor {
	uint16_t offset_low;
	uint16_t segment_selector;
	uint8_t reserved;
	uint8_t flags;
	uint16_t offset_high;
};

struct __attribute__((__packed__)) idt_ptr {
	uint16_t size;
	uint32_t offset;
};

static struct descriptor idt[256];
// not actually a char, we just need to put an arbitrary type so we can get the address of the extern
extern char default_isr;
static struct idt_ptr idt_ptr;

static void install_default_isrs(void)
{
	for (size_t i = 0; i < sizeof(idt) / sizeof(idt[0]); ++i) {
		idt[i].offset_low = ((uintptr_t) &default_isr) & 0xFFFF;
		idt[i].segment_selector = 0x08;
		idt[i].flags = 0x8E;
		idt[i].offset_high = ((uintptr_t) &default_isr) >> 16;
	}
}

void install_idt(void)
{
	install_default_isrs();
	idt_ptr.size = sizeof(idt) -1;
	idt_ptr.offset = (uintptr_t) &idt;
	asm volatile ("lidt (%0)" :: "m"(idt_ptr));
}

void enable_interrupts(void)
{
	asm volatile ("sti");
}

void disable_interrupts(void)
{
	asm volatile ("cli");
}
