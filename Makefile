all : os-image

C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJS=$(C_SOURCES:.c=.o)

os-image : boot.bin kernel.bin
	cat $^ > os-image

boot.bin : ./boot/boot.asm
	nasm -f bin -o $@ $< -i/mnt/c/dev/ANTON/OS/boot/

kernel.bin : ./kernel/KernelEntry.o ./kernel/kernel.o $(OBJS)
	ld -m elf_x86_64 -o $@ -Ttext 0x1000 $^ --oformat binary 

kernel/%.o : kernel/%.c $(HEADERS)
	@echo test
	gcc -ffreestanding -c $< -o $@

./kernel/KernelEntry.o : kernel/KernelEntry.asm
	nasm kernel/KernelEntry.asm -f elf64 -o ./kernel/KernelEntry.o

clean :
	rm -fr *.bin *.dis *.o os-image
	rm -fr kernel/*.o boot/*.bin drivers/*.o

run : all
	qemu-system-i386 -fda os-image
