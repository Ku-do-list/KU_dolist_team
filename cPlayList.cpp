// ****** cPlayList.cpp ******
#include "cPlayList.h"


cPlayList::cPlayList()
{
    this->list = new cSchedule[100];

    // +a ) ���� �� ī�װ� Data ���� By file �Է�
    /*

    Data ���� ����

    12                  -> &sCount
    1 / 0 2022 10 12 19 30      -> //index[0]
                            &sType-(1: ���ݺ�, 2: ��, 3: ��, 4: �ݺ� ����),
                            &sIsDone(0: ����, 1: ������),
                            &��¥
    4 1 2022 10 1 10 30&2022 10 2 11 0   -> �������� (Ÿ�� �޾Ƽ� �б� �ڵ� ���� �� ��)
    */

    /*
    categoryData ���� ����
    4            -> &cateroryNum
    // ���� categoryData = new string[num] ���ְ�
    �         -> &categoryData[0]
    ���         -> ~[1]
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

    // �޸� ��ȯ :: ī�װ�
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
        cout << ">> ������ �� �̻� �߰��� �� �����ϴ�.\n";
        _getch();
    }
}
void cPlayList::editSchedule(int index)
{
    list[index].edit_Schedule();
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
            printf("2. ��������");
            break;
        }
        case 3: {
            printf("3. ����Ȯ��");
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
            printf("5. ī�װ� ����");
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
    cout << "1) ���� �߰� 2) ���� ���� 3) ���� Ȯ�� 4) ���� ���� 5) ī�װ� ���� 6) ����\n"
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