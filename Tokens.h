// Tokens.h: interface for the CTokens class.
//
// Programmed by cdecl (byung-kyu kim)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOKENS_H__8AA8097B_79A0_4B2A_960E_DA4B536B7EAA__INCLUDED_)
#define AFX_TOKENS_H__8AA8097B_79A0_4B2A_960E_DA4B536B7EAA__INCLUDED_

#include <string>		// for string class 
using namespace std;

class CTokens  
{
public:
	CTokens();
	CTokens(const string &strBuff, int nPos = 0);
	virtual ~CTokens();

public:
	bool IsEOF();
	bool SetPosition(const int &nPos);
	int GetPosition() const;
	string GetNextWord(const int &nLen = 0);
	string GetNextWord(const string &strFD);
	string GetNextWord(const char cFD);
	void Str(const string &strBuff, int nPos = 0);
	string Str();

private:
	int m_nPos;
	string m_strBuff;
	
};

#endif // !defined(AFX_TOKENS_H__8AA8097B_79A0_4B2A_960E_DA4B536B7EAA__INCLUDED_)
