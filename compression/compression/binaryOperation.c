#include "binaryOperation.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>
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
			bitsArray.arrayOfBits=NULL;
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
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit7=convertedBit;bitsArray->countBits++;break;
		case 2:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit6=convertedBit;bitsArray->countBits++;break;
		case 3:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit5=convertedBit;bitsArray->countBits++;break;
		case 4:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit4=convertedBit;bitsArray->countBits++;break;
		case 5:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit3=convertedBit;bitsArray->countBits++;break;
		case 6:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit2=convertedBit;bitsArray->countBits++;break;
		case 7:
			bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit1=convertedBit;bitsArray->countBits++;break;
		}
	}
	else
	{
		newBlock=(blockOfBits*)malloc(sizeof(blockOfBits)*((bitsArray->countBits/8)+1));
		if(newBlock==NULL)
			return -1;
		for(i=0;i<(bitsArray->countBits/8);i++)
		{
			newBlock[i].block=bitsArray->arrayOfBits[i].block;
		}
		free(bitsArray->arrayOfBits);
		bitsArray->arrayOfBits=newBlock;
		if(bitsArray->countBits==0)
			bitsArray->arrayOfBits[0].block=0;
		bitsArray->countBits++;
		bitsArray->arrayOfBits[bitsArray->countBits/8].elements.bit8=convertedBit;
	}
	return 1;
}

char getBit(int number, bits bitsArray)
{
	int residue;
	int index;
	index=number/8;
	residue=number%8;
	if(bitsArray.countBits<number)
		return '\0';
	if(number==0)
		return '\0';
	switch (residue)
	{

	case 0:
		if(bitsArray.arrayOfBits[index-1].elements.bit1)
			return '1';
		else
		{
			return '0';
		}
	case 1:
		if(bitsArray.arrayOfBits[index].elements.bit8)
			return '1';
		else
		{
			return '0';
		}
	case 2:
		if(bitsArray.arrayOfBits[index].elements.bit7)
			return '1';
		else
		{
			return '0';
		}
	case 3:
		if(bitsArray.arrayOfBits[index].elements.bit6)
			return '1';
		else
		{
			return '0';
		}
	case 4:
		if(bitsArray.arrayOfBits[index].elements.bit5)
			return '1';
		else
		{
			return '0';
		}
	case 5:
		if(bitsArray.arrayOfBits[index].elements.bit4)
			return '1';
		else
		{
			return '0';
		}
	case 6:
		if(bitsArray.arrayOfBits[index].elements.bit3)
			return '1';
		else
		{
			return '0';
		}
	case 7:
		if(bitsArray.arrayOfBits[index].elements.bit2)
			return '1';
		else
		{
			return '0';
		}
	default: return '\0';
	}
}

void catBinArr(bits* bitsArrayOne, bits* bitsArrayTwo)
{
	int i;
	char bit;
	if(bitsArrayTwo!=NULL)
	{
		if(bitsArrayOne==NULL)
		{
			bitsArrayOne=bitsArrayTwo;
		}
		else
		{
			for(i=0;i<bitsArrayTwo->countBits;i++)
			{
				bit=getBit(i+1,*bitsArrayTwo);
				addBit(bit,bitsArrayOne);
			}
		}
	}
}

bits cutAndGetResidue(bits* arrayOfBits, int countByteToCut)
{
	bits arrayOfBitsReside;
	int residue;
	int len;
	int i;
	char bit;
	arrayOfBitsReside.countBits=0;
	arrayOfBitsReside.arrayOfBits=NULL;
	len=arrayOfBits->countBits-(countByteToCut*8);
	if(len<=0)
		return arrayOfBitsReside;
	residue = len%8;
	arrayOfBitsReside.arrayOfBits=(blockOfBits*)malloc(sizeof(blockOfBits)*((len/8)+1));
	if(arrayOfBitsReside.arrayOfBits==NULL)
		return arrayOfBitsReside;
	arrayOfBitsReside.countBits=len;
	for(i=arrayOfBits->countBits-len+8;i<=arrayOfBits->countBits;i++)
	{
		bit=getBit(i,*arrayOfBits);
		addBit(bit,&arrayOfBitsReside);
	}
	arrayOfBits->countBits-=len;
	return arrayOfBitsReside;
}

bits* findCode(char character, dictionaryOfBitsElem* dictionary,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		if(dictionary[i].elem==character)
			return &dictionary[i].code;
	}
	return NULL;
}