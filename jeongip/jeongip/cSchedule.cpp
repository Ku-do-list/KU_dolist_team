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

// $ NEW : 날짜 입력 시 int -> string 타입 교체 및 예외처리
void cSchedule::makeSchedule(string* category, int& categorySize)
{
	writeFileList.open("KU_do_list.txt", ios::out | ios::app);
	writeFileCategory.open("KU_do_list_category.txt", ios::out | ios::app);
	bool check = true;		// 예외 발생 체크
	int sel = -1;
	//int year, month, day, hour, min;
	string name;

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
			char ch1[40] = ""; //초기화 적용
			strcpy(ch1, name.c_str());
			writeFileList.put('\n');
			writeFileList.write(ch1, sizeof(ch1));
			writeFileList.put('/');
		}

		// 2. 일정 카테고리
	re2:;
		while (1) {
			cin.clear(); cin.ignore(INT_MAX, '\n');
			category[categorySize] = "직접 입력";
			categorySize++;
			for (int i = 0; i < categorySize; i++) {
				cout << i + 1 << ". " << category[i] << " ";
			}
			cout << endl;
			category[categorySize] = "";
			categorySize--;
			cout << "일정의 카테고리 번호를 입력해주세요 >> ";
			cin >> categoryNum;

			// @ 예외처리
			if (!categoryNum) {
				cout << "숫자만 입력하세요. " << endl << endl;
			}
			else if (categoryNum < 1 || categoryNum >categorySize + 1) {
				cout << "1~" << categorySize + 1 << "사이의 숫자만 입력해주세요 " << endl << endl;
			}
			else if (categoryNum - 1 == categorySize) {
				cout << "<카테고리 추가>" << endl;
				while (1) {
					cin.clear(); cin.ignore(INT_MAX, '\n');
					cout << "추가하실 카테고리 이름을 입력해주세요(모든 기호 사용 제외) >>";
					getline(cin, s);

					if (!isRightSchedule(s)) {
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
				}
			}
			else {
				char ch[20] = "";
				strcpy(ch, category[categoryNum - 1].c_str());
				this->sCategory = category[categoryNum - 1];
				writeFileList.write(ch, sizeof(ch));
				writeFileList.put(' ');
				writeFileCategory.write(ch, sizeof(ch));
				writeFileCategory.put('\n');
				break;
			}
		}
		writeFileCategory.close();


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
			writeFileList.put((char)(sel + 48));
			writeFileList.put(' ');
		}


		// 4. 시작 및 마감 날짜 입력
	re4:;
		string Stime;

		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "일정의 시작 날짜 및 시각을 입력해주세요 [ex) 2022 12 25 15 00] >> ";
		getline(cin, Stime);
		//cout << Stime << " => 입력 시간 체크\n사이즈 : " << Stime.size();
		if (!isRightTimeString(true, Stime)) {
			check = false;
			_getch();
			goto re4;
		}
		else {
			//transTimeToInt(true, Stime);
			string sresult = Stime;
			char ch4[20] = "";
			strcpy(ch4, sresult.c_str());
			writeFileList.write(ch4, sizeof(ch4));
		}

	re5:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		if (sel == 4) {
			string Etime;
			cout << "일정의 마감 날짜 및 시각을 입력해주세요 [ex) 2022 12 30 17 00] >> ";
			getline(cin, Etime);
			if (!isRightTimeString(false, Etime)) {
				check = false;
				_getch();
				goto re5;
			}
			else {
				string sresult = "&" + Etime;
				char ch4[20] = "";
				strcpy(ch4, sresult.c_str());
				writeFileList.write(ch4, sizeof(ch4));
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
bool cSchedule::isSign(std::string name) {
	for (size_t i = 0; i < name.length(); i++) {
		if ((name.at(i) > 32 && name.at(i) < 48) || (name.at(i) > 57 && name.at(i) < 65) ||
			(name.at(i) > 90 && name.at(i) < 97) || (name.at(i) > 122 && name.at(i) < 127)) {
			cout << ">> 특수문자 입력 불가. 다시 입력해주세요.\n\n";
			return false;
		}
	}
}

// # 예외처리 함수 :: 일정 이름
bool cSchedule::isRightSchedule(string name)
{
	if (name.empty()) {
		cout << ">> 공백 입력 불가. 다시 입력해주세요.\n";
		return false;
	}

	char* s;
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
		cout << "20자 이하로 다시 입력해주세요.\n";
		return false;
	}

	for (size_t i = 0; i < name.length(); i++) {
		if ((name.at(i) > 32 && name.at(i) < 48) || (name.at(i) > 57 && name.at(i) < 65) ||
			(name.at(i) > 90 && name.at(i) < 97) || (name.at(i) > 122 && name.at(i) < 127)) {
			cout << ">> 특수문자 입력 불가. 다시 입력해주세요.\n";
			return false;
		}
	}

	this->sName = name;
	return true;
}

// # 예외처리 함수 :: 반복 타입
bool cSchedule::isRightSchedule(int type)
{
	if (!cin) {
		cout << ">> 올바른 입력을 해주세요.\n\n";
		return false;
	}
	else if (!(type == 1 || type == 2 || type == 3 || type == 4)) {
		cout << ">> 1에서 4 사이의 값을 입력해주세요.\n\n";
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
		cout << ">> 올바른 입력을 해주세요.\n";
		return false;
	}
	else {
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
				//cout << "\n 요일 : " << this->rWeekly << '\n';
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

// $ NEW : 날짜 및 시각 입력 시 형식 체크, 옳은 형식일 시 자동 등록까즤
bool cSchedule::isRightTimeString(bool isStart, string time)
{
	// 여기서 transTimeToInt 써야함, isStart 멤버 추가해서 유동적 수정 해보자...
	if (time.size() != 16) {
		cout << ">> 올바른 형식의 입력을 해주세요.\n";
		return false;
	}

	for (int i = 0; i < 16; i++) {
		if(i==4 || i==7 || i==10 || i==13){
			if (!(time.at(i) == 32)) {
				cout << ">> 올바른 형식의 입력을 해주세요.\n";
				return false;
			}
		}
		else {
			if (!(time.at(i) >= '0' && time.at(i) <= '9')) {
				cout << ">> 올바른 형식의 입력을 해주세요.\n";
				return false;
			}
		}
	}

	if (transTimeToInt(isStart, time))
		return true;
	else
		return false;
}

// $ NEW : string -> int로 날짜 바꿔서 예외처리 후 입력
bool cSchedule::transTimeToInt(bool isStart, string time)
{
	int year, month, day, hour, min;

	year = (int)((time.at(0) - 48) * 1000 + (time.at(1) - 48) * 100 + (time.at(2) - 48) * 10 + (time.at(3) - 48));
	month = (int)((time.at(5) - 48) * 10 + (time.at(6) - 48));
	day = (int)((time.at(8) - 48) * 10 + (time.at(9) - 48));
	hour = (int)((time.at(11) - 48) * 10 + (time.at(12) - 48));
	min = (int)((time.at(14) - 48) * 10 + (time.at(15) - 48));
	
	if (isRightSchedule(isStart, year, month, day, hour, min)) {
		return true;
	}
	else {
		return false;
	}
}

void cSchedule::deleteSchedule()
{
	string delete_name;
	bool check = true;

	while (1) {
		system("cls");
		cout << "<일정 삭제>\n\n";

		// 1. 일정 이름
	re1:;
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "삭제할 일정의 이름을 입력해주세요 >> ";
		getline(cin, delete_name);
		if (!isRightSchedule(delete_name)) {
			check = false;
			_getch();
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
			cout << "\n<카테고리 추가>" << endl;
			while (1) {
				cin.clear(); cin.ignore(INT_MAX, '\n');
				cout << "추가하실 카테고리 이름을 입력해주세요(모든 기호 사용 제외) >>";
				getline(cin, s);

				if (!isRightSchedule(s)) {
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
					cout << "숫자만 입력하세요 >>\n";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				else if (categoryNum < 1 || categoryNum >categorySize) {
					cout << "범위 사이의 숫자만 입력해주세요 >>\n";
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
				cout << "사전에 있는 카테고리 입니다.\n" << endl;
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

void cSchedule::edit_Schedule() {
	bool check = true;      // 예외 발생 체크
	int sel = -1;
	int done;
	int year, month, day, hour, min; //시작 날짜
	int eyear, emonth, eday, ehour, emin; //마감 날짜
	int repeat = 0;
	string name, category;

	while (1) {

		system("cls");
		int sel = 0;

		// 1. 일정 이름   :: 엔터 한 번 입력해야하는 버그 디버깅하기
		if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');

		while (sel != 6) {
			sel = showmenu_edit();//12345 중에 골라서 sel에 넘겨받음;
			srand((unsigned)time(NULL));

			system("cls");
			switch (sel) {
			case 1: {
				//edit_Schedule_sName();
			re1:;
				if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
				cout << "현재 이름: " << sName << endl;
				cout << "수정된 일정의 이름을 입력해주세요 >> ";
				getline(cin, name);
				if (!isRightSchedule(name)) {
					check = false;
					_getch();
					goto re1;
				}
				else {
					//데이터 파일에 넣어주기
				}
				cout << "일정 이름 편집이 완료되었습니다.";
				_getch();
				break;
			}
			case 2: { //반복 여부에 따라 case 나누기**
			   //edit_Schedule_sDate();
				  // 4. 시작 및 마감 날짜 입력
			re2:;
				if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');

				string Stime;
				if (sType == 4) {
					cout << "현재 시작 날짜 및 시각: " << sYear << sMonth << sDay << sHour << sMin << endl;
					cout << "수정된 일정의 시작 날짜 및 시각을 입력해주세요 [ex) 2022 02 03 00 30] \n >> ";

					getline(cin, Stime);
					if (!isRightTimeString(true, Stime)) {
						check = false;
						_getch();
						goto re2;
					}
					else {
						//데이터 파일에 넣어주기
					}
					cout << "일정 시작 및 마감 날짜 편집이 완료되었습니다.";
				}
				else {
					cout << "현재 시작 날짜 및 시각: " << sYear << sMonth << sDay << sHour << sMin << endl;
					cout << "수정된 일정의 시작 날짜 및 시각을 입력해주세요 [ex) 2022 02 03 00 30] \n >> ";

					getline(cin, Stime);
					if (!isRightTimeString(true, Stime)) {
						check = false;
						_getch();
						goto re2;
					}
					else {
						//데이터 파일에 넣어주기
					}

					cout << "현재 마감 날짜 및 시각: " << sYear << sMonth << sDay << sHour << sMin << endl;
					cout << "수정된 일정의 마감 날짜 및 시각을 입력해주세요 [ex) 2022 02 03 00 30] \n >> ";
					string Etime;
					getline(cin, Etime);
					if (!isRightTimeString(false, Etime)) {
						check = false;
						_getch();
						goto re2;
					}
					else {
						//데이터 파일에 넣어주기
					}
					cout << "일정 시작 및 마감 날짜 편집이 완료되었습니다.";
				}

				_getch();
				break;
			}

			case 3: { //찬규가 하기
			   //edit_Schedule_sCategory();
			re3:;
				if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
				cout << "일정의 카테고리를 입력해주세요 >> ";
				cin >> category;

				/*   // 카테고리 확인 구문
				for (size_t i = 0; i < categoryNum; i++) {
				   if (category.compare(categoryData[i])) {
					  this->sCategory = category;
				   }
				   else {
					  cout << ">> 해당 카테고리가 존재하지 않습니다.";
					  system("pause");
					  goto re3;
				   }
				}
				*/
				break;
			}
			case 4: {
				//edit_Schedule_sRepeat();
				// 일정 반복 기능
			re4:;
				if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');

				cout << "현재 반복 (1: 연반복, 2: 월반복, 3: 주반복, 4: 반복X): " << sType << endl;
				cout << "수정된 일정의 반복 기능을 설정해주세요 1)연 반복 2)월 반복 3)요일 반복 4)반복 없음 >> ";

				cin >> sel;
				if (!isRightSchedule(sel)) {
					check = false;
					_getch();
					goto re4;
				}
				else {
					//데이터 파일에 넣어주기
				}
				break;
			}
			case 5: { //반복 여부에 따라 case 나누기**
			   //edit_Schedule_sEndorNot();
			   // 5. 일정 완료 여부
			re5:;
				if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
				cout << "현재 (0(default): 완료, 1: 미완료): " << sIsDone << endl;

				cout << "수정된 일정의 완료 여부를 선택해주세요 1) 완료 2) 진행 중 >> ";
				cin >> done;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << ">> 올바른 입력 값을 다시 입력하세요.\n";
					_getch();
					goto re5;
				}
				else if (done < 1 || done > 2) { //??
					cout << ">> 1에서 5 사이의 값을 입력해주세요.\n";
					_getch();
					goto re5;
				}
				//데이터 파일 넣어주기
				break;
			}
			}
		}
	}
}

// # 예외처리 함수 :: 편집/ 고르세용!
int cSchedule::showmenu_edit() {
	int sel;
re:;

	system("cls");
	cout << "일정의 편집할 내용을 선택하세요. \n";
	cout << "1)이름 2)날짜 및 시각 3)카테고리 4)반복기능 ";

	if (sType == 4) {
		cout << "5)일정 완료 여부 >> ";

		cin >> sel;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << ">> 올바른 입력 값을 다시 입력하세요.\n";
			_getch();
			goto re;
		}
		else if (sel < 1 || sel > 5) {
			cout << ">> 1에서 5 사이의 값을 입력해주세요.\n";
			_getch();
			goto re;
		}

	}
	else {
		cout << ">> ";

		cin >> sel;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << ">> 올바른 입력 값을 다시 입력하세요.\n";
			_getch();
			goto re;
		}
		else if (sel < 1 || sel > 4) {
			cout << ">> 1에서 4 사이의 값을 입력해주세요.\n";
			_getch();
			goto re;
		}
	}
	return sel;
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
	string day[7] = { "일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일" };
	return day[weekly];
}

void cSchedule::setsName(const string& name)
{
	this->sName = name;
}

void cSchedule::setRepeat(const int& type, const cSchedule& _list)
{
	bool isLeaf;
	if (_list.sYear % 4 == 0 && _list.sYear % 100 != 0 || _list.sYear % 400 == 0)
		isLeaf = true;
	else
		isLeaf = false;
	int m[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	m[1] = isLeaf ? 29 : 28;
	int a = 0, b = 0;
	bool check = 1;
re:;
	if (type == 1) {
		cout << "수정할 반복 월일을 입력해주세요 [ex) 06 10] >> ";
		cin >> a >> b;
		if (cin.fail()) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else if (a < 1 || a > 12) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else if (b < 1 || b>m[a-1]) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else {
			this->rAnnual.first = a;
			this->rAnnual.second = b;
			cout << "일정의 연 반복 주기가 변경 완료되었습니다.\n";
		}
	}
	else if (type == 2) {
		cout << "수정할 반복 일을 입력해주세요 [ex) 10] >> ";
		cin >> a;
		if (cin.fail()) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else if (a < 1 || a > 31) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else {
			this->rMontly = a;
			cout << "일정의 월 반복 주기가 변경 완료되었습니다.\n";
		}
	}
	else if (type == 3) {
		cout << "수정할 반복 요일을 입력해주세요 [0=일요일, 6=월요일] >> ";
		cin >> a;
		if (!cin) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else if (a < 0 || a > 6) {
			cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
			check = false;
			_getch();
			goto re;
		}
		else {
			this->rWeekly = a;
			cout << "일정의 요일 반복 주기가 변경 완료되었습니다.\n";
		}
	}
	_getch();
}

void cSchedule::setIsDone(const bool& is)
{
	this->sIsDone = is;
}

void cSchedule::setsType(const int& type)
{
	this->sType = type;
}