// mysnakeDoc.cpp : implementation of the CMysnakeDoc class
//

#include "stdafx.h"
#include "mysnake.h"

#include "mysnakeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysnakeDoc

IMPLEMENT_DYNCREATE(CMysnakeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMysnakeDoc, CDocument)
	//{{AFX_MSG_MAP(CMysnakeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysnakeDoc construction/destruction

CMysnakeDoc::CMysnakeDoc()
{
	// TODO: add one-time construction code here

}

CMysnakeDoc::~CMysnakeDoc()
{
}

BOOL CMysnakeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMysnakeDoc serialization

void CMysnakeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMysnakeDoc diagnostics

#ifdef _DEBUG
void CMysnakeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMysnakeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMysnakeDoc commands
