#include <stdint.h>
#include "io.h"
#include "keyboard.h"
#include "kstd.h"

static const char charmap[] = {
	[SCANCODE_1] = '1', [SCANCODE_2] = '2', [SCANCODE_3] = '3', [SCANCODE_4] = '4', [SCANCODE_5] = '5', [SCANCODE_6] = '6',
	[SCANCODE_7] = '7', [SCANCODE_8] = '8', [SCANCODE_9] = '9', [SCANCODE_0] = '0', [SCANCODE_MINUS] = '-', [SCANCODE_EQUALS] = '=',
	[SCANCODE_Q] = 'Q', [SCANCODE_W] = 'W', [SCANCODE_E] = 'E', [SCANCODE_R] = 'R', [SCANCODE_T] = 'T', [SCANCODE_Y] = 'Y', [SCANCODE_U] = 'U',
	[SCANCODE_I] = 'I', [SCANCODE_O] = 'O', [SCANCODE_P] = 'P', [SCANCODE_LEFT_BRACKET] = '[', [SCANCODE_RIGHT_BRACKET] = ']', [SCANCODE_A] = 'A',
	[SCANCODE_S] = 'S', [SCANCODE_D] = 'D', [SCANCODE_F] = 'F', [SCANCODE_G] = 'G', [SCANCODE_H] = 'H', [SCANCODE_J] = 'J', [SCANCODE_K] = 'K',
	[SCANCODE_L] = 'L', [SCANCODE_SEMICOLON] = ';', [SCANCODE_SINGLE_QUOTE] = '\'', [SCANCODE_BACKTICK] = '`', [SCANCODE_BACKSLASH] = '\\',
	[SCANCODE_Z] = 'Z', [SCANCODE_X] = 'X', [SCANCODE_C] = 'C', [SCANCODE_V] = 'V', [SCANCODE_B] = 'B', [SCANCODE_N] = 'N', [SCANCODE_M] = 'M',
	[SCANCODE_COMMA] = ',', [SCANCODE_PERIOD] = '.', [SCANCODE_SLASH] = '/', [SCANCODE_KEYPAD_ASTERIX] = '*', [SCANCODE_SPACE] = ' ',
	[SCANCODE_KEYPAD_7] = '7', [SCANCODE_KEYPAD_8] = '8', [SCANCODE_KEYPAD_9] = '9', [SCANCODE_KEYPAD_MINUS] = '-', [SCANCODE_KEYPAD_4] = '4',
	[SCANCODE_KEYPAD_5] = '5', [SCANCODE_KEYPAD_6] = '6', [SCANCODE_KEYPAD_PLUS] = '+', [SCANCODE_KEYPAD_1] = '1', [SCANCODE_KEYPAD_2] = '2',
	[SCANCODE_KEYPAD_3] = '3', [SCANCODE_KEYPAD_0] = '0', [SCANCODE_KEYPAD_PERIOD] = '.',
};
static volatile bool keyboard_keystates[256 - (1<<7)];
static volatile bool pending_second_byte = false;

char sc2ch(enum scancode sc)
{
	return charmap[sc];
}

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
