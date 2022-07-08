OUTPUT_FORMAT("binary")

SECTIONS {
	. = 0x7C00;

	.text : {
		boot.o(.text)
		*(.text)
		*(.data)
		*(.rodata)
		*(.bin-end)
		FILL(0xCC)
		. = ALIGN(512);
	}
}
