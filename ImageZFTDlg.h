#if !defined(AFX_IMAGEZFTDLG_H__CC7F91ED_BC84_447A_975F_6922F2DFE23E__INCLUDED_)
#define AFX_IMAGEZFTDLG_H__CC7F91ED_BC84_447A_975F_6922F2DFE23E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageZFTDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageZFTDlg dialog

class CImageZFTDlg : public CDialog
{
// Construction
public:
	CImageZFTDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageZFTDlg)
	enum { IDD = IDD_DIALOG_ZFT };
	CString	m_blueXS;
	CString	m_greenXS;
	CString	m_redXS;
	CString	m_blueBZC;
	CString	m_redBZC;
	CString	m_bluePJHD;
	CString	m_greenPJHD;
	CString	m_redPJHD;
	CString	m_blueZZHD;
	CString	m_greenZZHD;
	CString	m_redZZHD;
	CString	m_greenBZC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageZFTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageZFTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEZFTDLG_H__CC7F91ED_BC84_447A_975F_6922F2DFE23E__INCLUDED_)
