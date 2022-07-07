	.code16
	.section .text
	# 0x7C00 base address is set by ld (see Makefile)

	# Ensure we're using segment 0, because some BIOS load to 0x7C0:0x0000 instead of 0x0000:0x7C00 (equivalent physical address, but different segment)
	jmp $0x00, $after_initial_jmp
after_initial_jmp:

	# Zero the segment registers
	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

	# Set up stack
	mov $0xFFF0, %sp

	# print test char
	mov $0xE, %ah
	mov $3, %al
	int $0x10

	# read more sectors to memory
	mov $0x02, %ah
	mov $0x01, %al # number of sectors to read
	xor %ch, %ch # cylinder number
	mov $0x02, %cl # sector number 1-63 (bits 0-5)
	xor %dh, %dh # head number
	# %dl holds the drive numer to read from, BIOS puts the __boot drive__ drive number in it during boot
	# es:bx is the pointer to read to
	mov $end_boot_sector, %bx

stall:
	jmp stall

	.org 510
	.byte 0x55, 0xAA
end_boot_sector:
