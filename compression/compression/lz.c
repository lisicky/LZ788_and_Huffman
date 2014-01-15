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
			
				return i;
			
	}
	return 0;
}

returnCode lz78_encode(FILE* in, FILE* out)
{
	unsigned short n=0,prepreviousN=0;
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
	{
		free(buff);
		free(dictionary);
		return not_enough_memory;
	}
	dictionary[0].elem=0;
	dictionary[0].n=0;
	do
	{
	countOfRead= fread(buff,sizeof(char),BUFSIZ,in);
	if(ferror(in))
	{
		free(buff);
		free(dictionary);
		return read_error;
	}
	for(i=0;i<countOfRead;i++)
	{
		elem=buff[i];
		do
		{
		n=findInDictionary(dictionary,dictionaryLength,n+1,elem);
		} while ((dictionary[n].n!=prepreviousN)&&(n!=0));
		if(n==0)
		{
			dictionary[dictionaryLength].elem=elem;
			dictionary[dictionaryLength].n=prepreviousN;
			dictionaryLength++;
			n=0;
			prepreviousN=0;
		}
		else
		{
			prepreviousN=n;
		}
		if(dictionaryLength==USHRT_MAX)
			{
			countOfWrited=fwrite(dictionary,sizeof(dictionaryElem),dictionaryLength,out);
			if (countOfWrited!=dictionaryLength)
			{
				free(buff);
				free(dictionary);
				return write_error;
			}
			dictionaryLength=1;
			n=0;
			
		}
	}
	if((prepreviousN==n!=0)&&(feof(in)))
	{
		dictionary[dictionaryLength].elem=elem;
		dictionary[dictionaryLength].n=dictionary[prepreviousN].n;
			dictionaryLength++;
			n=0;
			prepreviousN=0;

	}
	if ((dictionaryLength<USHRT_MAX)&&(feof(in)))
		{
			countOfWrited=fwrite(dictionary,sizeof(dictionaryElem),dictionaryLength,out);
			if (countOfWrited!=dictionaryLength)
			{
				free(buff);
				free(dictionary);
				return write_error;
			}
			dictionaryLength=1;
			n=0;
			
		}
	}
	while(!feof(in));
	free(buff);
	free(dictionary);
	return complete;

}


returnCode lz78_decode(FILE* in, FILE* out)
{
	unsigned short n;
	int writedInBuff=0;
	int countOfRead;
	int countOfWrited;
	int stringLength=0;
	int i,j;
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
	{
		free(buff);
		free(dictionary);
		return not_enough_memory;
	}
	do
	{
		countOfRead=fread(dictionary,sizeof(dictionaryElem),USHRT_MAX,in);
		
		if(ferror(in))
		{
			free(buff);
			free(dictionary);
			return read_error;
		}
		for(i=1;i<countOfRead;i++)
		{
			stringLength=0;
			n=i;
				while(n!=0)
				{
					n=dictionary[n].n;
					stringLength++;
				}
				while (stringLength>0)
				{
					n=i;
					for(j=0;j<stringLength;j++)
					{
						elem=dictionary[n].elem;
						n=dictionary[n].n;
					}
					stringLength--;
					buff[writedInBuff]=elem;
					writedInBuff++;
					if(writedInBuff==BUFSIZ)
					{
						countOfWrited=fwrite(buff,sizeof(char),writedInBuff,out);
						if(countOfWrited!=writedInBuff)
						{
							free(buff);
							free(dictionary);
							return write_error;
						}
						writedInBuff=0;
					}
				}
		}
		if(feof(in)&&(writedInBuff<BUFSIZ))
		{
						countOfWrited=fwrite(buff,sizeof(char),writedInBuff,out);
						if(countOfWrited!=writedInBuff)
						{
							free(buff);
							free(dictionary);
							return write_error;
						}
						writedInBuff=0;
						
		}
	}while(!feof(in));
	free(buff);
	free(dictionary);
	return complete;

}