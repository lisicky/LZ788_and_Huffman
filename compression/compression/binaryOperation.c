#include "binaryOperation.h"
#include <string.h>
#include <malloc.h>
bits stringToBits(char* stringOfBits)
{
	int i;
	int len;
	bits bitsArray;
	bitsArray.countBits=0;
	bitsArray.arrayOfBits=NULL;
	len=strlen(stringOfBits);
	for(i=0;i<len;i++)
	{
		if(addBit(stringOfBits[i],&bitsArray)!=1)
		{
			bitsArray.countBits=0;
			free(bitsArray.arrayOfBits);
			bitsArray.arrayOfBits==NULL;
		}
	}
		bitsArray.countBits=len;
		return bitsArray;

}

int addBit (char bit, bits *bitsArray)
{
	unsigned convertedBit=0;
	blockOfBits* newBlock;
	int residue;
	int i;
	if(bitsArray==NULL)
		return -1;
	residue=bitsArray->countBits%8;
	if(bit=='1')
	{
		convertedBit=1;
	}
	else
	{
		if(bit=='0')
			convertedBit=0;
		else
		{
			return -1;
		}
	}
	if((residue)!=0)
	{
	switch (residue)
	{
		case 1:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit8=convertedBit;bitsArray->countBits++;break;
		case 2:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit7=convertedBit;bitsArray->countBits++;break;
		case 3:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit6=convertedBit;bitsArray->countBits++;break;
		case 4:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit5=convertedBit;bitsArray->countBits++;break;
		case 5:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit4=convertedBit;bitsArray->countBits++;break;
		case 6:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit3=convertedBit;bitsArray->countBits++;break;
		case 7:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit2=convertedBit;bitsArray->countBits++;break;
	}
	}
	else
	{
		newBlock=(blockOfBits*)malloc(sizeof(blockOfBits)*((bitsArray->countBits/8)+1));
		for(i=0;i<(bitsArray->countBits/8);i++)
		{
			newBlock[i].block=bitsArray->arrayOfBits[i].block;
		}
		if(newBlock==NULL)
			return -1;
		free(bitsArray->arrayOfBits);
		bitsArray->arrayOfBits=newBlock;
		bitsArray->countBits++;
		bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit1=convertedBit;
	}
	return 1;
}