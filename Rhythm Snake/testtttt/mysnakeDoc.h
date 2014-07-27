// mysnakeDoc.h : interface of the CMysnakeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSNAKEDOC_H__7A4AEBF3_9473_4975_BEEF_A0D15BF479E1__INCLUDED_)
#define AFX_MYSNAKEDOC_H__7A4AEBF3_9473_4975_BEEF_A0D15BF479E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMysnakeDoc : public CDocument
{
protected: // create from serialization only
	CMysnakeDoc();
	DECLARE_DYNCREATE(CMysnakeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysnakeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMysnakeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMysnakeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSNAKEDOC_H__7A4AEBF3_9473_4975_BEEF_A0D15BF479E1__INCLUDED_)
