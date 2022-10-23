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

	// @ ī�װ�� ������, ī�װ�� ��
	string* categoryData = nullptr;

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
	void editSchedule();

	// @ 5) ī�װ�� ����
	void mCategory();

	// @ 6) ����

	// @ Schedule ������ �б� �� �����ϱ�
	bool readData(string filename);
	bool saveData(string filename);

	// @ ī�װ�� ������ ����
	bool makeCategory();

	// @ ȯ�� Set
	void getSetting();

	// @ play �Լ�
	void playList();

	// @ showMenu
	int showMenu();

	string category[100] = { "" }; //카테고리 배열 선언(개수제한 100개)
	int categorySize = 3;
};

