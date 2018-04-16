// vrDlg.cpp : implementation file
//���ߣ����	ʱ��2018��04��
//
#include "stdafx.h"
#include "vr.h"
#include "vrDlg.h"
#include "Data.h"
#include "About.h"
#include "Settdcs.h"
#include "math.h"
#include "Help.h"
#include "DAmd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "MP422E.h" 
#pragma comment(lib,"MP422E.lib")//get DLL of MP422E
/*
*���²��ֶ���ȫ�ֱ���
*
*/
#define		cnt0_ini 10
#define		maxnum 3000000						//����һ�������С
double		PI=3.1415926;						//Բ����
HANDLE		hDevice;							//�豸�ľ����ע��Ҫʵʱ��ȡ�忨�ľ��
long		databuff[maxnum];					//�ɼ��������ݵĻ���
long	    buff[600000];						//ʵ��ɼ���ʱ�����ɼ����ݳ���Ϊ30000�࣬���ó�6���ʱ���ǲ��������
double		data[16][maxnum];					//ת��������ݴ洢
double		fftdata[16][maxnum];				//fftת��������ݴ洢
double		datamin[16]={0};					//ͨ����ֵ����ѹ��
double		datamax[16]={0};					//ÿ��ͨ�����ֵ
double		pinlv[16]={0};						//ÿ��ͨ�������ֵ
long		DA[400]={0};						//���������ڴ洢DA�������
bool		DA_run=FALSE;						//�Ƿ���DAת��
HANDLE		hThread1;							//ΪDA�����̵߳��߳̾��
int			DArange;							//1ֵ0:0��10V ,  20:-10��+10V��Ӧ
/////////////////////////////////////////////////////////////////////////////
// CVrDlg dialog

CVrDlg::CVrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVrDlg)
	m_times = 200000;
	m_max = 0;
	m_min = 0;
	m_edit1 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//�����������һЩ���ݵĳ�ʼ��
	tdcolor[0 ]=RGB(0  ,255,0  );
	tdcolor[1 ]=RGB(0  ,0  ,255);
	tdcolor[2 ]=RGB(255,0  ,0  );
	tdcolor[3 ]=RGB(0  ,170,170);
	tdcolor[4 ]=RGB(170,170,0  );
	tdcolor[5 ]=RGB(170,0  ,170);
	tdcolor[6 ]=RGB(255,255,85 );
	tdcolor[7 ]=RGB(85 ,255,255);
	tdcolor[8 ]=RGB(255,255,255);
	tdcolor[9 ]=RGB(255,85 ,255);
	tdcolor[10]=RGB(255,85 ,85 );
	tdcolor[11]=RGB(85 ,85 ,85 );
	tdcolor[12]=RGB(0  ,85 ,255);
	tdcolor[13]=RGB(85 ,0  ,255);
	tdcolor[14]=RGB(85 ,255,0  );
	tdcolor[15]=RGB(255,0  ,85 );
	for(int i=1;i<=15;i++)
	{
		tdflag[i]=FALSE;
		datamax[i]=0;
		datamin[i]=0;
	}
	runflag=FALSE;
	data_exit=FALSE;
	file_exit=FALSE;
	topbuff=0;
	topdata=0;
	modul=0;
	fDeltaX_ad=1;
	ADrang=10;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON);
}

void CVrDlg::DoDataExchange(CDataExchange* pDX)//�ؼ���ؼ��Ͷ���Ĺ���
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVrDlg)
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_COMBO, m_box);
	DDX_Text(pDX, IDC_TIMES, m_times);
	DDX_Text(pDX, IDC_MAX, m_max);
	DDX_Text(pDX, IDC_MIN, m_min);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVrDlg, CDialog)//��Ϣӳ��
	//{{AFX_MSG_MAP(CVrDlg)
	ON_WM_PAINT()
	ON_COMMAND(IDM_AUOUT, OnAuout)
//	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RADIO0, OnClickedRadio0)
	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio1)
//	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnClickedRadio3)
	ON_WM_TIMER()
	ON_COMMAND(ID_RUN, OnRun)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_SAVEDATA, OnSavedata)
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_COMMAND(ID_OPENDATA, OnOpendata)
	ON_BN_CLICKED(IDC_CHECK0, OnCheck0)
	ON_COMMAND(ID_ANALYSEFILE, OnAnalysefile)
	ON_COMMAND(ID_BEGAINFFT, OnBegainfft)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER, OnCustomdrawSlider)
	ON_COMMAND(ID_SETDAMOUDL, OnSetdamoudl)
	ON_COMMAND(ID_DATA, OnLookData)
	ON_COMMAND(ID_SAVEBMP, OnSavebmp)
	ON_COMMAND(ID_RATEFORHARDWARE, OnRateforhardware)
	ON_COMMAND(ID_USE, OnUse)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck0)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVrDlg message handlers

BOOL CVrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//���ز˵�
	m_Menu.LoadMenu(IDR_MENU);  
	SetMenu(&m_Menu);
	//���ع�����
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);//�������ĺ���

	//��ʼ����ѡ��״̬
	CButton *pBtn;
	for(int st=IDC_CHECK0;st<=IDC_CHECK15;st++)
	{
		pBtn=static_cast <CButton *>(GetDlgItem(st));
		if(pBtn!=NULL)
		{
			if(tdflag[st-IDC_CHECK0])
				pBtn->SetCheck(BST_CHECKED);
			else
				pBtn->SetCheck(BST_UNCHECKED);
		}
	}

	m_box.SetCurSel(0);//������Ͽ�����ԣ����ó�ʼ����Ϊ10V
	//��������״̬
	if(modul==0)
		((CButton *)GetDlgItem(IDC_RADIO0))->SetCheck(1);
	else if(modul==1)
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	else if(modul==2)
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	else
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);

	//��ȡ����ͼƬ�ؼ���DC��Ϊ��ͼ����׼��
	CSliderCtrl* p1=(CSliderCtrl*)GetDlgItem(IDC_BX);
	CSliderCtrl* p2=(CSliderCtrl*)GetDlgItem(IDC_BX2);
	p1->GetClientRect(&rectPicture);  
	p2->GetClientRect(&rectPicture2);
	pDCbx=p1->GetDC();
	pDCbx2=p2->GetDC();

	//���ù�������ʼ��
	pScrollBar1 = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	pScrollBar1->SetScrollRange(1,800);//�����ƶ���λ��Ϊ1��1000
	pScrollBar1->SetScrollPos(1);
	//���ù������ĳ�ʼ״̬
	CToolBarCtrl& tb= m_wndToolBar.GetToolBarCtrl(); 
	tb.EnableButton(ID_OPENDATA,FALSE);
	tb.EnableButton(ID_SAVEDATA,FALSE);
	tb.EnableButton(ID_SETDAMOUDL,FALSE);
	tb.EnableButton(ID_ANALYSEFILE,FALSE);
	tb.EnableButton(ID_BEGAINFFT,FALSE);
	//����ؼ�
	m_slider.SetRange(1,15,FALSE);
	m_slider.SetPos(1);
	CString str;
	str.Format("%d",fDeltaX_ad);
	GetDlgItem(IDC_ABC)->SetWindowText(str);
	//��̬����һ���鿴���ݵĶԻ���
	pDlg=new CData();
	pDlg->Create(IDD_DATA); 
	//Ԥ��ʼ��DA����
	DA_Sin();
	return TRUE; 
}

void CVrDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); 
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawColorTable();
		DrawBackGround(pDCbx, rectPicture);
		DrawWave(pDCbx, rectPicture);
		DrawBackGroundForFFT(pDCbx2, rectPicture2);
		DrawFFT(pDCbx2, rectPicture2);
		CDialog::OnPaint();
	}
}

BOOL CVrDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&(pMsg->wParam==27||pMsg->wParam==13))//����ESC��ť������
		return NULL;
	return CDialog::PreTranslateMessage(pMsg);
}

void CVrDlg::OnAuout() //����
{
	CAbout About;
	About.DoModal();
}

void CVrDlg::DrawWave(CDC *pDC, CRect &rectPicture)//����ʱ���κ���
{
	double dpos=(double)(pScrollBar1->GetScrollPos()-1)/800;
    int nX;
    int nY;
    CPen newPen; 
    CPen *pOldPen; 
    for(int j=0;j<=15;j++)
		if(tdflag[j])
		{
			pDC->MoveTo(rectPicture.left,(rectPicture.bottom+rectPicture.top)/2 - (int)data[j][(int)(topdata*dpos)]);
			CString aa;
			/*aa.Format("%dHz",pScrollBar1->GetScrollPos());
			GetDlgItem(IDC_RATFORHARDWARE)->SetWindowText(aa);*///��Ϊ������Ϣ
			newPen.CreatePen(PS_SOLID, 1,tdcolor[j] ); 
			pOldPen = pDC->SelectObject(&newPen);
			for (int i=(int)(topdata*dpos),int k=0; i<=topdata; i++,k++)  
			{   
				nX = rectPicture.left +k/fDeltaX_ad;  
				nY = (rectPicture.bottom+rectPicture.top)/2- (int)data[j][i]; 
				if(nX>=575)
				{
					break;
				}
				pDC->LineTo(nX, nY);
			}
			pDC->SelectObject(pOldPen); 
			newPen.DeleteObject();		 
		}
		//�������
		pDlg->m_list.DeleteAllItems();
		CString str;
		for(int i=15;i>=0;i--)
			if(tdflag[i])
			{
				GetWaveTimes(i);
				str.Format("ch%d",i);
				pDlg->m_list.InsertItem(0,"");
				pDlg->m_list.SetItemText(0,0,str);
				if(datamax[i]!=-1000)
				{
					str.Format("%.2f",datamax[i]/15);
					pDlg->m_list.SetItemText(0,1,str);
					str.Format("%.2f",datamin[i]/15);
					pDlg->m_list.SetItemText(0,2,str);
					str.Format("%.2f",pinlv[i]/2);
					pDlg->m_list.SetItemText(0,3,str);
					str.Format("%.3f",1/pinlv[i]*1000*2);
					pDlg->m_list.SetItemText(0,4,str);
				}
				else
				{
					pDlg->m_list.SetItemText(0,1,"NULL");
					pDlg->m_list.SetItemText(0,2,"NULL");
					pDlg->m_list.SetItemText(0,3,"NULL");
					pDlg->m_list.SetItemText(0,4,"NULL");
				}
				if(pinlv[i]<=0)
				{
					pDlg->m_list.SetItemText(0,3,"NULL");
					pDlg->m_list.SetItemText(0,4,"NULL");
				}

			}
		DrawTimeBack(21,65);		
}

void CVrDlg::DrawTimeBack(int x,int y)//����ʱ��ͼ�ε�ʱ����
{
	CString str;
	double time;
	double m=m_max-m_min+1;
	time=1000/(double)m_times*30*m*(double)fDeltaX_ad;
	str.Format("%.3fms/div  2V/div",time);
	CDC *pDC = GetDC();
	CFont mFont;
	//��������
	VERIFY(mFont.CreateFont(					
			12, 10, 0, 0, FW_THIN, FALSE, FALSE, 
			0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
			DEFAULT_PITCH | FF_SWISS, "����"));
	CFont* pOldFont = pDC->SelectObject(&mFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,0));	
	pDC->TextOut(x,y,str);
	pDC->SelectObject(pOldFont);
	mFont.DeleteObject();
	if(m_times*m>400000&&modul==1)
		GetDlgItem(IDC_FACTTIMES)->SetWindowText("�޷����");
	else
	{
		m=m_times/m;
		str.Format("%.0f",m);
		GetDlgItem(IDC_FACTTIMES)->SetWindowText(str);
	}
	UpdateData(FALSE);
}

/*void CVrDlg::OnLButtonDown(UINT nFlags, CPoint point) //���������������Ƿ�������ɫѡ������
{
	CString str;
	CPoint p1,p2;
	int m=-1;
	if(672<=point.x&&690>=point.x)
	{
		p1.x=672;p2.x=690;
		if	   (414<=point.y&&430>=point.y){m=0;p1.y=414;p2.y=430;}
		else if(438<=point.y&&454>=point.y){m=1;p1.y=438;p2.y=454;}
		else if(462<=point.y&&478>=point.y){m=2;p1.y=462;p2.y=478;}
		else if(486<=point.y&&502>=point.y){m=3;p1.y=486;p2.y=502;}
		else if(510<=point.y&&526>=point.y){m=4;p1.y=510;p2.y=526;}
		else if(534<=point.y&&550>=point.y){m=5;p1.y=534;p2.y=550;}
		else if(558<=point.y&&574>=point.y){m=6;p1.y=558;p2.y=574;}
		else if(582<=point.y&&599>=point.y){m=7;p1.y=582;p2.y=599;}
		else	;
	}
	else if(790<=point.x&&808>=point.x)
	{
		p1.x=790;
		p2.x=808;
		if	   (414<=point.y&&430>=point.y){m=8 ;p1.y=414;p2.y=430;}
		else if(438<=point.y&&454>=point.y){m=9 ;p1.y=438;p2.y=454;}
		else if(462<=point.y&&478>=point.y){m=10;p1.y=462;p2.y=478;}
		else if(486<=point.y&&502>=point.y){m=11;p1.y=486;p2.y=502;}
		else if(510<=point.y&&526>=point.y){m=12;p1.y=510;p2.y=526;}
		else if(534<=point.y&&550>=point.y){m=13;p1.y=534;p2.y=550;}
		else if(558<=point.y&&574>=point.y){m=14;p1.y=558;p2.y=574;}
		else if(582<=point.y&&599>=point.y){m=15;p1.y=582;p2.y=599;}
		else	;
	}
	else	;
	if(m!=-1&&modul!=2)
	{
		CColorDialog dlg;//��ɫ�Ի����࣬�����ĶԻ���һ��ʹ�ü���
		dlg.m_cc.Flags|=CC_FULLOPEN|CC_RGBINIT;//CC_FULLOPEN��������Ի��������Ĵ�
		dlg.m_cc.rgbResult=tdcolor[m];//�ñ�ѡ�����ɫ��ֵ����һ��ѡ�����ɫ
		if(IDOK==dlg.DoModal())//���������ȷ�ϰ�ť
		{
			tdcolor[m]=dlg.m_cc.rgbResult;
		}
	CBrush brush(tdcolor[m]);
	CClientDC dc(this);
	dc.SelectObject(brush);
	dc.Rectangle(CRect(p1,p2));
	if(pScrollBar1->GetScrollPos()!=1)
				DrawBackGround(pDCbx, rectPicture);
	DrawWave(pDCbx, rectPicture);
	DrawFFT(pDCbx2, rectPicture2);
	CDialog::OnLButtonDown(nFlags, point);
	}

}*/

void CVrDlg::DrawColorTable()//��ʼ����ɫ�����ɫ
{
	CPoint p1,p2;
	CBrush brush;
	CClientDC dc(this);
	p1.y=414;
	p2.y=430;
	for(int i=0;i<=15;i++)
	{
		if  (i<=7){p1.x=672;p2.x=690;}
		else	  {p1.x=790;p2.x=808;}
		if(i!=8&&i!=0){p1.y=p1.y+24;p2.y=p2.y+24;}
		else		  {p1.y=414;p2.y=430;}
		brush.CreateSolidBrush(tdcolor[i]);
		dc.FillRect(CRect(p1,p2),&brush);
		brush.DeleteObject();	
	}
}

void CVrDlg::OnClickedRadio0() 
{
	OnSetcanshu(TRUE);
	modul=0;
	ChangeToolBarState();
}

void CVrDlg::OnClickedRadio1() 
{
	OnSetcanshu(TRUE);
	modul=1;
	ChangeToolBarState();
}

//void CVrDlg::OnClickedRadio2() 
//{
//	modul=2;
//	ChangeToolBarState();
//}

void CVrDlg::OnClickedRadio3() 
{
	OnSetcanshu(FALSE);
	modul=3;
	file_exit=FALSE;
	data_exit=FALSE;
	ChangeToolBarState();	
}

void CVrDlg::DrawFFT(CDC *pDC, CRect &rectPicture)//����FFT�Ĳ���
{
	int nX;
    int nY; 
    CPen newPen; 
    CPen *pOldPen; 
    for(int j=0;j<=15;j++)
		if(tdflag[j])
		{	
			pDC->MoveTo(rectPicture.left, rectPicture.bottom);
			newPen.CreatePen(PS_SOLID, 1,tdcolor[j] ); 
			pOldPen = pDC->SelectObject(&newPen);
			for (int i=0; i<=topdata; i=i++)  
			{   
				nX = rectPicture.left +i*1.1;
				nY = rectPicture.bottom- (int)fftdata[j][i]/500; 
				if(nX>=575)
				{
					break;
				}
				pDC->LineTo(nX, nY);
			} 		      
			pDC->SelectObject(pOldPen); 
			newPen.DeleteObject();		 
		}
}

void CVrDlg::OnTimer(UINT nIDEvent) //OnTimer�����Ļص�����
{
	if(nIDEvent==1)
	{
		long length;
		long t;
		length=MP422E_Poll(hDevice);//��ѯӲ�������е����ݲ������ȣ�����С��0��ʾ��������������ٲɼ�
		m_edit1=length;
		UpdateData(FALSE);
		if(length<0)
		{	
			MP422E_StopAD(hDevice);//����ˣ�Ӧ��ֹͣ�������˺���Ҳ��ʾ��ֹ����
			MP422E_CloseDevice(hDevice);
			runflag=FALSE;
			CWnd *pWnd = GetDlgItem(IDC_COMBO);
			pWnd->EnableWindow(TRUE);
			data_exit=TRUE;
			KillTimer(1);
			OnSetcanshu(TRUE);
			MessageBox("�忨�ڴ������AD�ɼ��Ѿ��Զ�ֹͣ","��ʾ");
		}
		else
		{	
			MP422E_Read(hDevice,length,buff);//��ȡӲ�����嵥Ԫ�е�����
			for(int i=0;i<length;i++)
			{
				if((topbuff)!=maxnum)
				{
					topbuff++;
					topdata=topbuff/(m_max-m_min+1);
					databuff[topbuff]=buff[i];
					t=topbuff%(m_max-m_min+1)+m_min;
					data[t][topdata]=(MP422E_ADV(ADrang,buff[i])/1000*15);
					if(data[t][topdata]>datamax[t])
					{
						datamax[t]=data[t][topdata];
					}
					if(data[t][topdata]<datamin[t])
					{
						datamin[t]=data[t][topdata];
					}
				}
				else
				{
					MP422E_StopAD(hDevice);
					MP422E_CloseDevice(hDevice);
					runflag=FALSE;
					CWnd *pWnd = GetDlgItem(IDC_COMBO);
					pWnd->EnableWindow(TRUE);
					data_exit=TRUE;
					KillTimer(1);
					OnSetcanshu(TRUE);
					DrawWave(pDCbx, rectPicture);
					MessageBox("�Ѿ��ﵽ���洢���ݳ��ȣ�AD�ɼ��Ѿ��Զ�ֹͣ","��ʾ");
					ChangeToolBarState();
					break;
				}
			}
			if(pScrollBar1->GetScrollPos()!=1)
				DrawBackGround(pDCbx, rectPicture);
			DrawWave(pDCbx, rectPicture);
		}
	}//timer=1����Ϣ��Ӧ
	CDialog::OnTimer(nIDEvent);
}

void CVrDlg::OnRun() //�������а�ť�¼�
{
	if(runflag==FALSE)
	{	
		hDevice=MP422E_OpenDevice(0);//���豸
		if(hDevice==INVALID_HANDLE_VALUE)
		{
			MessageBox("��ǰ�Ҳ����豸����ȷ����\n����ȷ���Ӻ������ԣ�","������ʾ",MB_ICONERROR);
			return ;
		}
		else
		{
			runflag=TRUE;

			if(modul!=2)//ADģʽ
			{
				file_exit=FALSE;
				if(MP422E_CAL(hDevice)==0)//AD�����������ɹ�����0
				{	
					topbuff=-1;
					topdata=-1;
					OnSetcanshu(FALSE);
					DrawBackGround(pDCbx, rectPicture);
					MP422E_AD(hDevice,m_min,m_max,ADrang,0,modul,0,0,0,0,10000000/m_times);
					for(int i=0;i<=15;i++)
					{
						datamax[i]=-1000;
						datamin[i]=1000; 
					}
					SetTimer(1,50,NULL);//AD��ʼ
				}
				else
					MessageBox("ADУ��ʧ�ܣ�","����",MB_ICONERROR);
			}
			else
			{
				DA_run=TRUE;
				hThread1=CreateThread(NULL,0,DAProc,this,0,NULL);//DA������һ���߳�
			}
		}
	}
	else
	{
		runflag=FALSE;
		if(modul!=2)
		{
			MP422E_StopAD(hDevice);  //����ˣ�Ӧ��ֹͣ�������˺���Ҳ��ʾ��ֹ����
			OnSetcanshu(TRUE);
			MP422E_CloseDevice(hDevice);
			runflag=FALSE;
			data_exit=TRUE;
			KillTimer(1);
			DrawWave(pDCbx, rectPicture);
		}
		else 
		{
			DA_run=false;//��״̬����
			CloseHandle(hThread1);//�ر�����߳�
		}
	}
	ChangeToolBarState();
}

void CVrDlg::OnExit() //�˳�����
{
	exit(0);
}

void CVrDlg::OnSelchangeCombo() //��Ͽ򱻸ı�ѡ��
{
	ADrang=m_box.GetCurSel();//��ȡ��Ͽ�ؼ���ѡ����ֵ
}

void CVrDlg::OnSavedata() //���Ϊ�����ļ�
{
		ChangeToolBarState();
		CFileDialog fileDlg(FALSE);//FALSE�����Ϊ�ļ��Ի���
		fileDlg.m_ofn.lpstrTitle="���Ϊ�����ļ�";//�Ի������
		fileDlg.m_ofn.lpstrFilter="Data Files(*.data)\0*.data\0\0";//��ʽ����\0�ָ2��\0��β
		fileDlg.m_ofn.lpstrDefExt="data";//����ȱʡ��չ��
		int a=65536;
		if(IDOK==fileDlg.DoModal())
		{
			CFile file(fileDlg.GetFileName(),CFile::modeCreate|CFile::modeWrite);
			file.Write(&a,4);//��֤��
			file.Write(&m_max,4);//ͨ�����ֵ
			file.Write(&m_min,4);//ͨ����Сֵ
			file.Write(&m_times,4);//����Ƶ��
			file.Write(&ADrang,4);//����
			file.Write(&topbuff,4);//���ݳ��ȣ��ܵģ�
			file.Write(&databuff,(topbuff+1)*4);//Դ����
			file.Close();
			MessageBox("����ɹ���","��Ϣ");
		}
}

void CVrDlg::OnOpendata() 
{
	CFileDialog fileDlg(TRUE);//TRUE�Ǵ��ļ��Ի���
	fileDlg.m_ofn.lpstrTitle="�������ļ�";//�Ի������
	fileDlg.m_ofn.lpstrFilter="Data Files(*.data)\0*.data\0\0";
	if(IDOK==fileDlg.DoModal())
	{
		CFile file(fileDlg.GetFileName(),CFile::modeRead);
		int a;
		file.Read(&a,4);//��֤��
		if(a!=65536)
		{
			MessageBox("��ȡ���ļ���ʽ���ԣ�\n��ѡ����ȷ���ļ���","����",MB_ICONERROR);
			file.Close();
			return ;
		}
		file.Read(&m_max,4);//ͨ�����ֵ
		file.Read(&m_min,4);//ͨ����Сֵ
		file.Read(&m_times,4);//����Ƶ��
		file.Read(&ADrang,4);//����
		file.Read(&topbuff,4);//�����ܳ���
		file.Read(&databuff,(topbuff+1)*4);//ԭʼ����
		file.Close();
		file_exit=TRUE;
		data_exit=TRUE;
		m_box.SetCurSel(ADrang);
		UpdateData(FALSE);
		OnSetcanshu(FALSE);
		ChangeToolBarState();
		MessageBox("��ȡ�ɹ���\n���������ļ�","��Ϣ");
	}
}

void CVrDlg::ChangeToolBarState()//�������κ�һ����ť��ʱ�򽫸ı�һ�����а�ť��״̬
{
	CToolBarCtrl& tb= m_wndToolBar.GetToolBarCtrl(); 
		if((modul==0||modul==1)&&runflag)//ADģʽrun�½�ֹ���е�
		{
			tb.EnableButton(ID_OPENDATA,FALSE);
			tb.EnableButton(ID_SAVEDATA,FALSE);
			tb.EnableButton(ID_ANALYSEFILE,FALSE);
			tb.EnableButton(ID_SETDAMOUDL,FALSE);
			tb.EnableButton(ID_RUN,TRUE);
			tb.EnableButton(ID_BEGAINFFT,FALSE);
		}
		if((modul==0||modul==1)&&!runflag)//ADģʽ��RUN
		{
			tb.EnableButton(ID_OPENDATA,FALSE);
			if(data_exit)
				tb.EnableButton(ID_SAVEDATA,TRUE);
			else
				tb.EnableButton(ID_SAVEDATA,FALSE);
			tb.EnableButton(ID_ANALYSEFILE,FALSE);
			tb.EnableButton(ID_SETDAMOUDL,FALSE);
			tb.EnableButton(ID_RUN,TRUE);
			if(data_exit)
				tb.EnableButton(ID_BEGAINFFT,TRUE);
			else
				tb.EnableButton(ID_BEGAINFFT,FALSE);
		}
		if(modul==2&&runflag)//DAģʽrun
		{
			tb.EnableButton(ID_OPENDATA,FALSE);
			tb.EnableButton(ID_SAVEDATA,FALSE);
			tb.EnableButton(ID_ANALYSEFILE,FALSE);
			tb.EnableButton(ID_SETDAMOUDL,FALSE);
			tb.EnableButton(ID_RUN,TRUE);
			tb.EnableButton(ID_BEGAINFFT,FALSE);
		}
		if(modul==2&&!runflag)//DAģʽ��run
		{
			tb.EnableButton(ID_OPENDATA,FALSE);
			tb.EnableButton(ID_SAVEDATA,FALSE);
			tb.EnableButton(ID_ANALYSEFILE,FALSE);
			tb.EnableButton(ID_SETDAMOUDL,TRUE);
			tb.EnableButton(ID_RUN,TRUE);
			tb.EnableButton(ID_BEGAINFFT,FALSE);
		}
		if(modul==3)//�ļ�ģʽ
		{
			tb.EnableButton(ID_OPENDATA,TRUE);
			if(data_exit)
				tb.EnableButton(ID_SAVEDATA,TRUE);
			else
				tb.EnableButton(ID_SAVEDATA,FALSE);
			if(file_exit)
				tb.EnableButton(ID_ANALYSEFILE,TRUE);
			else
				tb.EnableButton(ID_ANALYSEFILE,FALSE);
			tb.EnableButton(ID_SETDAMOUDL,FALSE);
			tb.EnableButton(ID_RUN,FALSE);
			if(data_exit)
				tb.EnableButton(ID_BEGAINFFT,TRUE);
			else
				tb.EnableButton(ID_BEGAINFFT,FALSE);
		}
}

void CVrDlg::OnCheck0() //һ������ӳ������ѡ����Ϣ
{
	CButton *pBtn;
	for(int st=IDC_CHECK0;st<=IDC_CHECK15;st++)
	{
		pBtn=static_cast <CButton *>(GetDlgItem(st));
		if(pBtn!=NULL)
		{
			tdflag[st-IDC_CHECK0]=(bool)pBtn->GetCheck();
			
		}
	}
	DrawBackGround(pDCbx, rectPicture);
	DrawWave(pDCbx, rectPicture);
}

void CVrDlg::DrawBackGround(CDC *pDC, CRect &rectPicture)//����ʱ��ı���ͼ
{
	CPen pen(PS_DOT,1,RGB(120,120,120));//��������
	CPen pen1(PS_SOLID,1,RGB(120,120,120));//����ʵ��
	pDC->SetBkMode(TRANSPARENT);
	CPoint p;
	CPen *pOldPen;   
    CBrush newBrush;    
    CBrush *pOldBrush;   
	pOldPen=pDC->SelectObject(&pen);
	newBrush.CreateSolidBrush(RGB(0,0,0)); // ������ɫ�»�ˢ   
    pOldBrush = pDC->SelectObject(&newBrush);// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
    pDC->Rectangle(rectPicture);//�Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����
    pDC->SelectObject(pOldBrush);// �ָ��ɻ�ˢ   
    newBrush.DeleteObject();// ɾ���»�ˢ
	p.y=2+rectPicture.top;
	for(int i=0;i<=10;i++)
	{	
		p.x=0;pDC->MoveTo(p);p.x=575;
		if(i==5){pDC->SelectObject(&pen1);}
		else    {pDC->SelectObject(&pen); }
		pDC->LineTo(p);
		p.y=p.y+30;
	}
	p.x=2+rectPicture.left;
	for(i=0;i<20;i++)
	{
		p.y=1;
		pDC->MoveTo(p);
		p.y=305;
		pDC->LineTo(p);
		p.x=p.x+30;
	}
	pDC->SelectObject(&pOldPen);
}

void CVrDlg::DrawBackGroundForFFT(CDC *pDC, CRect &rectPicture)//����FFT�ı���ͼ
{
	CPen pen(PS_DOT,1,RGB(120,120,120));//��������
	CPen pen1(PS_SOLID,1,RGB(120,120,120));//����ʵ��
	pDC->SetBkMode(TRANSPARENT);
	CPoint p;
	CPen *pOldPen;   
    CBrush newBrush;    
    CBrush *pOldBrush;   
	pOldPen=pDC->SelectObject(&pen);
	newBrush.CreateSolidBrush(RGB(0,0,0)); // ������ɫ�»�ˢ   
    pOldBrush = pDC->SelectObject(&newBrush);// ѡ���»�ˢ�������ɻ�ˢ��ָ�뱣�浽pOldBrush   
    pDC->Rectangle(rectPicture);//�Ժ�ɫ��ˢΪ��ͼ�ؼ�����ɫ���γɺ�ɫ����
    pDC->SelectObject(pOldBrush);// �ָ��ɻ�ˢ   
    newBrush.DeleteObject();// ɾ���»�ˢ
	p.y=17+rectPicture.top;
	for(int i=0;i<=6;i++)
	{
		p.x=0;
		pDC->MoveTo(p);
		p.x=575;//���Ϊ575
		pDC->LineTo(p);
		p.y=p.y+30;
	}
	p.x=2+rectPicture.left;
	for(i=0;i<20;i++)
	{
		p.y=1;
		pDC->MoveTo(p);
		p.y=200;//ͼƬ�ؼ�2�ĸ߶�Ϊ200
		pDC->LineTo(p);
		p.x=p.x+30;
	}
	pDC->SelectObject(&pOldPen);//��ԭ����
}

void CVrDlg::OnAnalysefile() 
{
	int t;
	for(int i=0;i<=15;i++)
	{
		datamax[i]=-1000;
		datamin[i]=1000;
	}
	for(i=0;i<=topbuff;i++)
	{
		t=i%(m_max-m_min+1)+m_min;
		topdata=i/(m_max-m_min+1);
		data[t][topdata]=MP422E_ADV(ADrang,databuff[i])/1000*15;//������150�ĸ��ӣ��������10VΪ�޶�
		if(data[t][topdata]>datamax[t])
		{
			datamax[t]=data[t][topdata];
		}
		if(data[t][topdata]<datamin[t])
		{
			datamin[t]=data[t][topdata];
		}
	}
	DrawBackGround(pDCbx, rectPicture);
	DrawWave(pDCbx, rectPicture);
}

void CVrDlg::FFT(double *data, double *new_data, int N)
{
	/*
	FFT�任����,����3������
	data      double������    �洢���任������
	new_data  double������    �洢�任���
	N            int�ͱ���    �洢�任�����ݵ���
	*/
	for(int weith=1;(1<<weith)<N;weith++);
	int B=0,n=N;
	N=1<<weith;
	double *Real=new double[N],*Imag=new double[N];
	double Rbufer=0,Ibufer=0,bufer=0;
	for(int i=0;i<n;i++)
	{	
		Real[InvertOrder(i,weith)]=data[i];
		Imag[InvertOrder(i,weith)]=0;
	}
	for(;i<N;i++)//����2^weith�� ����
	{	
		Real[InvertOrder(i,weith)]=0;
		Imag[InvertOrder(i,weith)]=0;
	}
	for(int L=0;L<weith;L++)
	{	
		B=1<<L;
		for(int j=0;j<B;j++)		
		{						
			bufer=-1*PI*j/(1<<L);	
			for(i=0;i<N;i+=2*B)
			{	n=i+j;	
			Rbufer= cos(bufer)*Real[n+B]-sin(bufer)*Imag[n+B];
			Ibufer= sin(bufer)*Real[n+B]+cos(bufer)*Imag[n+B];
			Real[n+B]=Real[n]-Rbufer;
			Imag[n+B]=Imag[n]-Ibufer;
			Real[n]=Real[n]+Rbufer;
			Imag[n]=Imag[n]+Ibufer;
			}
		}
	}
	for(i=0;i<N;i++)
		new_data[i]=sqrt(Real[i]*Real[i]+Imag[i]*Imag[i]);
	delete []Imag;
	delete []Real;
	return ;
}

void CVrDlg::OnBegainfft() 
{
	for(int i=0;i<=15;i++)
		if(tdflag[i])
		FFT(data[i], fftdata[i], 2000);
	DrawBackGroundForFFT(pDCbx2, rectPicture2);
	DrawFFT(pDCbx2,rectPicture2);//����FFT�Ĳ���	
}

int CVrDlg::InvertOrder(int x, int WEITH)
{
	//FFT�����õ��Ĺ��ܺ���
	unsigned int v1=1,y=0;
	for(int i=0;i<WEITH;i++)
	{		
		if(v1&x)
			y=y|(1<<(WEITH-1-i));
		v1=v1<<1;
	}
	return y;
}

void CVrDlg::OnCustomdrawSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString str;
	fDeltaX_ad=m_slider.GetPos(); 
	str.Format("%d",fDeltaX_ad);
	GetDlgItem(IDC_ABC)->SetWindowText(str);
	DrawBackGround(pDCbx, rectPicture);
	DrawWave(pDCbx, rectPicture);//��ʱ����
	*pResult = 0;
}

void CVrDlg::OnSetdamoudl() 
{
	CSettdcs dlg;
	dlg.da=daa;
	if(IDOK==dlg.DoModal())
	{
		daa=dlg.da;
	}

	if(daa.min>=0)
		DArange=10;
	else if(daa.max<=0||daa.min<=0)
		DArange=20;
	if(daa.damould==0)DA_Sin();
	if(daa.damould==1)DA_Sq();
	if(daa.damould==2)DA_Dt();
}

void CVrDlg::OnLookData() 
{
	pDlg->ShowWindow(SW_SHOWNORMAL);
}

void CVrDlg::OnSavebmp() 
{
	screenShot(rectPicture,rectPicture.left+22,rectPicture.top+64,"ʱ����.bmp");
	screenShot(rectPicture2,rectPicture.left+22,rectPicture.top+407,"Ƶ����.bmp");
}

void CVrDlg::screenShot(CRect rect, int left, int top, char *name)
{
	CBitmap*  m_pBitmap;                                                     
    CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     
    CPaintDC   dc(pMainFrame); 
    m_pBitmap=new   CBitmap;   
    m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   
    CDC   memDC;  
    memDC.CreateCompatibleDC(&dc); 
    CBitmap memBitmap, *oldmemBitmap;                                        
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
    oldmemBitmap = memDC.SelectObject(&memBitmap);
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,left, top, SRCCOPY);  // ����߶ȿ��
    BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                               // ���λͼ��Ϣ 
    FILE *fp = fopen(name, "w+b");
    BITMAPINFOHEADER bih = {0};                                              // λͼ��Ϣͷ
    bih.biBitCount = bmp.bmBitsPixel;                                        // ÿ�������ֽڴ�С
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                             // �߶�
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // ͼ�����ݴ�С
    bih.biWidth = bmp.bmWidth;                                               // ���
    BITMAPFILEHEADER bfh = {0};                                              // λͼ�ļ�ͷ
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // ��λͼ���ݵ�ƫ����
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // �ļ��ܵĴ�С
    bfh.bfType = (WORD)0x4d42;
     
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //д��λͼ�ļ�ͷ
     
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);
     
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];
     
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);
    delete [] p;    
    fclose(fp);
    memDC.SelectObject(oldmemBitmap);
    memDC.DeleteDC();
}

void CVrDlg::OnSetcanshu(bool sueflag) //�����پͽ�ֹ����Ͳ���ֹ
{
	CButton *pBtn;
	if(!sueflag)
	{
		sueflag=TRUE;
		UpdateData(TRUE);//��ȡ�ؼ���ֵ
		if(10000>m_times){m_times=10000;}
		else if(400000<m_times)
			m_times=400000;
		if(m_max>=15)
			m_max=15;
		if(m_min<=0)
			m_min=0;
		if(m_min>m_max)
			m_min=m_max-1;
		UpdateData(FALSE);
		for(int i=0;i<=15;i++)
		{
			pBtn=static_cast <CButton *>(GetDlgItem(IDC_CHECK0+i));
			if(i<m_min||i>m_max)
			{
				pBtn->EnableWindow(FALSE);
				pBtn->SetCheck(BST_UNCHECKED);
				tdflag[i]=FALSE;
			}
			else
			{
				pBtn->EnableWindow(TRUE);
			}	
		}
		GetDlgItem(IDC_MAX)->EnableWindow(FALSE);
		GetDlgItem(IDC_MIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_TIMES)->EnableWindow(FALSE);
		CWnd *pWnd = GetDlgItem(IDC_COMBO);
		pWnd->EnableWindow(FALSE);
	}
	else
	{
		sueflag=FALSE;
		CWnd *pWnd = GetDlgItem(IDC_COMBO);
		pWnd->EnableWindow(TRUE);
		GetDlgItem(IDC_MAX)->EnableWindow(TRUE);
		GetDlgItem(IDC_MIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_TIMES)->EnableWindow(TRUE);
	}	
}

void CVrDlg::GetWaveTimes(int s)//s�ǵڼ���
{
	double midle=(datamax[s]+datamin[s])/2;
	if(midle==datamax[s])
	{
		pinlv[s]=-1;
		return;
	}
	bool f=FALSE;
	double low=0,high=0,a=0;
	for(int i=1;i<topdata;i++)
	{
		if((data[s][i-1]<=midle&&data[s][i+1]>=midle)||(data[s][i-1]>=midle&&data[s][i+1]<=midle))
		{
			if(!f)
			{
				a++;
				f=TRUE;
			}
		}
		else
			f=FALSE;
		if(a==1)
			low=i;
		if(a==3)
		{
			high=i;
			break;
		}
	}

	if(high!=0)
	{
		for(i=high;i<topdata;i++)
			if((data[s][i-1]<=midle&&data[s][i+1]>=midle)||(data[s][i-1]>=midle&&data[s][i+1]<=midle))
				high--;
			else
				break;
		//pinlv[s]=(((double)m_times/(m_max-m_min+1))/(double)(high-low+1));
			//����Ĺ�ʽ�ڼ����Ͽ��ܴ�������ΪADת���ļ����������ֵ��1ǧ��/m_times��������Ǵ�������,��һ�����źŷ����������ź�Ҳ�Ǵ�������
		pinlv[s]=1000000/((double)((int)10000000/m_times)*(double)(m_max-m_min+1)*(double)(high-low+1)*0.1);
	}
	else
		pinlv[s]=-1;
}

void CVrDlg::OnRateforhardware() //Ӳ����Ƶ��
{
	long i,j,tdata;
	double t;
	hDevice=MP422E_OpenDevice(0);//���豸
	if(hDevice==INVALID_HANDLE_VALUE)
	{
		MessageBox("�������豸���޷���Ƶ�ʣ�\n��ȷ���豸��ȷ���Ӻ������ԣ�","������ʾ",MB_ICONERROR);
		return ;
	}
	MP422E_CNT_Run(hDevice,0, 5);
	do
	{
		MP422E_CNT_Read (hDevice,0, &j, &tdata);
		MP422E_CNT_Read (hDevice,0, &i, &tdata);
	}while(i!=j);
	t=tdata*0.1/4;
	t=1/t;
	CString aa;
	aa.Format("%.2fHz",t);
	GetDlgItem(IDC_RATFORHARDWARE)->SetWindowText(aa);
}

void CVrDlg::OnUse() 
{
	CHelp dlg;
	dlg.DoModal();
}

void CVrDlg::DA_Sin()//���Ҳ��δ���
{
	double t,DA_zhong;
	if(DArange==10)
	for(int i=0;i<=399;i++)
	{
		DA_zhong=(daa.max+daa.min)/2;
		t=((daa.max-daa.min)/2)*sin(((double)i/400)*3.1415926*2);
		t=t+DA_zhong;
		DA[i]=(int)((t/DArange)*4095);
	}
	else
	for(int i=0;i<=399;i++)
	{
		DA_zhong=(daa.max+daa.min)/2;
		t=((daa.max-daa.min)/2)*sin(((double)i/400)*3.1415926*2);
		t=t+DA_zhong;
		DA[i]=(int)((t/DArange)*4095)-2048;
	}
}

void CVrDlg::DA_Sq()//��������
{
	int i;
	if(DArange==20)
	{
	for(i=0;i<=(400*daa.zhankongbi/100);i++)
		DA[i]=(int)((daa.max/DArange)*4095)-2048;
	for(i=(400*daa.zhankongbi/100);i<=399;i++)
		DA[i]=(int)((daa.min/DArange)*4095)-2048;
	}
	else
	{
	for(i=0;i<=(400*daa.zhankongbi/100);i++)
		DA[i]=(int)((daa.max/DArange)*4095);
	for(i=(400*daa.zhankongbi/100);i<=399;i++)
		DA[i]=(int)((daa.min/DArange)*4095);
	}
}

void CVrDlg::DA_Dt()//���ǲ��δ���
{
	int i;
	double bbb;//��ѹֵֵ��iȡ��ͬʱ��Ӧ�ĵ�ѹֵ��ͬ
	double k=(daa.max-daa.min)/200;//б��
	if(DArange==10)
	{
		for(i=0;i<=199;i++)
		{
			bbb=k*(double)i+daa.min;
			DA[i]=(int)((bbb/DArange)*4095);
		}
		for(i=200;i<=399;i++)
		{
			bbb=(-1)*k*(double)i+2*daa.max-daa.min;
			DA[i]=(int)((bbb/DArange)*4095);
		}
	}
	else
	{
		for(i=0;i<=199;i++)
		{
			bbb=k*(double)i+daa.min;
			DA[i]=(int)((bbb/DArange)*4095)-2048;
		}
		for(i=200;i<=399;i++)
		{
			bbb=(-1)*k*(double)i+2*daa.max-daa.min;
			DA[i]=(int)((bbb/DArange)*4095)-2048;
		}
	}
}
/*
�������Է���(�����ĵ�)��
����0ͨ������DA���ʱ���ⲿ����Ϊ�������ĸ�����ͷ��3�Ŷ˿ڣ�3�ǽӸߣ�
����1ͨ������DA���ʱ���ⲿ����Ϊ�������ĸ�����ͷ��3�Ŷ˿ڣ�4�ǽӸߣ�
ÿ������DAת��ʱ��Ҫ��þ������Ϊһ��ʱ�䲻����API������ͻ����ı�
DA�����ֵһ��Ҫ�ڷ�Χ�ڣ�0-4095�ڣ�����ͻ�����ʧ�ܣ��൱��û�в���һ���������Щͬѧ
��������Ԥ���Ч������һ�涼�Ǵ����ֵ���ڷ�Χ��
һ����������ѹֵ��ʱ��ʽ�ǶԵģ����ǻ����㲻������ԭ���Ǽ���ʽ�ı������͵��µ�
����:
(int)5/(int)3=1
(int)3/(int)8=0
(double)3/(double)8=0.375
��˼����ʱ�������������ͣ���þ���ǿ����������ת��һ�£���֤���㲻��ʧ����*/

void CVrDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	/*
	*����������Ϣ����
	*
	*/
	int TempPos = pScrollBar->GetScrollPos();
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:	//�϶�����
		{
		pScrollBar->SetScrollPos(nPos);
		break;
		}
	case SB_LINELEFT:		//�����ߵļ�ͷ
		if(TempPos>1)
		{
			TempPos--;
		}
		DrawBackGround(pDCbx, rectPicture);
		DrawWave(pDCbx, rectPicture);
		pScrollBar->SetScrollPos(TempPos);
		break;
	case SB_LINERIGHT:		//����ұߵļ�ͷ
		if(TempPos<800)
		{
			TempPos++;
			DrawBackGround(pDCbx, rectPicture);
			DrawWave(pDCbx, rectPicture);
			pScrollBar->SetScrollPos(TempPos);
		}
		break;
	case SB_THUMBTRACK:		//���鷢������
		{
			pScrollBar->SetScrollPos(nPos);
			DrawBackGround(pDCbx, rectPicture);
			DrawWave(pDCbx, rectPicture);
			break;
		}
	} 
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

DWORD WINAPI CVrDlg::DAProc(LPVOID lpParameter)
{
	int i;
	hDevice=MP422E_OpenDevice(0);
	while(DA_run)							
	{	
		for(i=0;i<=399;i++)	
		{	
			if(DArange==10)
				MP422E_DA_Mode(hDevice,1,0);
			else
				MP422E_DA_Mode(hDevice,1,1);
			MP422E_DA(hDevice,1,DA[i]);
			CVrDlg* pDlg = (CVrDlg*)lpParameter;
			Sleep(pDlg->daa.rate*2);
		}
	}	
	return 0; 
}
