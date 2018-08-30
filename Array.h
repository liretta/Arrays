#pragma once
class BackUp;

class Array
{
	int mnSize, m_iCurInd;
	int * mpAr;
	BackUp * m_pBackUp;
	void addMemory();

public:
	Array(int nSize);
	~Array();
	Array(const Array &R); //own copy-constructor
	void push_back(int a);
	void Show();

	int Save(); //return error-code
	int LoadFromFile();

	//int Load(const char * sFileName);
	void SetBackUp(BackUp * pBackUp); //function to move a pointer from external source to class
};