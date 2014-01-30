#include <stdio.h>
#include <tchar.h>
#include "huffman.h"


int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out; 
	in=fopen("C:\\Users\\God\\Desktop\\yyy1.bmp", "rb");
	out=fopen("C:\\Users\\God\\Desktop\\yyy1.huff", "wb");
	huffman_encode(in,out);
	return 0;
}

