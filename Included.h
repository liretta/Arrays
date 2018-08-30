#pragma once
#include <iostream>
#include <iomanip>
#include <string.h>
#include <time.h>
#define HOMEWORK

using namespace std;
enum FileErrorCode { 
	ERR_FILE_NOT_EXISTS, 
	FILE_OK, ERR_ACCESS, 
	ERR_EMPTY_FILE, 
	BACK_UP_ISNT_INITIALIZED,
	ERR_NO_DATA_TO_WRITE //if we haven't data for writing (exmpl. array is empty)
};

