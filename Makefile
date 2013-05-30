TARGET = arm-none-eabi

AS           = $(TOOLCHAINPATH)/bin/$(TARGET)-as
CC           = $(TOOLCHAINPATH)/bin/$(TARGET)-gcc
LD           = $(TOOLCHAINPATH)/bin/$(TARGET)-ld
OBJCOPY      = $(TOOLCHAINPATH)/bin/$(TARGET)-objcopy
GFX2GBA      = tools/gfx2gba/gfx2gba-static
GIFS2SPRITES = wine tools/gifs2sprites/gifs2sprites.exe
WAV2GBA      = tools/wav2gba/wav2gba
BIN2C        = tools/bin2c/bin2c

ASFLAGS     = -I libgba -mcpu=arm7tdmi -gstabs
CFLAGS      = -I libgba/ -g -Wall -mcpu=arm7tdmi -c
LDFLAGS     = -L libgba/ -Tlibgba/cart.ld -nostartfiles

OBJS        = build/matamarcianos.o build/contador.o build/enemigo.o build/pausa.o build/disparobueno.o build/disparomalo.o build/escudo.o build/jugador.o build/colisiones.o build/explosion.o build/sonido.o
STARTUP = build/startup.o
SOUNDS = build/gameover_s.o build/playershoot_s.o build/armyshoot_s.o build/playerexplosion_s.o build/armyexplosion_s.o build/congratulations_s.o build/tic_s.o build/armydeath_s.o build/explosion_s.o build/welcome_s.o
BACKGROUNDS = build/bg_b.o build/bgpause_b.o build/bgsplash_b.o
SPRITES = build/spritedata.o

SPRITELIST = res/player.gif res/army1a.gif res/army1b.gif res/army2a.gif res/army2b.gif res/army3a.gif res/army3b.gif res/army4a.gif res/army4b.gif res/army5a.gif res/army5b.gif res/army6a.gif res/army6b.gif res/army7a.gif res/army7b.gif res/playershoot.gif res/armyshoot.gif res/shield1.gif res/shield2.gif res/shield3.gif res/explosion1.gif res/explosion2.gif res/explosion3.gif res/explosion4.gif res/explosionb1.gif res/explosionb2.gif res/explosionb3.gif res/explosionb4.gif res/explosionc1.gif res/explosionc2.gif res/explosionc3.gif res/explosionc4.gif res/explosiond1.gif res/explosiond2.gif res/explosiond3.gif res/explosiond4.gif

LIBGBA      = libgba/libgba.a

all: checkpath build SpaceARMy.gba

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

SpaceARMy.gba : build/spacearmy-wrongchecksum.gba
	tools/gba-header/gba-header -i $< -o $@ -fix -title SpaceARMy
	chmod u+x SpaceARMy.gba

build/spacearmy-wrongchecksum.gba : build/spacearmy.elf
	$(OBJCOPY) -O binary $<  $@

build/spacearmy.elf : $(OBJS) $(SOUNDS) $(BACKGROUNDS) $(SPRITES) $(STARTUP) $(LIBGBA)
	$(LD) $(LDFLAGS) $(OBJS) $(STARTUP) $(SOUNDS) $(BACKGROUNDS) $(SPRITES) -o $@ -lgba

# Startup

build/startup.o : libgba/startup.s
	$(AS) $(ASFLAGS) $< -o $@

# Sounds

build/%_s.o : build/%.c
	$(CC) $(CFLAGS) $< -o $@

build/%_s.c : build/%_s.bin $(BIN2C)
	$(BIN2C) $< $@

build/%_s.bin : res/%.wav $(WAV2GBA)
	$(WAV2GBA) $< $@


# Backgrounds

build/%_b.o : build/%.c
	$(CC) $(CFLAGS) $< -o $@

build/%_b.c : res/%.bmp 
	$(GFX2GBA) -obuild -fsrc -c32k $<
	mv "`echo $@ | sed s/'_b\.c'/'.raw.c'/g`" "$@"

# Sprites

build/spritedata.c : $(SPRITELIST)
	$(GIFS2SPRITES) 256 build/spritedata.h $(SPRITELIST)
	mv build/spritedata.h build/spritedata.c

# Object code

build/%.o : src/%.c src/*.h
	$(CC) $(CFLAGS) $< -o $@

# libgba

$(LIBGBA):
	make -C libgba/

# Tools

$(BIN2C):
	make -C tools/bin2c

$(WAV2GBA):
	make -C tools/wav2gba

# Clean

clean:
	make -C tools/wav2gba/ clean
	make -C tools/bin2c/ clean
	rm -rf build

