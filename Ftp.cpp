// Ftp.cpp: implementation of the CFtp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlassFTP.h"
#include "Ftp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtp::CFtp()
{
	m_pFtpCon = NULL;
	m_pFFind = NULL;
	m_pInetSession = NULL;
}

CFtp::~CFtp()
{
	Release();
}

//////////////////////////////////////////////////////////////////////
// Ftp Open
BOOL CFtp::Open(CString strServer, CString strUserID, CString strPassword, 
				INTERNET_PORT nPort /* = INTERNET_INVALID_PORT_NUMBER */,
				BOOL bPassive /* = FALSE */ )
{
	BOOL bRet = FALSE;

	m_pInetSession = new CInternetSession();

	try {
		m_pFtpCon = m_pInetSession->GetFtpConnection(strServer, strUserID, strPassword, nPort, bPassive);
		if (m_pFtpCon) {
			m_pFFind = new CFtpFileFind(m_pFtpCon);
			bRet = TRUE;
		}
		else {
			bRet = FALSE;
		}
	}
	catch (CInternetException &ie) {
		bRet = FALSE;
		Release();
	}
	catch (...) {
		bRet = FALSE;
		Release();
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////
// Ftp Memory Free
void CFtp::Release()
{
	if (m_pFFind) {
		m_pFFind->Close(); 
		delete m_pFFind;
		m_pFFind = NULL;
	}

	if (m_pFtpCon) {
		m_pFtpCon->Close();
		m_pFtpCon = NULL;
	}

	if (m_pInetSession) {
		m_pInetSession->Close(); 
		delete m_pInetSession;
		m_pInetSession = NULL;
	}
}

BOOL CFtp::IsOpen()
{
	return (m_pFtpCon != NULL);
}

BOOL CFtp::SendNOOP()
{
	HINSTANCE hDll = ::LoadLibrary("wininet.dll");
	if (!hDll) {
		return FALSE;
	}

	BOOL bRet = FALSE;
	DWORD *pContext = reinterpret_cast<DWORD*>(m_pInetSession->GetContext());
	HINTERNET hInternet = NULL;

	try {
		FtpCommand fnCommand = (FtpCommand)::GetProcAddress(hDll, "FtpCommandA");

		if (!fnCommand) {
			throw -1;
		}

		HINTERNET hSession = (HINTERNET)*m_pFtpCon;
		if (!fnCommand(hSession, FALSE, FTP_TRANSFER_TYPE_BINARY, "NOOP", pContext, &hInternet)) {
			throw -1;
		}
		bRet = TRUE;
	}
	catch (...) {
		bRet = FALSE;
	}
	
	FreeLibrary(hDll);
	return bRet;
}
