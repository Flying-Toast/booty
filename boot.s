	.code16
	.section .text
	# 0x7C00 base address is set by ld (see link.ld)
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

	# read more sectors to memory until we read one with the magic bytes at the end
	mov $end_boot_sector, %bx # es:bx is the pointer to read to
	mov $0x02, %cl # sector number 1-63 (bits 0-5)
read_a_sector:
	mov $0x02, %ah
	mov $0x01, %al # number of sectors to read
	xor %ch, %ch # cylinder number
	xor %dh, %dh # head number
	# %dl holds the drive numer to read from, BIOS puts the __boot drive__ drive number in it during boot
	int $0x13

	# check for magic
	add $512, %bx # increment buffer pointer to the next base address to read to
	push %edx
	mov $0xCCCCCCCC, %edx
	cmp %edx, -4(%bx) # compare the last 32 bits of the previous sector
	pop %edx
	je done_reading_sectors
	inc %cl
	jmp read_a_sector
done_reading_sectors:

	# enable A20
	mov $0x2401, %ax
	int $0x15

	cli
	lgdt (gdt_ptr)

	# enter protected mode
	mov %cr0, %eax
	or $1, %eax
	mov %eax, %cr0
	# long jump to set cs
	jmp $0x08, $begin_protected

start_gdt:
gdt_ptr:
	# null entry - we store the gdt pointer (6 bytes) here, inside the null entry (8 bytes)
	.short end_gdt - start_gdt - 1 # gdt size minus 1
	.long start_gdt # base address
	.short 0 # pad 2 bytes after the pointer to fill rest of the null entry
	# entry 1 (kernel mode code)
	.short 0xFFFF # bits 0-15 of limit address
	.short 0 # bits 0-15 of base address
	.byte 0 # bits 16-23 of base address
	.byte 0b10011010 # access byte (exe bit = 1, code)
	.byte 0b11001111 # upper part of limit address (bits 0-3), flags (bits 4-7)
	.byte 0 # upper part of base address
	# entry 2 (kernel mode data)
	.short 0xFFFF # bits 0-15 of limit address
	.short 0 # bits 0-15 of base address
	.byte 0 # bits 16-23 of base address
	.byte 0b10010010 # access byte (exe bit = 0, data)
	.byte 0b11001111 # upper part of limit address (bits 0-3), flags (bits 4-7)
	.byte 0 # upper part of base address
end_gdt:

	.org 510
	.byte 0x55, 0xAA
end_boot_sector:

begin_protected:
	.code32
	mov $0x7BF0, %esp
	call cmain
stall:
	jmp stall

.global asm_int21_wrapper
asm_int21_wrapper:
	call handle_keyboard_interrupt
	jmp isr_done

.global default_isr
default_isr:
isr_done:
	mov $0x20, %al
	outb %al, $0x20
	iret

	# we use a series of at least 4 consecutive 0xCC bytes at the end of the last sector, so we know when we've loaded the last sector of our program
	.section .bin-end
	.long 0xCCCCCCCC
