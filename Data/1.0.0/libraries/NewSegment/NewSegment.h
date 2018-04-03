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
#define DOT DIO10

#define T3CON_ENABLE_BIT 0x8000
#define T3CON_PRESCALER_BITS 0x0070


typedef enum 
{
	MODE_DIGIT,
	MODE_LOGIC,
	MODE_VOLTAGE
}SegmentMode;
typedef enum 
{
	LOGIC_HIGH,
	LOGIC_LOW,
	LOGIC_ERR
}LogicLevel;
class NewSegment
{
public:

	NewSegment();
	void initMultiplex(isrFunc myISR);
	void setNumber(int);
	void setMode(SegmentMode);
	void setState(LogicLevel);
	void multiplex();
	SegmentMode returnMode();
	void setVoltage(double);
	void toggleDot();
private:
	bool isDot = false;
	SegmentMode mode;
	char tempDig1 = '1', tempDig2 = '2';
	void setSegment(char d1);
	void virtualPort(char);
	void setDigits(char, char);
	bool wasMultiplex;
	
};

