CC=gcc
CFLAGS=-ffreestanding -mno-red-zone -Wall -Wextra -m32 -Os
C_OBJS=main.o interrupts.o kstd.o vga.o io.o

.PHONY: run
run: bsect.bin
	@qemu-system-i386 -monitor stdio -drive file=bsect.bin,format=raw

bsect.bin: boot.o $(C_OBJS)
	@ld -T link.ld -m elf_i386 --orphan-handling=discard boot.o $(C_OBJS) -o bsect.bin

boot.o: boot.s
	@as --32 --fatal-warnings -o boot.o boot.s

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(RM) *.o
	@$(RM) bsect.bin
