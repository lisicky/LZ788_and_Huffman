#include "lz.h"

unsigned short findInDictionary(dictionaryElem* dictionary,unsigned short length,unsigned short startIndex, char elem)
{
	unsigned short i;
	if(dictionary==NULL)
		fprintf(stderr,"ERROR: dictionary is null");
		return 0;
	for(i=startIndex;i<length;i++)
	{
		if(dictionary[i].elem==elem)
			return i;
	}
	return 0;
}
