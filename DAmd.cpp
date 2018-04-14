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
	 damould=0;		//正弦波
	 max=5;			//最大值5V
	 min=0;			//最小值0V
	 rate=1;		//周  期1s
	 zhankongbi=0;  //占空比初值无意义
}

CDAmd::~CDAmd()
{

}
