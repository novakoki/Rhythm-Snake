// mysnakeView.h : interface of the CMysnakeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSNAKEVIEW_H__E1083EED_A27A_4501_9B0B_F3A083E2FA8A__INCLUDED_)
#define AFX_MYSNAKEVIEW_H__E1083EED_A27A_4501_9B0B_F3A083E2FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"snake.h"
#include"mysnakeDoc.h"
#include"net.h"

extern int onstart;
extern int two;
extern int addai;
class CMysnakeView : public CView
{
protected: // create from serialization only
	CMysnakeView();
	DECLARE_DYNCREATE(CMysnakeView)

// Attributes
static int mode;
public:
	CMysnakeDoc* GetDocument();
// Operations
	void Drawmap(CBitmap* icon,POINT p);
	
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysnakeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMysnakeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMysnakeView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
//	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedServer();
	afx_msg void OnBnClickedSearchgame();
	//afx_msg UINT __cdecl On32771(LPVOID pParam);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void speed(void);
//	afx_msg void OnButton5();
//	afx_msg void OnButton6();
//	afx_msg void OnButton7();
	afx_msg void OnBnClickedButton5();
	void Onstart(void);
	void OnTwo(void);
	void AddAI(void);
	int scores(void);
	afx_msg void On32774();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32775();
	afx_msg void On32776();
	afx_msg void On32777();
};

#ifndef _DEBUG  // debug version in mysnakeView.cpp
inline CMysnakeDoc* CMysnakeView::GetDocument()
   { return (CMysnakeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSNAKEVIEW_H__E1083EED_A27A_4501_9B0B_F3A083E2FA8A__INCLUDED_)

