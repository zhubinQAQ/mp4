// DAmd.h: interface for the CDAmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAMD_H__A0622367_A20D_4F18_ABA6_63AA87889E34__INCLUDED_)
#define AFX_DAMD_H__A0622367_A20D_4F18_ABA6_63AA87889E34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDAmd  
{
public:
	CDAmd();
	int damould;//DA的波形0正弦  1 方波 2 三角  3自绘
	double max;//-10-+10v
	double min;//-10-+10V
	double	rate;//频率
	double	zhankongbi;//占空比20-80之间的值,0表示无意义


	
	virtual ~CDAmd();

};

#endif // !defined(AFX_DAMD_H__A0622367_A20D_4F18_ABA6_63AA87889E34__INCLUDED_)
