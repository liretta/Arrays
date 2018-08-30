#include "Included.h"
#include "BackUp.h"

BackUp ::BackUp(const char *sFileName)
{
	cout << "Constructor BackUp" << endl;
	int nLength = strlen(sFileName) +1;
	if (nLength > _MAX_PATH) 
		return;
	memcpy(m_sFileName, sFileName, nLength); 

}

int BackUp::Write(const void * pData, int nBytes)
{
	int iRet = ERR_ACCESS;//error code to return
	cout << "BackUp Write " << m_sFileName << endl;

	FILE *f;
	errno_t err = fopen_s(&f, m_sFileName, "wb");
	if (f == NULL || f < 0)
	{
		iRet = ERR_FILE_NOT_EXISTS; 
	}
	else
	{
		int nWritten = fwrite(pData, 1, nBytes,f);
		
		iRet = FILE_OK;
		fclose(f);
	}
	
	return iRet;
}

void * BackUp::Read(int *pnReadedBytes, int *pErrCode)
{

	void * pRet = 0;//error code to return
	cout << "BackUp Read" << endl;
	FILE *f;
	*pErrCode = ERR_FILE_NOT_EXISTS;
	errno_t err = fopen_s(&f, m_sFileName, "rb");
	if (f == NULL)
	{
		*pErrCode = ERR_FILE_NOT_EXISTS; 
	}
	else
	{
		fseek(f, 0, SEEK_END);
		int nBytes = ftell(f);

		fseek(f, 0, SEEK_SET);
		if (nBytes == 0)
		{
			*pErrCode = ERR_EMPTY_FILE;
			fclose(f);
		}
		else
		{
			//create char-buffer, 'cose char in any case will be allocated 1 bytes
			//than we will cast it in integer 
			pRet = new char[nBytes];//TODO: here may be axception if we haven't enough mem
			

			int nReaded = fread(pRet, 1, nBytes, f);
			*pnReadedBytes = nBytes;
			*pErrCode = FILE_OK;
			fclose(f);
		}
	}
	return pRet;
}

#ifndef HOMEWORK



int BackUp::Write(const char * sFile, const void * pData, int nDataSize) 
{
	//try to write BackUp file
	const char * BackUpFile = "BackUp.tmp";
	static bool log;
	
	FILE *f;
	errno_t err = fopen_s(&f, BackUpFile, "wb");
	if (f == NULL)
	{
		cout << "Error!! Can't open file for BackUp!" << endl;
		return 1;
	}
	else
	{
		int nWritten = 0;
		int nTotalBytes = 0;
		int nBuff = nDataSize; //counter for bytes to write
		int BytesToWrite = 2000;

		char * psData = (char *)pData;
		while (nTotalBytes < nDataSize)// while nod all bytes with data not writen
		{
			nBuff -= nWritten;
			if (nBuff > BytesToWrite)
				nWritten = fwrite(psData, 1, BytesToWrite, f);// writing to file bytes from 1 to nBuff
			else
				nWritten = fwrite(psData, 1, nBuff, f);

			nTotalBytes += nWritten;
			psData = psData + nWritten; //move the pointer for write to amount butes, wich was allready write 
		}
		nWritten != 0 ? log = true : log = false;
		fclose(f);
	}

	if (log)
	{
		//writing array to file, if BackUp was sucessful
		FILE *f;
		errno_t err = fopen_s(&f, sFile, "wb");
		if (f == NULL)
			{
				cout << "Error!! Can't open file!" << endl;
				return 1;
			}
		else
			{
				int nWritten = 0;
				int nTotalBytes = 0;
				int nBuff = nDataSize; //counter for bytes to write
				int BytesToWrite = 2000;

				char * psData = (char *)pData;
				while (nTotalBytes < nDataSize)// while nod all bytes with data not writen
				{
					nBuff -= nWritten;
					if (nBuff > BytesToWrite)
						nWritten = fwrite(psData, 1, BytesToWrite, f);// writing to file bytes from 1 to nBuff
					else
						nWritten = fwrite(psData, 1, nBuff, f);
					nTotalBytes += nWritten;
					psData = psData + nWritten; 
				}
				fclose(f);
				return 0;
			}
	}
		else
		{
			cout << "Writing fo file wasn't succesful" << endl;
			return 1;
		}
}
#endif // !HOMEWORK

//int Read(const char *sFile, const void * pData, int nDataSize)
//{
//
//	FILE * f;
//	errno_t err = fopen_s(&f, "Students.txt", "rb");
//	if (f == NULL || f < 0)
//	{
//		cout << "Error!!Can't open file!" << endl;
//		break;
//	}
//
//	fseek(f, 0, SEEK_END);
//	int nBytes = ftell(f);
//	nSize2 = nBytes / sizeof(Student);
//
//	fseek(f, 0, SEEK_SET);
//	Student *pStud2 = new Student[nSize2];
//	if (fread(pStud2, sizeof(Student), nSize2, f) < 0)
//		cout << "Error!! Cant read file!" << endl;;
//
//
//}
//


