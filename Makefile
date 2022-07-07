.PHONY: run
run: bsect.bin
	qemu-system-i386 bsect.bin -monitor stdio

bsect.bin: boot.o
	objcopy --only-section=.text --set-start=0x7C00 --output-target=binary boot.o bsect.bin

boot.o: boot.s
	as -o boot.o.tmp boot.s
	ld -Ttext 0x7C00 boot.o.tmp -o boot.o
	rm boot.o.tmp
	chmod -x boot.o

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) bsect.bin
