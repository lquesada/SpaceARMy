
all: checkpath tools

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

tools: tools/wav2gba/ tools/bin2c/

clean:
	make -C tools/wav2gba/ clean
	make -C tools/bin2c/ clean

