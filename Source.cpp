#include "Included.h"
#include "Array.h"
#include "BackUp.h"
#define HOMEWORK

using namespace std;

void Mem();

int main()
{
	int iChoice = 0;
	cout << "Enter 1 to WRITE file" << endl;
	cout << "Enter 2 to READ file" << endl;
	cin >> iChoice;
	BackUp * pBu = new BackUp("test2.txt");
	if (iChoice == 1)
	{
		int nSize, nSize2;
		cout << "Enter basic size of arrays: ";
		cin >> nSize;

		cout << "Enter basic of second arrays: ";
		cin >> nSize2;
		Array ar(nSize), ar2(nSize2);

		for (int i = 0; i < 20; ++i)
			ar.push_back(rand() % 100);

		for (int i = 0; i < 12; ++i)
			ar2.push_back(rand() % 2);

		ar.Show();
		ar2.Show();
		cout << "----------------" << endl;

		
		ar.SetBackUp(pBu);
		int iErrCode = ar.Save();
		if (iErrCode == ERR_ACCESS)
			cout << "Erorr access" << endl;
		else
			cout << "All int data was saved" << endl;
		
		cout << "----------------" << endl;
		
#ifndef HOMEWORK

		srand((unsigned int)time);

		int nSize, nSize2;
		cout << "Enter basic size of arrays: ";
		cin >> nSize;

		cout << "Enter basic of second arrays: ";
		cin >> nSize2;


		{
			Array ar(nSize), ar2(nSize2);

			for (int i = 0; i < 20; ++i)
				ar.push_back(rand() % 100);

			for (int i = 0; i < 12; ++i)
				ar2.push_back(rand() % 2);

			ar.Show();
			ar2.Show();

			Array ar3(ar);
			ar3.Show();
			int iError = ar.Save("data.txt");
		}
		cout << "sizeof Array" << sizeof(Array) << endl;


#endif // !HOMEWORK
		
	}
	else
	{
		Array ar(0);
		ar.SetBackUp(pBu);
		int iErrCode = ar.LoadFromFile();
		if (iErrCode == ERR_ACCESS)
			cout << "Erorr open file" << endl;
		else
		{
			cout << "All int data was loaded" << endl;
			ar.Show();
		}
		
		//for checkoing loaded array:
		for (int i = 0; i < 3; ++i)
			ar.push_back(5);

		cout << "show new array" << endl;
		ar.Show();
	}
	delete pBu; //delete backUp
	Mem();

	system("pause");
	return 0;
}

void Mem()
{
	if (_CrtDumpMemoryLeaks())
		cout << "Error" << endl;
	else
		cout << "mem OK!" << endl;
}

