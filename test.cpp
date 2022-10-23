#include <iostream>
#include <regex>
//#include <string>
using namespace std;


/*class schedule(){
    public:

    void add_category(){
        category
    }
}*/
bool isSign(std::string const& str) {
    return std::regex_match(str, std::regex("^[가-힣A-Aa-z0-9]+$"));
}

int main() {
    int user = 0;
    string category[100] = { "" }; //카테고리 배열 선언(개수제한 100개)
    int categoryNum = 3;
    int categorySize = 3;
    bool duplicate = false;
    string s = "";
    category[0] = "운동";
    category[1] = "공부";
    category[2] = "취미";

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
            //break;
        }
        else if (user == 2)
        {
            cout << "<카테고리 편집>";
            /////// 부분은 합칠 때 함수로 만들것입니다.
            //category[categorySize] = "직접 입력";
            //categorySize++;
            for (int i = 0; i < categorySize; i++) {
                cout << i + 1 << ". " << category[i] << " ";
            }
            cout << endl;
            //category[categorySize] = "";
            //categorySize--;
            ///////
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
                category[categoryNum-1] = s;
                cout << "변경되었습니다.";
            }
            else {
                cout << "사전에 있는 카테고리 입니다." << endl;
                duplicate = false;
            }
            //break;
        }
        else if (user == 3)
        {
            cout << "<카테고리 삭제>";
            /////// 부분은 합칠 때 함수로 만들것입니다.
            for (int i = 0; i < categorySize; i++) {
                cout << i + 1 << ". " << category[i] << " ";
            }
            cout << endl;
            ///////
            cout << "삭제하실 카테고리 번호를 입력해주세요(모든 기호 사용 제외)>>";
            cin >> categoryNum;
            for (int i = categoryNum-1; i < categorySize; i++) {
                category[i] = category[i + 1];
            }
            categorySize--;
        }
    }
    category[categorySize] = "직접 입력";
    categorySize++;
    for (int i = 0; i < categorySize; i++) {
        cout << i + 1 << ". "<<category[i]<<" ";
    }


    return 0;


}