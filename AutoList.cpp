// AutoList.cpp: implementation of the CAutoList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "glassftp.h"
#include "AutoList.h"
#include <iterator>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAutoList::CAutoList()
{
	_v.reserve(30);
}

CAutoList::~CAutoList()
{

}

void CAutoList::Reset(const CString &strExtList)
{
	const char FD = ';';

	CTokens Token((LPCSTR)strExtList);
	_v.clear();

	while (!Token.IsEOF()) {
		_v.push_back(LowerCase(Token.GetNextWord(FD))); 
	}
}

BOOL CAutoList::IsExistsAscFile(const CString &strExt)
{
	if (strExt.IsEmpty()) {
		return FALSE;
	}

	ExtList::iterator it = std::find(_v.begin(), _v.end(), LowerCase(static_cast<LPCSTR>(strExt)));
	return (it == _v.end()) ? FALSE : TRUE;
}

std::string CAutoList::LowerCase(const std::string &str)
{
	std::string s; 
	transform(str.begin(), str.end(), std::back_inserter(s), tolower);
	return s;
}
