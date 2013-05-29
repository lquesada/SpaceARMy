all: tools/wav2gba/wav2gba tools/bin2c/bin2c

clean:
	make -C tools/wav2gba/ clean
	make -C tools/bin2c/ clean

