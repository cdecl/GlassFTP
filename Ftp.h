// Ftp.h: interface for the CFtp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTP_H__C78138E9_F6E6_4BB0_A392_187C67B78F7D__INCLUDED_)
#define AFX_FTP_H__C78138E9_F6E6_4BB0_A392_187C67B78F7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFtp  
{
public:
	typedef BOOL (__stdcall *FtpCommand)(HINTERNET, BOOL, DWORD, LPCSTR, DWORD*, HINTERNET*);

public:
	CFtp();
	virtual ~CFtp();

public:
	BOOL Open(CString strIP, CString strID, CString strPassword, 
		INTERNET_PORT nPort = INTERNET_INVALID_PORT_NUMBER, BOOL bPassive = FALSE
	);
	

public:
	BOOL IsOpen();
	void Release();

public:
	BOOL SendNOOP();
	CFtpConnection *m_pFtpCon;
	CFtpFileFind *m_pFFind;

private:
	CInternetSession *m_pInetSession;
};

#endif // !defined(AFX_FTP_H__C78138E9_F6E6_4BB0_A392_187C67B78F7D__INCLUDED_)
