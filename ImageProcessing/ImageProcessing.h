// ImageProcessing.h : main header file for the IMAGEPROCESSING application
//

#if !defined(AFX_IMAGEPROCESSING_H__3C8F4B5D_C7FA_41CF_8AF2_F2CD3883645E__INCLUDED_)
#define AFX_IMAGEPROCESSING_H__3C8F4B5D_C7FA_41CF_8AF2_F2CD3883645E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingApp:
// See ImageProcessing.cpp for the implementation of this class
//

class CImageProcessingApp : public CWinApp
{
public:
	CImageProcessingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageProcessingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImageProcessingApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROCESSING_H__3C8F4B5D_C7FA_41CF_8AF2_F2CD3883645E__INCLUDED_)
