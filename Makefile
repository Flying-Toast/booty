.PHONY: run
run: bsect.bin
	qemu-system-i386 bsect.bin -monitor stdio

bsect.bin: boot.o
	ld -T link.ld --orphan-handling=discard boot.o -o bsect.bin

boot.o: boot.s
	as -o boot.o boot.s

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) bsect.bin
