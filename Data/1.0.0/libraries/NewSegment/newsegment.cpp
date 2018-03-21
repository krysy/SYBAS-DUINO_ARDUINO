#include "NewSegment.h"
extern "C" {
#include "tinyprintf.h"
}


const int digits[] = { 0x3F, //0
						0x06,//1
						0x5B,//2
						0x4F,//3
						0x66,//4
						0x6D,//5
						0x7D,//6
						0x07,//7
						0x7F,//8
						0x6F,//9
						0x77,//A
						0x7C,//B
						0x39,//C
						0x5E,//D
						0x79,//E
						0x71//F
};


NewSegment::NewSegment()
{
	pinMode(A, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(C, OUTPUT);
	pinMode(D, OUTPUT);
	pinMode(E, OUTPUT);
	pinMode(F, OUTPUT);
	pinMode(G, OUTPUT);
	pinMode(mpx, OUTPUT);
	temp = false;
}


void NewSegment::setNumber(int number) {
	if (!(number<0 || number >255))
	{
		char hex[1];
		if (number<16) {
			tfp_sprintf(hex, "%X", number);
			setDigits('0', hex[0]);
		}
		else {
			tfp_sprintf(hex, "%X", number);
			setDigits(hex[0], hex[1]);
		}
	}
}
void NewSegment::setDigits(char cr1, char cr2) {
	tempDig1 = cr1;
	tempDig2 = cr2;
}

void NewSegment::virtualPort(char cr) {
	digitalWrite(A, CHECK_BIT(cr, 0));
	digitalWrite(B, CHECK_BIT(cr, 1));
	digitalWrite(C, CHECK_BIT(cr, 2));
	digitalWrite(D, CHECK_BIT(cr, 3));
	digitalWrite(E, CHECK_BIT(cr, 4));
	digitalWrite(F, CHECK_BIT(cr, 5));
	digitalWrite(G, CHECK_BIT(cr, 6));
}

void NewSegment::setSegment(char d1) {
	switch (d1) {
	case '0':
		virtualPort(digits[0]);
		break;
	case '1':
		virtualPort(digits[1]);
		break;
	case '2':
		virtualPort(digits[2]);
		break;
	case '3':
		virtualPort(digits[3]);
		break;
	case '4':
		virtualPort(digits[4]);
		break;
	case '5':
		virtualPort(digits[5]);
		break;
	case '6':
		virtualPort(digits[6]);
		break;
	case '7':
		virtualPort(digits[7]);
		break;
	case '8':
		virtualPort(digits[8]);
		break;
	case '9':
		virtualPort(digits[9]);
		break;
	case 'A':
		virtualPort(digits[10]);
		break;
	case 'B':
		virtualPort(digits[11]);
		break;
	case 'C':
		virtualPort(digits[12]);
		break;
	case 'D':
		virtualPort(digits[13]);
		break;
	case 'E':
		virtualPort(digits[14]);
		break;
	case 'F':
		virtualPort(digits[15]);
		break;
	default:
		break;
	}
}

void NewSegment::initMultiplex(isrFunc myISR) {
	temp = false;
	T3CONCLR = T3CON_ENABLE_BIT;
	T3CONCLR = T3CON_PRESCALER_BITS;
	TMR3 = 128;
	PR3 = 255;
	T3CONSET = T3CON_ENABLE_BIT;

	setIntVector(_TIMER_3_VECTOR, myISR);
	setIntPriority(_TIMER_3_VECTOR, 4, 0);

	clearIntFlag(_TIMER_3_IRQ);

	setIntEnable(_TIMER_3_IRQ);
}

void NewSegment::multiplex() {
	if (temp == false)
	{
		setSegment(tempDig1);
		digitalWrite(mpx, 0);
		temp = true;
	}
	else
	{
		setSegment(tempDig2);
		digitalWrite(mpx, 1);
		temp = false;
	}
	TMR3 = 2048;
	clearIntFlag(_TIMER_3_IRQ);
}