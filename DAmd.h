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
	int damould;//DA�Ĳ���0����  1 ���� 2 ����  3�Ի�
	double max;//-10-+10v
	double min;//-10-+10V
	double	rate;//Ƶ��
	double	zhankongbi;//ռ�ձ�20-80֮���ֵ,0��ʾ������


	
	virtual ~CDAmd();

};

#endif // !defined(AFX_DAMD_H__A0622367_A20D_4F18_ABA6_63AA87889E34__INCLUDED_)
