#include <string.h>
#include "huffman.h"
#define DICTIONARY_LENGTH 256
#define SIZE_OF_LENGTH_DICTIONARY 4 

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
	int lengthOfBinaryDictionary=0;
	int countOfRead;
	long oldPosition;
	int countOfWrite;
	char* buff;
	char* code="";
	bits buffOfBits;
	bits* binCode;
	bits residueBinCode;
	dictionaryElem *dictionary, *memoryBlockForDictionary;
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
		countOfRead=fread_s(buff,BUFSIZ,sizeof(char),BUFSIZ,in);
		if(ferror(in))
			return read_error;
		for (i=0;i<countOfRead;i++)
		{
			j=(unsigned char)buff[i];
			dictionary[j].probability++;
		}
	}
	fseek(in,oldPosition,SEEK_SET);
	qsort(dictionary,length,sizeof(dictionaryElem),compare);
	j=0;
	for(i=0;i<length;i++)
	{
		if(dictionary[0].probability==0)
		{
			dictionary++;
			j++;
		}
		else
		{

			break;
		}
	}
	length-=j;
	if(length==0)
		return complete;
	root=createTree(dictionary,length);
	if(root==NULL)
	{
		free(memoryBlockForDictionary);
		free(buff);
		return not_enough_memory;
	}
	dictionaryOfBits =(dictionaryOfBitsElem*)malloc(sizeof(dictionaryOfBitsElem)*length);
	if(dictionaryOfBits==NULL)
	{
		free(memoryBlockForDictionary);
		free(buff);
		destroyTree(&root);
		return not_enough_memory;
	}
	createDictionaryOfBits(root,code,dictionaryOfBits,&lengthOfBinaryDictionary);
	if(lengthOfBinaryDictionary==0)
	{
		destroyTree(&root);
		free(memoryBlockForDictionary);
		free(buff);
		free(dictionaryOfBits);
		return complete;
	}
	fwrite(&length,SIZE_OF_LENGTH_DICTIONARY,1,out);
	countOfWrite=fwrite(dictionary,sizeof(dictionaryElem),length,out);
	if((countOfWrite!=length)||ferror(out))
	{
		destroyTree(&root);
		free(memoryBlockForDictionary);
		free(buff);
		free(dictionaryOfBits);
		return write_error;
	}
	buffOfBits.countBits=0;
	buffOfBits.arrayOfBits=NULL;
	while (!feof(in))
	{
		countOfRead=fread_s(buff,BUFSIZ,sizeof(char),BUFSIZ,in);
		if(ferror(in))
			return read_error;
		for(i=0;i<countOfRead;i++)
		{
			binCode=findCode(buff[i],dictionaryOfBits,lengthOfBinaryDictionary);
			catBinArr(&buffOfBits,binCode);
			if((buffOfBits.countBits/8)>=BUFSIZ)
			{
				if((buffOfBits.countBits/8)>BUFSIZ)
				{
					residueBinCode=cutAndGetResidue(&buffOfBits,BUFSIZ);
					fwrite(buffOfBits.arrayOfBits,sizeof(blockOfBits),BUFSIZ,out);
					if(ferror(out))
						return write_error;
					buffOfBits.countBits=0;
					free(buffOfBits.arrayOfBits);
					buffOfBits.arrayOfBits=NULL;
					catBinArr(&buffOfBits,&residueBinCode);
					free(residueBinCode.arrayOfBits);
					residueBinCode.arrayOfBits=NULL;

				}
				else
				{
					fwrite(buffOfBits.arrayOfBits,sizeof(blockOfBits),BUFSIZ,out);
					if(ferror(out))
						return write_error;
					buffOfBits.countBits=0;
					free(buffOfBits.arrayOfBits);
					buffOfBits.arrayOfBits=NULL;
				}
			}
		}
		if((feof(in))&&(buffOfBits.countBits!=0))
		{
			fwrite(buffOfBits.arrayOfBits,sizeof(blockOfBits),(buffOfBits.countBits/8)+((buffOfBits.countBits%8)!=0?1:0),out);
			if(ferror(out))
				return write_error;
			buffOfBits.countBits=0;
			free(buffOfBits.arrayOfBits);
			buffOfBits.arrayOfBits=NULL;
		}
	}
	destroyTree(&root);
	free(memoryBlockForDictionary);
	free(buff);
	free(dictionaryOfBits);
	return complete;
}

returnCode huffman_decode(FILE *in,FILE *out)
{
	int i;
	int fillingOfBuffer=0;
	int len;
	int countOfRead;
	char* buffOfWrite;
	char bit;
	bits buffOfRead;
	dictionaryElem* dictionary;
	node* nextNode;
	node* root;
	if(in==NULL)
		return read_error;
	if(out==NULL)
		return write_error;
	fread(&len,SIZE_OF_LENGTH_DICTIONARY,1,in);
	if(ferror(in))
	{return read_error;}
	dictionary=(dictionaryElem*)malloc(sizeof(dictionaryElem)*len);
	if(dictionary==NULL)
	{
		return not_enough_memory;
	}
	countOfRead=fread(dictionary,sizeof(dictionaryElem),len,in);

	if ((countOfRead!=len)||(ferror(in)))
	{
		free(dictionary);
		return read_error;
	}
	root=createTree(dictionary,len);
	nextNode = root; 
	if (root==NULL)
	{
		free(dictionary);
		return not_enough_memory;
	}
	buffOfWrite=(char*)malloc(sizeof(char)*BUFSIZ);
	if(buffOfWrite==NULL)
	{
		free(dictionary);
		destroyTree(&root);
		return not_enough_memory;
	}
	buffOfRead.arrayOfBits=(blockOfBits*)malloc(sizeof(blockOfBits)*BUFSIZ);
	if(buffOfRead.arrayOfBits==NULL)
	{
		free(buffOfWrite);
		free(dictionary);
		destroyTree(&root);
		return not_enough_memory;
	}
	while (!feof(in))
	{
		countOfRead=fread(buffOfRead.arrayOfBits,sizeof(blockOfBits),BUFSIZ,in);
		buffOfRead.countBits=countOfRead*8;
		for(i=0;i<buffOfRead.countBits;i++)
		{
			bit=getBit(i+1,buffOfRead);
			if(bit=='1')
			{
				if(nextNode->one!=NULL)
				{
					nextNode=nextNode->one;
					continue;
				}
				else
				{
					if((nextNode->zero==NULL))
					{
						buffOfWrite[fillingOfBuffer]=nextNode->charater;
						fillingOfBuffer++;	
						nextNode=root;
						if(fillingOfBuffer==BUFSIZ)
						{
							fwrite(buffOfWrite,sizeof(char),BUFSIZ,out);
							fillingOfBuffer=0;
							if(ferror(in))
							{
								free(buffOfRead.arrayOfBits);
								free(buffOfWrite);
								free(dictionary);
								destroyTree(&root);
								return write_error;
							}
						}
					}
					else
					{
						free(buffOfRead.arrayOfBits);
						free(buffOfWrite);
						free(dictionary);
						destroyTree(&root);
						return read_error;
					}
				}
			}
			if(bit=='0')
			{
				if((nextNode->zero!=NULL))
				{
					nextNode=nextNode->zero;
					continue;
				}
				else
				{
					if(nextNode->one==NULL)
					{
						buffOfWrite[fillingOfBuffer]=nextNode->charater;
						fillingOfBuffer++;	
						nextNode=root;
						if(fillingOfBuffer==BUFSIZ)
						{
							fwrite(buffOfWrite,sizeof(char),BUFSIZ,out);
							fillingOfBuffer=0;
							if(ferror(in))
							{
								free(buffOfRead.arrayOfBits);
								free(buffOfWrite);
								free(dictionary);
								destroyTree(&root);
								return write_error;
							}
						}
					}
					else
					{
						free(buffOfRead.arrayOfBits);
						free(buffOfWrite);
						free(dictionary);
						destroyTree(&root);
						return read_error;
					}
				}
			}
		}
		if((fillingOfBuffer>0)&&(feof(in)))
		{
			fwrite(buffOfWrite,sizeof(char),fillingOfBuffer,out);
			fillingOfBuffer=0;
			if(ferror(in))
			{
				free(buffOfRead.arrayOfBits);
				free(buffOfWrite);
				free(dictionary);
				destroyTree(&root);
				return write_error;
			}
		}
	}
	free(buffOfRead.arrayOfBits);
	free(buffOfWrite);
	free(dictionary);
	destroyTree(&root);

	return complete;

}

node* createTree(dictionaryElem* dictionary, int length)
{
	int i,j;
	node* newNode;
	node **nodes;
	nodes=(node**)malloc(sizeof(node*)*length);
	if(nodes==NULL)
		return NULL;
	for (i=0;i<length;i++)
	{
		newNode=(node*)malloc(sizeof(node));
		nodes[i]=newNode;
		if(nodes[i]==NULL)
		{
			for(j=0;j<i;j++)
			{
				destroyTree(&nodes[j]);
			}
			free(nodes);
			return NULL;
		}
		nodes[i]->charater=dictionary[i].elem;
		nodes[i]->probability=dictionary[i].probability;
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
			free(nodes);
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
	return nodes[0];
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

void createDictionaryOfBits(node* root,char* code,dictionaryOfBitsElem* dictionaryOfBits, int* length)
{
	if((root->zero == NULL) && (root->one== NULL))
	{
		dictionaryOfBits[*length].elem=root->charater;
		dictionaryOfBits[*length].code=stringToBits(code);
		(*length)++;
	}
	if(root->zero!= NULL){
		char temp[256];
		strcpy(temp, code);
		strcat(temp, "0");
		createDictionaryOfBits(root->zero, temp,dictionaryOfBits,length);
	}
	if(root->one!= NULL){
		char temp[256];
		strcpy(temp, code);
		strcat(temp, "1");
		createDictionaryOfBits(root->one,temp ,dictionaryOfBits,length);
	}
}