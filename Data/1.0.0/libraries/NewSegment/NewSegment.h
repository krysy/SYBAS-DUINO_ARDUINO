#include <Arduino.h>


#define CHECK_BIT(var,pos) !!((var) & (1<<(pos)))
#define A DIO11
#define B DIO12
#define C DIO13
#define D DIO2
#define E DIO3
#define F DIO7
#define G DIO8
#define mpx	DIO9
#define T3CON_ENABLE_BIT 0x8000
#define T3CON_PRESCALER_BITS 0x0070
class NewSegment
{

	

public:
	NewSegment();
	void initMultiplex(isrFunc myISR);
	void setNumber(int);
	void multiplex();
private:
	char tempDig1 = '1', tempDig2 = '2';
	void setSegment(char d1);
	void virtualPort(char);
	void setDigits(char, char);
	bool temp;

};

