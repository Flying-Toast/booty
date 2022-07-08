CC=gcc
CFLAGS=-ffreestanding -Wall -Wextra -m32 -Os
C_OBJS=main.o

.PHONY: run
run: bsect.bin
	qemu-system-i386 bsect.bin -monitor stdio

bsect.bin: boot.o $(C_OBJS)
	ld -T link.ld -m elf_i386 --orphan-handling=discard boot.o $(C_OBJS) -o bsect.bin

boot.o: boot.s
	as --32 -o boot.o boot.s

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) bsect.bin
