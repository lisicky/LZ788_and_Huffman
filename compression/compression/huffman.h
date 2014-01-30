#include <stdio.h>
#include <stdlib.h>
#include "binaryOperation.h"
#ifndef HUFFMAN_H
#define HUFFMAN_H
typedef enum returnCode
{
	complete,
	read_error,
	write_error,
	not_enough_memory
}returnCode;

typedef struct dictionaryElem
{
	int probability;
	char elem;
}dictionaryElem;

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
void createDictionaryOfBits(node* root,char* code,dictionaryOfBitsElem* dictionaryOfBits, int* length);
node* createTree(dictionaryElem* dictionaty, int length);
#endif