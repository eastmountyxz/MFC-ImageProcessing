// ImageSFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ImageSFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageSFDlg dialog


CImageSFDlg::CImageSFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageSFDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageSFDlg)
	m_sfbs = 0;
	//}}AFX_DATA_INIT
}


void CImageSFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageSFDlg)
	DDX_Text(pDX, IDC_EDIT_SF, m_sfbs);
	DDV_MinMaxInt(pDX, m_sfbs, 0, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageSFDlg, CDialog)
	//{{AFX_MSG_MAP(CImageSFDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageSFDlg message handlers
