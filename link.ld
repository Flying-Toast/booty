SECTIONS {
	. = 0x7C00;

	.text : {
		boot.ao(.text)
		*(.text)
		*(.data)
		*(.rodata*)

		/* must stay here at the very end of the .text section */
		*(.bin-end)
		FILL(0xCC)
		. = ALIGN(512);
	}

	/* gets discarded during objcopy */
	.bss : { *(.bss) }
}
