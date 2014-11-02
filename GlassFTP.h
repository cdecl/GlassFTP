// GlassFTP.h : main header file for the GLASSFTP application
//

#if !defined(AFX_GLASSFTP_H__1CF59A6C_D605_4846_8804_18F19E1B07C6__INCLUDED_)
#define AFX_GLASSFTP_H__1CF59A6C_D605_4846_8804_18F19E1B07C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGlassFTPApp:
// See GlassFTP.cpp for the implementation of this class
//

class CGlassFTPApp : public CWinApp
{
public:
	CGlassFTPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlassFTPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGlassFTPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLASSFTP_H__1CF59A6C_D605_4846_8804_18F19E1B07C6__INCLUDED_)
