// ImagePYDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImagePYDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagePYDlg dialog


CImagePYDlg::CImagePYDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImagePYDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImagePYDlg)
	m_xPY = 0;
	m_yPY = 0;
	//}}AFX_DATA_INIT
}


void CImagePYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImagePYDlg)
	DDX_Text(pDX, IDC_EDIT_PYX, m_xPY);
	DDX_Text(pDX, IDC_EDIT_PYY, m_yPY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImagePYDlg, CDialog)
	//{{AFX_MSG_MAP(CImagePYDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagePYDlg message handlers
