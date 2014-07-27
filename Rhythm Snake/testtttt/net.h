#pragma once
#include<afxsock.h>
#include"resource.h"
// net 对话框
extern int only;//单机为1
class net : public CDialogEx
{
	DECLARE_DYNAMIC(net)

	public:
	void require(int,int );
	int server ;
	int n;//玩家的ID号码。
	CString name;
	void net::select(char a, CString s);
	void requrie();
	net(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~net();
	//void oncl();
	//void onac();
	//void onrev(int);
	//void Onsend();
	int initserver();
	int initclient();
	int sendmessage(char a, char * c);
	// 对话框数据
	enum { IDD = IDD_NET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedConnect();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnIdok();
	afx_msg void OnIdcancel();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};
	extern net dlg;