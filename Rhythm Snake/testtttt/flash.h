#pragma once
#include "shockwaveflash1.h"
#include"resource.h"

// flash �Ի���

class flash : public CDialogEx
{
	DECLARE_DYNAMIC(flash)

public:
	flash(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~flash();
	int n;
// �Ի�������
	enum { IDD = IDD_FLASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 movie;
};
