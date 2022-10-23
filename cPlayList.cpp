// ****** cPlayList.cpp ******
#include "cPlayList.h"

cPlayList::cPlayList()
{
	this->list = new cSchedule[100];

	category[0] = "�";
	category[1] = "����";
	category[2] = "���";

}


cPlayList::~cPlayList()
{
	// �޸� ��ȯ :: ����
	if (this->list != nullptr) {
		delete[] this->list;
		this->list = nullptr;
	}

	// �޸� ��ȯ :: ī�װ�
	if (this->categoryData != nullptr) {
		delete[] this->categoryData;
		this->categoryData = nullptr;
	}
}

void cPlayList::addSchedule()
{
	if (sCount < 100) {
		list[sCount++].makeSchedule(category, categorySize);
	}
	else {
		cout << ">> ������ �� �̻� �߰��� �� �����ϴ�.\n";
		_getch();
	}
}

void cPlayList::removeSchedule()
{
	list[sCount--].deleteSchedule();
}

void cPlayList::editSchedule(int index)
{
	list[index].edit_Schedule();
}

void cPlayList::checkSchedule()
{
	system("cls");
	int year, month;
	bool check = true;
re:;
	if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
	cout << "Ȯ���Ͻ� ������ ������ ���� �Է����ּ��� [ex) 2022 12] >> ";
	cin >> year >> month;
	if (!isRightSchedule(year, month)) {
		check = false;
		_getch();
		goto re;
	}
	cout << "====================================\n"
		<< '\t' << year << "�� " << month << "�� ����\n"
		<< "====================================\n";
	int count = 1;

	bool isLeaf;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		isLeaf = true;
	else
		isLeaf = false;
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeaf ? 29 : 28;

	// ���⼭���� �ݺ��� / �ݺ�x ������ �����ؼ� �ٽ� �ڵ� ¥����.
	// sType�� �������� �ؾ��� ��, getDayOfWeek �Լ� �ٽ� �ǵ������
	for (size_t i = 0; i < sCount; i++) {
		int type = list[i].getsType();
		switch (type) {
		case 1: {	// �� �ݺ�
			if (list[i].getsYear() <= year) {
				if (list[i].getsMonth() == month) {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - ��¥ : " << year << "�� " << month << "�� ";
					if (list[i].getrAnnual().second > m[month - 1]) {
						cout << m[month - 1] << "��\n";
					}
					else {
						cout << list[i].getrAnnual().second << "��\n";
					}
					cout << "  - �� �� " << month << "�� " << list[i].getrAnnual().second << "�� �ݺ� ����\n";
				}
			}
			break;
		}
		case 2: {	// �� �ݺ�
			if (list[i].getsYear() == year) {
				if (list[i].getsMonth() <= month) {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - ��¥ : " << year << "�� " << month << "�� ";
					if (list[i].getrMonthly() > m[month - 1]) {
						cout << m[month - 1] << "��\n";
					}
					else {
						cout << list[i].getrMonthly() << "��\n";
					}
					cout << "  - �� �� " << list[i].getrMonthly() << "�� �ݺ� ����\n";
				}
			}
			else if (list[i].getsYear() < year) {
				cout << " [" << count++ << "] " << list[i].getsName() << "\n";
				cout << "  - ��¥ : " << year << "�� " << month << "�� ";
				if (list[i].getrMonthly() > m[month - 1]) {
					cout << m[month - 1] << "��\n";
				}
				else {
					cout << list[i].getrMonthly() << "��\n";
				}
				cout << "  - �� �� " << list[i].getrMonthly() << "�� �ݺ� ����\n";
			}
			break;
		}
		case 3: {	// �� �ݺ�
			if (list[i].getsYear() == year) {
				if (list[i].getsMonth() <= month) {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - ��¥ : " << year << "�� " << month << "��";
					for (size_t j = 1; j <= m[month - 1]; j++) {
						if (getDayOfWeek(year, month, j) == list[i].getrWeekly()) {
							cout << " " << j;
						}
					}
					cout << "��\n  - �� �� " << getDayW(list[i].getrWeekly()) << " �ݺ� ����\n";
				}
			}
			else if (list[i].getsYear() < year) {
				cout << " [" << count++ << "] " << list[i].getsName() << "\n";
				cout << "  - ��¥ : " << year << "�� " << month << "��";
				for (size_t j = 1; j <= m[month - 1]; j++) {
					if (getDayOfWeek(year, month, j) == list[i].getrWeekly()) {
						cout << " " << j;
					}
				}
				cout << "��\n  - �� �� " << getDayW(list[i].getrWeekly()) << " �ݺ� ����\n";
			}
			break;
		}
		case 4: {	// �ݺ�x, �������� ����
			int sy = list[i].getsYear();	// ���� ����
			int sm = list[i].getsMonth();	// ���� ��
			int ey = list[i].geteYear();	// ���� ����
			int em = list[i].geteMonth();	// ���� ��
			if (sy <= year && ey >= year) {
				if (sy == year) {
					if (sm <= month) {
						cout << " [" << count++ << "] " << list[i].getsName() << "\n";
						cout << "  - ���� ��¥ : " << sy << "�� " << sm << "��" << list[i].getsDay() << "��\n";
						cout << "  - ���� ��¥ : " << ey << "�� " << em << "��" << list[i].geteDay() << "��\n";
					}
				}
				else if (ey == year) {
					if (em >= month) {
						cout << " [" << count++ << "] " << list[i].getsName() << "\n";
						cout << "  - ���� ��¥ : " << sy << "�� " << sm << "��" << list[i].getsDay() << "��\n";
						cout << "  - ���� ��¥ : " << ey << "�� " << em << "��" << list[i].geteDay() << "��\n";
					}
				}
				else {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - ���� ��¥ : " << sy << "�� " << sm << "��" << list[i].getsDay() << "��\n";
					cout << "  - ���� ��¥ : " << ey << "�� " << em << "��" << list[i].geteDay() << "��\n";
				}
			}
			break;
		}
		}
	}
	if (count == 1)
		cout << " - �ش� ������ ������ �����ϴ�.\n";
	_getch();
}

bool cPlayList::readData(string filename)
{


	return false;
}

bool cPlayList::saveData(string filename)
{
	return false;
}

void cPlayList::mCategory() {
	manageCategory(category, categorySize);
}

bool cPlayList::makeCategory()
{
	string fileName = "categoryData.txt";
	ifstream fin(fileName);

	// @ ���� ���� ���� �� ����ó��
	if (!fin.is_open()) {
		cerr << "[Error] categoryData.txt ������ �� �� �����ϴ�. ��θ� Ȯ�����ּ���.\n";
		_getch();
		return false;
	}

	fin >> this->categoryNum;
	this->categoryData = new string[this->categoryNum];

	for (size_t i = 0; i < this->categoryNum; i++)
		fin >> this->categoryData[i];

	return true;
}

void cPlayList::getSetting()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	srand((unsigned)time(NULL));
	// @ ���� color ���� ��� �ʿ��� �ʱ� ����
}

void cPlayList::playList()
{
	int sel = 0;
	while (sel != 6) {
		sel = showMenu();
		srand((unsigned)time(NULL));

		switch (sel) {
		case 1: {
			addSchedule();
			break;
		}
		case 2: {
			removeSchedule();
			break;
		}
		case 3: {
			printf("3. ����Ȯ��");
			checkSchedule();
			break;
		}
		case 4: {
			printf("4. ��������");

			system("cls");

			bool check = true;      // ���� �߻� üũ
			string _name;

			re_edit1:;

			if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');

			cout << "������ ������ �̸��� �Է����ּ��� >> ";
			getline(cin, _name);

			isRightexit(_name);

			if (v.size() == 0) {
				check = false;
				_getch();
				goto re_edit1;
			}
			else if (v.size() == 1) {
				editSchedule(v.back());
			}
			else {
				system("cls");
				isRightexit_over1();
				editSchedule(v.back());
			}

			break;
		}
		case 5: {
			mCategory();
			break;
		}
		case 6: {
			printf("6. ����");
			break;
		}
		}
	}
}

int cPlayList::showMenu()
{
	int sel;
re:;

	system("cls");
	cout << "1) ���� �߰�  2) ���� ����  3) ���� Ȯ��  4) ���� ����  5) ī�װ� ����  6) ����\n"
		<< "\n�޴� ��ȣ�� �Է����ּ��� >> ";
	cin >> sel;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << ">> �ùٸ� �Է� ���� �ٽ� �Է��ϼ���.\n";
		_getch();
		goto re;
	}
	else if (sel < 1 || sel > 6) {
		cout << ">> 1���� 6 ������ ���� �Է����ּ���.\n";
		_getch();
		goto re;
	}

	return sel;
}

void cPlayList::isRightexit(string _name) {
	v.clear();
	vector<int>().swap(v);

	for (int i = 0; i <= 100; i++) {
		if (_name.compare(list[i].getsName()) == 0) {
			v.push_back(i);
		}
	}
}

void cPlayList::isRightexit_over1() { //2�� �̻� ���� ó��
	string name;
	int ch;

re_edit2:;
	system("cls");

	cin.clear(); cin.ignore(INT_MAX, '\n');

	for (int i = 0; i < v.size(); i++) {
		int index;
		index = v.at(i);
		cout << "���� ��ȣ:" << index << "�����̸�: " << list[index].getsName() << " ��¥ �� �ð�: " << list[index].getsYear() << list[index].getsMonth() << list[index].getsDay() << list[index].getsHour() << list[index].getsMin() << "\n" << endl;
	}

	cout << "������ ������ �̸��� �ߺ��˴ϴ�." << "\n" << "��µ� ���� ��, �ش��ϴ� ������ ���� ��ȣ�� �Է����ּ���! >> ";
	cin >> ch;
	if (cin.fail()) {
		cout << ">> �������� �ʴ� �ε��� �Դϴ�. �ٽ� �Է����ּ���.\n";
		//check = false;
		_getch();
		goto re_edit2;
	}

	for (int i = 0; i < v.size(); i++) {

		//std::string str = std::to_string(v.at(i));

		/*if(name.compare(str)==0){
		   v.push_back(stoi(name));
		}*/
		if (ch == v.at(i)) {
			v.push_back(ch);
		}
		else {
			cout << ">> �������� �ʴ� �ε��� �Դϴ�. �ٽ� �Է����ּ���.\n";
			//check = false;
			_getch();
			goto re_edit2;
		}
	}
}