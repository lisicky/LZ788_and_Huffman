#include "huffman.h"
#define DICTIONARY_LENGTH 256

int compare(const void * x1, const void * x2)
{
	return((*(dictionaryElem*)x1).probability-(*(dictionaryElem*)x2).probability);
}

int compareNode(const void * x1, const void * x2)
{
	return(((node**)x1)[0]->probability)-(((node**)x2)[0]->probability);
}

returnCode huffman_encode(FILE *in ,FILE *out)
{
	int i,j;
	int length = DICTIONARY_LENGTH;
	int countOfRead;
	long oldPosition;
	dictionaryElem *dictionary, *memoryBlockForDictionary;
	char* buff;
	dictionaryOfBitsElem* dictionaryOfBits;
	node* root;
	if(in==NULL)
		return read_error;
	if(out==NULL)
		return write_error;
	buff=(char*)malloc(sizeof(char)*BUFSIZ);
	if(buff==NULL)
		return not_enough_memory;
	memoryBlockForDictionary=(dictionaryElem*)malloc(sizeof(dictionaryElem)*length);
	dictionary=memoryBlockForDictionary;
	if(dictionary==NULL)
	{
		free(buff);
		return not_enough_memory;
	}
	for(i=0;i<length;i++)
	{
		dictionary[i].elem=i;
		dictionary[i].probability=0;
	}
	oldPosition = ftell(in);
	while(!feof(in))
	{
		countOfRead= fread_s(buff,BUFSIZ,sizeof(char),BUFSIZ,in);
		if(ferror(in))
			return read_error;
		for (i=0;i<countOfRead;i++)
			dictionary[buff[i]].probability++;
	}
	fseek(in,oldPosition,SEEK_SET);
	qsort(dictionary,length,sizeof(dictionaryElem),compare);
	for(i=0;i<length;i++)
	{
		if(dictionary->probability==0)
		{
			dictionary++;
			length--;
		}
		else
		{
			break;
		}
	}
	if(length==0)
		return complete;
    
	root=createTree(dictionary,length);
//	dictionaryOfBits = createDictionaryOfBits(root);
}

node* createTree(dictionaryElem* dictionary, int length)
{
	int i,j;
	node* newNode;
	node **nodes, **memoryBlockForNodes;
	memoryBlockForNodes=(node**)malloc(sizeof(node*));
	nodes=memoryBlockForNodes;
	if(nodes==NULL)
		return NULL;
	for (i=0;i<length;i++)
	{
		nodes[i]=(node*)malloc(sizeof(node));
		if(nodes[i]==NULL)
		{
			for(j=0;j<i;j++)
			{
				destroyTree(&nodes[j]);
			}
			free(memoryBlockForNodes);
			return NULL;
		}
		nodes[i]->charater=dictionary->elem;
		nodes[i]->probability=dictionary->probability;
		nodes[i]->one=NULL;
		nodes[i]->zero=NULL;
	}
	while (length!=1)
	{
		newNode=(node*)malloc(sizeof(node));
		if(newNode==NULL)
		{
			for(i=0;i<length;i++)
			{
				destroyTree(&nodes[i]);
			}
			free(memoryBlockForNodes);
			return NULL;
		}
		newNode->probability=nodes[0]->probability+nodes[1]->probability;
		newNode->zero=nodes[0];
		newNode->one=nodes[1];
		nodes[1]=newNode;
		nodes++;
		length--;
		qsort(nodes,length,sizeof(node*),compareNode);
	}
	newNode=nodes[0];
	free(memoryBlockForNodes);
	return newNode;
}

void destroyTree(node** root)
{
	if(root!=NULL)
	{
	if(root[0]->one!=NULL)
	{
		destroyTree(&root[0]->one);
	}
	if(root[0]->zero!=NULL)
	{
		destroyTree(&root[0]->zero);
	}
	free(root[0]);
	}
}