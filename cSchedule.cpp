// ****** cSchedule.cpp ******
#include "cSchedule.h"

cSchedule::cSchedule()
{
}


cSchedule::~cSchedule()
{
}

void cSchedule::makeSchedule()
{
	bool check = true;		// ���� �߻� üũ
	int sel = -1;
	int year, month, day, hour, min;
	int cnt=0;
	char ch;
	string input;
	string name, category;

	while (1) {

		system("cls");
		cout << "<���� �߰�>\n\n";

		// 1. ���� �̸�	:: ���� �� �� �Է��ؾ��ϴ� ���� ������ϱ�
	re1:;
		if (!check) cin.clear(); 
		cin.ignore(INT_MAX, '\n');
		
		cout << "������ �̸��� �Է����ּ��� >> ";
		while(1){		
			if (_kbhit()) {
			ch = _getch();
			swrite(&ch, &cnt, input);
		}}

		name=input;
		
		if (!isRightSchedule(name)) {
			check = false;
			_getch();
			goto re1;
		}

		// 2. ���� ī�װ�
	re2:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "������ ī�װ��� �Է����ּ��� >> ";
		cin >> category;

		/*	// ī�װ� Ȯ�� ����
		for (size_t i = 0; i < categoryNum; i++) {
			if (category.compare(categoryData[i])) {
				this->sCategory = category;
			}
			else {
				cout << ">> �ش� ī�װ��� �������� �ʽ��ϴ�.";
				system("pause");
				goto re;
			}
		}
		*/

		// 3. ���� �ݺ� ���
	re3:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "������ �ݺ� ����� �������ּ��� 1)�� �ݺ� 2)�� �ݺ� 3)���� �ݺ� 4)�ݺ� ���� >> ";
		cin >> sel;
		if (!isRightSchedule(sel)) {
			check = false;
			_getch();
			goto re3;
		}


		// 4. ���� �� ���� ��¥ �Է�
	re4:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "������ ���� ��¥ �� �ð��� �Է����ּ��� [ex) 2022 02 03 00 30] >> ";
		cin >> year >> month >> day >> hour >> min;
		if (!isRightSchedule(true, year, month, day, hour, min)) {
			check = false;
			_getch();
			goto re4;
		}

	re5:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		if (sel == 4) {
			cout << "������ ���� ��¥ �� �ð��� �Է����ּ��� [ex) 2022 02 07 15 30] >> ";
			cin >> year >> month >> day >> hour >> min;
			if (!isRightSchedule(true, year, month, day, hour, min)) {
				check = false;
				_getch();
				goto re5;
			}
		}
		else {
			// ���� ��¥ ����ؼ� �ݺ� �ֱ� �����ϱ�
		}
		cout << "\n\"" << sName << "\" ���� �߰��� �Ϸ�Ǿ����ϴ�.";
		_getch();

		break;
	}
}

// # ����ó�� �Լ� :: ���� �̸�
bool cSchedule::isRightSchedule(string name)
{
	if (name.size() > 20) {
		cout << ">> 20�� ���Ϸ� �Է����ּ���.\n";
		return false;
	}
	else if (name.empty()) {
		cout << ">> ���� �Է� �Ұ�. �ٽ� �Է����ּ���.\n";
		return false;
	}
	else {
		this->sName = name;
		return true;
	}
}

// # ����ó�� �Լ� :: �ݺ� Ÿ��
bool cSchedule::isRightSchedule(int type)
{
	if (!cin) {
		cout << ">> �ùٸ� �Է��� ���ּ���.\n";
		return false;
	}
	else if (!(type == 1 || type == 2 || type == 3 || type == 4)) {
		cout << ">> 1���� 4 ������ ���� �Է����ּ���.\n";
		return false;
	}
	else {
		this->sType = type;
		return true;
	}
}

// # ����ó�� �Լ� :: ���� ��¥ �� �ð�
bool cSchedule::isRightSchedule(bool isS, int year, int month, int day, int hour, int min)
{
	if (!cin) {
		cout << ">> �ùٸ� �Է��� ���ּ���.\n";
		return false;
	}
	else if (year > 2025) {
		cout << ">> �Է��Ͻ� ��¥�� ������ �ٽ� Ȯ�����ּ���.\n";
		return false;
	}
	else if (month < 1 || month > 12) {
		cout << ">> �Է��Ͻ� ��¥�� ���� �ٽ� Ȯ�����ּ���.\n";
		return false;
	}
	else if (hour < 0 || hour > 23) {
		cout << ">> �Է��Ͻ� ��¥�� �ð��� �ٽ� Ȯ�����ּ���.\n";
		return false;
	}
	else if (min < 0 || min > 59) {
		cout << ">> �Է��Ͻ� ��¥�� ���� �ٽ� Ȯ�����ּ���.\n";
		return false;
	}
	// �߰� ����ó����
	/*
	1. �޿� ���� �� �� ����
	2. �����̸� 2�� 29�ϱ���
	3. ���� �ð����� ���� �ð� �߰� �Ұ�
	*/
	// !isS�� �� start time�� �����ϴ� ���� �� �޼ҵ忡�� check
	else {
		if (isS) {
			this->sYear = year;
			this->sMonth = month;
			this->sDay = day;
			this->sHour = hour;
			this->sMin = min;
			return true;
		}
		else {
			this->eYear = year;
			this->eMonth = month;
			this->eDay = day;
			this->eHour = hour;
			this->eMin = min;
			return true;
		}
	}
}

bool cSchedule::swrite (char* ch, int* cnt, string input)
{
	if (!(*ch >= 0 && *ch <= 47) && !(*ch >= '58' && *ch <= '64') && !(*ch >= '91' && *ch <= '96') && !(*ch >= '124' && *ch <= '127')) 
	{
		printf("%c", *ch); //_getch() �Լ��� �ۼ����� �� �Ⱥ����༭ ���
		input[*cnt] = *ch;
		(*cnt)++;
		return true;
	}
	else if (*ch == 8) {
		if (*cnt > 0) {
			(*cnt)--;
			printf("\b \b");
		}
	}
	else{
		cout << ">> ��ȣ �Է� �Ұ�. �ٽ� �Է����ּ���.\n";
		return false;
	}
}