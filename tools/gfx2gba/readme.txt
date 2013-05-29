====================
gfx2gba v0.13 README
====================

this tool converts

PCX - 8 bit (256 color)
TGA - 8 bit (256 color)
SPR - 8 bit (256 color)
BMP - 8 bit (256 color) or 4 bit (16 color)
TIM - 8 bit (256 color) or 4 bit (16 color)

graphic files to GBA useable data (raw, tiles, map). The special thing
about this tool is that it is able to combine the palettes of several
gfx files into one single "master palette". it removes/remaps double
colors. of course if you try to combine 2 files with 256 unique colors
each it will fail, heh ... :p

Usage: gfx2gba [options] bmp/pcx/tga/spr/tim files ...

Options are:
 
 -pPalettename                    -m generate map (optimized)
 -oOutputdir                      -M generate map (not optimized)
 -fOutput format                  -mm generate metatiled map (optimized)
 -sSection                        -MM generate metatiled map (not optimized)
 -SpSuffix for palette            -bBank for map
 -SmSuffix for map                -mc save map in column order *new*
 -StSuffix for tiledata           -F turn off check for flipped tiles
 -TMetatilesize                   -rs output a rotate/scale BG screen map
 -tTilesize                       -P don't save palette data
 -tc save tiles as columns *new*  -G don't save tile/image data
 -cColordepth                     -D don't save map data
 -CColor-Offset                   -X don't save anything
 -A force color offset add        -Z compress everything
 -aTransparent color              -zt compress tile/bitmap data
 -vVRAM-Offset                    -zp compress palette data
 -x don't merge palettes          -zm compress map data
 -q quiet mode                    -ap use aPLib as compressor
 -B only optimize blank tiles     -aps use aPLib (safe) as compressor
                                  -align add alignment info for GCC *new*

-align adds alignment info to arrays (needed sometimes for GCC)

-mc saves map's in column order instead of rows

-tc saves the tiles in column order instead of rows

-B only optimize/remove BLANK tiles and don't touch others

-A forces color offset adding to ALL colors (it doesn't add the offset to
   index 0 by default)

-ap use aPLib as compressor instead of lz77

-aps use aPLib (safe mode) as compressor instead of lz77

NOTE: for detailed info about aPLib check http://home19.inet.tele.dk/jibz/apack/
      thanks to Jørgen Ibsen for this excellent piece of software

-q quiet mode reduces output to a minimum

-p specifies the name of the master palette (default: master.pal)

-o specifies the output directory (default is current dir)

-f specifies the output format (raw/src/asm/arm) (default is raw)

-s will allow you to select the ROM section used in the assembler
   outputfiles (default is .rodata)

-Sp specifices a custom extension for palette files (ie replace
    ".pal" by something else)

-Sm like above but to customize/replace ".map"

-St like above but to customize/replace ".raw"

NOTE: if C or ASM output is selected, .c or .s will ALWAYS be added
      to the filename, regardless of what custom extension you
      selected!

-T specifies the metatilesize (1/8/16/32/64) (default is 1, which
   means NO metatiling at all)

-t specifies the tilesize (1/8/16/32/64) (default is 1, which means
   NO tiling at all, giving you plain raw data for mode4/5 bg's)

-c specifies input/output color depth (16/256/32k) (default is 256)
   NOTE: in 256 color mode you can also READ 16 color images, but
         they'll be saved as 256 color images!
   NOTE2: 32k setting only works for OUTPUT of raw 15+1bit gfx data
          for use in MODE3/5, you can NOT READ other formats than
          16/256 color BMP or 256 color PCX. this tool was not
          designed for this mode anyway, so expect some bugs there
          (especially if you mix it with other options)

-C will add an offset (0-255) to the bitmap color indexes (default 0)
   it will NOT add the offset to color index #0 (transparent) !!!

-a changes the transparent color (0-255). (default 0)

-v specifies the offset to be added when saving tilemaps (default
   is 0)

-b specifies the color bank to use for 16 color tile maps (0-15)
   (default is 0)

NOTE: DO NOT USE SPACES between -p/-o/-s/-Sp/-Sm/-St-t/-c/-v/-C/-b
      and it's parameter!!! use -t16 or something like that, but
      -t 16 won't work!!!

-m will generate an optimized tile map from the inputfile. optimized
   means it removes double tiles and also checks for horizontal,
   vertical and h+v flipped doubles. of course it sets the correct
   flags in the tile map data. the output .raw file will ONLY contain
   the used tiles (of course).

-M will generate a NON optimized tilemap

-mm will tile a generated map into 32x32 tile sub-maps for easy DMA'ing
    them around

-MM same as -mm just for non optimized maps

-F will turn off check for flipped tiles in map. only "real" doubles will
   be removed.

NOTE: activating map generation will change default tile size from 1 to
      a more GBA friendly size of 8. you can still set your own size using
      the -t option.
      fixed a stupid bug that produced an endless loop in v0.6 if your
      input gfx bitmap was >= 4mbyte.

-rs will force the map to be saved in 1 byte per tile format making it
    suitable for rotate/scale backgrounds. you lose color bank info and
    h/v flip info obviously and the max number of tiles is 256. but hey,
    you knew that already, don't ya?
    NOTE: this one is fixed now, had a silly bug that was not catched
          by -Wall ... :/

-P will disable palette output at all

-G will disable graphics (tiles/images) output at all

-D will disable map output at all

-X will disable all data output

-x will prevent gfx2gba from merging/optimizing your palettes and save
   a separate .pal file for each input gfx file.

-zt will lz77 compress tile/gfx data

-zp will lz77 compress palette data

-zm will lz77 compress map data

-Z will lz77 compress everything

NOTE: all compression stuff is compatible to the GBA internal Lz77 depacker.
      if it fails to compress it will show you a warning and save the normal
      data.

==========================
Frequently Asked Questions
==========================

Q: so far so good, but what if i want to convert all my 36 .bmp files and
   12 .pcx files ?!
A: easy: gfx2gba *.pcx *.bmp
   could it be any simpler?! :)

Q: what -t value do i need for correct sprites and background tiles?
A: use -t8 to get what you need ...

Q: but i am using Linux for GBA dev?!
A: just use the included Linux binary (you may have to set exec flag)

Q: wtf is -v good for? why would i want to add an offset?!
A: HINT: to maximize the number of useable tiles.

Q: is it possible that your tool is the only free available one that
   also supports 16 color / 4 bit gfx?!
A: erm... well... seems so... looks like other tool coders ignore the
   presence of the 16 color modes on GBA ...

Q: v0.4 features are the same as in v0.3?! what's new or changed?!
A: *cough* this release has 2 major bugs fixed. bitmap export to 4bit
   (16 color) was broken (pixel swapped) (export to tiles was working,
   that's why i found this nasty bug so late) and my color optimizing
   stuff made ALL black (0x0000) colors transparent (thanks to Michael
   Jagger for yelling at me about this)

Q: soo, what's new in v0.5 ? i still can't see any new options?!
A: *cough*cough* the black color bug was nastier than i thought but at
   the end they all DIE ... or short: the last bug in color optimizing
   is removed now ... fixed bitmap remapping (last pixel wasn't remapped)
   and finally it compiles now without even a warning! :-)

Q: hey, i can mix all kind of options and gfx2gba doesn't complain about
   stuff that doesn't make sense?!
A: it is a tool to help you developing GBA stuff, not a brain replacement
   and it assumes you know at least a little bit what you are doing.

Q: I have a problem with 32k mode...
A: I don't care ... 32k mode is just a little add-on and not something
   high-priority for me ... :)

Q: hey, who's responsible for the color bank & rot/scale option? i don't
   think you're smart enough to think about 'em yourself!?
A: sad but true ... thanks to Alex D. for this obviously useful ideas.
   cheers mate, keep the ideas coming (even if they arrive in my inbox
   at 00:30 in the morning)!

Q: are there any other people who are giving you their valuable ideas
   free of charge?
A: yeah! many thanks to Dennis R. for the idea to change some of the
   default values and kicking my butt to implement C/C++ array output
   at least. and then we have Bengt Johannesson who found out that the
   symbol name creation was f*cked when you used files not placed in
   the current directory (it had the complete path in the label name
   instead of just the filename) ...

Q: who wanted the l33t flipped tile check to be removable!?
A: Nikita Mikros needed it so i added it ... :)

Q: metatiling? wow! cool name for a feature, BUT WHAT THE HELL IS IT?!
A: it more or less means that your input gfx will get tiled twice. for
   example my game "engine" is building large objects from 16x16 sprites.
   but 16x16 sprites have to made from 8x8 data internally anyway. so
   with a normal tool you have to group your objects in 16xY gfx to get
   a good result. now here comes metatiling into play: it first tiles
   your gfx into X*X and then in Y*Y. so -T16 -t8 will split up the gfx
   into 16x16 blocks first and then this blocks into 8x8 blocks ...
   i hope you get the idea ... :-)

Q: who's responsible for the compressing stuff?
A: thanks to Tony McB. for permisson to use his packer source!

Q: what else is changed/added/fixed in v0.9?
A: added check for incorrect BMP headers (some tools don't set the
   "used colors" entry) and use the depth as default if header info is
   missing.
   also fixed rot/scale BG generation (thanks to Alex D. for reporting)
   added some headers in asm/c outputfiles (that's for you Alex! :) )
   added size info for linker to asm outputfiles

Q: who brought up the idea to add options to disable data output?
A: Erik G. asked for it and now he got it ... :p

Q: not many *NEW*'s in v0.10, what has changed?
A: added function to convert artist-filenames to coder-filenams
   (ie replacing illegal characters in label names by _'s)
   fixed filename generation and handling if sourcefiles are in
   a sub-directory
   message if saving was successful or not
   (thanks to Dennis R. for all this ideas/reports)
   Andreas T. told me that -p together with -x was not working so
   i fixed it :)
   also for Andreas T. are the -mm and -MM options
   thanks to Peter H. (PED) you can now also enjoy the -q option
   made -C work with -x ( thanks to Thomas H. for this one)
   added -a option to set the transparent color (also for Thomas H.)

Q: any updates in v0.11 ?
A: added -B (only blank tile optimize) for light1
   added -A (for Thomas H.)
   added -ap and -aps (aPlib compression) (for Dennis R.)
   added -farm
   added TGA 256 color (packed/unpacked) loader
   fixed color index 0 color in master.pal (for Tyler Gregg)
   fixed GCC ASM .align 4 to .align 2
   fixed "***ERROR: need 256 free colors, only 255 available!" problem
   included a static linked linux version (for Joeri)

Q: no new features in v0.12???
A: no, just 2 important bug fixes:
   - fixed -mm and -MM for metatiled maps (thanks to Phantasm for this one)
   - fixed RAW palette output

Q: what's really new in v0.13?
A: added ProMotion .spr loader
   added Playstation(tm) .tim loader
   added more precise error texts to image loader
   added -mc option to convert row based maps to column based maps (Luc B.)
   added -tc option to convert tiles/bitmaps to columns (Luc B.)
   added possibility to have a ' ' (space) between argument and parameter (Krystian W.)
   added -align option to add  __attribute__ ((aligned (4))) to C/C++ arrays (Thomas H.)
   added extern to C/C++ arrays (Thomas H.)
   added try{} catch(){} around new to prevent termination without error message


=======
Contact
=======

any questions, reports, suggestions are welcome ...
contact me at: markus@console-dev.de

