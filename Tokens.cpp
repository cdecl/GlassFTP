// Tokens.cpp: implementation of the CTokens class.
//
// Programmed by cdecl (byung-kyu kim)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tokens.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTokens::CTokens()
{
	Str(string(""));
}


CTokens::CTokens(const string &strBuff, int nPos)
{
	Str(strBuff, nPos);
}


CTokens::~CTokens()
{

}

//////////////////////////////////////////////////////////////////////
// 초기화 
void CTokens::Str(const string &strBuff, int nPos)
{
	m_strBuff = strBuff;
	m_nPos = nPos;
}


//////////////////////////////////////////////////////////////////////
// Get Buffer String
string CTokens::Str()
{
	return m_strBuff;
}

//////////////////////////////////////////////////////////////////////
// 고정길이 파싱 
string CTokens::GetNextWord(const int &nLen)
{
	if (m_nPos >= m_strBuff.length()) {
		return string("");
	}

	string str;
	// 0을 넘기면 나머지 모든 문자열을 리턴한다 
	if (nLen == 0) {
		str = m_strBuff.substr(m_nPos);
		m_nPos = m_strBuff.length();
	}
	else {
		str = m_strBuff.substr(m_nPos, nLen);
		m_nPos += nLen;
	}
	
	return str;
}

//////////////////////////////////////////////////////////////////////
// 구분자 파싱 
string CTokens::GetNextWord(const string &strFD)
{
	if (m_nPos >= m_strBuff.length()) {
		return string("");
	}

	const int nStartPos = m_nPos;
	int nPos = m_nPos;

	const int nFDSize = strFD.length();
	const int nBuffSize = m_strBuff.length();

	while (nPos < nBuffSize) {
		for (int i = 0; i < nFDSize; i++) {
			if (m_strBuff[nPos] == strFD[i]) {
				m_nPos = nPos + 1;
				return m_strBuff.substr(nStartPos, nPos - nStartPos);	
			}
		}
		++nPos;
	}

	nPos = m_nPos;
	m_nPos = nBuffSize;

	return m_strBuff.substr(nPos);
}

string CTokens::GetNextWord(const char cFD)
{
	return GetNextWord(string(&cFD, 1));
}

//////////////////////////////////////////////////////////////////////
// Get Position Index
int CTokens::GetPosition() const
{
	return m_nPos;
}

//////////////////////////////////////////////////////////////////////
// Set Position Index
bool CTokens::SetPosition(const int &nPos)
{
	if (m_strBuff.length() <= nPos) {
		return false;
	}

	m_nPos = nPos;
	return true;
}

bool CTokens::IsEOF()
{
	return (m_nPos >= m_strBuff.length());
}
