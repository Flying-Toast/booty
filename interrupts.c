#include <stdint.h>
#include <stddef.h>
#include "interrupts.h"
#include "io.h"

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
static struct idt_ptr idt_ptr;
// not actually chars, we just need to put an arbitrary type so we can get the address of the externs
extern char default_isr;
extern char asm_int21_wrapper;

static void install_isrs(void)
{
	for (size_t i = 0; i < sizeof(idt) / sizeof(idt[0]); ++i) {
		idt[i].offset_low = ((uintptr_t) &default_isr) & 0xFFFF;
		idt[i].segment_selector = 0x08;
		idt[i].flags = 0x8E;
		idt[i].offset_high = ((uintptr_t) &default_isr) >> 16;
	}

	idt[0x21].offset_low = ((uintptr_t) &asm_int21_wrapper) & 0xFFFF;
	idt[0x21].offset_high = ((uintptr_t) &asm_int21_wrapper) >> 16;
}

static void install_idt(void)
{
	install_isrs();
	idt_ptr.size = sizeof(idt) -1;
	idt_ptr.offset = (uintptr_t) &idt;
	asm volatile ("lidt (%0)" :: "m"(idt_ptr));
}

static void remap_pics(void)
{
	// yuck, x86 :/
	uint8_t mask1 = inb(0x21);
	uint8_t mask2 = inb(0xA1);
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20); // pic 1 offset
	outb(0xA1, 0x28); // pic 2 offset
	outb(0x21, 4);
	outb(0xA1, 2);
	outb(0x21, mask1);
	outb(0xA1, mask2);
}

void setup_interrupts(void)
{
	install_idt();
	remap_pics();
}

void enable_interrupts(void)
{
	asm volatile ("sti");
}

void disable_interrupts(void)
{
	asm volatile ("cli");
}
