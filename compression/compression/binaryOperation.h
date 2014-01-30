#define END_STRING_OF_BITS '2'
typedef union blockOfBits
{
	char block;
	struct elements
	{
		unsigned bit1:1;
        unsigned bit2:1;
        unsigned bit3:1;
        unsigned bit4:1;
        unsigned bit5:1;
        unsigned bit6:1;
        unsigned bit7:1;	
        unsigned bit8:1; 
	};
}blockOfBits; 

typedef struct bits
{
	short countBits;
	blockOfBits* arrayOfBits;
}bits;

typedef struct dictionaryOfBitsElem
{
	bits code;
	char elem;
}dictionaryOfBitsElem;

int addBit (char bit, bits bitsArray);
bits findCode(char character);
bits concatenateBitsArray(bits bitsArrayOne, bits bitsArrayTwo);
char getBit(short number, bits bitsArray);
bits stringToBits(char stringOfBits);