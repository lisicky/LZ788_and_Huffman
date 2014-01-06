#include <stdio.h>

typedef enum returnCode
{
	complete,
	read_error,
	write_error,
	not_enough_memory
}returnCode;

typedef struct dictionaryElem
{
	char elem;
	unsigned short n;
}dictionaryElem;

returnCode lz78_encode(FILE in, FILE out);
returnCode lz78_decode(FILE in, FILE out);
unsigned short findInDictionary(dictionaryElem* dictionary,unsigned short length,unsigned short startIndex, char elem);
