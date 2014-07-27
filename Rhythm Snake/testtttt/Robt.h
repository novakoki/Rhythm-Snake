// Robt.h: interface for the CRobt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBT_H__AFD8BBDC_514A_4645_B3B4_3E4AAD66B047__INCLUDED_)
#define AFX_ROBT_H__AFD8BBDC_514A_4645_B3B4_3E4AAD66B047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Snake.h"

class CRobt  //机器人，体现所有的自动操作。
{
protected:
	int AI();
	
public:
	int AI_c();
	Snake * control;//控制的对象
	int level;
	int go();
	void draw(CDC*p);
	void draw();
	CRobt();
	virtual ~CRobt();

};

#endif // !defined(AFX_ROBT_H__AFD8BBDC_514A_4645_B3B4_3E4AAD66B047__INCLUDED_)
