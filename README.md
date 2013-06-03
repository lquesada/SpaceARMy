SpaceARMy
=========

SpaceARMy (Shoot 'Em Up game for the Game Boy Advance (ARM7TDMI)).  
Copyright (c) 2013, Luis Quesada - https://github.com/lquesada


In order to compile SpaceARMy:

1. Download the GNU Tools for ARM Embedded Processors from https://launchpad.net/gcc-arm-embedded

2. Extract the GNU Tools for ARM Embedded Processors somewhere.

3. Install wine (it is required only during a part of the compilation process).

4. Download SpaceARMy source.

5. Get into the SpaceARMy source directory and run:
            
            $ make TOOLCHAINPATH=path/to/toolchain

Example:

            $ make TOOLCHAINPATH=~/gcc-arm-none-eabi-4_7-2013q1/

This will create SpaceARMy.gba.

You can run that file in a Game Boy Advance emulator such as Visual Boy Advance (http://vba.ngemu.com/) or in an actual Game Boy Advance/Nintendo DS.
