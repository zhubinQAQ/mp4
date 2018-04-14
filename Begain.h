#if !defined(AFX_BEGAIN_H__B07708BA_01EF_4FFD_B002_77E1F7494618__INCLUDED_)
#define AFX_BEGAIN_H__B07708BA_01EF_4FFD_B002_77E1F7494618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Begain.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Begain dialog

class Begain : public CDialog
{
// Construction
public:
	Begain(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Begain)
	enum { IDD = IDD_BEGAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Begain)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Begain)
	afx_msg void OnBegain();
	afx_msg void OnClose();
	afx_msg void OnCancle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEGAIN_H__B07708BA_01EF_4FFD_B002_77E1F7494618__INCLUDED_)
