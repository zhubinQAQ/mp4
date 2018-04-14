// Data.cpp : implementation file
//

#include "stdafx.h"
#include "vr.h"
#include "Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CData dialog


CData::CData(CWnd* pParent /*=NULL*/)
	: CDialog(CData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CData)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CData, CDialog)
	//{{AFX_MSG_MAP(CData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CData message handlers



BOOL CData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES
		|LVS_EX_TWOCLICKACTIVATE);	//设置报表扩展风格
	m_list.InsertColumn(0,"通道号",LVCFMT_CENTER,64,0);
	m_list.InsertColumn(1,"max(V)",LVCFMT_LEFT,64,1);
	m_list.InsertColumn(2,"min(V)",LVCFMT_LEFT,65,2);
	m_list.InsertColumn(3,"f(Hz)",LVCFMT_LEFT,65,3);
	m_list.InsertColumn(4,"T(ms)",LVCFMT_LEFT,65,4);
	return TRUE;             
}








