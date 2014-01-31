#ifndef BIT_OPERATION_H
#define BIT_OPERATION_H
#pragma pack (push, 1)
typedef struct eightBits
	{
		unsigned char bit1:1;
        unsigned char bit2:1;
        unsigned char bit3:1;
        unsigned char bit4:1;
        unsigned char bit5:1;
        unsigned char bit6:1;
        unsigned char bit7:1;	
        unsigned char bit8:1; 
	};

typedef union blockOfBits
{   
	char block;
	struct eightBits elements;
}blockOfBits; 
#pragma pack (pop)
typedef struct bits
{
	int countBits;
	blockOfBits* arrayOfBits;
}bits;

typedef struct dictionaryOfBitsElem
{
	bits code;
	char elem;
}dictionaryOfBitsElem;

int addBit (char bit, bits* bitsArray);
bits* findCode(char character, dictionaryOfBitsElem* dictionary,int len);
void catBinArr(bits* bitsArrayOne, bits* bitsArrayTwo);
char getBit(int number, bits bitsArray);
bits stringToBits(char* stringOfBits);
bits cutAndGetResidue(bits* arrayOfBits, int countByteToCut);
#endif