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
	GetDlgItem(IDC_STATIC1)->SetWindowText("ʹ���ֲ᣺\n\tAD֧����������źŵ����ڡ�Ƶ�ʡ���ֵ��ͬʱ֧��Ӳ������Ƶ�ʣ�ADģʽ�²���Ƶ��Ӧ�����ź�����Ƶ�ʵ�2�����ϣ��������Ƶ�ʵ�ʱ��Ӧ������Ƶ�ʲ���̫�ߣ�Ҳ����̫�ͣ������ֲ�����Ƶ����ʾ�仯��λ��β���Ƶ����ֵ��һ��Ӧ����β�����\n\n���ʵ�ֵĹ����У�\n\t1.AD�ɼ�����������ͼ����������źŵ�Ƶ�ʡ���ֵ�����ڣ�\n\t2.FFT�任\n\t3.Ӳ�������ź�Ƶ��\n\t4.���ݱ���ͻָ�\n\t5.DA���\n\nע�⣺�뾡����Ҫ��ADSHģʽ�²�Ƶ�ʺ����ڣ���Ϊ������Ƶ��*ͨ������>40��ʱʵ�ʵĲ���Ƶ�ʾͻ�С���趨�Ĳ���Ƶ�ʣ���������õ����ݾͲ��ԡ�����û���Ҫѡ���ڸ�ģʽ�²������עʵ����Ƶ������ʾ�����ݡ�");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
