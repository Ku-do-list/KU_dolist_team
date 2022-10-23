// ****** cSchedule.cpp ******
#include "cSchedule.h"
#include <string>

cSchedule::cSchedule()
{
}


cSchedule::~cSchedule()
{
}

bool cSchedule::isSign(string str) {
	for (size_t i = 0; i < str.length(); i++) {
		if ((str.at(i) > 32 && str.at(i) < 48) || (str.at(i) > 57 && str.at(i) < 65) ||
			(str.at(i) > 90 && str.at(i) < 97) || (str.at(i) > 122 && str.at(i) < 127)) {
			return false;
		}
	}
}
void cSchedule::manageCategory(string* category, int& categorySize) {
	int user = 0;

	while (1) {
		cout << "1) 카테고리 추가 2) 카테고리 편집 3) 카테고리 삭제" << endl;
		cout << "\n 메뉴 번호를 입력해주세요 >>";
		cin >> user;
		if (!user) {
			cout << "숫자만 입력하세요 >>";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (user < 1 || user >4) {
			cout << "1~4 사이의 숫자만 입력해주세요 >>";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (user == 1)
		{
			cout << "<카테고리 추가>" << endl;
			cout << "추가하실 카테고리 이름을 입력해주세요(모든 기호 사용 제외) >>";
			while (1) {
				cin >> s;
				if (s.size() > 20) {
					cout << " 20자 이하로 입력해주세요 >>";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				else if (!isSign(s)) {
					cout << "기호를 입력하지 마세요 >>";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				else {
					break;
				}
			}
			for (int i = 0; i < categorySize; i++) {
				if (category[i] == s) {
					duplicate = true;
					break;
				}
			}
			if (duplicate == false) {
				cout << "성공적으로 추가 되었습니다." << endl;
				category[categorySize] = s;
				categorySize++;
			}
			else {
				cout << "사전에 있는 카테고리 입니다." << endl;
				duplicate = false;
			}
			break;
		}
		else if (user == 2)
		{
			cout << "<카테고리 편집>";
			for (int i = 0; i < categorySize; i++) {
				cout << i + 1 << ". " << category[i] << " ";
			}
			cout << endl;
			cout << "편집하실 카테고리 번호를 입력해주세요(모든 기호 사용 제외)>>";
			while (1) {
				cin >> categoryNum;
				if (!categoryNum) {
					cout << "숫자만 입력하세요 >>";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				else if (categoryNum < 1 || categoryNum >categorySize) {
					cout << "범위 사이의 숫자만 입력해주세요 >>";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				else {
					break;
				}
			}
			cout << category[categoryNum - 1] << " -> ";
			cin >> s;
			for (int i = 0; i < categorySize; i++) {
				if (category[i] == s) {
					duplicate = true;
					break;
				}
			}
			cout << endl;
			if (duplicate == false) {
				category[categoryNum - 1] = s;
				cout << "변경되었습니다.";
			}
			else {
				cout << "사전에 있는 카테고리 입니다." << endl;
				duplicate = false;
			}
			break;
		}
		else if (user == 3)
		{
			cout << "<카테고리 삭제>";
			for (int i = 0; i < categorySize; i++) {
				cout << i + 1 << ". " << category[i] << " ";
			}
			cout << endl;
			cout << "삭제하실 카테고리 번호를 입력해주세요(모든 기호 사용 제외)>>";
			cin >> categoryNum;
			for (int i = categoryNum - 1; i < categorySize; i++) {
				category[i] = category[i + 1];
			}
			categorySize--;
			break;
		}
	}
}
void cSchedule::makeSchedule(string* category,int& categorySize)
{
	bool check = true;		// ���� �߻� üũ
	int sel = -1;
	int year, month, day, hour, min;
	string name;


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


		// 2. ���� ī�װ��
	re2:;
		while (1) {
			if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
			category[categorySize] = "직접 입력";
			categorySize++;
			for (int i = 0; i < categorySize; i++) {
				cout << i + 1 << ". " << category[i] << " ";
			}
			cout << endl;
			category[categorySize] = "";
			categorySize--;
			cout << "일정의 카테고리번호를 입력해주세요 >> ";
			cin >> categoryNum;
			if (!categoryNum) {
				cout << "숫자만 입력하세요 >>";
			}
			else if (categoryNum < 1 || categoryNum >categorySize+1) {
				cout << "1~" << categorySize+1 << "사이의 숫자만 입력해주세요 >>";
			}
			else if (categoryNum-1 == categorySize) {
				cout << "<카테고리 추가>" << endl;
				cout << "추가하실 카테고리 이름을 입력해주세요(모든 기호 사용 제외) >>";
				while (1) {
					cin >> s;
					if (s.size() > 20) {
						cout << " 20자 이하로 입력해주세요 >>";
						cin.clear();
						cin.ignore(INT_MAX, '\n');
					}
					else if (!isSign(s)) {
						cout << "기호를 입력하지 마세요 >>";
						cin.clear();
						cin.ignore(INT_MAX, '\n');
					}
					else {
						break;
					}
				}
				for (int i = 0; i < categorySize; i++) {
					if (category[i] == s) {
						duplicate = true;
						break;
					}
				}
				if (duplicate == false) {
					cout << "성공적으로 추가 되었습니다." << endl;
					category[categorySize] = s;
					categorySize++;
					break;
				}
				else {
					cout << "사전에 있는 카테고리 입니다." << endl;
					duplicate = false;
					break;
				}
			}
			else {
			}
		}
		for (int i = 0; i < categorySize; i++) {
			cout << i + 1 << ". " << category[i] << " ";
		}

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

