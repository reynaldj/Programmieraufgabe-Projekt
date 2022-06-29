#!/usr/bin/make
.SUFFIXES:
SRC = $(wildcard *.c) $(wildcard *.s)
HDR = $(wildcard *.h)
TAR = bootloader.bin
PCK = lab-1.zip

CFLAGS = -m32 -c -Os -march=i686 -ffreestanding -Wall
LFLAGS = -m elf_i386 -static -Tlinker.ld -nostdlib --nmagic

%.o: %.c
	$(CC) $(CFLAGS)  $^ -o $@

%.elf: %.o
	$(LD) $(LFLAGS) -o $@ $^

%.bin: %.elf
	objcopy -O binary $^ $@

all: $(TAR)

run: $(TAR)
	qemu-system-x86_64 -drive format=raw,file=$^

pack:
	zip $(PCK) Makefile $(SRC) $(HDR)

clean:
	$(RM) $(RMFILES) $(TAR) $(PCK)
