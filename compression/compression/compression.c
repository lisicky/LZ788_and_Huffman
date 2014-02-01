#include "huffman.h"
#include "lz.h"
#include <time.h>
#include <string.h>
#include <sys/stat.h> 

int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;
	clock_t timeStart,timeEnd;
	char nameCompressedFileLZ[256];
	char nameCompressedFileHUFF[256];
	long fileSize, lzSise, huffSize;
	returnCode code;
	double timeHuffEncode,timeHuffDecode;
	double timeLZEncode,timeLZDecode;
	double ratio;
	struct stat fileStat;
	int i;
	if (argc<2)
	{
		printf("\nNot specified file \nUse: compression \"filename\"");
		return 0;
	}
	for(i=1;i<argc;i++)
	{
	in=fopen(argv[i],"rb");
	if(in==NULL)
	{
		printf("File not found");
		continue;
	}
	strcpy(nameCompressedFileLZ,argv[i]);
	strcpy(nameCompressedFileHUFF,argv[i]);
	strcat(nameCompressedFileLZ, ".lz");
	strcat(nameCompressedFileHUFF, ".huff");



	out=fopen(nameCompressedFileLZ,"wb");
	if(out==NULL)
	{
		printf("write error");
		return -1;
	}
	timeStart=clock();
	code=lz78_encode(in,out);
	timeEnd=clock();
	timeLZEncode=(double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
	if(code==write_error)
		{
		printf("write error");
		return -1;
	}
	if(code==read_error)
		{
		printf("read error");
		return -1;
	}
	if(code==not_enough_memory)
		{
		printf("not enough memory");
		return -1;
	}
	fclose(out);
	fclose(in);










	in=fopen(argv[i],"rb");	
	out=fopen(nameCompressedFileHUFF,"wb");
	if(out==NULL)
	{
		printf("write error");
		return -1;
	}
	if(in==NULL)
	{
		printf("File not found");
		return 0;
	}
	timeStart=clock();
	code=huffman_encode(in,out);
	timeEnd=clock();
	timeHuffEncode=(double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
	if(code==write_error)
		{
		printf("write error");
		return -1;
	}
	if(code==read_error)
		{
		printf("read error");
		return -1;
	}
	if(code==not_enough_memory)
		{
		printf("not enough memory");
		return -1;
	}
	fclose(out);
	fclose(in);







		in=fopen(nameCompressedFileHUFF,"rb");	
	out=fopen(argv[i],"wb");
	if(out==NULL)
	{
		printf("write error");
		return -1;
	}
	if(in==NULL)
	{
		printf("File not found");
		return 0;
	}
	timeStart=clock();
	code=huffman_decode(in,out);
	timeEnd=clock();
	timeHuffDecode=(double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
	if(code==write_error)
		{
		printf("write error");
		return -1;
	}
	if(code==read_error)
		{
		printf("read error");
		return -1;
	}
	if(code==not_enough_memory)
		{
		printf("not enough memory");
		return -1;
	}
	fclose(out);
	fclose(in);






	in=fopen(nameCompressedFileLZ,"rb");
	out=fopen(argv[i],"wb");
	if(out==NULL)
	{
		printf("write error");
		return -1;
	}
	if(in==NULL)
	{
		printf("File not found");
		return 0;
	}
	timeStart=clock();
	code=lz78_decode(in,out);
	timeEnd=clock();
	timeLZDecode=(double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
	if(code==write_error)
		{
		printf("write error");
		return -1;
	}
	if(code==read_error)
		{
		printf("read error");
		return -1;
	}
	if(code==not_enough_memory)
		{
		printf("not enough memory");
		return -1;
	}
	fclose(out);
	fclose(in);

	stat(argv[i],&fileStat);
	fileSize=fileStat.st_size;
	stat(nameCompressedFileLZ,&fileStat);
	lzSise=fileStat.st_size;
	stat(nameCompressedFileHUFF,&fileStat);
	huffSize=fileStat.st_size;
	printf("\n------------------------------------------------\nFlename: %s\n------------------------------------------------",argv[i]);
	printf("\nSize:%d\n------------------------------------------------",fileSize);
	ratio=(double)fileSize/lzSise;
	printf("\nLZ78 code:\n\tEncode time: %f\n\tDecode time: %fsecond\n\tCompression ratio: %fsecond\n\tSize: %d\n",timeLZEncode,timeLZDecode,ratio,lzSise);
	ratio=(double)fileSize/huffSize;
	printf("\nHuffman code:\n\tEncode time: %f\n\tDecode time: %fsecond\n\tCompression ratio: %fsecond\n\tSize: %d\n",timeHuffEncode,timeHuffDecode,ratio,huffSize);
	}
	return 0;
}

