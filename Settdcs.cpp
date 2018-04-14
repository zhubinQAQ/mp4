// Settdcs.cpp : implementation file
//

#include "stdafx.h"
#include "vr.h"
#include "Settdcs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettdcs dialog


CSettdcs::CSettdcs(CWnd* pParent /*=NULL*/)
	: CDialog(CSettdcs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettdcs)
	m_max = 0.0;
	m_min = 0.0;
	m_pinlv = 0.0;
	m_zhankongbi = 0.0;
	//}}AFX_DATA_INIT
}


void CSettdcs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettdcs)
	DDX_Text(pDX, IDC_MAX, m_max);
	DDX_Text(pDX, IDC_MIN, m_min);
	DDX_Text(pDX, IDC_PINLV, m_pinlv);
	DDX_Text(pDX, IDC_ZHANKONGBI, m_zhankongbi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettdcs, CDialog)
	//{{AFX_MSG_MAP(CSettdcs)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettdcs message handlers


BOOL CSettdcs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_max=da.max;
	m_min=da.min;
	m_pinlv=da.rate;
	m_zhankongbi=da.zhankongbi;
	if(da.damould==0)
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	else if(da.damould==1)
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	else if(da.damould==2)
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	else
		;
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//注意没有OnRadio2
void CSettdcs::OnRadio1() 
{
	da.damould=0;
	GetDlgItem(IDC_PINLV)->EnableWindow(TRUE);
	GetDlgItem(IDC_ZHANKONGBI)->EnableWindow(FALSE);
	GetDlgItem(IDC_MAX)->EnableWindow(TRUE);
	GetDlgItem(IDC_MIN)->EnableWindow(TRUE);

	
}

void CSettdcs::OnRadio3() 
{
	da.damould=1;
	GetDlgItem(IDC_ZHANKONGBI)->EnableWindow(TRUE);
	
}

void CSettdcs::OnRadio4() 
{
	da.damould=2;
	GetDlgItem(IDC_ZHANKONGBI)->EnableWindow(FALSE);
	
}

void CSettdcs::OnRadio5() 
{
	da.damould=3;
	GetDlgItem(IDC_ZHANKONGBI)->EnableWindow(FALSE);
	
}

void CSettdcs::OnOK() 
{
	UpdateData(TRUE);
	if(da.damould==0||da.damould==2)
	{
		if(m_max>m_min&&m_max<=10&&m_min>=-10&&m_pinlv<=10000&&m_pinlv>0)
		{
			da.max=m_max;
			da.min=m_min;
			da.rate=m_pinlv;
			da.zhankongbi=0;
			CDialog::OnOK();
		}
		else
			MessageBox("数据填写有误请重新填写！");
	}
	else if(da.damould==3)
		return;
	else
	{
		if(m_max>m_min&&m_max<=10&&m_min>=-10&&m_pinlv<=10000&&m_pinlv>0&&m_zhankongbi<=80&&m_zhankongbi>=20)
		{
			da.max=m_max;
			da.min=m_min;
			da.rate=m_pinlv;
			da.zhankongbi=m_zhankongbi;
			CDialog::OnOK();
		}
		else
			MessageBox("数据填写有误请重新填写！");
	}

}
