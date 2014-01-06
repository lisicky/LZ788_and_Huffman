#include <stdio.h>

enum returnCode
{
	complete,
	read_error,
	write_error,
	not_enough_memory
};

typedef struct dictionaryElem
{
	char elem;
	short n;
};

returnCode lz78_encode(FILE in, FILE out);
returnCode lz78_decode(FILE in, FILE out);