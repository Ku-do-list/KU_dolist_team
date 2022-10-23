#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

/*void create_Listfile(vector <string> outname, vector <string> outdateNtime)
{
	ofstream writeFileList;
	writeFileList.open("KU_do_list.txt", ios::out | ios::trunc);
	if (writeFileList.fail()) // ���� ���� ���� ����
	{
		cout << "KU_do_list.txt ������ �� �� �����ϴ�." << endl;
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
	if (writeFileCategory.fail()) // ���� ���� ���� ����
	{
		cout << "KU_do_list_category.txt ������ �� �� �����ϴ�." << endl;
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
	char c; // �Է��� �� ���
	bool iter; // �ݺ����� Ȯ��
	iter = false; // �ݺ� ������ ����Ʈ
	string name; // ���� �̸�
	string category; // ī�װ� �̸�
	string dateNtimeFirst; // �ݺ����� ��¥ �� ���۽ð�
	string dateNtimeLast; // �ݺ����� ��¥ �� ����ð�
	string dateNtimeIter; // �ݺ� �ִ� ���� �߰� �� ��¥ �� �ð�
	string Iter;
	string Done;
	int num = 0;
	vector<string> outname; // ����� ���� �迭
	vector<string> outcategory; // ����� ���� �迭
	vector<string> outdateNtimeFirst; // ����� ���� �迭
	vector<string> outdateNtimeLast; // ����� ���� �迭
	vector<string> outdateNtimeIter; // ����� ���� �迭
	vector<string> outIter;// ����� ���� �迭
	vector<string> outDone;// ����� ���� �迭
	vector<int>outindex;
	
	vector<vector<string>> all(100); //��ü �迭

	//vector<string> allin;
	//all.push_back(allin);

	int ai=0; // ��ü�迭 index
	
	int index; // ã�� ���� �ε���
	string key; //ã�� ����
	
	bool replace;
	replace = false;
	

	/*���� ����*/
	ofstream writeFileList;
	ofstream writeFileCategory;
	writeFileList.open("KU_do_list.txt", ios::out | ios:: app); // ���� ���� ����(������ �������)
	writeFileCategory.open("KU_do_list_category.txt", ios::out | ios::app); // ī�װ� ���� ����(������ �������)

	if (writeFileList.fail()) // ���� ���� ���� ����
	{
		cout << "KU_do_list.txt ������ �� �� �����ϴ�." << endl; 
	}

	if (writeFileCategory.fail()) // ī�װ� ���� ���� ����
	{
		cout << "KU_do_list_category.txt ������ �� �� �����ϴ�." << endl;
	}

	cout << "�̸� " << endl;
	while (cin.get(c) && c != '\n') // ���� ���Ͽ� �Է� / �����Է��ϸ� ���� / �̸� �Է�
	{
		writeFileList.put(c);
	}
	writeFileList.put('/');

	cout << "ī�װ��̸� " << endl;
	while (cin.get(c) && c != '\n') // ī�װ� ���Ͽ� �Է� / �����Է��ϸ� ����
	{
		writeFileCategory.put(c);
		writeFileList.put(c);
	}
	writeFileList.put('/');
	writeFileCategory.put('\n');
	
	cout << "�ݺ����� " << endl;
	while (cin.get(c) && c != '\n') // ���� ���Ͽ� �Է� / �����Է��ϸ� ���� / �ݺ���� �Է�
	{
		writeFileList.put(c);
		if (c != '4')
		{
			iter = true;
		}
	}
	writeFileList.put('/');

	cout << "�����ϷῩ�� ���� " << endl;
	//while (cin.get(c) && c != '\n') // ���� ���Ͽ� �Է� / �����Է��ϸ� ���� / �����ϷῩ�� �Է�
	//{
	//	writeFileList.put(c);
	//}
	writeFileList << "����";
	writeFileList.put('/');
	
	if (iter) // �ݺ� ������
	{
		cout << "��¥ " << endl;
		while (cin.get(c) && c != '\n') // ���� ���Ͽ� �Է� / �����Է��ϸ� ���� / ���� ��¥
		{
			writeFileList.put(c);
		}
		writeFileList.put('\n');
	}
	else // �ݺ� ������
	{
		cout << "���� ��¥ �� �ð�" << endl;
		while (cin.get(c) && c != '\n') // ���� ���Ͽ� �Է� / �����Է��ϸ� ���� / ���� ��¥ �� �ð�
		{
			writeFileList.put(c);
		}
		writeFileList.put('&');

		cout << "���� ��¥ �� �ð�" << endl;
		while (cin.get(c) && c != '\n') // ���� ���Ͽ� �Է� / �����Է��ϸ� ���� / ���� ��¥ �� �ð�
		{
			writeFileList.put(c);
		}
		writeFileList.put('\n');
	}
	writeFileList.close(); // ���� ���� �ݱ�
	writeFileCategory.close(); // ī�װ� ���� �ݱ�
	
	/*���� �б�*/
	ifstream readFileList;
	ifstream readFileCategory;
	readFileList.open("KU_do_list.txt"); // ���� ���� ����
	readFileCategory.open("KU_do_list_category.txt"); // ī�װ� ���� ����

	if (!readFileList) // ���� ���� ���� ����
	{
		cerr << "KU_do_list.txt ������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	if (!readFileCategory) // ī�װ� ���� ���� ����
	{
		cerr << "KU_do_list_category.txt ������ �� �� �����ϴ�." << endl;
		exit(1);
	}

	

	if (readFileList.is_open())
	{
		while (1) // ���� ���� ������ �о����� Ȯ��
		{
			getline(readFileList, name, '/');
			all[ai].push_back(name);
			getline(readFileList, category, '/');
			getline(readFileList, Iter, '/');
			all[ai].push_back(Iter);
			if (Iter != "4")
			{
				getline(readFileList, Done, '/');
				all[ai].push_back(Done);
				getline(readFileList, dateNtimeIter);
				all[ai].push_back(dateNtimeIter);

			}
			else
			{
				getline(readFileList, Done, '/');
				all[ai].push_back(Done);
				getline(readFileList, dateNtimeFirst, '&');
				all[ai].push_back(dateNtimeFirst);
				getline(readFileList, dateNtimeLast, '\n');
				all[ai].push_back(dateNtimeLast);
			}
			ai++;
			if (readFileList.eof())
			{
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
	for (int i = 0; i < outcategory.size(); i++)
	{
		cout << outcategory[i] << endl;
	}
	*/
	readFileList.close(); // ���� ���� �ݱ�
	readFileCategory.close(); // ī�װ� ���� �ݱ�
	
	return 0;
}