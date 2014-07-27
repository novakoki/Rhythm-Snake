#pragma once
#include "shockwaveflash1.h"
#include"resource.h"

// flash 对话框

class flash : public CDialogEx
{
	DECLARE_DYNAMIC(flash)

public:
	flash(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~flash();
	int n;
// 对话框数据
	enum { IDD = IDD_FLASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 movie;
};
