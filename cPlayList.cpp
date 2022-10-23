// ****** cPlayList.cpp ******
#include "cPlayList.h"
//#include "cSchedule.h"
cPlayList::cPlayList()
{
	this->list = new cSchedule[100];
	
	category[0] = "운동";
	category[1] = "공부";
	category[2] = "취미";

	// +a ) ���� �� ī�װ�� Data ���� By file �Է�
	/*
	
	Data ���� ����

	12						-> &sCount
	1 0 2022 10 12 19 30		-> &sType, &sIsDone, &��¥s
	4 1 2022 10 1 10 30 2022 10 2 11 0	-> �������� (Ÿ�� �޾Ƽ� �б� �ڵ� ���� �� ��)
	*/
	
	/*
	categoryData ���� ����
	4				-> &cateroryNum
	// ���� categoryData = new string[num] ���ְ�
	�			-> &categoryData[0]		
	���			-> ~[1]
	����
	�Ƹ�����Ʈ
	*/

}


cPlayList::~cPlayList()
{
	// �޸� ��ȯ :: ����
	if (this->list != nullptr) {
		delete[] this->list;
		this->list = nullptr;
	}

	// �޸� ��ȯ :: ī�װ��
	if (this->categoryData != nullptr) {
		delete[] this->categoryData;
		this->categoryData = nullptr;
	}
}

void cPlayList::addSchedule()
{
	if (sCount < 100) {
		list[sCount++].makeSchedule(category,categorySize);
	}
	else {
		cout << ">> ������ �� �̻� �߰��� �� �����ϴ�.\n";
		_getch();
	}
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
	manageCategory(category,categorySize);
}
/*bool cPlayList::makeCategory()
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
}*/

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
			printf("2. ��������");
			break;
		}
		case 3: {
			printf("3. ����Ȯ��");
			break;
		}
		case 4: {
			printf("4. ��������");
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
	cout << "1) ���� �߰� 2) ���� ���� 3) ���� Ȯ�� 4) ���� ���� 5) ī�װ�� ���� 6) ����\n"
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
