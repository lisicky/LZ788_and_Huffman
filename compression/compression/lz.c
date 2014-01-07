#include "lz.h"
#include <malloc.h> 
#include <limits.h>
#include <stdlib.h>


unsigned short findInDictionary(dictionaryElem* dictionary,int length,unsigned short startIndex, char elem)
{
	unsigned short i;
	if(dictionary==NULL)
	{
		fprintf(stderr,"ERROR: dictionary is null");
		exit(-1);
	}
	for(i=startIndex;i<length;i++)
	{
		if(dictionary[i].elem==elem)
			if(startIndex==i)
				continue;
			else
			{
				return i;
			}
			
	}
	return 0;
}

returnCode lz78_encode(FILE* in, FILE* out)
{
	unsigned short n=1;
	int dictionaryLength=1;
	int countOfRead;
	int countOfWrited;
	int i;
	char elem;
	char* buff;
	dictionaryElem* dictionary;
	if(in==NULL)
		return read_error;
	if(out==NULL)
		return write_error;
	buff= (char*)malloc(sizeof(char)*BUFSIZ);
	dictionary=(dictionaryElem*)malloc(sizeof(dictionaryElem)*USHRT_MAX);
	if ((buff==NULL)||(dictionary==NULL))
		return not_enough_memory;
	dictionary[0].elem=0;
	dictionary[0].n=0;
	do
	{
	countOfRead= fread(buff,sizeof(char),BUFSIZ,in);
	if(ferror(in))
		return read_error;
	for(i=0;i<countOfRead;i++)
	{
		elem=buff[i];
		n=findInDictionary(dictionary,dictionaryLength,n,elem);
		if(n==0)
		{
			dictionary[dictionaryLength].elem=elem;
			dictionary[dictionaryLength].n=n;
			dictionaryLength++;
			n=1;
		}
		if(dictionaryLength==USHRT_MAX)
			{
			countOfWrited=fwrite(dictionary,sizeof(dictionaryElem),dictionaryLength,out);
			if (countOfWrited!=(sizeof(dictionaryElem)*dictionaryLength))
				write_error;
			dictionaryLength=1;
			n=1;
			
		}
	}
	if ((dictionaryLength<USHRT_MAX)&&(feof(in)))
		{
			countOfWrited=fwrite(dictionary,sizeof(dictionaryElem),dictionaryLength,out);
			if (countOfWrited!=(sizeof(dictionaryElem)*dictionaryLength))
				write_error;
			dictionaryLength=1;
			n=1;
			
		}
	}
	while(!feof(in));
	return complete;

}