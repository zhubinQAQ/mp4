// Help.cpp : implementation file
//

#include "stdafx.h"
#include "vr.h"
#include "Help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelp dialog


CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelp, CDialog)
	//{{AFX_MSG_MAP(CHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelp message handlers

BOOL CHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC1)->SetWindowText("使用手册：\n\tAD支持软件测量信号的周期、频率、幅值。同时支持硬件测量频率，AD模式下采样频率应当在信号输入频率的2倍以上，软件测量频率的时候应当采样频率不宜太高，也不宜太低，若发现采样中频率显示变化多次或多次测量频率数值不一，应当多次测量。\n\n软件实现的功能有：\n\t1.AD采集（包括放缩图像、软件计算信号的频率、幅值、周期）\n\t2.FFT变换\n\t3.硬件测量信号频率\n\t4.数据保存和恢复\n\t5.DA输出\n\n注意：请尽量不要在ADSH模式下测频率和周期，因为当采样频率*通道数量>40万时实际的采样频率就会小于设定的采样频率，因此软件测得的数据就不对。如果用户非要选择在该模式下测量请关注实采样频率中显示的内容。");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
