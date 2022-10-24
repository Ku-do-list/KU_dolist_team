// ****** cDate.h ******
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif // !DBG_NEW
#endif
#include <ctime>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <cstdlib>
#include <conio.h>
#include <utility>

using namespace std;

class cDate
{
private:
	// @ 현재 시간
	time_t temp;
	struct tm* timeinfo;

	// @ 12달의 각 일수 저장 (윤년 계산)
	int* daysofMonth;

	// @ 반복 일정의 유형 별 data
	int repeatAnnual = -1;
	int repeatMonthly = -1;
	int repeatWeekly = -1;

protected:
	// @ 일정의 시작 시각
	int sYear, sMonth, sDay, sHour, sMin;

	// @ 일정의 종료 시각
	int eYear, eMonth, eDay, eHour, eMin;

	// @ 윤년 체크
	bool isLeafYear = false;

public:

	cDate();
	~cDate();

	// @ 현재 시각과 비교
	bool isAfterNow(int year, int month, int day, int hour, int min);

	// @ 시작 시각과 비교 in 반복일정
	bool isAfterStart(int year, int month, int day, int hour, int min);

	// @ 해당하는 날짜 요일 구하기
	int getDayOfWeek(int year, int month, int day);

	// @ 윤년 여부 판단
	bool IsLeafYear(const int& year);

	//@ get methods
	int getsYear() const;
	int getsMonth() const;
	int getsDay() const;

	int geteYear() const;
	int geteMonth() const;
	int geteDay() const;

	int getsHour() const;
	int getsMin() const;

	// @ set methods
	void setsTime(const int& year, const int& month, const int& day, const int& hour, const int& min);
	void seteTime(const int& year, const int& month, const int& day, const int& hour, const int& min);

	// @ and Windows API Functions . . .
	void gotoxy(int x, int y) {
		COORD pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	void setCursorView(bool visible) {
		CONSOLE_CURSOR_INFO cursor = { 1, visible };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	}
};