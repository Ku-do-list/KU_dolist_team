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
	// @ ���� �ð�
	time_t temp;
	struct tm* timeinfo;

	// @ 12���� �� �ϼ� ���� (���� ���)
	int* daysofMonth;

	// @ �ݺ� ������ ���� �� data
	int repeatAnnual = -1;
	int repeatMonthly = -1;
	int repeatWeekly = -1;

protected:
	// @ ������ ���� �ð�
	int sYear, sMonth, sDay, sHour, sMin;

	// @ ������ ���� �ð�
	int eYear, eMonth, eDay, eHour, eMin;

	// @ ���� üũ
	bool isLeafYear = false;

public:

	cDate();
	~cDate();

	// @ ���� �ð��� ��
	bool isAfterNow(int year, int month, int day, int hour, int min);

	// @ ���� �ð��� �� in �ݺ�����
	bool isAfterStart(int year, int month, int day, int hour, int min);

	// @ �ش��ϴ� ��¥ ���� ���ϱ�
	int getDayOfWeek(int year, int month, int day);

	// @ ���� ���� �Ǵ�
	bool IsLeafYear(const int& year);

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

