// ****** cSchedule.h ******
#pragma once
#include "cDate.h"

class cSchedule :
	public cDate
{
private:
	// @ ���� �̸� �� ī�װ���
	string sName;
	string sCategory;

	// @ ������ Ÿ��
	int sType = 0;
	/*
	 - sType = 1	::  �ݺ���  ���� (�� �� ���� ����)
	 - sType = 2	::  �ݺ���  ���� (�� �� ���� ��)
	 - sType = 3	::  �ݺ���  ���� (�� �� ���� ����)
	 - sType = 4	::	�Ⱓ��  ���� (�ݺ� X)
	*/

	// @ �ݺ� �ֱ�
	pair<int, int> rAnnual = { 0,0 };	// ���ݺ�
	int rMontly = 0;
	int rWeekly = 0;

	// @ ������ �Ϸ� ����
	bool sIsDone = false;

public:
	// @ ������s
	cSchedule();
	~cSchedule();

	// @ ���� �߰�
	void makeSchedule();

	// @ ���� ����ó�� �Լ�
	//int isRightSchedule();
	int isRightSchedule(string name);
	int isRightSchedule(int type);
	int isRightSchedule(int year, int month, int day, int hour, int min);
};
