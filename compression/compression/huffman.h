#include <stdio.h>

typedef enum returnCode
{
	complete,
	read_error,
	write_error,
	not_enough_memory
};

typedef union blockOfBits
{
	char block;
	struct elements
	{
		int bitOne:1;
		int bitTwo:1;
		int bitThree:1;
		int bitFour:1;
		int bitFive:1;
		int bitSix:1;
		int bitSeven:1;
		int bitEight:1;
	};
}; 

typedef struct dictionaryElem
{
	double probability;
	char elem;
}dictioinaryElem;


typedef struct dictionaryOfBits
{
	blockOfBits bits;
	short countBits;
	char elem;
}dictioinaryElem;

typedef struct treeElem
{
	char charater;
	treeElem* zero;
	treeElem* one;
}treeElem;

returnCode huffman_encode(FILE *in ,FILE *out);
returnCode huffman_decode(FILE *in,FILE *out);
void sortDictionary(dictionaryElem* dictionary, int length);
treeElem* createTree(dictionaryElem* dictionaty, int length);