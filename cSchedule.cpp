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
	bool check = true;		// 예외 발생 체크
	int sel = -1;
	int year, month, day, hour, min;
	int cnt=0;
	char ch;
	string input;
	string name, category;

	while (1) {

		system("cls");
		cout << "<일정 추가>\n\n";

		// 1. 일정 이름	:: 엔터 한 번 입력해야하는 버그 디버깅하기
	re1:;
		if (!check) cin.clear(); 
		cin.ignore(INT_MAX, '\n');
		
		cout << "일정의 이름을 입력해주세요 >> ";
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

		// 2. 일정 카테고리
	re2:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "일정의 카테고리를 입력해주세요 >> ";
		cin >> category;

		/*	// 카테고리 확인 구문
		for (size_t i = 0; i < categoryNum; i++) {
			if (category.compare(categoryData[i])) {
				this->sCategory = category;
			}
			else {
				cout << ">> 해당 카테고리가 존재하지 않습니다.";
				system("pause");
				goto re;
			}
		}
		*/

		// 3. 일정 반복 기능
	re3:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "일정의 반복 기능을 설정해주세요 1)연 반복 2)월 반복 3)요일 반복 4)반복 없음 >> ";
		cin >> sel;
		if (!isRightSchedule(sel)) {
			check = false;
			_getch();
			goto re3;
		}


		// 4. 시작 및 마감 날짜 입력
	re4:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "일정의 시작 날짜 및 시각을 입력해주세요 [ex) 2022 02 03 00 30] >> ";
		cin >> year >> month >> day >> hour >> min;
		if (!isRightSchedule(true, year, month, day, hour, min)) {
			check = false;
			_getch();
			goto re4;
		}

	re5:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		if (sel == 4) {
			cout << "일정의 마감 날짜 및 시각을 입력해주세요 [ex) 2022 02 07 15 30] >> ";
			cin >> year >> month >> day >> hour >> min;
			if (!isRightSchedule(true, year, month, day, hour, min)) {
				check = false;
				_getch();
				goto re5;
			}
		}
		else {
			// 시작 날짜 계산해서 반복 주기 설정하기
		}
		cout << "\n\"" << sName << "\" 일정 추가가 완료되었습니다.";
		_getch();

		break;
	}
}

// # 예외처리 함수 :: 일정 이름
bool cSchedule::isRightSchedule(string name)
{
	if (name.size() > 20) {
		cout << ">> 20자 이하로 입력해주세요.\n";
		return false;
	}
	else if (name.empty()) {
		cout << ">> 공백 입력 불가. 다시 입력해주세요.\n";
		return false;
	}
	else {
		this->sName = name;
		return true;
	}
}

// # 예외처리 함수 :: 반복 타입
bool cSchedule::isRightSchedule(int type)
{
	if (!cin) {
		cout << ">> 올바른 입력을 해주세요.\n";
		return false;
	}
	else if (!(type == 1 || type == 2 || type == 3 || type == 4)) {
		cout << ">> 1에서 4 사이의 값을 입력해주세요.\n";
		return false;
	}
	else {
		this->sType = type;
		return true;
	}
}

// # 예외처리 함수 :: 일정 날짜 및 시각
bool cSchedule::isRightSchedule(bool isS, int year, int month, int day, int hour, int min)
{
	if (!cin) {
		cout << ">> 올바른 입력을 해주세요.\n";
		return false;
	}
	else if (year > 2025) {
		cout << ">> 입력하신 날짜의 연도를 다시 확인해주세요.\n";
		return false;
	}
	else if (month < 1 || month > 12) {
		cout << ">> 입력하신 날짜의 월을 다시 확인해주세요.\n";
		return false;
	}
	else if (hour < 0 || hour > 23) {
		cout << ">> 입력하신 날짜의 시간을 다시 확인해주세요.\n";
		return false;
	}
	else if (min < 0 || min > 59) {
		cout << ">> 입력하신 날짜의 분을 다시 확인해주세요.\n";
		return false;
	}
	// 추가 예외처리들
	/*
	1. 달에 따라 일 수 범위
	2. 윤년이면 2월 29일까지
	3. 현재 시간보다 이전 시간 추가 불가
	*/
	// !isS일 때 start time에 후행하는 지도 이 메소드에서 check
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
		printf("%c", *ch); //_getch() 함수는 작성중인 것 안보여줘서 출력
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
		cout << ">> 기호 입력 불가. 다시 입력해주세요.\n";
		return false;
	}
}