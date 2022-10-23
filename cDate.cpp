// ****** cDate.cpp ******
#include "cDate.h"

cDate::cDate()
{
}


cDate::~cDate()
{
}

bool cDate::isAfterNow(int year, int month, int day, int hour, int min)
{
	srand((unsigned)time(NULL));
	time_t t;
	struct tm* now;

	time(&t);
	now = localtime(&t);

	int yearNow = 1900 + now->tm_year;
	int monthNow = 1 + now->tm_mon;
	int dayNow = now->tm_mday;
	int hourNow = now->tm_hour;
	int minNow = now->tm_min;

	if (year == yearNow) {
		if (month == monthNow) {
			if (day == dayNow) {
				if (hour == hourNow) {
					if (min < minNow)
						return false;
				}
				else if (hour < hourNow)
					return false;
			}
			else if (day < dayNow)
				return false;
		}
		else if (month < monthNow)
			return false;
	}
	else if (year < yearNow)
		return false;
	else
		return true;
}

bool cDate::isAfterStart(int year, int month, int day, int hour, int min)
{
	if (year == sYear) {
		if (month == sMonth) {
			if (day == sDay) {
				if (hour == sHour) {
					if (min < sMin)
						return false;
				}
				else if (hour < sHour)
					return false;
			}
			else if (day < sDay)
				return false;
		}
		else if (month < sMonth)
			return false;
	}
	else if (year < sYear)
		return false;
	else
		return true;
}

int cDate::getDayOfWeek(int year, int month, int day)
{
	// [0~6] = [ÀÏ~¿ù]
	if (month < 3) {
		year -= 1;
		month += 12;
	}
	return (year + (year / 4) - (year / 100) + (year / 400) + (13 * month + 8) / 5 + day) % 7;
}

bool cDate::IsLeafYear(const int& year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return true;
	else
		return false;
}

int cDate::getsYear() const
{
	return this->sYear;
}

int cDate::getsMonth() const
{
	return this->sMonth;
}

int cDate::geteYear() const
{
	return this->eYear;
}

int cDate::geteMonth() const
{
	return this->eMonth;
}

int cDate::geteDay() const
{
	return this->eDay;
}

int cDate::getsDay() const
{
	return this->sDay;
}

int cDate::getsHour() const
{
	return this->sHour;
}

int cDate::getsMin() const
{
	return this->sMin;
}

void cDate::setsTime(const int& year, const int& month, const int& day, const int& hour, const int& min)
{
	this->sYear = year;
	this->sMonth = month;
	this->sDay = day;
	this->sHour = hour;
	this->sMin = min;
}

void cDate::seteTime(const int& year, const int& month, const int& day, const int& hour, const int& min)
{
	this->eYear = year;
	this->eMonth = month;
	this->eDay = day;
	this->eHour = hour;
	this->eMin = min;
}