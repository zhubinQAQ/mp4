#if !defined(AFX_DATA_H__C7EC9D77_724D_4CE0_B9D7_3C6ABC233498__INCLUDED_)
#define AFX_DATA_H__C7EC9D77_724D_4CE0_B9D7_3C6ABC233498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Data.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CData dialog

class CData : public CDialog
{
// Construction
public:
	CData(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CData)
	enum { IDD = IDD_DATA };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_H__C7EC9D77_724D_4CE0_B9D7_3C6ABC233498__INCLUDED_)
