SpaceARMy
=========

Shoot 'Em Up game for the Game Boy Advance (ARM7TDMI)

In order to compile SpaceARMy:

1. Download GNU Tools for ARM Embedded Processors.

- https://launchpad.net/gcc-arm-embedded

2. Extract them somewhere.

3. Install wine (it is required only during a part of the compilation process).

3. Download SpaceARMy source.

4. Run make TOOLCHAINPATH=path/to/toolchain

Example: make TOOLCHAINPATH=~/gcc-arm-none-eabi-4_7-2013q1/


Then, you can run SpaceARMy.gba by using an emulator or in a Game Boy Advance/Nintendo DS.

A recommended emulator is Visual Boy Advance: http://vba.ngemu.com/ 
