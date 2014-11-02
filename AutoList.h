// AutoList.h: interface for the CAutoList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOLIST_H__0AA7A39B_F3A6_4573_84ED_92E0B2E4BF2E__INCLUDED_)
#define AFX_AUTOLIST_H__0AA7A39B_F3A6_4573_84ED_92E0B2E4BF2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <algorithm>
#include <string>
#include "Tokens.h"


class CAutoList  
{
public:
	CAutoList();
	virtual ~CAutoList();

public:
	typedef std::vector<std::string> ExtList;

public:
	BOOL IsExistsAscFile(const CString &strExt);
	void Reset(const CString &strExtList);

private:
	std::string LowerCase(const std::string &str);
	
private:
	ExtList _v;	
		
};

#endif // !defined(AFX_AUTOLIST_H__0AA7A39B_F3A6_4573_84ED_92E0B2E4BF2E__INCLUDED_)
