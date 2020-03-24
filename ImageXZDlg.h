#if !defined(AFX_IMAGEXZDLG_H__9E4C8A62_BC8E_4984_988C_20F6F701AE79__INCLUDED_)
#define AFX_IMAGEXZDLG_H__9E4C8A62_BC8E_4984_988C_20F6F701AE79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageXZDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageXZDlg dialog

class CImageXZDlg : public CDialog
{
// Construction
public:
	CImageXZDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageXZDlg)
	enum { IDD = IDD_DIALOG_XZ };
	int		m_xzds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageXZDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageXZDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEXZDLG_H__9E4C8A62_BC8E_4984_988C_20F6F701AE79__INCLUDED_)
