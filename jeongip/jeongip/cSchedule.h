// ****** cSchedule.h ******
#pragma once
#include "cDate.h"

class cSchedule :
	public cDate
{
protected:
	// @ 일정 이름 및 카테고리명
	string sName;
	string sCategory;

	// @ 일정의 타입
	int sType = 0;
	/*
	 - sType = 1	::  반복성  일정 (매 년 같은 월일)
	 - sType = 2	::  반복성  일정 (매 월 같은 일)
	 - sType = 3	::  반복성  일정 (매 주 같은 요일)
	 - sType = 4	::	기간성  일정 (반복 X)
	*/

	// @ 반복 주기
	pair<int, int> rAnnual = { 0,0 };	// 연 반복 주기
	int rMontly = 0;					// 월 반복 주기
	int rWeekly = 0;					// 주 반복 주기 [일 = 0 ~ 월 = 6]

	// @ 스케줄 완료 여부
	bool sIsDone = false;

public:
	// @ 생성자s
	cSchedule();
	~cSchedule();

	// @ 일정 추가
	void makeSchedule();

	// @ 일정 예외처리 함수
	// bool isRightSchedule(); : ProtoType, Override needed
	bool isRightSchedule(string name);
	bool isRightSchedule(int type);
	bool isRightSchedule(int year, int month);
	bool isRightSchedule(bool isS, int year, int month, int day, int hour, int min);

	// @ get methods
	string getsName() const;
	string getsCategory() const;
	int getsType() const;
	pair<int, int> getrAnnual() const;
	int getrMonthly() const;
	int getrWeekly() const;
	string getDayW(int weekly) const;

	// @ set methods
	void setsName(const string& name);
	void setRepeat(const int& type);
	void setIsDone(const bool& is);
	void setsType(const int& type);
};

