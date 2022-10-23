// ****** cPlayList.cpp ******
#include "cPlayList.h"


cPlayList::cPlayList()
{
	this->list = new cSchedule[100];
	
	// +a ) 일정 및 카테고리 Data 구문 By file 입력
	/*
	
	Data 파일 예시

	12						-> &sCount
	1 0 2022 10 12 19 30		-> &sType, &sIsDone, &날짜s
	4 1 2022 10 1 10 30 2022 10 2 11 0	-> 마찬가지 (타입 받아서 분기 코드 쓰면 될 듯)
	*/
	
	/*
	categoryData 파일 예시
	4				-> &cateroryNum
	// 이후 categoryData = new string[num] 해주고
	운동			-> &categoryData[0]		
	취미			-> ~[1]
	공부
	아르바이트
	*/

}


cPlayList::~cPlayList()
{
	// 메모리 반환 :: 일정
	if (this->list != nullptr) {
		delete[] this->list;
		this->list = nullptr;
	}

	// 메모리 반환 :: 카테고리
	if (this->categoryData != nullptr) {
		delete[] this->categoryData;
		this->categoryData = nullptr;
	}
}

void cPlayList::addSchedule()
{
	if (sCount < 100) {
		list[sCount++].makeSchedule();
	}
	else {
		cout << ">> 일정을 더 이상 추가할 수 없습니다.\n";
		_getch();
	}
}

void cPlayList::checkSchedule()
{
	system("cls");
	int year, month;
	bool check = true;
re:;
	if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
	cout << "확인하실 일정의 연도와 월을 입력해주세요 [ex) 2022 12] >> ";
	cin >> year >> month;
	if (!isRightSchedule(year, month)) {
		check = false;
		_getch();
		goto re;
	}
	cout << "====================================\n"
		<< '\t' << year << "년 " << month << "월 일정\n"
		<< "====================================\n";
	int count = 1;

	bool isLeaf;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		isLeaf = true;
	else
		isLeaf = false;
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeaf ? 29 : 28;

	// 여기서부터 반복성 / 반복x 나눠서 생각해서 다시 코드 짜보자.
	// sType을 기준으로 해야할 듯, getDayOfWeek 함수 다시 건드려야함
	for (size_t i = 0; i < sCount; i++) {
		int type = list[i].getsType();
		switch (type) {
		case 1: {	// 연 반복
			if (list[i].getsYear() <= year) {
				if (list[i].getsMonth() == month) {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - 날짜 : " << year << "년 " << month << "월 ";
					if (list[i].getrAnnual().second > m[month - 1]) {
						cout << m[month - 1] << "일\n";
					}
					else {
						cout << list[i].getrAnnual().second << "일\n";
					}
					cout << "  - 매 년 " << month << "월 " << list[i].getrAnnual().second << "일 반복 일정\n";
				}
			}
			break;
		}
		case 2: {	// 월 반복
			if (list[i].getsYear() == year) {
				if (list[i].getsMonth() <= month) {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - 날짜 : " << year << "년 " << month << "월 ";
					if (list[i].getrMonthly() > m[month - 1]) {
						cout << m[month - 1] << "일\n";
					}
					else {
						cout << list[i].getrMonthly() << "일\n";
					}
					cout << "  - 매 월 " << list[i].getrMonthly() << "일 반복 일정\n";
				}
			}
			else if (list[i].getsYear() < year) {
				cout << " [" << count++ << "] " << list[i].getsName() << "\n";
				cout << "  - 날짜 : " << year << "년 " << month << "월 ";
				if (list[i].getrMonthly() > m[month - 1]) {
					cout << m[month - 1] << "일\n";
				}
				else {
					cout << list[i].getrMonthly() << "일\n";
				}
				cout << "  - 매 월 " << list[i].getrMonthly() << "일 반복 일정\n";
			}
			break;
		}
		case 3: {	// 주 반복
			if (list[i].getsYear() == year) {
				if (list[i].getsMonth() <= month) {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - 날짜 : " << year << "년 " << month << "월";
					for (size_t j = 1; j <= m[month - 1]; j++) {
						if (getDayOfWeek(year, month, j) == list[i].getrWeekly()) {
							cout << " " << j;
						}
					}
					cout << "일\n  - 매 주 " << getDayW(list[i].getrWeekly()) << " 반복 일정\n";
				}
			}
			else if (list[i].getsYear() < year) {
				cout << " [" << count++ << "] " << list[i].getsName() << "\n";
				cout << "  - 날짜 : " << year << "년 " << month << "월";
				for (size_t j = 1; j <= m[month - 1]; j++) {
					if (getDayOfWeek(year, month, j) == list[i].getrWeekly()) {
						cout << " " << j;
					}
				}
				cout << "일\n  - 매 주 " << getDayW(list[i].getrWeekly()) << " 반복 일정\n";
			}
			break;
		}
		case 4: {	// 반복x, 마감일정 포함
			int sy = list[i].getsYear();	// 시작 연도
			int sm = list[i].getsMonth();	// 시작 월
			int ey = list[i].geteYear();	// 마감 연도
			int em = list[i].geteMonth();	// 마감 월
			if (sy <= year && ey >= year) {
				if (sy == year) {
					if (sm <= month) {
						cout << " [" << count++ << "] " << list[i].getsName() << "\n";
						cout << "  - 시작 날짜 : " << sy << "년 " << sm << "월" << list[i].getsDay() << "일\n";
						cout << "  - 마감 날짜 : " << ey << "년 " << em << "월" << list[i].geteDay() << "일\n";
					}
				}
				else if (ey == year) {
					if (em >= month) {
						cout << " [" << count++ << "] " << list[i].getsName() << "\n";
						cout << "  - 시작 날짜 : " << sy << "년 " << sm << "월" << list[i].getsDay() << "일\n";
						cout << "  - 마감 날짜 : " << ey << "년 " << em << "월" << list[i].geteDay() << "일\n";
					}
				}
				else {
					cout << " [" << count++ << "] " << list[i].getsName() << "\n";
					cout << "  - 시작 날짜 : " << sy << "년 " << sm << "월" << list[i].getsDay() << "일\n";
					cout << "  - 마감 날짜 : " << ey << "년 " << em << "월" << list[i].geteDay() << "일\n";
				}
			}
			break;
		}
		}
	}
	if (count == 1)
		cout << " - 해당 연월에 일정이 없습니다.\n";
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

bool cPlayList::makeCategory()
{
	string fileName = "categoryData.txt";
	ifstream fin(fileName);

	// @ 파일 열기 실패 시 예외처리
	if (!fin.is_open()) {
		cerr << "[Error] categoryData.txt 파일을 열 수 없습니다. 경로를 확인해주세요.\n";
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
	// @ 이후 color 설정 등등 필요한 초기 설정
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
			printf("2. 일정삭제");
			break;
		}
		case 3: {
			checkSchedule();
			break;
		}
		case 4: {
			printf("4. 일정편집");
			break;
		}
		case 5: {
			printf("5. 카테고리 관리");
			break;
		}
		case 6: {
			printf("6. 종료");
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
	cout << "1) 일정 추가 2) 일정 삭제 3) 일정 확인 4) 일정 편집 5) 카테고리 관리 6) 종료\n"
		<< "\n메뉴 번호를 입력해주세요 >> ";
	cin >> sel;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << ">> 올바른 입력 값을 다시 입력하세요.\n";
		_getch();
		goto re;
	}
	else if (sel < 1 || sel > 6) {
		cout << ">> 1에서 6 사이의 값을 입력해주세요.\n";
		_getch();
		goto re;
	}

	return sel;
}
