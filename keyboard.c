#include <stdint.h>
#include "io.h"
#include "keyboard.h"
#include "kstd.h"

static volatile bool keyboard_keystates[256 - (1<<7)];
static volatile bool pending_second_byte = false;

bool is_key_down(enum scancode sc)
{
	return keyboard_keystates[sc];
}

void setup_keyboard(void)
{
	memset((void *)keyboard_keystates, 0, sizeof(keyboard_keystates));
}

void handle_keyboard_interrupt(void)
{
	uint8_t scancode = inb(0x60);

	if (pending_second_byte) {
		// for now, we just ignore extended scancodes
		// TODO: handle them
		pending_second_byte = false;
		return;
	}

	if (scancode == 0xE0) {
		pending_second_byte = true;
		return;
	}

	if (scancode & 1<<7) {
		// key release
		keyboard_keystates[scancode & ~(1<<7)] = false;
	} else {
		// key press
		keyboard_keystates[scancode & ~(1<<7)] = true;
	}
}
