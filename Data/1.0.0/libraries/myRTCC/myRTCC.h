#pragma once

class myRTCC
{
public:
	myRTCC();
	void clearRAM();
	int getSeconds();
	int getMinutes();
	int getHours();
	int getDay();
	int getMonth();
	int getYear();
	int getDate();
	String getDayInString();
	String getMonthInString();

	void setSeconds(int);
	void setMinutes(int);
	void setHours(int);
	void setDay(int);
	void setDate(int);
	void setMonth(int);
	void setYear(int);

	void setEverything(int seconds,int minutes,int hours,int weekday,int date, int month, int year);

	void unlockEEPROM();
	void lockEEPROM();
	void writeEEPROM(char,char);
	char readEEPROM(char);
private:
	void writeRegister(char reg, char dat);
	char readRegister(char reg);
	byte bcdToDec(byte val);
	byte decToBcd(byte val);
};

