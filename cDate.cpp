// ****** cDate.cpp ******
#include "cDate.h"



cDate::cDate()
{
}


cDate::~cDate()
{
}

void cDate::printNow()
{
	bool isOn = true;
	srand((unsigned)time(NULL));

	time_t t;
	char* str;

	while (isOn) {
		time(&t);
		str = ctime(&t);
		cout << "현재 시간 : " << str;
		Sleep(1000);
		system("cls");
	}
}

void cDate::applyLeafYear(const int& year)
{
	// isLeafYear UPDATE
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		this->isLeafYear = true;
	else
		this->isLeafYear = false;

	// Day/Month UPDATE
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeafYear ? 29 : 28;
	this->daysofMonth = m;
	// cout << m[1];
}