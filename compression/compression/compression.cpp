#include <stdio.h>
#include <tchar.h>
#include "lz.h"

int main(int argc, char* argv[])
{
		FILE *in,*out;
	returnCode code;
	in = fopen("C:\\Users\\God\\Desktop\\yyy.bmp","rb");
	out =fopen("C:\\Users\\God\\Desktop\\yyy.lz78","wb");
	code = lz78_encode(in,out);
	printf("%d",code);
	fclose(in);
	fclose(out); 
	in = fopen("C:\\Users\\God\\Desktop\\yyy.lz78","rb");
	out = fopen("C:\\Users\\God\\Desktop\\yyy1.bmp","wb");
	code = lz78_decode(in,out);
	printf("%d",code);
	fclose(in);
	fclose(out); 
	return 0;
}

