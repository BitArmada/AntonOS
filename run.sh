nasm -f bin -o ./build/boot.bin ./boot/boot.asm -i/mnt/c/dev/ANTON/OS/boot/
dd status=noxfer conv=notrunc if=./build/boot.bin of=./build/boot.flp

cat build/boot.bin kernel.bin > os-image

qemu-system-i386 -fda os-image