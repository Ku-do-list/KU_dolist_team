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
    bool check = true;      // 예외 발생 체크
    int sel = -1;
    int year, month, day, hour, min;
    string name, category;

    while (1) {

        system("cls");
        cout << "<일정 추가>\n\n";

        // 1. 일정 이름   :: 엔터 한 번 입력해야하는 버그 디버깅하기
    re1:;
        if (!check) cin.clear(); cin.ignore(INT_MAX, '\n');
        cout << "일정의 이름을 입력해주세요 >> ";
        getline(cin, name);
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

        /*   // 카테고리 확인 구문
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
            if (!isRightSchedule(false, year, month, day, hour, min)) {
                check = false;
                _getch();
                goto re5;
            }
        }
        cout << "\n\"" << sName << "\" 일정 추가가 완료되었습니다.";
        _getch();

        break;
    }
}

// # 예외처리 함수 :: 일정 이름
bool cSchedule::isRightSchedule(string name)
{
    if (name.empty()) {
        cout << ">> 공백 입력 불가. 다시 입력해주세요.\n";
        return false;
    }
    else if (name.length() > 20) {
        cout << ">> 20자 이하로 다시 입력해주세요.\n";
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
            case 1: {   // 매 년 같은 월일 반복
                this->rAnnual.first = sMonth;
                this->rAnnual.second = sDay;
                break;
            }
            case 2: {   // 매 월 같은 날 반복
                this->rMontly = sDay;
                break;
            }
            case 3: {   // 매 주 같은 요일 반복
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
        int sel=0;

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

                if (sType == 4) {
                    cout << "현재 시작 날짜 및 시각: " << sYear << sMonth << sDay << sHour << sMin << endl;
                    cout << "수정된 일정의 시작 날짜 및 시각을 입력해주세요 [ex) 2022 02 03 00 30] \n >> ";

                    cin >> year >> month >> day >> hour >> min;
                    if (!isRightSchedule(true, year, month, day, hour, min)) {
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

                    cin >> year >> month >> day >> hour >> min;
                    if (!isRightSchedule(true, year, month, day, hour, min)) {
                        check = false;
                        _getch();
                        goto re2;
                    }
                    else {
                        //데이터 파일에 넣어주기
                    }

                    cout << "현재 마감 날짜 및 시각: " << sYear << sMonth << sDay << sHour << sMin << endl;
                    cout << "수정된 일정의 마감 날짜 및 시각을 입력해주세요 [ex) 2022 02 03 00 30] \n >> ";

                    cin >> eyear >> emonth >> eday >> ehour >> emin;
                    if (!isRightSchedule(false, eyear, emonth, eday, ehour, emin)) {
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