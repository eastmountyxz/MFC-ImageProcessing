#if !defined(AFX_IMAGEPYDLG_H__9E8DA9E2_84D7_4514_8345_1F76CDF86A14__INCLUDED_)
#define AFX_IMAGEPYDLG_H__9E8DA9E2_84D7_4514_8345_1F76CDF86A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImagePYDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImagePYDlg dialog

class CImagePYDlg : public CDialog
{
// Construction
public:
	CImagePYDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImagePYDlg)
	enum { IDD = IDD_DIALOG_PY };
	int		m_xPY;
	int		m_yPY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagePYDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImagePYDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPYDLG_H__9E8DA9E2_84D7_4514_8345_1F76CDF86A14__INCLUDED_)
