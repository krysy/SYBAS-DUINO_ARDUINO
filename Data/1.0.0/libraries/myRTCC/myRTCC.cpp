#include <Arduino.h>
#include "myRTCC.h"

#define EEREAD	0b00000011
#define EEWRITE	0b00000010
#define EEWRDI	0b00000100
#define EEWREN	0b00000110
#define SRREAD	0b00000101
#define SRWRITE	0b00000001
#define READ	0b00010011 //0x13
#define WRITE	0b00010010 //0x12
#define UNLOCK	0b00010100
#define IDWRITE	0b00110010
#define IDREAD	0b00110011
#define CLRRAM	0b01010100

#define RTCYEAR  0x07
#define RTCMTH	 0x06
#define RTCDATE  0x05
#define RTCWKDAY 0x04
#define RTCHOUR	 0x03
#define RTCMIN	 0x02
#define RTCSEC	 0x01

#define RTCC_CONTROL_REG 0x08
#define RTCC_CONFIG 0b11111111

#define SDAm	DIO27	
#define SCLm	DIO28
#define CSm		DIO29

myRTCC::myRTCC()
{
	pinMode(CSm, OUTPUT);
	pinMode(SDAm, OUTPUT);
	pinMode(SCLm, OUTPUT);
	writeRegister(RTCSEC, 0xff);
	writeRegister(RTCC_CONTROL_REG, 0x00);
	writeRegister(RTCWKDAY, 0xFF);
}
/*Helper functions*/
byte myRTCC::bcdToDec(byte val)
{
	return((val / 16 * 10) + (val % 16));
}

byte myRTCC::decToBcd(byte val)
{
	return((val / 10 * 16) + (val % 10));
}

/*Low level functions*/
void myRTCC::writeRegister(char reg, char dat) {
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, WRITE);
	shiftOut(SDAm, SCLm, MSBFIRST, reg);
	shiftOut(SDAm, SCLm, MSBFIRST, dat);
	digitalWrite(CSm, 1);
}

char myRTCC::readRegister(char reg) {
	char temp;
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, READ);
	shiftOut(SDAm, SCLm, MSBFIRST, reg);
	digitalWrite(SDAm, LOW);
	pinMode(SDAm, INPUT);
	temp = shiftIn(SDAm, SCLm, MSBFIRST);
	digitalWrite(CSm, 1);
	return temp;
}

void myRTCC::clearRAM() {
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, CLRRAM);
	shiftOut(SDAm, SCLm, MSBFIRST, 0xff);
	digitalWrite(CSm, 1);
}

/*RTC Functions*/

//getter functions
int myRTCC::getSeconds() {
	return bcdToDec(readRegister(RTCSEC) & 0b01111111);
}

int myRTCC::getMinutes() {
	return bcdToDec(readRegister(RTCMIN) & 0b01111111);
}

int myRTCC::getHours() {
	return bcdToDec(readRegister(RTCHOUR) & 0b00111111);
}

int myRTCC::getDay() {
	return bcdToDec(readRegister(RTCWKDAY) & 0b00000011);
}

int myRTCC::getDate() {
	return bcdToDec(readRegister(RTCDATE) & 0b00111111);
}

int myRTCC::getMonth() {
	return bcdToDec(readRegister(RTCMTH) & 0b00011111);
}

int myRTCC::getYear() {
	return bcdToDec(readRegister(RTCYEAR));
}

//setter functions

void myRTCC::setSeconds(int secs) {
	writeRegister(RTCSEC, decToBcd(secs)|readRegister(RTCSEC) & 0b10000000);
}
void myRTCC::setMinutes(int mins) {
	writeRegister(RTCMIN, decToBcd(mins)|readRegister(RTCMIN) & 0b10000000);
}
void myRTCC::setHours(int hours) {
	writeRegister(RTCHOUR, decToBcd(hours)|readRegister(RTCHOUR) & 0b11000000);
}

void myRTCC::setDay(int day) {
	writeRegister(RTCWKDAY, decToBcd(day) | readRegister(RTCWKDAY) & 0b11111100);
}

void myRTCC::setDate(int date) {
	writeRegister(RTCDATE, decToBcd(date)|readRegister(RTCDATE) & 0b11000000);
}

void myRTCC::setMonth(int month) {
	writeRegister(RTCMTH, decToBcd(month) | readRegister(RTCMTH) & 0b11100000);
}

void myRTCC::setYear(int year) {
	writeRegister(RTCYEAR, decToBcd(year));
}

void myRTCC::setEverything(int seconds, int minutes, int hours, int weekday, int date, int month, int year) {
	setSeconds(seconds);
	setMinutes(minutes);
	setHours(hours);
	setDay(weekday);
	setDate(date);
	setMonth(month);
	setYear(year);
}

String myRTCC::getMonthInString() {
	switch (getMonth())
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";

	default:
		return "Not defined";
	}
}
String myRTCC::getDayInString() {
	char temp = readRegister(RTCWKDAY);
	switch (bcdToDec(temp & 0b00000011))
	{
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	case 7:
		return "Sunday";
	default:
		return "Not defined";
	}
}

/*EEPROM*/

void myRTCC::unlockEEPROM() {
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, EEWREN);
	digitalWrite(CSm, 1);
}
void myRTCC::lockEEPROM() {
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, EEWRDI);
	digitalWrite(CSm, 1);
}

char myRTCC::readEEPROM(char addr) {
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, EEREAD);
	shiftOut(SDAm, SCLm, MSBFIRST, addr);
	digitalWrite(SDAm, LOW);
	pinMode(SDAm, INPUT);
	return shiftIn(SDAm, SCLm, MSBFIRST);
	digitalWrite(CSm, 1);
}
void myRTCC::writeEEPROM(char addr, char data) {
	pinMode(SDAm, OUTPUT);
	digitalWrite(CSm, 0);
	shiftOut(SDAm, SCLm, MSBFIRST, EEWRITE);
	shiftOut(SDAm, SCLm, MSBFIRST, addr);
	shiftOut(SDAm, SCLm, MSBFIRST, data);
	digitalWrite(CSm, 1);
}