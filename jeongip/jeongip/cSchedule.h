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
	pair<int, int> rAnnual = { 0,0 };	// �� �ݺ� �ֱ�
	int rMontly = 0;					// �� �ݺ� �ֱ�
	int rWeekly = 0;					// �� �ݺ� �ֱ� [�� = 0 ~ �� = 6]

	// @ ������ �Ϸ� ����
	bool sIsDone = false;

public:
	// @ ������s
	cSchedule();
	~cSchedule();

	// @ ���� �߰�
	void makeSchedule();

	// @ ���� ����ó�� �Լ�
	// bool isRightSchedule(); : ProtoType, Override needed
	bool isRightSchedule(string name);
	bool isRightSchedule(int type);
	bool isRightSchedule(bool isS, int year, int month, int day, int hour, int min);

};

