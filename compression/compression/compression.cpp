#include <stdio.h>
#include <tchar.h>
#include "huffman.h"



int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out; 
	int i;
	printf("%d",sizeof(blockOfBits));
	in=fopen("C:\\Users\\God\\Desktop\\yyy1.bmp", "rb");
	out=fopen("C:\\Users\\God\\Desktop\\yyy1.huff", "wb");
	i=huffman_encode(in,out);
	fclose(in);
	fclose(out);
	return 0;
}

