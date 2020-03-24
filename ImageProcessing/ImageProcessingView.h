// ImageProcessingView.h : interface of the CImageProcessingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESSINGVIEW_H__2E589CAF_6BCD_4586_8B07_F024B9B6D16E__INCLUDED_)
#define AFX_IMAGEPROCESSINGVIEW_H__2E589CAF_6BCD_4586_8B07_F024B9B6D16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageProcessingView : public CView
{
protected: // create from serialization only
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// Attributes
public:
	CImageProcessingDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageProcessingView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//添加成员函数
	void ShowBitmap(CDC* pDC,CString BmpName); //显示位图函数
	bool ReadBmp();                            //用来读取bmp个手机图片
	bool SaveBmp(LPCSTR lpFileName);           //用来保存bmp格式图片

	//添加成员变量
	CString EntName;     //图像文件扩展名
	CString BmpName;     //图像文件名称
	CBitmap m_bitmap;    //创建位图对象

	int	m_nWidth;		//图像实际宽度
	int	m_nHeight;		//图像实际高度
	int	m_nDrawWidth;	//图像显示宽度
	int	m_nDrawHeight;	//图像显示高度
	DWORD m_nImage;		//图像数据的字节数 只含位图
	DWORD m_nSize;      //图像文件大小
	int m_nLineByte;    //图像一行所占字节数
	int	m_nBitCount;    //图像每个像素所占位数
	int	m_nPalette;     //位图实际使用的颜色表中的颜色数
	
	BYTE *m_pImage;         //读入图片数据后的指针
	BITMAPFILEHEADER bfh;   //全局变量文件头
	BITMAPINFOHEADER bih;   //全局变量信息头
	RGBQUAD m_pPal;         //颜色表指针

	CBitmap m_bitmaplin;   //创建临时位图对象进行处理
	CString BmpNameLin;    //保存图像副本文件

	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageProcessingView)
	afx_msg void OnFileOpen();
	afx_msg void OnShowTwo();
	afx_msg void OnShowHd();
	afx_msg void OnFileSave();
	afx_msg void OnLh2();
	afx_msg void OnLh4();
	afx_msg void OnLh8();
	afx_msg void OnLh16();
	afx_msg void OnLh32();
	afx_msg void OnLh64();
	afx_msg void OnCy();
	afx_msg void OnZftYt();
	afx_msg void OnDysXxjx();
	afx_msg void OnDysXxqb();
	afx_msg void OnDysXxzq();
	afx_msg void OnDysXxyd();
	afx_msg void OnDysFxxhs();
	afx_msg void OnDysFxxpf();
	afx_msg void OnDysYzbh();
	afx_msg void OnDysJhh();
	afx_msg void OnJhbhPy();
	afx_msg void OnJhbhTxxz();
	afx_msg void OnJhbhFz();
	afx_msg void OnJhbhDz();
	afx_msg void OnJhbhSf();
	afx_msg void OnTxzqPtph1();
	afx_msg void OnTxzqPtph2();
	afx_msg void OnTxzqGsph();
	afx_msg void OnTxzqZzlb();
	afx_msg void OnRHLaplacian();
	afx_msg void OnRHIsotropic();
	afx_msg void OnRHPrewitt();
	afx_msg void OnRHSobel();
	afx_msg void OnRhGtmb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageProcessingView.cpp
inline CImageProcessingDoc* CImageProcessingView::GetDocument()
   { return (CImageProcessingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROCESSINGVIEW_H__2E589CAF_6BCD_4586_8B07_F024B9B6D16E__INCLUDED_)
