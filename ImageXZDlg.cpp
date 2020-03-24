// ImageXZDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImageXZDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageXZDlg dialog


CImageXZDlg::CImageXZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageXZDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageXZDlg)
	m_xzds = 0;
	//}}AFX_DATA_INIT
}


void CImageXZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageXZDlg)
	DDX_Text(pDX, IDC_EDIT_XZ, m_xzds);
	DDV_MinMaxInt(pDX, m_xzds, 0, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageXZDlg, CDialog)
	//{{AFX_MSG_MAP(CImageXZDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageXZDlg message handlers
