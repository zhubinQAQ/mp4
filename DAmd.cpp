// DAmd.cpp: implementation of the CDAmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vr.h"
#include "DAmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDAmd::CDAmd()
{
	 damould=0;		//���Ҳ�
	 max=5;			//���ֵ5V
	 min=0;			//��Сֵ0V
	 rate=1;		//��  ��1s
	 zhankongbi=0;  //ռ�ձȳ�ֵ������
}

CDAmd::~CDAmd()
{

}
