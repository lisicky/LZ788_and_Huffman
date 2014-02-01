#include <stdio.h>
#ifndef LZ_H
#define LZ_H
#ifndef HUFFMAN_H
typedef enum returnCode
{
	complete,
	read_error,
	write_error,
	not_enough_memory
}returnCode;
#endif
#pragma pack(push,1)
typedef struct dictionaryElem
{
	char elem;
	unsigned short n;
}dictionaryElem;
#pragma pack(pop)

returnCode lz78_encode(FILE* in, FILE* out);
returnCode lz78_decode(FILE* in, FILE* out);
unsigned short findInDictionary(dictionaryElem* dictionary,int length,unsigned short startIndex, char elem);
#endif 