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
	int sel = -1;
	string name, category;

	while (1) {
	re:;
		system("cls");
		cout << "<���� �߰�>\n\n";

		// 1. ���� �̸�
		cout << "������ �̸��� �Է����ּ��� >> ";
		cin >> name;

		if (name.size() > 20) {
			cout << ">> 20�� ���Ϸ� �Է����ּ���.";
			system("pause");
			goto re;
		}
		else if (name.empty()) {
			cout << ">> ���� �Է� �Ұ�. �ٽ� �Է����ּ���.";
			system("pause");
			goto re;
		}
		//else if () {
		//	isRightSchedule(name);
		//} //��ȣ �Է� ���� ���� 
		else {
			this->sName = name;
		}

		// 2. ���� ī�װ�
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
		cout << "������ �ݺ� ����� �������ּ��� 1)�� �ݺ� 2)�� �ݺ� 3)���� �ݺ� 4)�ݺ� ���� >> ";
		cin >> sel;

		if ((typeid(sel) != typeid(int)) || !(sel == 1 || sel == 2 || sel == 3 || sel == 4)) {
			cin.clear();
			getchar();
			sel = -1;
			cout << ">> �ùٸ� �Է��� ���ּ���.\n";
			Sleep(1000);
			goto re;
		}
		else
			this->sType = sel;

		// 4. ���� �� ���� ��¥ �Է�
		cout << "������ ���� ��¥ �� �ð��� �Է����ּ��� [ex) 2022 02 03 00 30] >> ";
		cin >> sYear >> sMonth >> sDay >> sHour >> sMin;
		// ����ó�� ���� ����
		if(sYear )
		if (sel == 4) {
			cout << "������ ���� ��¥ �� �ð��� �Է����ּ��� [ex) 2022 02 07 15 30] >> ";
			cin >> eYear >> eMonth >> eDay >> eHour >> eMin;
			// ����ó�� ���� ����
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
int cSchedule::isRightSchedule(string name)
{
	return 0;
}

// # ����ó�� �Լ� :: �ݺ� Ÿ��
int cSchedule::isRightSchedule(int type)
{
	return 0;
}

// # ����ó�� �Լ� :: ���� ��¥ �� �ð�
int cSchedule::isRightSchedule(int year, int month, int day, int hour, int min)
{
	return 0;
}
