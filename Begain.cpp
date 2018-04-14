// Begain.cpp : implementation file
//

#include "stdafx.h"
#include "vr.h"
#include "Begain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "MP422E.h" 
#pragma comment(lib,"MP422E.lib")   //get DLL of AC6623
/////////////////////////////////////////////////////////////////////////////
// Begain dialog


Begain::Begain(CWnd* pParent /*=NULL*/)
	: CDialog(Begain::IDD, pParent)
{
	//{{AFX_DATA_INIT(Begain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Begain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Begain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Begain, CDialog)
	//{{AFX_MSG_MAP(Begain)
	ON_BN_CLICKED(IDC_BEGAIN, OnBegain)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CANCLE, OnCancle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Begain message handlers

void Begain::OnBegain() 
{

	HANDLE hDevice;
	hDevice=MP422E_OpenDevice(0);
	if(hDevice!=INVALID_HANDLE_VALUE)
	{
		MessageBox("没有找到设备！请重试");
	}
	else
	{
		CDialog::OnOK();
	}
}

void Begain::OnClose() 
{

	
	CDialog::OnClose();
	exit(0);
}

void Begain::OnCancle() 
{

	Begain::OnClose();
	exit(0);
}


BOOL Begain::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==27)
		return NULL;
	return CDialog::PreTranslateMessage(pMsg);
}
