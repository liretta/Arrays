#pragma once
#include "Included.h"



class BackUp
{
	char m_sFileName[_MAX_PATH]; //variable-array to storage file name

public:
	BackUp(const char * sFileName);
	~BackUp() { cout << "Destructor BackUp" << endl; };
	int Write(const void * pData, int nBytes);
	/*
	pnReadedBytes [out] - return amount of read bytes - in fact it is file size (from "write")
	pErrCode [out] - return error code after work with file (from "write")
	@RETURN pointer to read data
	
	*/
	void * Read(int *pnReadedBytes, int *pErrCode);

};

