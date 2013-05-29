// Unknown author.

//////////////////////////////////////////////////////////////////////////////
// bin2c.cpp                                                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Includes                                                                 //
//////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void strlwr(char* s)
{
  while ((*s++ = tolower(*s)));
}

//////////////////////////////////////////////////////////////////////////////
// main                                                                     //
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	if (argc < 3) { printf("Syntax: %s <input.bin> <output.c> [<identifier>]\n", argv[0]); return -1; }
	FILE *fi = fopen(argv[1], "rb");
	if (!fi) { printf("Error opening input file!\n"); return -1; }
	FILE *fo = fopen(argv[2], "wt");
	if (!fo) { printf("Error opening output file!\n"); return -1; }

	// identifier	
	if (argc >= 4)
	{
		fprintf(fo, "const unsigned char %s[] =\n{\n", argv[3]);
	}
	else
	{
		char s[256]; strcpy(s, argv[1]);
		char *p = strrchr(s, '\\');
		if (!p) p = strrchr(s, '/');	// remove directory
		if (p) p++; else p = s;
		strcpy(strrchr(s, '.'), "");	// remove extension
		strlwr(p);
		fprintf(fo, "const unsigned char %s[] =\n{\n", p);
	}

	// convert
	while (!feof(fi))
	{
	  int i;
		for (i=0; i<16; i++)
		{
			int c = fgetc(fi); if (c < 0) break;
			if (i == 0) fprintf(fo, "\t0x%02X,", c); else fprintf(fo, "0x%02X,", c);
		}
		if (i) fprintf(fo, "\n");
	}

	fprintf(fo, "};\n");

	fclose(fi);
	fclose(fo);
	return 0;
}
