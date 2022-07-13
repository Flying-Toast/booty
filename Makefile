CC=gcc
CFLAGS=-ffreestanding -mno-red-zone -Wall -Wextra -m32 -Os
C_OBJS=main.o interrupts.o kstd.o vga.o io.o keyboard.o panic.o

.PHONY: run
run: kern.bin
	@qemu-system-i386 -monitor stdio -drive file=kern.bin,format=raw

kern.bin: kern.o
	@objcopy --output-target=binary --only-section=.text kern.o kern.bin

kern.o: boot.o $(C_OBJS)
	@ld -T link.ld -m elf_i386 --orphan-handling=discard boot.o $(C_OBJS) -o kern.o

boot.o: boot.s
	@as --32 --fatal-warnings -o boot.o boot.s

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(RM) *.o
	@$(RM) kern.bin
