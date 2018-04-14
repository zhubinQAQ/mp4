// vr.h : main header file for the VR application
//

#if !defined(AFX_VR_H__1C5AFB40_10BE_4635_AA70_D9BA949BD8CD__INCLUDED_)
#define AFX_VR_H__1C5AFB40_10BE_4635_AA70_D9BA949BD8CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVrApp:
// See vr.cpp for the implementation of this class
//

class CVrApp : public CWinApp
{
public:
	CVrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VR_H__1C5AFB40_10BE_4635_AA70_D9BA949BD8CD__INCLUDED_)
