// flash.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mysnake.h"
#include "flash.h"
#include "afxdialogex.h"


// flash �Ի���

IMPLEMENT_DYNAMIC(flash, CDialogEx)

flash::flash(CWnd* pParent /*=NULL*/)
	: CDialogEx(flash::IDD, pParent)
{
	n=0;
}

flash::~flash()
{
}

void flash::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, movie);
	CString str;
	 TCHAR szCurrentDir[MAX_PATH];    
    ::GetCurrentDirectory(MAX_PATH,szCurrentDir);    
    str.Format(_T("%s"),szCurrentDir); 
	switch(n){
	case 1:str = str+_T("\\��ʼ����.swf");
		break;
	case 2:str = str+_T("\\Game Over.swf");
		break;
	}
	movie.LoadMovie(0, str);
	movie.Play();
}

BEGIN_MESSAGE_MAP(flash, CDialogEx)
END_MESSAGE_MAP()


// flash ��Ϣ�������
