#if !defined(AFX_SETTDCS_H__72A3721D_362D_431B_B5A6_8964CEDF285B__INCLUDED_)
#define AFX_SETTDCS_H__72A3721D_362D_431B_B5A6_8964CEDF285B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Settdcs.h : header file
//
#include "DAmd.h"
/////////////////////////////////////////////////////////////////////////////
// CSettdcs dialog

class CSettdcs : public CDialog
{
// Construction
public:
	CSettdcs(CWnd* pParent = NULL);   // standard constructor
	CDAmd da;
// Dialog Data
	//{{AFX_DATA(CSettdcs)
	enum { IDD = IDD_SETDA };
	double	m_max;
	double	m_min;
	double	m_pinlv;
	double	m_zhankongbi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettdcs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettdcs)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTDCS_H__72A3721D_362D_431B_B5A6_8964CEDF285B__INCLUDED_)
