TARGET = arm-none-eabi

AS           = $(TOOLCHAINPATH)/bin/$(TARGET)-as
CC           = $(TOOLCHAINPATH)/bin/$(TARGET)-gcc
LD           = $(TOOLCHAINPATH)/bin/$(TARGET)-ld
GDB          = $(TOOLCHAINPATH)/bin/$(TARGET)-insight
OBJCOPY      = $(TOOLCHAINPATH)/bin/$(TARGET)-objcopy
GFX2GBA      = tools/gfx2gba/gfx2gba-static
GIFS2SPRITES = wine tools/gifs2sprites/gifs2sprites.exe
WAV2GBA      = tools/wav2gba/wav2gba
BIN2C        = tools/bin2c/bin2c

CFLAGS      = $(INCDIR) -g -Wall -mcpu=arm7tdmi -c

SOUND = build/gameover_s.o build/playershoot_s.o build/armyshoot_s.o build/playerexplosion_s.o build/armyexplosion_s.o build/congratulations_s.o build/tic_s.o build/armydeath_s.o build/explosion_s.o build/welcome_s.o

all: checkpath build spacearmy.gba

checkpath:
ifndef TOOLCHAINPATH
	@echo
	@echo No toolchain path defined.
	@echo
	@echo Please, use make TOOLCHAINPATH=path/to/toolchain
	@echo
	@echo Example: make TOOLCHAINPATH=~/Download/gcc-arm-none-eabi-4_7-2013q1/
	@echo
	@echo Get a suitable toolchain from https://launchpad.net/gcc-arm-embedded
	@echo
	exit 1
endif

build:
	mkdir build

spacearmy.gba : build/spacearmy-wrongchecksum.gba

build/spacearmy-wrongchecksum.gba : resources

resources : $(SOUND)

build/%_s.o : build/%_s.c
	$(CC) $(CFLAGS) $< -o $@

build/%_s.c : build/%_s.bin $(BIN2C)
	$(BIN2C) $< $@

build/%_s.bin : res/%.wav $(WAV2GBA)
	$(WAV2GBA) $< $@

$(BIN2C):
	make -C tools/bin2c

$(WAV2GBA):
	make -C tools/wav2gba

clean:
	make -C tools/wav2gba/ clean
	make -C tools/bin2c/ clean
	rm -rf build

