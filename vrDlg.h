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
	static	DWORD WINAPI DAProc(LPVOID lpParameter );			//子线程的过程函数
	void DA_Dt();												//获得DA三角波数据
	void DA_Sq();												//获得DA的方波（可调占封比）数据
	void DA_Sin();												//获得DA的正弦波数据
	void GetWaveTimes(int s);									//计算频率的函数，s指的是通道号
	void screenShot(CRect rect,int left,int top,char *name);	//截屏函数
	int InvertOrder(int x,int WEITH);							//用于被FFT调用的函数
	void FFT(double *data,double *new_data,int N);				//进行FFT变换的函数
	void DrawBackGroundForFFT(CDC *pDC, CRect &rectPicture);	//绘制频域波形图的背景
	void DrawBackGround(CDC *pDC, CRect &rectPicture);			//绘制时域波形图的背景
	void ChangeToolBarState();									//设置所有控件的状态
	void OnSetcanshu(bool sueflag);								//当点击运行后被调用的函数，用来更改控件的禁用和数值合理性检测
	void DrawFFT(CDC *pDC, CRect &rectPicture);					//绘制FFT波形
	void DrawColorTable();										//绘制颜色表，16个通道的颜色
	void DrawTimeBack(int x,int y);
	CVrDlg(CWnd* pParent = NULL);	// standard constructor  
	bool runflag;					//标志采集器是否在运行的状态标志
	int topbuff;					//缓存数据的顶部
	int topdata;					//存储数据的最后一个点
	bool tdflag[16];				//16个通道的选通状态
	COLORREF tdcolor[16];			//16个通道的颜色选择保存
	bool data_exit;					//数据存在的标志，用来标志能否另存为数据文件
	bool file_exit;					//只有读取了数据文件的时候才能分析文件
	int ADrang;						//0:10v,1:5v,2:2.5v,3:1.25v
	int modul;						//0:AD_NORMAL,1:AD_SH,2:DA,3:文件数据
	int fDeltaX_ad;					// AD绘图的x轴相邻两个绘图点的坐标距离 
	CRect rectPicture;				//时域波形窗口大小的保存
	CRect rectPicture2;				//频域..
	CDC *pDCbx;						//时域的设备描述符表的指针
	CDC *pDCbx2;					//频域..
	CData *pDlg;					//查看数据的对话框的指针
	CDAmd daa;						//DA转换用的参数对象
	CScrollBar* pScrollBar1;		//滚动条1的指针



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
	HICON m_hIcon;						//图标
	CMenu m_Menu;						//菜单栏关联对象
	CToolBar m_wndToolBar;				//工具栏关联的对象
	/*
	*以下代码是MFC的消息映射
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
	void DrawWave(CDC *pDC, CRect &rectPicture);	//绘制时域波形的函数
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VRDLG_H__F135F5E5_8D82_40D2_A5EE_ABF0FC79ABB1__INCLUDED_)
