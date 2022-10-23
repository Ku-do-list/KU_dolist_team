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
	iter = true; // �ݺ� ������ ����Ʈ
	string name; // ���� �̸�
	string category; // ī�װ� �̸�
	string dateNtime; // �ݺ����� ��¥ �� ���ð�
	string dateNtimeIter; // �ݺ� �ִ� ���� �߰� �� ��¥ �� �ð�
	
	vector<string> outname; // ����� ���� �迭
	vector<string> outcategory; // ����� ���� �迭
	vector<string> outdateNtime; // ����� ���� �迭
	vector<string> outdateNtimeIter; // ����� ���� �迭

	vector<int>outindex;
	
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
	while (cin.get(c) && c != '\n' ) // ī�װ� ���Ͽ� �Է� / �����Է��ϸ� ����
	{
		writeFileCategory.put(c);
	}
	writeFileCategory.put('\n');

	
	if (!iter) // �ݺ� ������
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

	if (!iter) // �ݺ�����
	{
		if (readFileList.is_open())
		{

			while (1) // ���� ���� ������ �о����� Ȯ��
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
	
	else //�ݺ�����
	{
		if (readFileList.is_open())
		{

			while (1) // ���� ���� ������ �о����� Ȯ��
			{
				getline(readFileList, name, '/');
				outname.push_back(name);
				getline(readFileList, dateNtime); // ������ ���Ͽ��� /�� �Ľ��� ���� ���� ��¥ �ð��̶� ���� ��¥ �ð��� �ε����� �ٸ� �� ���� �׷��� &�� ����
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
	for (int i = 0; i < outname.size(); i++) // ��ü ����� �� ����Ϸ��� �ϸ� ��¥�� ������ ����� ��¥�� �� �� �ݺ��Ǵ� ������ ����.. �ε����� ã���� ���� ����
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

	cout << "ã�� �̸�?" << endl;
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
		cout << "�����ҰԿ�" << endl;
		create_Listfile(outname, outdateNtime);
		create_Categoryfile(outcategory);
	}
	*/
	readFileList.close(); // ���� ���� �ݱ�
	readFileCategory.close(); // ī�װ� ���� �ݱ�
	
	return 0;
}