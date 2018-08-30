#include "Included.h"
#include "Array.h"
#include "BackUp.h" 

using namespace std;

//constructor (init array)

Array::Array(int nSize) :mnSize(nSize), m_iCurInd(0),
mpAr(0), m_pBackUp(0)
{
	if (nSize <= 0) 
		mnSize = 0;
	else
	{
		mpAr = new int[mnSize];
	}
	cout << "Array (int)" << this << ' ' << mnSize << endl;

}

Array::~Array()
{
	if (mpAr != 0)
		delete[] mpAr;
	cout << "Array (int)" << this << ' ' << "CurInd " << m_iCurInd << endl;
}

void Array::push_back(int a)
{
	if (m_iCurInd == mnSize)
		addMemory(); //private function for array increase
	mpAr[m_iCurInd++] = a;

}

void Array::addMemory() //private function for array increase
{
	
	switch (mnSize)
	{
	case 0:
	{
		int * buffMpAr = new int[mnSize + 1];
		delete[] mpAr;
		mpAr = buffMpAr;
		mnSize += 1;
		cout << "Case 0 - creating new array with 1 elements: " << "mnSize " << mnSize << " m_iCurInd" << m_iCurInd << endl;
		break;
	}
	case 1:
	{
		int * buffMpAr = new int[mnSize + 1];
		buffMpAr[0] = mpAr[0];

		delete[]mpAr;
		mpAr = buffMpAr;
		++mnSize;
		cout << "Case 1 - creating new array with 2 elements and copy 0-element: " << mnSize << ' ' << m_iCurInd << endl;
		break;

	}
	default:
	{
		int newNSize = mnSize * 2;
		int * pArBuf = new int[newNSize];
		memcpy(pArBuf, mpAr, sizeof(int)*mnSize);
		delete[]mpAr;
		mpAr = pArBuf;
		mnSize = newNSize;
		cout << "Case default - creating new array with size *2: " << mnSize << ' ' << m_iCurInd << endl;
		break;
	}
	}
	
}

void Array::Show()
{
	cout << "Show array:" << endl;
	
	if (mnSize == 0) 
	    cout << "Array is empty" << endl;
	else
	{
		for (int i = 0; i < m_iCurInd; ++i)
		{
			cout << setw(3) << i+1 << ':';
			cout << setw(3) << mpAr[i] << endl;
			 
		}
	}
	
}

Array::Array(const Array &R) : mnSize(R.mnSize), m_iCurInd(R.m_iCurInd), mpAr(0), m_pBackUp(0) //copy constructor
{	
	if (R.mpAr != 0)
	{
		mpAr = new int[mnSize];
		memcpy(mpAr, R.mpAr, sizeof(int)*m_iCurInd);
	}
	cout << "Array(const &R) " << this << "from " << &R << " " << mnSize << endl;
}

#ifndef HOMEWORK

int Array::Save(const char * sFileName)
{
	int iErrCode = mpBackUp->Write(sFileName, mpAr, m_iCurInd * sizeof(int));
	return iErrCode;
}
#endif // !HOMEWORK

void Array::SetBackUp(BackUp * pBackUp)
{
	m_pBackUp = pBackUp;
	cout << "here was SetbackUp" << endl;
}

int Array::Save()
{
	cout << "Function save" << endl;
	int iRet = FILE_OK;
	if (0 == m_pBackUp)
	{
		int iRet = BACK_UP_ISNT_INITIALIZED;
	}
	else
	{
		int nBytes = sizeof(int)*m_iCurInd;
		iRet = m_pBackUp->Write(mpAr, nBytes);
	}
	return iRet;

}

int Array::LoadFromFile()
{
	int iRet = FILE_OK;
	if (0 == m_pBackUp)
	{
		int iRet = BACK_UP_ISNT_INITIALIZED;
	}
	else
	{
		int nReaded = 0;
		int iErrCode = ERR_EMPTY_FILE;
		void * pVChunk = m_pBackUp->Read(&nReaded, &iErrCode); // pVchuk - just memory chunk 
			if (pVChunk != 0)
			{
				mpAr = (int*)pVChunk; //cast out memory chuk to int and assign his address to mpAr
				m_iCurInd = mnSize = nReaded / sizeof(int);
				
			}
		iRet = iErrCode;
	}
	 
	return iRet;
}