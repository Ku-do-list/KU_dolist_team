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
	string name, category;
	char s;

	while (1) {

		system("cls");
		cout << "<���� �߰�>\n\n";

		// 1. ���� �̸�	:: ���� �� �� �Է��ؾ��ϴ� ���� ������ϱ�
	re1:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "������ �̸��� �Է����ּ��� >> ";
		getline(cin, name);
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
			if (!isRightSchedule(false, year, month, day, hour, min)) {
				check = false;
				_getch();
				goto re5;
			}
		}
		cout << "\n\"" << sName << "\" ���� �߰��� �Ϸ�Ǿ����ϴ�.";
		_getch();

		break;
	}
}

// # ����ó�� �Լ� :: ���� �̸�
bool cSchedule::isRightSchedule(string name)
{
	if (name.empty()) {
		cout << ">> ���� �Է� �Ұ�. �ٽ� �Է����ּ���.\n";
		return false;
	}

	char *s;
	double size = 0;
	s = new char[name.length()];
	for (size_t i = 0; i < name.length(); i++) {
		s[i] = name.at(i);
		if (s[i] >> 7)
			size -= 0.5;
	}
	size += name.length(); 
	delete[] s;
	s = nullptr;

	if ((int)size > 20) {
		cout << "20�� ���Ϸ� �ٽ� �Է����ּ���.\n";
		return false;
	}

	for (size_t i = 0; i < name.length(); i++) {
		if ((name.at(i) > 32 && name.at(i) < 48) || (name.at(i) > 57 && name.at(i) < 65) ||
			(name.at(i) > 90 && name.at(i) < 97) || (name.at(i) > 122 && name.at(i) < 127)) {
			cout << ">> Ư������ �Է� �Ұ�. �ٽ� �Է����ּ���.\n";
			return false;
		}
	}

	this->sName = name;
	return true;
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

bool cSchedule::isRightSchedule(int year, int month)
{

	if (!cin) {
		cout << ">> �ùٸ� �Է��� ���ּ���.\n";
		return false;
	}
	else {
		return true;
	}
}

// # ����ó�� �Լ� :: ���� ��¥ �� �ð�
bool cSchedule::isRightSchedule(bool isS, int year, int month, int day, int hour, int min)
{
	// ���� �� ���� �� ��
	bool isLeaf;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		isLeaf = true;
	else
		isLeaf = false;
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeaf ? 29 : 28;

	if (!cin) {
		cout << ">> ���Ŀ� �´� �ùٸ� �Է��� ���ּ���.\n";
		return false;
	}
	else if (year > 2025 ) {
		cout << ">> 2025�� ������ �Է� �����մϴ�. �ٽ� �Է����ּ���.\n";
		return false;
	}
	else if (month < 1 || month > 12) {
		cout << ">> �Է��Ͻ� ��¥�� ���� �ٽ� Ȯ�����ּ���.\n";
		return false;
	}
	else if (day < 1 || day > m[month - 1]) {
		cout << ">> �Է��Ͻ� ��¥�� ���ڸ� �ٽ� Ȯ�����ּ���.\n";
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
	
	else {
		if (isS) {
			if (!isAfterNow(year, month, day, hour, min)) {
				cout << ">> ���� ������ ��¥�� �Է��Ͻ� �� �����ϴ�.\n";
				return false;
			}
			this->sYear = year;
			this->sMonth = month;
			this->sDay = day;
			this->sHour = hour;
			this->sMin = min;
			switch (this->sType) {
			case 1: {	// �� �� ���� ���� �ݺ�
				this->rAnnual.first = sMonth;
				this->rAnnual.second = sDay;
				break;
			}
			case 2: {	// �� �� ���� �� �ݺ�
				this->rMontly = sDay;
				break;
			}
			case 3: {	// �� �� ���� ���� �ݺ�
				this->rWeekly = getDayOfWeek(sYear, sMonth, sDay);
				cout << "\n ���� : " << this->rWeekly << '\n';
				break;
			}
			}
			return true;
		}
		else {
			if (!isAfterStart(year, month, day, hour, min)) {
				cout << ">> ���� ���� �ð��� �Է� �����մϴ�.\n";
				return false;
			}
			this->eYear = year;
			this->eMonth = month;
			this->eDay = day;
			this->eHour = hour;
			this->eMin = min;
			return true;
		}
	}
}

string cSchedule::getsName() const
{
	return this->sName;
}

string cSchedule::getsCategory() const
{
	return this->sCategory;
}

int cSchedule::getsType() const
{
	return this->sType;
}

pair<int, int> cSchedule::getrAnnual() const
{
	return { this->rAnnual.first, this->rAnnual.second };
}

int cSchedule::getrMonthly() const
{
	return this->rMontly;
}

int cSchedule::getrWeekly() const
{
	return this->rWeekly;
}

string cSchedule::getDayW(int weekly) const
{
	string day[7] = { "�Ͽ���", "������", "ȭ����", "������", "�����", "�ݿ���", "�����" };
	return day[weekly];
}

void cSchedule::setsName(const string & name)
{
	this->sName = name;
}

void cSchedule::setRepeat(const int & type)
{
	bool isLeaf;
	if (sYear % 4 == 0 && sYear % 100 != 0 || sYear % 400 == 0)
		isLeaf = true;
	else
		isLeaf = false;
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeaf ? 29 : 28;
	int a = 0, b = 0;
	bool check = 1;
re:;
	if (type == 1) {
		cout << "������ �ݺ� ������ �Է����ּ��� [ex) 06 10] >> ";
		cin >> a >> b;
		if (cin.fail()) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}
		else if (a < 1 || a > 12) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}
		/*else if (b < m[sMonth-1] || b>m[sMonth-1]) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}*/
		else {
			this->rAnnual.first = a;
			this->rAnnual.second = b;
			cout << "������ �� �ݺ� �ֱⰡ ���� �Ϸ�Ǿ����ϴ�.\n";
		}
	}
	else if (type == 2) {
		cout << "������ �ݺ� ���� �Է����ּ��� [ex) 10] >> ";
		cin >> a;
		if (cin.fail()) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}
		/*else if (a < m[sMonth-1] || a>m[sMonth-1]) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}*/
		else {
			this->rMontly = a;
			cout << "������ �� �ݺ� �ֱⰡ ���� �Ϸ�Ǿ����ϴ�.\n";
		}
	}
	else if (type == 3) {
		cout << "������ �ݺ� ������ �Է����ּ��� [0=�Ͽ���, 6=������] >> ";
		cin >> a;
		if (!cin) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}
		else if (a < 0 || a>6) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n";
			check = false;
			_getch();
			goto re;
		}
		else {
			this->rWeekly = a;
			cout << "������ ���� �ݺ� �ֱⰡ ���� �Ϸ�Ǿ����ϴ�.\n";
		}
	}
	_getch();
}

void cSchedule::setIsDone(const bool & is)
{
	this->sIsDone = is;
}

void cSchedule::setsType(const int & type)
{
	this->sType = type;
}

