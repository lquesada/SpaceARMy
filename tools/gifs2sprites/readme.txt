gifs2sprites v1.0
=============

By:		anli, one of the #gbadev devotees
		Member of Parallax Sisters

Format:		gifs2sprites <16/256> <output.h> <file1.gif> [file2.gif] .....

Description:	This is a utility to create GBA sourcecode from a set of sprites.
		Put every sprite you want to include in a gif-file. Decide if you want
		to get a 16-color palette (15 actually because you transparentness) or
		a 256-color palette (which actually is 255 color big). Run the command.
		The resulting header is then meant to be #included from your source.
				
		All palettes of the gif-files are merged down to one palette, which will
		be place in an array named "palette" as a series of u16 quantities.

		Every sprite will be placed in a u16 array named obj# where # is a number
		starting with 0 and increasing.

		If the result palette grows too large for the desired color depth, the number of
		colors will be decreased with help of color quantization. (All colors will be
		placed in a cube that is divided in a number of blocks until the number of blocks
		corresponds to the number of colors). If this happends, a warning will be displayed
		when the command is run.

Category:	Freeware

