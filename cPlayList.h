// ****** cPlayList.h ******
#pragma once
#include "cSchedule.h"

#ifdef _MSC_VER
#define localtime_r(_time, _result) _localtime64_s(_result, _time)
#endif

class cPlayList
	:public cSchedule
{
private:
	// @ ���� ������ �迭
	cSchedule* list;

	// @ ���� �� ����
	int sCount = 0;

	// @ ���� index number
	vector<int> v;

	// @ ī�װ� ������, ī�װ� ��
	string* categoryData = nullptr;
	int categoryNum = 0;

	// @ Data Files	:: ���� ���� ���
	string dataSchedule = "data.txt";
	string dataCategory = "dataCategory.txt";
public:
	cPlayList();
	~cPlayList();

	// @ 1) ���� �߰�
	void addSchedule();

	// @ 2) ���� ����
	void removeSchedule();

	// @ 3) ���� Ȯ��
	void checkSchedule();

	// @ 4) ���� ����
	void editSchedule(int index);

	// @ ó�� ������ ���� �̸� �Է½� ����Ȯ�� ����ó�� �Լ�
	void isRightexit(string name);
	void isRightexit_over1();

	// @ 5) ī�װ� ����
	void mCategory();

	// @ 6) ����

	// @ Schedule ������ �б� �� �����ϱ�
	bool readData(string filename);
	bool saveData(string filename);

	// @ ī�װ� ������ ����
	bool makeCategory();

	// @ ȯ�� Set
	void getSetting();

	// @ play �Լ�
	void playList();

	// @ showMenu
	int showMenu();

	string category[100] = { "" }; //ī�װ� �迭 ����(�������� 100��)
	int categorySize = 3;

};