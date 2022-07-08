OUTPUT_FORMAT("binary")

SECTIONS {
	. = 0x7C00;

	.text : {
		boot.o(.text)
		*(.text)
		*(.data)
		*(.rodata*)
		*(.bss)

		/* must stay here at the very end of the .text section */
		*(.bin-end)
		FILL(0xCC)
		. = ALIGN(512);
	}
}
