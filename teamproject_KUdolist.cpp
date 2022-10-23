#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

/*void create_Listfile(vector <string> outname, vector <string> outdateNtime)
{
	ofstream writeFileList;
	writeFileList.open("KU_do_list.txt", ios::out | ios::trunc);
	if (writeFileList.fail()) // 일정 파일 열기 실패
	{
		cout << "KU_do_list.txt 파일을 열 수 없습니다." << endl;
	}
	for (int i = 0; i < outname.size(); i++)
	{
		writeFileList << outname[i] << '/' ;
		writeFileList << outdateNtime[i] << endl;
	}

	writeFileList.close();
}

void create_Categoryfile(vector <string> outCategory)
{
	ofstream writeFileCategory;
	writeFileCategory.open("KU_do_list_category.txt", ios::out | ios::trunc);
	if (writeFileCategory.fail()) // 일정 파일 열기 실패
	{
		cout << "KU_do_list_category.txt 파일을 열 수 없습니다." << endl;
	}
	for (int i = 0; i < outCategory.size(); i++)
	{
		writeFileCategory << outCategory[i]<<endl;
	}

	writeFileCategory.close();
}
*/
int main(void)
{
	char c; // 입력할 때 사용
	bool iter; // 반복여부 확인
	iter = true; // 반복 없음이 디폴트
	string name; // 일정 이름
	string category; // 카테고리 이름
	string dateNtime; // 반복없는 날짜 및 종시간
	string dateNtimeIter; // 반복 있는 일정 추가 시 날짜 및 시간
	
	vector<string> outname; // 출력할 때의 배열
	vector<string> outcategory; // 출력할 때의 배열
	vector<string> outdateNtime; // 출력할 때의 배열
	vector<string> outdateNtimeIter; // 출력할 때의 배열

	vector<int>outindex;
	
	int index; // 찾는 값의 인덱스
	string key; //찾는 내용
	
	bool replace;
	replace = false;
	

	/*파일 쓰기*/
	ofstream writeFileList;
	ofstream writeFileCategory;
	writeFileList.open("KU_do_list.txt", ios::out | ios:: app); // 일정 파일 열기(없으면 만들어짐)
	writeFileCategory.open("KU_do_list_category.txt", ios::out | ios::app); // 카테고리 파일 열기(없으면 만들어짐)

	if (writeFileList.fail()) // 일정 파일 열기 실패
	{
		cout << "KU_do_list.txt 파일을 열 수 없습니다." << endl; 
	}

	if (writeFileCategory.fail()) // 카테고리 파일 열기 실패
	{
		cout << "KU_do_list_category.txt 파일을 열 수 없습니다." << endl;
	}

	cout << "이름 " << endl;
	while (cin.get(c) && c != '\n') // 일정 파일에 입력 / 엔터입력하면 종료 / 이름 입력
	{
		writeFileList.put(c);
	}
	writeFileList.put('/');
	
	cout << "카테고리이름 " << endl;
	while (cin.get(c) && c != '\n' ) // 카테고리 파일에 입력 / 엔터입력하면 종료
	{
		writeFileCategory.put(c);
	}
	writeFileCategory.put('\n');

	
	if (!iter) // 반복 있으면
	{
		cout << "날짜 " << endl;
		while (cin.get(c) && c != '\n') // 일정 파일에 입력 / 엔터입력하면 종료 / 시작 날짜
		{
			writeFileList.put(c);
		}
		writeFileList.put('\n');
	}
	else // 반복 없으면
	{
		cout << "시작 날짜 및 시간" << endl;
		while (cin.get(c) && c != '\n') // 일정 파일에 입력 / 엔터입력하면 종료 / 시작 날짜 및 시각
		{
			writeFileList.put(c);
		}
		writeFileList.put('&');

		cout << "마감 날짜 및 시간" << endl;
		while (cin.get(c) && c != '\n') // 일정 파일에 입력 / 엔터입력하면 종료 / 마감 날짜 및 시각
		{
			writeFileList.put(c);
		}
		writeFileList.put('\n');
	}


	writeFileList.close(); // 일정 파일 닫기
	writeFileCategory.close(); // 카테고리 파일 닫기
	
	/*파일 읽기*/
	ifstream readFileList;
	ifstream readFileCategory;
	readFileList.open("KU_do_list.txt"); // 일정 파일 열기
	readFileCategory.open("KU_do_list_category.txt"); // 카테고리 파일 열기

	if (!readFileList) // 일정 파일 열기 실패
	{
		cerr << "KU_do_list.txt 파일을 열 수 없습니다." << endl;
		exit(1);
	}

	if (!readFileCategory) // 카테고리 파일 열기 실패
	{
		cerr << "KU_do_list_category.txt 파일을 열 수 없습니다." << endl;
		exit(1);
	}

	if (!iter) // 반복있음
	{
		if (readFileList.is_open())
		{

			while (1) // 일정 파일 끝까지 읽었는지 확인
			{
				getline(readFileList, name, '/');
				outname.push_back(name);
				getline(readFileList, dateNtimeIter);
				outdateNtimeIter.push_back(dateNtimeIter);
				if (readFileList.eof())
					break;
			}

		}
	}
	
	else //반복없음
	{
		if (readFileList.is_open())
		{

			while (1) // 일정 파일 끝까지 읽었는지 확인
			{
				getline(readFileList, name, '/');
				outname.push_back(name);
				getline(readFileList, dateNtime); // 데이터 파일에서 /로 파싱할 때에 시작 날짜 시간이란 마감 날짜 시간의 인덱스가 다를 수 있음 그래서 &로 설정
				outdateNtime.push_back(dateNtime);
				if (readFileList.eof())
					break;
			}

		}
	}

	if (readFileCategory.is_open())
	{
		
		while (1)
		{
			getline(readFileCategory, category);
			outcategory.push_back(category);
			if (readFileCategory.eof())
				break;
		}
	}

	/* 
	for (int i = 0; i < outname.size(); i++) // 전체 목록을 다 출력하려고 하면 날짜가 마지막 저장된 날짜가 두 번 반복되는 현상이 있음.. 인덱스로 찾으면 문제 없음
	{
		cout << outname[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < outdateNtimeIter.size(); i++)
	{
		cout << outdateNtimeIter[i] << endl;
	}
	cout << endl;
	for (int i = 0; i < outcategory.size(); i++)
	{
		cout << outcategory[i] << endl;;
	}
	*/

	cout << "찾는 이름?" << endl;
	cin >> key;

	for (int j = 0; j < outname.size(); j++)
	{
		if (outname[j] == key)
		{
			outindex.push_back(j);
		}
	}

	for (int j = 0; j < outindex.size(); j++)
	{
		index = outindex[j];
		cout << outname[index] << endl;
	}
	for (int j = 0; j < outindex.size(); j++)
	{
		index = outindex[j];
		cout << outcategory[index] << endl;
	}
	for (int j = 0; j < outindex.size(); j++)
	{
		index = outindex[j];
		cout << outdateNtime[index] << endl;
	}
	//outname.erase(outname.begin() + 1);
	/*
	if (replace)
	{
		cout << "수정할게용" << endl;
		create_Listfile(outname, outdateNtime);
		create_Categoryfile(outcategory);
	}
	*/
	readFileList.close(); // 일정 파일 닫기
	readFileCategory.close(); // 카테고리 파일 닫기
	
	return 0;
}