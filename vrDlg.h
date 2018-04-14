// vrDlg.h : header file
//
#include "data.h"
#include "DAmd.h"
#if !defined(AFX_VRDLG_H__F135F5E5_8D82_40D2_A5EE_ABF0FC79ABB1__INCLUDED_)
#define AFX_VRDLG_H__F135F5E5_8D82_40D2_A5EE_ABF0FC79ABB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVrDlg dialog

class CVrDlg : public CDialog
{
// Construction
public:
	static	DWORD WINAPI DAProc(LPVOID lpParameter );			//���̵߳Ĺ��̺���
	void DA_Dt();												//���DA���ǲ�����
	void DA_Sq();												//���DA�ķ������ɵ�ռ��ȣ�����
	void DA_Sin();												//���DA�����Ҳ�����
	void GetWaveTimes(int s);									//����Ƶ�ʵĺ�����sָ����ͨ����
	void screenShot(CRect rect,int left,int top,char *name);	//��������
	int InvertOrder(int x,int WEITH);							//���ڱ�FFT���õĺ���
	void FFT(double *data,double *new_data,int N);				//����FFT�任�ĺ���
	void DrawBackGroundForFFT(CDC *pDC, CRect &rectPicture);	//����Ƶ����ͼ�ı���
	void DrawBackGround(CDC *pDC, CRect &rectPicture);			//����ʱ����ͼ�ı���
	void ChangeToolBarState();									//�������пؼ���״̬
	void OnSetcanshu(bool sueflag);								//��������к󱻵��õĺ������������Ŀؼ��Ľ��ú���ֵ�����Լ��
	void DrawFFT(CDC *pDC, CRect &rectPicture);					//����FFT����
	void DrawColorTable();										//������ɫ��16��ͨ������ɫ
	void DrawTimeBack(int x,int y);
	CVrDlg(CWnd* pParent = NULL);	// standard constructor  
	bool runflag;					//��־�ɼ����Ƿ������е�״̬��־
	int topbuff;					//�������ݵĶ���
	int topdata;					//�洢���ݵ����һ����
	bool tdflag[16];				//16��ͨ����ѡͨ״̬
	COLORREF tdcolor[16];			//16��ͨ������ɫѡ�񱣴�
	bool data_exit;					//���ݴ��ڵı�־��������־�ܷ����Ϊ�����ļ�
	bool file_exit;					//ֻ�ж�ȡ�������ļ���ʱ����ܷ����ļ�
	int ADrang;						//0:10v,1:5v,2:2.5v,3:1.25v
	int modul;						//0:AD_NORMAL,1:AD_SH,2:DA,3:�ļ�����
	int fDeltaX_ad;					// AD��ͼ��x������������ͼ���������� 
	CRect rectPicture;				//ʱ���δ��ڴ�С�ı���
	CRect rectPicture2;				//Ƶ��..
	CDC *pDCbx;						//ʱ����豸���������ָ��
	CDC *pDCbx2;					//Ƶ��..
	CData *pDlg;					//�鿴���ݵĶԻ����ָ��
	CDAmd daa;						//DAת���õĲ�������
	CScrollBar* pScrollBar1;		//������1��ָ��



// Dialog Data
	//{{AFX_DATA(CVrDlg)
	enum { IDD = IDD_VR_DIALOG };
	CSliderCtrl	m_slider;
	CComboBox	m_box;
	long		m_times;
	long		m_max;
	long		m_min;
	long		m_edit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVrDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;						//ͼ��
	CMenu m_Menu;						//�˵�����������
	CToolBar m_wndToolBar;				//�����������Ķ���
	/*
	*���´�����MFC����Ϣӳ��
	*
	*/
	// Generated message map functions
	//{{AFX_MSG(CVrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnAuout();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedRadio0();
	afx_msg void OnClickedRadio1();
	afx_msg void OnClickedRadio2();
	afx_msg void OnClickedRadio3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRun();
	afx_msg void OnExit();
	afx_msg void OnSavedata();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnOpendata();
	afx_msg void OnCheck0();
	afx_msg void OnAnalysefile();
	afx_msg void OnBegainfft();
	afx_msg void OnCustomdrawSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetdamoudl();
	afx_msg void OnLookData();
	afx_msg void OnSavebmp();
	afx_msg void OnRateforhardware();
	afx_msg void OnUse();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawWave(CDC *pDC, CRect &rectPicture);	//����ʱ���εĺ���
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VRDLG_H__F135F5E5_8D82_40D2_A5EE_ABF0FC79ABB1__INCLUDED_)
