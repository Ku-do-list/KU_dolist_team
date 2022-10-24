// ****** cSchedule.h ******
#pragma once
#include "cDate.h"
#include <vector>
#include <fstream>

class cSchedule :
	public cDate
{
private:
	// @ ���� �̸� �� ī�װ���
	string sName;
	string sCategory;
	ofstream writeFileList; //txt ���� ��Ʈ��
	ofstream writeFileCategory;

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

	bool duplicate = false;
	int categoryNum = 3;

	// @ ���� �߰�
	void makeSchedule(string* category, int& categorySize);
	void manageCategory(string* category, int& categorySize);
	string s = "";

	// @ ���� ����
	void deleteSchedule();
	bool isSign(string str);

	// @ ���� ����
	void edit_Schedule();
	// @ ���� ���� ����ó�� �Լ� 
	int showmenu_edit();

	// @ ���� ����ó�� �Լ�
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
	void setRepeat(const int& type, const cSchedule& _list);
	void setIsDone(const bool& is);
	void setsType(const int& type);
};
