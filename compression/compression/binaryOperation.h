#define END_STRING_OF_BITS '2'

typedef struct eightBits
	{
		unsigned bit1:1;
        unsigned bit2:1;
        unsigned bit3:1;
        unsigned bit4:1;
        unsigned bit5:1;
        unsigned bit6:1;
        unsigned bit7:1;	
        unsigned bit8:1; 
	}eightBits;

typedef union blockOfBits
{
	char block;
	eightBits elements;
}blockOfBits; 

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
bits* cutAndGetResidue(bits* arrayOfBits, int countByteToCut);