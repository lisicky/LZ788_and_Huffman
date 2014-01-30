#include <stdio.h>
#include <stdlib.h>

typedef enum returnCode
{
	complete,
	read_error,
	write_error,
	not_enough_memory
}returnCode;

typedef union blockOfBits
{
	char block;
	struct elements
	{
		unsigned bit1:1;
        unsigned bit2:1;
        unsigned bit3:1;
        unsigned bit4:1;
        unsigned bit5:1;
        unsigned bit6:1;
        unsigned bit7:1;
        unsigned bit8:1; 
	};
}blockOfBits; 

typedef struct dictionaryElem
{
	int probability;
	char elem;
}dictionaryElem;


typedef struct dictionaryOfBitsElem
{
	blockOfBits bits;
	short countBits;
	char elem;
}dictionaryOfBitsElem;

typedef struct Node
{
	char charater;
	int probability;
	struct Node *zero;
	struct Node *one;
}node;

returnCode huffman_encode(FILE *in ,FILE *out);
returnCode huffman_decode(FILE *in,FILE *out);
void destroyTree(node** root);
dictionaryOfBitsElem* createDictionaryOfBits(node* root);
node* createTree(dictionaryElem* dictionaty, int length);
