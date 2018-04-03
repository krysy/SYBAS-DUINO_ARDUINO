#include "NewSegment.h"

/*extern "C" {
#include "tinyprintf.h"
}*/


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

const int letters[] = {
						0b1110110,//H
						0b0110000,//I
						0b0111000,//L
						0b0111111,//O
						0b1111001,//E
						0b1010000//r
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
	pinMode(DOT, OUTPUT);
	wasMultiplex = false;
	mode = MODE_DIGIT;
}

SegmentMode NewSegment::returnMode() {
	return mode;
}
void NewSegment::setNumber(int number) {
	if (mode==MODE_DIGIT)
	{
		if (!(number<0 || number >255))
		{
			char hex[1];
			if (number<16) {
				sprintf(hex, "%X", number);
				setDigits('0', hex[0]);
			}
			else {
				sprintf(hex, "%X", number);
				setDigits(hex[0], hex[1]);
			}
		}
	}
}

void NewSegment::setState(LogicLevel desiredLevel) {
	if (mode==MODE_LOGIC)
	{
		switch (desiredLevel)
		{
		case LOGIC_HIGH:
			tempDig1 = 'H';
			tempDig2 = 'I';
			break;
		case LOGIC_LOW:
			tempDig1 = 'L';
			tempDig2 = 'O';
			break;
		case LOGIC_ERR:
			tempDig1 = 'E';
			tempDig2 = 'R';
			break;
		default:
			break;
		}
	}
}

void NewSegment::setVoltage(double volts) {
	if (mode==MODE_VOLTAGE)
	{
		char buff[5];
		sprintf(buff,"%0.2f",volts);
		setDigits(buff[0], buff[2]);
	}
}
void NewSegment::setMode(SegmentMode desiredMode) {
	mode = desiredMode;
	
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
	case 'H':
		virtualPort(letters[0]);
		break;
	case 'I':
		virtualPort(letters[1]);
		break;
	case 'L':
		virtualPort(letters[2]);
		break;
	case 'O':
		virtualPort(letters[3]);

		break;
	case 'R':
		virtualPort(letters[5]);
		break;
		break;
	default:
		break;
	}
}
/*
void NewSegment::initMultiplex(isrFunc myISR) {
	wasMultiplex = false;
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
*/
void NewSegment::toggleDot() {
	isDot = !isDot;
}

void NewSegment::multiplex() {
	if (wasMultiplex == false)
	{
		if (mode==MODE_VOLTAGE && isDot==true)
		{
			digitalWrite(DOT, HIGH);
		}
		else
		{
			digitalWrite(DOT, LOW);
		}
		setSegment(tempDig1);
		digitalWrite(mpx, 0);
		wasMultiplex = true;
	}
	else
	{
		if (mode == MODE_VOLTAGE && isDot==true)
		{
			digitalWrite(DOT, LOW);
		}
		else
		{
			digitalWrite(DOT, LOW);
		}
		setSegment(tempDig2);
		digitalWrite(mpx, 1);
		wasMultiplex = false;
	}
}