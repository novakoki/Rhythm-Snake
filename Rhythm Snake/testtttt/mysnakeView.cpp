// mysnakeView.cpp : implementation of the CMysnakeView class
//

#include "stdafx.h"
#include "mysnake.h"
#include<afxsock.h>
#include "mysnakeDoc.h"
#include "mysnakeView.h"
#include<afxwin.h>
#include<MMSystem.h>
#pragma comment(lib, "WINMM.LIB")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include"Robt.h"
#include"manage.h"
#include"net.h"
#include"flash.h"
int CMysnakeView::mode;
flash a;
int onstart=0;
int two=0;
int addai=0;
clock_t start;
int id,id2;
manage m;
net dlg;
int t;
int rob=0;

/////////////////////////////////////////////////////////////////////////////
// CMysnakeView
//int user[2];
IMPLEMENT_DYNCREATE(CMysnakeView, CView)

BEGIN_MESSAGE_MAP(CMysnakeView, CView)
	//{{AFX_MSG_MAP(CMysnakeView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
//	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
//	ON_COMMAND(IDC_BUTTON4, &CMysnakeView::OnButton4)
//	ON_COMMAND(IDC_BUTTON5, &CMysnakeView::OnButton5)
//	ON_COMMAND(IDC_BUTTON6, &CMysnakeView::OnButton6)
//	ON_COMMAND(IDC_BUTTON7, &CMysnakeView::OnButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CMysnakeView::OnBnClickedButton5)
	ON_COMMAND(ID_32774, &CMysnakeView::On32774)
	ON_COMMAND(ID_32772, &CMysnakeView::On32772)
	ON_COMMAND(ID_32773, &CMysnakeView::On32773)
	ON_COMMAND(ID_32775, &CMysnakeView::On32775)
	ON_COMMAND(ID_32776, &CMysnakeView::On32776)
	ON_COMMAND(ID_32777, &CMysnakeView::On32777)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysnakeView construction/destruction
CPoint temfood;
CMysnakeView::CMysnakeView()
{
	// TODO: add construction code here
	
	//user[1]=m.login("me");
	//m.setdir(5,user[1]);
	
	POINT s;s.x=15;s.y=10;
	setfood(s);temfood=s;
	
	//backgroud.Draw(10*size,10*size,size,size,snake,80,120,size*2,2*size,80);
		//backgroud.Create(1000,800);
		//backgroud.Load("snake.bmp");

}

CMysnakeView::~CMysnakeView()
{
	snake.~CBitmapEx();
}

BOOL CMysnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMysnakeView drawing

void CMysnakeView::OnDraw(CDC* pDC)
{
	
	
	backgroud.Load(L"back.bmp");
	CMysnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	m.draw();
	backgroud.Draw(pDC->m_hDC);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMysnakeView diagnostics

#ifdef _DEBUG
void CMysnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CMysnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMysnakeDoc* CMysnakeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMysnakeDoc)));
	return (CMysnakeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMysnakeView message handlers

void CMysnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(t)
	if(only)
		switch(nChar)
	{
	case VK_UP:
		if(mode==3)m.setdir(UP, dlg.n);
		if(mode==2||mode==1)m.setdir(UP,id);
		
		break; 
	case VK_DOWN:
		if(mode==3)m.setdir(DOWN,dlg.n);
		if(mode==2||mode==1)m.setdir(DOWN,id);
		
		break;
	case VK_LEFT:
		if(mode==3)m.setdir(LEFT, dlg.n);
		if(mode==2||mode==1)m.setdir(LEFT,id);
		
		break;  
	case VK_RIGHT:
		if(mode==3)m.setdir(RIGHT,dlg.n);
		if(mode==2||mode==1)m.setdir(RIGHT,id);
		
		break;
	
	}
	else//网络部分
	{
	if(nChar == 87) rob=!rob;
	if(!rob)
		switch(nChar)
	{
		case 'e':
			dlg.sendmessage('2',"boss！");
		break;
	case VK_UP:
		dlg.require(UP, dlg.n);
		//dlg.sendmessage(4, "4");
		break; 
	case VK_DOWN:
		dlg.require(DOWN,dlg.n);
		//dlg.sendmessage(4, "3");
		break;
	case VK_LEFT:
		dlg.require(LEFT, dlg.n);
		
		//dlg.sendmessage(4, "1");
		break;  
	case VK_RIGHT:
		dlg.require(RIGHT,dlg.n);
		//dlg.sendmessage(4, "2");
		break;
	//default :m.setdir(5, dlg.n);
	}
	}
		this->RedrawWindow();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CMysnakeView::Drawmap(CBitmap* icon,POINT p)
{
	CClientDC clintDC(this);
	CDC MenDC;
	MenDC.CreateCompatibleDC(&clintDC);
	CBitmap *pOldDC = MenDC.SelectObject(icon);
	clintDC.BitBlt((p.x+8)*20,(p.y+1)*20,20,20,&MenDC,0,0,SRCCOPY);
	MenDC.SelectObject(pOldDC);
}

void CMysnakeView::OnTimer(UINT_PTR nIDEvent)
{
	if(only){
	if(onstart==1)
		Onstart();
	if(two==1)
		OnTwo();
	if(addai==1)
		AddAI();
	CPaintDC dc(this); // device context for painting
	POINT p;
	p.x=food.x;	p.y=food.y;
	t=m.go();
	this->RedrawWindow();
	if(temfood!=food.point()){
		//P->Rectangle(food.x*size,food.y*size,(food.x+1)*size,(food.y+1)*size);
		temfood=food.point();
	}
	if(!t)
		{
			KillTimer(1);
			mciSendString(TEXT("close song"),0,0,0);
			a.n=2;
			a.DoModal();
		}
	if(mode==1)
	{
		speed();
		scores();
	}
	}
	else{//网络部分
		if(rob&&dlg.n!=0)
	{	
		m.man.control=m.control[dlg.n];
		int w=m.man.AI_c();
		//m.setdir(w,dlg.n);
		dlg.require(w,dlg.n);
	}
	if(dlg.server){
		m.go();
	}
	}
	this->RedrawWindow();
	CView::OnTimer(nIDEvent);
}


void CMysnakeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	a.n=1;
	a.DoModal();
	dlg.Create(IDD_NET);
	dlg.ShowWindow(SW_SHOW);
	this->SetTimer(1,1000,NULL);
	// TODO: 在此添加专用代码和/或调用基类
}




BOOL CMysnakeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;//CView::OnEraseBkgnd(pDC);
}



UINT newdlg(LPVOID P){
	
	return 1;
}








void CMysnakeView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar)
	{
	case 'w':
		if(mode==2||mode==1)m.setdir(UP,id2);
		//dlg.sendmessage(4, "4");
		break; 
	case 's':
		if(mode==2||mode==1)m.setdir(DOWN,id2);
		//dlg.sendmessage(4, "3");
		break;
	case 'a':
		if(mode==2||mode==1)m.setdir(LEFT,id2);
		//dlg.sendmessage(4, "1");
		break;  
	case 'd':
		if(mode==2||mode==1)m.setdir(RIGHT,id2);
		//dlg.sendmessage(4, "2");
		break;
	//default :test.grow(1);
	}
		this->RedrawWindow();
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMysnakeView::speed(void)
{
	CString history;
	switch((clock()-start)/1000)
		 {
		 case 13:
			 KillTimer(1);
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"一级加速ing！！！！");
			 ::SetTimer(this->m_hWnd,1,125,NULL);
			 break;
		 case 33:
			 KillTimer(1);
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"二级加速ing！！！！");
			 ::SetTimer(this->m_hWnd,1,100,NULL);
			 break;
		 case 44:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"三级加速ing！！！！");
			 ::SetTimer(this->m_hWnd,1,75,NULL);
			 break;
		 case 52:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"四级加速ing！！！！");
			 ::SetTimer(this->m_hWnd,1,50,NULL);
			 break;
		 case 63:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"缓口气吧");
			 ::SetTimer(this->m_hWnd,1,75,NULL);
			 break;
		 case 81:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"五级加速ing！！！！");
			 ::SetTimer(this->m_hWnd,1,50,NULL);
			 break;
		 case 96:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"准备终极加速");
			 ::SetTimer(this->m_hWnd,1,75,NULL);
		 case 115:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"第一次终极加速");
			 ::SetTimer(this->m_hWnd,1,35,NULL);
			 break;
		 case 138:
			 KillTimer(1);
			  
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"准备第二次终极加速");
			 ::SetTimer(this->m_hWnd,1,50,NULL);
			 break;
		 case 148:
			 KillTimer(1);
			 dlg.SetDlgItemTextW(IDC_EDIT6,L"第二次终极加速");
			 ::SetTimer(this->m_hWnd,1,25,NULL);
			 break;
		 case 202:
			 KillTimer(1);
			  dlg.SetDlgItemTextW(IDC_EDIT6,L"恭喜你，可以歇一会了");
			 ::SetTimer(this->m_hWnd,1,70,NULL);
			 break;
		 }
}

void CMysnakeView::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CMysnakeView::Onstart(void)
{
	mode=1;
	::SetTimer(this->m_hWnd,1,150,NULL);
	id=m.login("玩家1");
	mciSendString(TEXT("open Crotia.mp3 alias song"),NULL,0,NULL);
	mciSendString(TEXT("play song"),0,0,0);
	start=clock();
	onstart=0;
}


void CMysnakeView::OnTwo(void)
{
	mode=2;
	id=m.login("玩家1");
	id2=m.login("玩家2");
	::SetTimer(this->m_hWnd,1,200,NULL);
	two=0;
}


void CMysnakeView::AddAI(void)
{
	int t = m.login("rrr");
	m.setdir(5, t);
	addai=0;
}


int CMysnakeView::scores(void)
{
	char a[1000]={0};
	int len=m.control[id]->body.size()+1;
	int scores;
	if(len<20)
		scores=len*10;
	else if(len>=20&&len<30)
		scores=len*100;
	else if(len>=50)
		scores=len*1000;
	else scores=len*10000;
	_itoa(scores,a,10);
	CString as;
	as=a;
	dlg.SetDlgItemInt(IDC_NAME,scores);
	return 0;
}


void CMysnakeView::On32774()
{
	// TODO: 在此添加命令处理程序代码
	int t = m.login("rrr");
	m.setdir(5, t);
}


void CMysnakeView::On32772()
{
	// TODO: 在此添加命令处理程序代码
	mode=1;
	::SetTimer(this->m_hWnd,1,150,NULL);
	id=m.login("玩家1");
	mciSendString(TEXT("open Crotia.mp3 alias song"),NULL,0,NULL);
	mciSendString(TEXT("play song"),0,0,0);
	start=clock();
}


void CMysnakeView::On32773()
{
	// TODO: 在此添加命令处理程序代码
	mode=2;
	id=m.login("玩家1");
	id2=m.login("玩家2");
	::SetTimer(this->m_hWnd,1,200,NULL);
}


void CMysnakeView::On32775()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
	mciSendString(TEXT("pause song"),0,0,0); 
}


void CMysnakeView::On32776()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1,200,NULL);
	mciSendString(TEXT("resume song"),0,0,0);
}


void CMysnakeView::On32777()
{
	// TODO: 在此添加命令处理程序代码
	static int m=1;
	if(m%2==1)
		mciSendString(TEXT("setaudio song volume to 0"), 0, 0, 0);
	else
		mciSendString(TEXT("setaudio song volume to 100"), 0, 0, 0);
	m++;
}
