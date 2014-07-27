// mysnake.h : main header file for the MYSNAKE application
//

#if !defined(AFX_MYSNAKE_H__217496F7_13BB_4CC1_8635_2E06D37F1860__INCLUDED_)
#define AFX_MYSNAKE_H__217496F7_13BB_4CC1_8635_2E06D37F1860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMysnakeApp:
// See mysnake.cpp for the implementation of this class
//

class CMysnakeApp : public CWinApp
{
public:
	CMysnakeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysnakeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMysnakeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSNAKE_H__217496F7_13BB_4CC1_8635_2E06D37F1860__INCLUDED_)
