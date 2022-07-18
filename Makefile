CC=gcc
CFLAGS=-ffreestanding -mno-red-zone -Wall -Wextra -m32 -Os
AS=as
ASFLAGS=--32 --fatal-warnings
OBJS=boot.ao main.o interrupts.o kstd.o vga.o io.o keyboard.o panic.o

.PHONY: run
run: kern.bin
	@qemu-system-i386 -monitor stdio -drive file=kern.bin,format=raw

kern.bin: kern.o
	@objcopy --output-target=binary --only-section=.text kern.o kern.bin

kern.o: $(OBJS)
	@ld -T link.ld -m elf_i386 --orphan-handling=discard $(OBJS) -o kern.o

%.ao: %.s
	@$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(RM) *.o
	@$(RM) *.ao
	@$(RM) kern.bin
