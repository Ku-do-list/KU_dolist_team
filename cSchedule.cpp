// ****** cSchedule.cpp ******
#include "cSchedule.h"
#include <regex>
#include <fstream>


cSchedule::cSchedule()
{
}


cSchedule::~cSchedule()
{
}

void cSchedule::makeSchedule()
{
	writeFileList.open("KU_do_list.txt", ios::out | ios::app);
	writeFileCategory.open("KU_do_list_category.txt", ios::out | ios::app);
	bool check = true;		// 예외 발생 체크
	int sel = -1;
	int year, month, day, hour, min;
	string name, category;

	while (1) {

		system("cls");
		cout << "<일정 추가>\n\n";

		// 1. 일정 이름	:: 엔터 한 번 입력해야하는 버그 디버깅하기
	re1:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "일정의 이름을 입력해주세요 >> ";
		getline(cin, name);

		if (!isRightSchedule(name)) {
			check = false;
			_getch();
			goto re1;
		}
		else {
			char ch1[20]=""; //초기화 적용
			strcpy(ch1, name.c_str());
			writeFileList.write(ch1, sizeof(ch1));
			writeFileList.put('/');
		}

		// 2. 일정 카테고리
	re2:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "일정의 카테고리를 입력해주세요 >> ";
		cin >> category;

		char ch2[20] = "";
		strcpy(ch2, category.c_str());
		writeFileCategory.write(ch2, sizeof(ch2));
		writeFileList.write(ch2, sizeof(ch2));
		writeFileCategory.put('\n');
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
		else {
			writeFileList.put((char)(sel+48));
			writeFileList.put(' ');
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
		else {
			string syear = to_string(year);
			string smonth = to_string(month);
			string sday = to_string(day);
			string shour = to_string(hour);
			string smin = to_string(min);
			string sresult = syear+" "+smonth+" "+sday+" "+shour+" "+smin;

			char ch4[20] = "";
			strcpy(ch4, sresult.c_str());
			writeFileList.write(ch4, sizeof(ch4));
			writeFileList.put('\n');
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
			else {
				string syear = to_string(year);
				string smonth = to_string(month);
				string sday = to_string(day);
				string shour = to_string(hour);
				string smin = to_string(min);
				string sresult = syear + " " + smonth + " " + sday + " " + shour + " " + smin;

				char ch4[20] = "";
				strcpy(ch4, sresult.c_str());
				writeFileList.write(ch4, sizeof(ch4));
				writeFileList.put('\n');

			}
		}
		else {
			// 시작 날짜 계산해서 반복 주기 설정하기
		}
		cout << "\n\"" << sName << "\" 일정 추가가 완료되었습니다.";
		_getch();
		writeFileList.close();
		break;
	}
}

//기호 입력에 대한 예외처리 
bool isSign(std::string const& name) {
	for (size_t i = 0; i < name.length(); i++) {
		if ((name.at(i) > 32 && name.at(i) < 48) || (name.at(i) > 57 && name.at(i) < 65) ||
			(name.at(i) > 90 && name.at(i) < 97) || (name.at(i) > 122 && name.at(i) < 127)) {
			cout << ">> 특수문자 입력 불가. 다시 입력해주세요.\n";
			return false;
		}
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
	else if (!isSign(name)) {
		cout << ">> 기호 입력 불가. 다시 입력해주세요.\n";
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
	// 윤년 및 달의 일 수
	bool isLeaf;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		isLeaf = true;
	else
		isLeaf = false;
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeaf ? 29 : 28;

	if (!cin) {
		cout << ">> 형식에 맞는 올바른 입력을 해주세요.\n";
		return false;
	}
	else if (year > 2025) {
		cout << ">> 2025년 까지만 입력 가능합니다. 다시 입력해주세요.\n";
		return false;
	}
	else if (month < 1 || month > 12) {
		cout << ">> 입력하신 날짜의 월을 다시 확인해주세요.\n";
		return false;
	}
	else if (day < 1 || day > m[month - 1]) {
		cout << ">> 입력하신 날짜의 일자를 다시 확인해주세요.\n";
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

	else {
		if (isS) {
			if (!isAfterNow(year, month, day, hour, min)) {
				cout << ">> 현재 이전의 날짜는 입력하실 수 없습니다.\n";
				return false;
			}
			this->sYear = year;
			this->sMonth = month;
			this->sDay = day;
			this->sHour = hour;
			this->sMin = min;
			switch (this->sType) {
			case 1: {	// 매 년 같은 월일 반복
				this->rAnnual.first = sMonth;
				this->rAnnual.second = sDay;
				break;
			}
			case 2: {	// 매 월 같은 날 반복
				this->rMontly = sDay;
				break;
			}
			case 3: {	// 매 주 같은 요일 반복
				this->rWeekly = getDayOfWeek(sYear, sMonth, sDay);
				cout << "\n 요일 : " << this->rWeekly << '\n';
				break;
			}
			}
			return true;
		}
		else {
			if (!isAfterStart(year, month, day, hour, min)) {
				cout << ">> 시작 이후 시각만 입력 가능합니다.\n";
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

void cSchedule::deleteSchedule()
{
	string delete_name;
	bool check = true;
	
	while (1) {
		system("cls");
		cout << "<일정 삭제>\n\n";

		// 1. 일정 이름	:: 엔터 한 번 입력해야하는 버그 디버깅하기
	re1:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "삭제할 일정의 이름을 입력해주세요 >> ";
		getline(cin, delete_name);
		if (!isRightSchedule(delete_name)) {
			check = false;
			_getch(); //
			goto re1;
		}

		//1) 같은 이름의 일정이 여러 개일 경우
	re2:;
		int delete_num;
		cout << "\n삭제할 일정의 번호를 입력해주세요 >> ";
		cin >> delete_num;

		char delete_flag;
		cout << "삭제할 일정의 번호가 맞습니까? (y/n) >> ";
		cin >> delete_flag;

		if (delete_flag == 'y') {
			cout << "일정이 삭제되었습니다." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			break;
		}
		else if (delete_flag == 'n') {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goto re2;
		}
		else {
			cout << "잘못 입력하였습니다. 다시 입력해주세요.";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goto re2;
		}
		//2) 사용자가 입력한 일정의 이름이 존재하지 않을 경우
		cout << "해당 이름을 가진 일정이 존재하지 않습니다. 이름을 다시 확인해주세요.";
		goto re1;
		//3) 일정이 1개일 경우 
		cout << "일정이 삭제되었습니다." << endl;
		
	}

}
