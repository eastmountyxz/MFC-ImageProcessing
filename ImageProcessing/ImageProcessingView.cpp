// ImageProcessingView.cpp : implementation of the CImageProcessingView class
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

//引用采样头文件
#include "ImageCYDlg.h"
//引用显示直方图头文件
#include "ImageZFTDlg.h"
#include "math.h"

//引用平移头文件
#include "ImagePYDlg.h"

//引用旋转头文件
#include "ImageXZDlg.h"

//引用缩放头文件
#include "ImageSFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	//{{AFX_MSG_MAP(CImageProcessingView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_SHOW_TWO, OnShowTwo)
	ON_COMMAND(ID_SHOW_HD, OnShowHd)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_LH_2, OnLh2)
	ON_COMMAND(ID_LH_4, OnLh4)
	ON_COMMAND(ID_LH_8, OnLh8)
	ON_COMMAND(ID_LH_16, OnLh16)
	ON_COMMAND(ID_LH_32, OnLh32)
	ON_COMMAND(ID_LH_64, OnLh64)
	ON_COMMAND(ID_CY, OnCy)
	ON_COMMAND(ID_ZFT_YT, OnZftYt)
	ON_COMMAND(ID_DYS_XXJX, OnDysXxjx)
	ON_COMMAND(ID_DYS_XXQB, OnDysXxqb)
	ON_COMMAND(ID_DYS_XXZQ, OnDysXxzq)
	ON_COMMAND(ID_DYS_XXYD, OnDysXxyd)
	ON_COMMAND(ID_DYS_FXXHS, OnDysFxxhs)
	ON_COMMAND(ID_DYS_FXXPF, OnDysFxxpf)
	ON_COMMAND(ID_DYS_YZBH, OnDysYzbh)
	ON_COMMAND(ID_DYS_JHH, OnDysJhh)
	ON_COMMAND(ID_JHBH_PY, OnJhbhPy)
	ON_COMMAND(ID_JHBH_TXXZ, OnJhbhTxxz)
	ON_COMMAND(ID_JHBH_FZ, OnJhbhFz)
	ON_COMMAND(ID_JHBH_DZ, OnJhbhDz)
	ON_COMMAND(ID_JHBH_SF, OnJhbhSf)
	ON_COMMAND(ID_TXZQ_PTPH1, OnTxzqPtph1)
	ON_COMMAND(ID_TXZQ_PTPH2, OnTxzqPtph2)
	ON_COMMAND(ID_TXZQ_GSPH, OnTxzqGsph)
	ON_COMMAND(ID_TXZQ_ZZLB, OnTxzqZzlb)
	ON_COMMAND(ID_RH_Laplacian, OnRHLaplacian)
	ON_COMMAND(ID_RH_Isotropic, OnRHIsotropic)
	ON_COMMAND(ID_RH_Prewitt, OnRHPrewitt)
	ON_COMMAND(ID_RH_Sobel, OnRHSobel)
	ON_COMMAND(ID_RH_GTMB, OnRhGtmb)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView construction/destruction

CImageProcessingView::CImageProcessingView()
{
	// TODO: add construction code here

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView drawing

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (!pDoc) return;  
	if( EntName.Compare(_T("bmp")) == 0 )      //bmp格式  
	{  
		ReadBmp();
		ShowBitmap(pDC,BmpName);               //显示图片  
	}  
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView printing

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView diagnostics

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView message handlers

/*************************************************************/
/* numPicture变量显示图片数量
/* 0-提示错误或未打开图片 1-显示一张图片 2-显示两张图片和处理
/*************************************************************/
int numPicture = 0;

/*************************************************************/
/* level变量显示具体的处理操作，每个处理函数中赋值该变量
/* 0-显示2张图片 1-显示灰度图片 3-显示图片采样
/* 2 4 8 16 32 64-不同量化等级量化图片
/*************************************************************/ 
int level = 0;    


/*定义显示图像缩放时的长宽与标记*/
int flagSF=0;          //图像几何变换缩放变换
int m_nDrawWidthSF=0;  //图像显示宽度缩放后
int	m_nDrawHeightSF=0; //图像显示高度缩放后

//****************显示BMP格式图片****************//
void CImageProcessingView::ShowBitmap(CDC *pDC, CString BmpName)
{
	//定义bitmap指针 调用函数LoadImage装载位图
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
		LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		
	/*************************************************************************/
	/* 1.要装载OEM图像，则设此参数值为0  OBM_ OEM位图 OIC_OEM图标 OCR_OEM光标
	/* 2.BmpName要装载图片的文件名                  
	/* 3.装载图像类型: 
	/*   IMAGE_BITMAP-装载位图 IMAGE_CURSOR-装载光标 IMAGE_ICON-装载图标    
	/* 4.指定图标或光标的像素宽度和长度 以像素为单位    
	/* 5.加载选项:
	/*   IR_LOADFROMFILE-指明由lpszName指定文件中加载图像
	/*   IR_DEFAULTSIZE-指明使用图像默认大小
	/*   LR_CREATEDIBSECTION-当uType参数为IMAGE_BITMAP时,创建一个DIB项
	/**************************************************************************/

	if( m_bitmap.m_hObject )
	{
		m_bitmap.Detach();           //切断CWnd和窗口联系
	}
	m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联
	
	//边界
	CRect rect;
	GetClientRect(&rect);

	//图片显示(x,y)起始坐标
	int m_showX=0;
	int m_showY=0;
	int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
	int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度
		
	//定义并创建一个内存设备环境DC
	CDC dcBmp;
	if( !dcBmp.CreateCompatibleDC(pDC) )   //创建兼容性的DC
		return;
	BITMAP m_bmp;                          //临时bmp图片变量
	m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中
	CBitmap *pbmpOld = NULL;      
	dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境
	
	//图片显示调用函数stretchBlt
	pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,
		m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
	
	/*******************************************************************************/
	/* BOOL StretchBlt(int x,int y,int nWidth,int nHeight,CDC* pSrcDC, 
	/*                 int xSrc,int ySrc,int nSrcWidth,int nSrcHeight,DWORD dwRop );
	/* 1.参数x、y位图目标矩形左上角x、y的坐标值      
	/* 2.nWidth、nHeigth位图目标矩形的逻辑宽度和高度      
	/* 3.pSrcDC表示源设备CDC指针                          
	/* 4.xSrc、ySrc表示位图源矩形的左上角的x、y逻辑坐标值 
	/* 5.dwRop表示显示位图的光栅操作方式 SRCCOPY用于直接将位图复制到目标环境中            
	/*******************************************************************************/
	
	dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
	DeleteObject(&m_bitmap);               //删除内存中的位图
	dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC


	/**
	 * 面代码为后面显示第二张图片
	 */

	if(numPicture==2) {
		//显示图片函数LoadImage
		HBITMAP m_hBitmapChange;
		if(level==0) //显示2张图 BmpNameLin原图
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else
		if(level==1) //灰度图片 BmpNameLin临时图片
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //量化2
		if(level==2)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //量化4
		if(level==4)  
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //量化8
		if(level==8)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //量化16
		if(level==16)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //量化32
		if(level==32)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //量化64
		if(level==64)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else if(level==3) //图片采样
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else        //图像点运算 线性变化
		if(level==101)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else        //图像几何变换
		if(level==200)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else        //图像增强
		if(level==400)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}


		if( m_bitmap.m_hObject ) {
			m_bitmap.Detach();            //m_bitmap为创建的位图对象
		}
		m_bitmap.Attach(m_hBitmapChange);
		//定义并创建一个内存设备环境
		CDC dcBmp;
		if( !dcBmp.CreateCompatibleDC(pDC) )   //创建兼容性的DC
			return;
		BITMAP m_bmp;                          //临时bmp图片变量
		m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中
		CBitmap *pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

		//图片显示调用函数StretchBlt 
		if(flagSF==1)
		{
			CString str;
			str.Format("缩放长=%d 宽%d 原图长=%d 宽=%d",m_nDrawWidthSF,m_nDrawHeightSF,m_nWidth,m_nHeight);
			AfxMessageBox(str);
			flagSF=0;
			//m_nDrawWidthSF缩放此存见函数最近邻插值法中赋值
			if(m_nDrawWidthSF<650 && m_nDrawHeightSF<650)   
				pDC->StretchBlt(m_nWindowWidth-m_nDrawWidthSF,0,
					m_nDrawWidthSF,m_nDrawHeightSF,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
			else
				pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,
					m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);  //显示大小为640*640
		}
		else {
			//如果图片太大显示大小为固定640*640 否则显示原图大小
			if(m_nDrawWidth<650 && m_nDrawHeight<650)
				pDC->StretchBlt(m_nWindowWidth-m_nDrawWidth,0,
					m_nDrawWidth,m_nDrawHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
			else
				pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,
					m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY); 
		}
		//恢复临时DC的位图
		dcBmp.SelectObject(pbmpOld);           
	}

}


//****************打开文件****************//
void CImageProcessingView::OnFileOpen() 
{
	//两种格式的文件：bmp gif
    CString filter;  
    filter="所有文件(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);            
  
    //按下确定按钮 dlg.DoModal() 函数显示对话框  
    if( dlg.DoModal() == IDOK )  
    {  
        BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp  
        BmpNameLin = "picture.bmp";      //临时变量名
		numPicture=1;                    //显示一张图片
		EntName = dlg.GetFileExt();      //获取文件扩展名  
        EntName.MakeLower();             //将文件扩展名转换为一个小写字符  
        Invalidate();                    //调用该函数就会调用OnDraw重绘画图  
    }  	
}

//***************读取图片数据*************//
bool CImageProcessingView::ReadBmp()
{
	//图片读出存储其中的东西
	FILE *fp = fopen(BmpName,"rb");
	if(fp==0)
	{		
		AfxMessageBox("无法打开文件!",MB_OK,0);
		return 0; 
	}
	//读取文件头 解决BMP格式倒置的方法
	fread(&bfh.bfType,sizeof(WORD),1,fp);
	fread(&bfh.bfSize,sizeof(DWORD),1,fp);
	fread(&bfh.bfReserved1,sizeof(WORD),1,fp);
	fread(&bfh.bfReserved2,sizeof(WORD),1,fp);
	fread(&bfh.bfOffBits,sizeof(DWORD),1,fp);
	//图像文件的总字节数
	m_nSize = bfh.bfSize;
	//判断是否是bmp格式图片
	if(bfh.bfType!=0x4d42)   //'BM'
	{
		AfxMessageBox("不是BMP格式图片!",MB_OK,0);
		return 0;
	}
	//读取信息头
	fread(&bih.biSize,sizeof(DWORD),1,fp);
	fread(&bih.biWidth,sizeof(LONG),1,fp);
	fread(&bih.biHeight,sizeof(LONG),1,fp);
	fread(&bih.biPlanes,sizeof(WORD),1,fp);
	fread(&bih.biBitCount,sizeof(WORD),1,fp);
	fread(&bih.biCompression,sizeof(DWORD),1,fp);
	fread(&bih.biSizeImage,sizeof(DWORD),1,fp);
	fread(&bih.biXPelsPerMeter,sizeof(LONG),1,fp);
	fread(&bih.biYPelsPerMeter,sizeof(LONG),1,fp);
	fread(&bih.biClrUsed,sizeof(DWORD),1,fp);
	fread(&bih.biClrImportant,sizeof(DWORD),1,fp);
	if(bih.biSize!=sizeof(bih))
	{
		AfxMessageBox("本结构所占用字节数出现错误");
		return 0;
	}
	//位图压缩类型，必须是 0（不压缩） 1（BI_RLE8压缩类型）或2（BI_RLE压缩类型）之一
	if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox("位图被压缩!");
		return 0;
	}
	//获取图像高宽和每个像素所占位数
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //每个像素所占位数
	//计算图像每行像素所占的字节数（必须是32的倍数）
	m_nLineByte = (m_nWidth*m_nBitCount+31)/32*4;
	//图片大小 调用系统自带的文件头 BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//否则用 BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;要 m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//位图实际使用的颜色表中的颜色数 biClrUsed
	m_nPalette = 0;                       //初始化
	if(bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//申请位图空间 大小为位图大小 m_nImage
	//malloc只能申请4字节的空间 （未知）
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fp);
	fclose(fp);
	return true;
}

//****************保存文件****************//
bool CImageProcessingView::SaveBmp(LPCSTR lpFileName) //lpFileName为位图文件名
{
	//保存bmp格式图片 写图片过程 只处理24像素的图片 该图片无调色板
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(lpFileName,"wb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//malloc只能申请4字节的空间 （未知）
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	return true;
}

//******************文件保存*****************//
void CImageProcessingView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CString filter;
	filter="所有文件(*.bmp,*.jpg)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	//重点: 1-文件打开 0-文件保存
	CFileDialog dlg(0,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);   
	//按下确定按钮
	if( dlg.DoModal() == IDOK ) {
		CString str;
		CString strName;
		CString filename;
		str = dlg.GetPathName();           //获取文件的路径
		filename = dlg.GetFileTitle();     //获取文件名
		int nFilterIndex=dlg.m_ofn.nFilterIndex;
		if( nFilterIndex == 2 )            //当用户选择文件过滤器为".BMP"时
		{
			str = str + ".bmp";	           //自动加扩展名.bmp
			SaveBmp(str);                  //保存bmp图片 就是一个写出图片的过程 
			AfxMessageBox("图片保存成功",MB_OK,0);
		}
	}
}

//****************显示两张图片****************//
void CImageProcessingView::OnShowTwo() 
{
	//如果没有导入图片直接点击双显 提示错误
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能显示2张图片!");
		return;
	}
	AfxMessageBox("显示两张图片!",MB_OK,0);
	numPicture = 2;    //全局变量 显示两图
	level =0;          //level=0双显
	Invalidate();      //调用Invalidate 每秒调用一次OnDraw画图
}


/********************************************************************************************/
/* 祥见http://blog.csdn.net/xiakq/article/details/2956902有详细的灰度算法                   
/* 其中24位的图片灰度时,采用如下算法:                                                       
/* 1.平均值算法 R=G=B=(R+G+B)/3                                                              
/* 2.快速算法 R=G=B=(R+G+B+128)/4>>2                                                          
/* 3.加权平均值算法 根据光的亮度特性,其实正确的灰度公式应当是R=G=B=R*0.299+G*0.587+B0.144   
/*   为了提高速度我们做一个完全可以接受的近似，公式变形如下 R=G=B=(R*3+G*6+B)/10            
/* 4.精确加权平均值算法 R=G=B=R*0.299+G*0.587+B0.144                                        
/********************************************************************************************/

//**灰度图像就是 R=G=B且为三者的1/3 level=1时灰度图像**//
void CImageProcessingView::OnShowHd() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能灰度图片!",MB_OK,0);
		return;
	}
	AfxMessageBox("灰度图像!",MB_OK,0);
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;

	/********************************************************************/
	/* 注意：原来下面所有操作都是for( i=0; i<m_nWidth*m_nHeight; i++ )  */
	/* 后发现如果图片最后一行没有完整的一行数据，会出现图像变多或变少   */
	/* 但图像的总像素为m_nImage，如果是m_nImage/3就可以保证所有像素都有 */
	/********************************************************************/

	for(int i=0; i < m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		color=(red+green+blue)/3;
		red=color;
		green=color;  
		blue=color;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=1;
	Invalidate();
}


//****************量化 量化等级为2****************//
void CImageProcessingView::OnLh2() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能量化!",MB_OK,0);
		return;
	}
	AfxMessageBox("量化等级Level=2!",MB_OK,0);
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//malloc只能申请4字节的空间
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//等级2量化
	for(int i=0; i<m_nImage; i++ ) {
		//24位的为调色板为真彩图 Red Green Blue 为3字节 
		//量化等级为2取中间值为 64 和 192
		if(m_pImage[i]<128) { 
			m_pImage[i]=0;
		}
		else if(m_pImage[i]>=128) {
			m_pImage[i]=128;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=2;
	Invalidate();
}

//****************量化 量化等级为4****************//
void CImageProcessingView::OnLh4() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能量化!",MB_OK,0);
		return;
	}
	AfxMessageBox("量化等级Level=4!",MB_OK,0);
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//等级4量化
	for(int i=0; i<m_nImage; i++ ) {
		if(m_pImage[i]<64) {
			m_pImage[i]=0;
		}
		else if( (m_pImage[i]>=64) && (m_pImage[i]<128) ) {
			m_pImage[i]=64;
		}
		else if( (m_pImage[i]>=128) && (m_pImage[i]<192) ) {
			m_pImage[i]=128;
		}
		else if(m_pImage[i]>=192) {
			m_pImage[i]=192;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=4;
	Invalidate();
}

//****************量化 量化等级为8****************//
void CImageProcessingView::OnLh8() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能量化!",MB_OK,0);
		return;
	}
	AfxMessageBox("量化等级Level=8!",MB_OK,0);
	//打开临时的图片 读取文件
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//malloc只能申请4字节的空间 （未知）
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//等级8量化
	for(int i=0; i<m_nImage; i++ ) {
		if(m_pImage[i]<32) {
			m_pImage[i]=0;
		}
		else if( (m_pImage[i]>=32) && (m_pImage[i]<64) ) {
			m_pImage[i]=32;
		}
		else if( (m_pImage[i]>=64) && (m_pImage[i]<96) ) {
			m_pImage[i]=64;
		}
		else if( (m_pImage[i]>=96) && (m_pImage[i]<128) ) {
			m_pImage[i]=96;
		}
		else if( (m_pImage[i]>=128) && (m_pImage[i]<160) ) {
			m_pImage[i]=128;
		}
		else if( (m_pImage[i]>=160) && (m_pImage[i]<192) ) {
			m_pImage[i]=160;
		}
		else if( (m_pImage[i]>=192) && (m_pImage[i]<224) ) {
			m_pImage[i]=192;
		}
		else if(m_pImage[i]>=224) {
			m_pImage[i]=224;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=8;
	Invalidate();
}

//****************量化 量化等级为16****************//
void CImageProcessingView::OnLh16() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能量化!",MB_OK,0);
		return;
	}
	AfxMessageBox("量化等级Level=16!",MB_OK,0);
	int i,j;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	for( i=0; i<m_nImage; i++ ) {
		j=16;
		while(j<=256)
		{
			if(m_pImage[i]<j) 
			{
				if(m_pImage[i]<16) 
					m_pImage[i]=0;
				else 
					m_pImage[i]=j-16;
				break;
			}
			else j+=16;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=16;
	Invalidate();
}

//****************量化 量化等级为32****************//
void CImageProcessingView::OnLh32() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能量化!",MB_OK,0);
		return;
	}
	AfxMessageBox("量化等级Level=32!",MB_OK,0);
	int i,j;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//等级32化
	for( i=0; i<m_nImage; i++ )
	{
		j=8;
		while(j<=256)
		{
			if(m_pImage[i]<j) 
			{
				if(m_pImage[i]<8) 
					m_pImage[i]=0;
				else 
					m_pImage[i]=j-8;
				break;
			}
			else j+=8;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=32;
	Invalidate();
}

//****************量化 量化等级为64****************//
void CImageProcessingView::OnLh64() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能量化!",MB_OK,0);
		return;
	}
	AfxMessageBox("量化等级Level=64!",MB_OK,0);
	int i,j;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//等级64量化
	for( i=0; i<m_nImage; i++ )
	{
		j=4;
		while(j<=256)
		{
			if(m_pImage[i]<j) 
			{
				if(m_pImage[i]<16) 
					m_pImage[i]=0;
				else 
					m_pImage[i]=j-4;
				break;
			}
			else j+=4;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=64;
	Invalidate();
}

//****************图片采样****************//
void CImageProcessingView::OnCy() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能采样!",MB_OK,0);
		return;
	}
	CImageCYDlg dlg;     //定义采样对话框
	//显示对话框
	if( dlg.DoModal()==IDOK ) {
		//采样坐标最初为图片的自身像素
		if( dlg.m_xPlace==0 || dlg.m_yPlace==0 ) {
			AfxMessageBox("输入图片像素不能为0!",MB_OK,0);
			return;
		}
		if( dlg.m_xPlace>m_nWidth || dlg.m_yPlace>m_nHeight ) {
			AfxMessageBox("图片像素不能为超过原图长宽!",MB_OK,0);
			return;
		}
		AfxMessageBox("图片采样!",MB_OK,0);
		//打开临时的图片 读取文件
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
		fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
		fread(m_pImage,m_nImage,1,fpo);
	
		/*图片采样*/
		int numWidth,numHeight;     //图片此区间取相同的像素点
		int numSYWidth,numSYHeight; //剩余期间区域 

		/*********************************************************/
		/* 表示numWidth*numHeight为一个区域 该区域颜色相同       */
		/* 如 512/512=1 512/512=1 1*1为一个区域                  */
		/* dlg.m_xPlace*dlg.m_yPlace 表示新的（x,y）坐标         */
		/* numSYWidth表示剩余空间 该区域统一为一个颜色           */
		/*********************************************************/

		numWidth=m_nWidth/dlg.m_xPlace;        
		numHeight=m_nHeight/dlg.m_yPlace;      
		numSYWidth=m_nWidth%dlg.m_xPlace;     
		numSYHeight=m_nHeight%dlg.m_yPlace;   
		int Y,X;
		int i,j,m,n;
		unsigned char red,green,blue;  //存储三种颜色
	
		/* 有((m_xPlace * m_yPlace)+ 剩余区域 )个小区域 */
		for( i=0; i<dlg.m_yPlace; i++ )       //高度
		{
			Y=numHeight*i;                    //获取Y坐标
			for( j=0; j<dlg.m_yPlace; j++ )   //宽度
			{
				X=numWidth*j;                 //获取X坐标
				/*获取填充颜色*/
				red=m_pImage[(X+Y*m_nWidth)*3];
				green=m_pImage[(X+Y*m_nWidth)*3+1];
				blue=m_pImage[(X+Y*m_nWidth)*3+2];
				/*填出图像循环 小区域中的长宽循环*/
				for( n=0; n<numHeight; n++ )
				{
					for( m=0; m<numWidth*3; )
					{
						m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=red;
						m++;
						m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=green;
						m++;
						m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=blue;
						m++;
					}
				}
			}
		}
		fwrite(m_pImage,m_nImage,1,fpw);
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level=3;
		Invalidate();
	}
}



/*全局变量在TestZFTDlg.cpp中引用 用extern*/
int Red[256],Green[256],Blue[256];

/**************************************************/
/* 添加直方图显示功能，并在直方图下方显示相关信息 
/* 如平均灰度、中值灰度、标准差和像素总数         
/* ID_ZFT_YT:直方图原图显示                       
/**************************************************/
void CImageProcessingView::OnZftYt() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能显示原图直方图!",MB_OK,0);
		return;
	}
	AfxMessageBox("显示原图直方图!",MB_OK,0);
	CImageZFTDlg dlg;

	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	
	int i,j;
	for(j=0;j<256;j++) { //定义数组并清零
		Red[j]=0;
		Green[j]=0;
		Blue[j]=0;
	}
	
	//计算4个数据
	unsigned char red,green,blue;
	int IntRed,IntGreen,IntBlue;                  //强制转换
	double sumRedHD=0,sumGreenHD=0,sumBlueHD=0;   //记录像素总的灰度值和
	for(i=0; i<m_nImage/3; i++ ) 
	{
		fread(&red,sizeof(char),1,fpo);
		IntRed=int(red);
		sumRedHD=sumRedHD+IntRed;
		if( IntRed>=0 && IntRed<256 ) Red[IntRed]++; //像素0-255之间
		
		fread(&green,sizeof(char),1,fpo);
		IntGreen=int(green);
		sumGreenHD=sumGreenHD+IntGreen;
		if( IntGreen>=0 && IntGreen<256 ) Green[IntGreen]++;
		
		fread(&blue,sizeof(char),1,fpo);
		IntBlue=int(blue);
		sumBlueHD=sumBlueHD+IntBlue;
		if( IntBlue>=0 && IntBlue<256 ) Blue[IntBlue]++;
	}
	fclose(fpo);
	
	//像素:int型转换为CString型 
	dlg.m_redXS.Format("%d",m_nImage);
	dlg.m_greenXS.Format("%d",m_nImage);
	dlg.m_blueXS.Format("%d",m_nImage);
	
	//平均灰度值:计算24位bmp图片的灰度值,我是记录RGB中的所有平均值	
	float pinRedHD,pinGreenHD,pinBlueHD; 
	pinRedHD=sumRedHD*3/m_nImage;
	pinGreenHD=sumGreenHD*3/m_nImage;     //平均灰度=总灰度/总像素
	pinBlueHD=sumBlueHD*3/m_nImage;
	
	dlg.m_redPJHD.Format("%.2f",pinRedHD);
	dlg.m_greenPJHD.Format("%.2f",pinGreenHD);
	dlg.m_bluePJHD.Format("%.2f",pinBlueHD);
	
	/****************************************************************/
	/* 中值灰度:算法重点(黄凯大神提供)                              
	/* 中值灰度:所有像素中的中位数,应该所有像素排序找到中间的灰度值 
	/* 算法:num[256]记录各灰度出现次数,sum+=num[i],找到sum=总像素/2 
	/****************************************************************/
	int sumRedZZHD=0,sumGreenZZHD=0,sumBlueZZHD=0;
	int redZZHD,greenZZHD,blueZZHD;
	for(i=0;i<256;i++)
	{
		sumRedZZHD=sumRedZZHD+Red[i];
		if(sumRedZZHD>=m_nImage/6)          //m_nImage被分成3份RGB并且sum=总像素/2
		{
			redZZHD=i;
			break;
		}
	}
	for(i=0;i<256;i++)
	{
		sumGreenZZHD=sumGreenZZHD+Green[i];
		if(sumGreenZZHD>=m_nImage/6)          //m_nImage被分成3份RGB并且sum=总像素/2
		{
			greenZZHD=i;
			break;
		}
	}
	for(i=0;i<256;i++)
	{
		sumBlueZZHD=sumBlueZZHD+Blue[i];
		if(sumBlueZZHD>=m_nImage/6)          //m_nImage被分成3份RGB并且sum=总像素/2
		{
			blueZZHD=i;
			break;
		}
	}
	
	dlg.m_redZZHD.Format("%d",redZZHD);
	dlg.m_greenZZHD.Format("%d",greenZZHD);
	dlg.m_blueZZHD.Format("%d",blueZZHD);
	
	/******************************************************************/
	/*标准差:标准差=方差的算术平方根                                   
	/*       方差s^2=[(x1-x)^2+(x2-x)^2+......(xn-x)^2]/n             
	/* 算法:不用开m_nImage数组进行计算 用num[256]中数进行             
	/* 方差=(平均灰度-i)*(平均灰度-i)*Red[i]  有Red[i]个灰度值为i的数 
	/******************************************************************/
	float redBZC,greenBZC,blueBZC;       //标准差
	double redFC=0,greenFC=0,blueFC=0;    //方差
	for(i=0;i<256;i++)
	{
		redFC=redFC+(pinRedHD-i)*(pinRedHD-i)*Red[i];   //有Red[i]个像素i
		greenFC=greenFC+(pinGreenHD-i)*(pinGreenHD-i)*Green[i];
		blueFC=blueFC+(pinBlueHD-i)*(pinBlueHD-i)*Blue[i];
	}
	
	redBZC=sqrt(redFC*3/m_nImage);
	greenBZC=sqrt(greenFC*3/m_nImage);
	blueBZC=sqrt(blueFC*3/m_nImage);
	
	dlg.m_redBZC.Format("%.2lf",redBZC);
	dlg.m_greenBZC.Format("%.2lf",greenBZC);
	dlg.m_blueBZC.Format("%.2lf",blueBZC);
	

	//重点必须添加该语句才能弹出对话框
	if(dlg.DoModal()==IDOK)
	{

	}
	
}


/**********************************************************************/
/* 图像点运算 4种线性变化直方图：                                                
/* ID_DYS_XXYD:表示线性灰度变化移动 D(B)=D(A)+50  灰度值上移下移        
/* ID_DYS_XXZQ:表示线性灰度变化增强 D(B)=1.5*D(A) 图像对比度增强       
/* ID_DYS_XXJX:表示线性灰度变化减小 D(B)=0.8*D(A) 图像对比度减小       
/* ID_DYS_XXQB:表示线性灰度求补 D(B)=-1*D(A)+255  图像暗区变亮,亮区变暗 
/**********************************************************************/

// 1.点运算 线性灰度变化移动 D(B)=D(A)+50
void CImageProcessingView::OnDysXxyd() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能线性灰度运算!",MB_OK,0);
		return;
	}
	AfxMessageBox("线性灰度直方图-灰度变化移动 D(B)=D(A)+50!",MB_OK,0);
	int i;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( (int)red+50 >255 )
			red=255;
		else
			red=(int)red+50;

		if( (int)green+50>255 )
			green=255;
		else
			green=(int)green+50;  

		if( (int)blue+50>255 )
			blue=255;
		else
			blue=(int)blue+50;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}

	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;       //赋值101在ShowBitmap中调用显示处理后的图片
	Invalidate();
}

// 2.点运算 线性灰度变化增强 D(B)=1.5*D(A)
void CImageProcessingView::OnDysXxzq() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能线性灰度运算!",MB_OK,0);
		return;
	}
	AfxMessageBox("线性灰度直方图-灰度变化增强 D(B)=1.5*D(A)!",MB_OK,0);
	int i;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( (int)red*1.5 >255 )
			red=255;
		else
			red=(int)red*1.5;

		if( (int)green*1.5>255 )
			green=255;
		else
			green=(int)green*1.5;  
		
		if( (int)blue*1.5>255 )
			blue=255;
		else
			blue=(int)blue*1.5;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;      //线性变化 ShowBitmap中调用
	Invalidate();
}

// 3.点运算 线性灰度变化减小D(B)=0.8*D(A)
void CImageProcessingView::OnDysXxjx() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能线性灰度处理!",MB_OK,0);
		return;
	}
	AfxMessageBox("线性灰度直方图-灰度减小 D(B)=0.8*D(A)!",MB_OK,0);
	int i;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=(int)red*0.8;
		green=(int)green*0.8;  
		blue=(int)blue*0.8;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

// 4.点运算 线性灰度求补 D(B)=-1*D(A)+255
void CImageProcessingView::OnDysXxqb() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能线性灰度处理!",MB_OK,0);
		return;
	}
	AfxMessageBox("线性灰度直方图-灰度求补 D(B)=-1*D(A)+255!",MB_OK,0);
	int i;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=(int)red*(-1)+255;
		green=(int)green*(-1)+255;  
		blue=(int)blue*(-1)+255;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}




/************************************************************************/
/* 2种非线性变化直方图：                                                
/* ID_DYS_FXXPF:表示非线性平方灰度变化,D(B)=D(A)*D(A)/255                
/* ID_DYS_FXXHS:表示非线性函数灰度变化,D(B)=D(A)+0.8*D(A)*(255-D(A))/255 
/************************************************************************/

// 非线性平方灰度变化 D(B)=D(A)*D(A)/252
void CImageProcessingView::OnDysFxxpf() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能非线性灰度处理!",MB_OK,0);
		return;
	}
	AfxMessageBox("非线性灰度变化 D(B)=D(A)*D(A)/255!",MB_OK,0);
	int i;
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//读取文件
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//灰度图像
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=(int)red*(int)red/255;
		green=(int)green*(int)green/255;
		blue=(int)blue*(int)blue/255;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

// 非线性函数灰度变化 D(B)=D(A)+0.8*D(A)*(255-D(A))/255
void CImageProcessingView::OnDysFxxhs() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能非线性灰度处理!",MB_OK,0);
		return;
	}
	AfxMessageBox("线性灰度直方图-灰度变化增强 D(B)=D(A)+0.8*D(A)*(255-D(A))/255!",MB_OK,0);
	int i;

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);	
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);

	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( ((int)red+0.8*(int)red*(255-(int)red)/255) > 255 )
			red=255;
		else
			red=(int)red+0.8*(int)red*(255-(int)red)/255;

		if( ((int)green+0.8*(int)green*(255-(int)green)/255) > 255 )
			green=255;
		else
			green=(int)green+0.8*(int)green*(255-(int)green)/255;  
		
		if( ((int)blue+0.8*(int)blue*(255-(int)blue)/255) > 255 )
			blue=255;
		else
			blue=(int)blue+0.8*(int)blue*(255-(int)blue)/255;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

/**************************************************************/
/* ID_DYS_YZBH:表示点运算阈值变换 也看做灰度拉伸                   
/* 此处的拉伸是：阈值化(thresholding)可以看作是削波的一个特例 
/* 只要令削波中的g1old=g2old就实现了阈值化。                  
/* 阈值就象个门槛，比它大就是白，比它小就是黑,二值            
/**************************************************************/

void CImageProcessingView::OnDysYzbh() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能点运算阈值化处理!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像点运算阈值化处理!",MB_OK,0);
	//读写文件
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//处理
	unsigned char color;
	unsigned char red,green,blue;
	for(int i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( (int)red > 128 )
			red=255;
		else
			red=0;

		if( (int)green > 128 )
			green=255;
		else
			green=0;  
		
		if( (int)blue > 128 )
			blue=255;
		else
			blue=0;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

// ID_DYS_JHH:表示图像均衡化 相见算法
void CImageProcessingView::OnDysJhh() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能图像均衡化!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像均衡化!",MB_OK,0);

    //第一步:获取图像的数据信息
	//此操作可以在打开图片时就进行 在直方图采样(ZFTCY)中也有该代码
	FILE *fpo = fopen(BmpName,"rb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);

	int i,j,k;
	for(j=0;j<256;j++) { //定义数组并清零
		Red[j]=0;
		Green[j]=0;
		Blue[j]=0;
	}
	
	//计算4个数据
	unsigned char red,green,blue;
	int IntRed,IntGreen,IntBlue;                  //强制转换
	double sumRedHD=0,sumGreenHD=0,sumBlueHD=0;   //记录像素总的灰度值和
	for(i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		IntRed=int(red);
		sumRedHD=sumRedHD+IntRed;
		if( IntRed>=0 && IntRed<256 ) Red[IntRed]++;
		
		fread(&green,sizeof(char),1,fpo);
		IntGreen=int(green);
		sumGreenHD=sumGreenHD+IntGreen;
		if( IntGreen>=0 && IntGreen<256 ) Green[IntGreen]++;
		
		fread(&blue,sizeof(char),1,fpo);
		IntBlue=int(blue);
		sumBlueHD=sumBlueHD+IntBlue;
		if( IntBlue>=0 && IntBlue<256 ) Blue[IntBlue]++;
	}
	fclose(fpo);

	/*****************************************************************/
	/* 图像均衡化处理                                                
	/* 利用全局变量 Red[256] Blue[256] Green[256]                    
	/* 第一步:用3个数组Count..记录0-255灰度出现的概率，即            
	/*        概率=该灰度出现次数*3/总得像素 (因为分成3部分RGB)      
	/* 第二步:i从1开始，令s[i]=s[i]+s[i-1] 记录新概率数              
	/* 第三步:用一个数组L记录新的调色板索引值，即                    
	/*        L[i]=s[i]×(256-1)结果四舍五入2.8即为3                 
	/* 第四步:将老的索引值对应的概率合并，作为对应的新的索引值的概率 
	/*   1.原来的索引值0,1都对应了新的索引值0，则灰度索引值为0的概率 
	/*     为P0+P1=0.03                                              
	/*   2.新的索引值3和7找不到老的索引值与之对应，所以令Q3和Q7为0   
	/*****************************************************************/

	//记录出现的概率,会加到1 用于相加到调色板
	float CountRed[256],CountGreen[256],CountBlue[256];      
	//记录原始数据,不会相加到1 用于计算新灰度概率
	float CountRedLin[256],CountGreenLin[256],CountBlueLin[256];   

	for( k=0 ; k<256 ; k++ )
	{
		CountRed[k]=(float)(Red[k])*3/m_nImage;
		CountRedLin[k]=CountRed[k];
		CountGreen[k]=(float)(Green[k])*3/m_nImage;
		CountGreenLin[k]=CountGreen[k];
		CountBlue[k]=(float)(Blue[k])*3/m_nImage;
		CountBlueLin[k]=CountBlue[k];
	}
	
	for( k=1 ; k<256 ; k++ )
	{ 
		CountRed[k]=CountRed[k]+CountRed[k-1];
		CountGreen[k]=CountGreen[k]+CountGreen[k-1];
		CountBlue[k]=CountBlue[k]+CountBlue[k-1];
	}

	/****************************************************/
	/* 此处百度到一个四舍五入浮点型的算法:              
	/* float a=3.456;   保留到小数点后两位              
	/* float b=(int)((a * 100) + 0.5) / 100.0;          
	/* output b=3.46                                    
	/****************************************************/

	int LRed[256],LGreen[256],LBlue[256];   //记录调色板
	for( k=0 ; k<256 ; k++ )
	{
		LRed[k]=(int)(CountRed[k]*(256-1)+0.5);
		LGreen[k]=(int)(CountGreen[k]*(256-1)+0.5);
		LBlue[k]=(int)(CountBlue[k]*(256-1)+0.5);
	}

	//第三步:处理均衡化图像写入 打开临时的图片
	fpo = fopen(BmpName,"rb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);

	FILE *fpw = fopen(BmpNameLin,"wb+");
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);

	//m_nWidth*m_nHeight 读取图片最后一行不为m_nWidth时会报错 改为m_nImage/3
	for( i=0; i<m_nImage/3 ; i++ )
	{	
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=LRed[int(red)];
		green=LGreen[int(green)];
		blue=LBlue[int(blue)];

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();	
}


/********************************************************/
/* 图像空间几何变换：图像平移 ID_JHBH_PY(几何变换-平移) 
/* 使用平移对话框：CImagePYDlg dlg                     
/* 算法：f(x,y)=f(x+x0,y+y0)图像所有点平移，空的补黑'0' 
/* 注意该图像平移方法只是从左上角(0,0)处开始平移        
/* 其他方向原理相同 自己去实现                           
/********************************************************/

void CImageProcessingView::OnJhbhPy() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能空间平移!",MB_OK,0);
		return;
	}
	//定义采样对话框也是用来空间变换平移的坐标
	CImagePYDlg dlg;     
	if( dlg.DoModal()==IDOK ) //显示对话框
	{
		//采样坐标最初为图片的自身像素
		if( dlg.m_xPY>m_nWidth || dlg.m_yPY>m_nHeight ) {
			AfxMessageBox("图片平移不能为超过原图长宽!",MB_OK,0);
			return;
		}
		AfxMessageBox("图片空间变换-平移!",MB_OK,0);

		//打开临时的图片 读写文件
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);

		int num;            //记录每行多余的图像素数个数
		int sfSize;         //补齐后的图像大小
		//重点:图像的每行像素都必须是4的倍数：1*1的图像为 r g b 00H 
		if(m_nWidth*3%4!=0)
		{
			num=(4-m_nWidth*3%4);
			sfSize=(m_nWidth*3+num)*m_nHeight; //每行多number个
		}
		else
		{
			num=0;
			sfSize=m_nWidth*m_nHeight*3;
		}
		//注意:假如最后一行像素不足,我默认处理为完整的一行,不足补00H
		//总之处理后的图像总是m*n且为4倍数,每行都完整存在

		/*更改文件头信息 定义临时文件头结构变量*/
		BITMAPFILEHEADER bfhsf;
		BITMAPINFOHEADER bihsf;       
		bfhsf=bfh;
		bihsf=bih;
		bfhsf.bfSize=sfSize+54;		
		fwrite(&bfhsf,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bihsf,sizeof(BITMAPINFOHEADER),1,fpw);
		fread(m_pImage,m_nImage,1,fpo);

		CString str;
		str.Format("补齐=%d",num);
		AfxMessageBox(str);

		/*临时变量存储的像素与sfSize相同 new和delete有效的进行动态内存的分配和释放*/
		unsigned char *ImageSize;      
	    ImageSize=new unsigned char[sfSize];  

		int Place;                    //建立临时坐标 记录起始坐标(0,0)平移过来的位置  
        int m_pImagePlace;            //原始图像平移为(0,0) 图像把它平移到Place位置  
        unsigned char black=0;        //填充黑色='0'  
		unsigned char other=0;        //补码00H='\0'

		Place=dlg.m_yPY*(m_nWidth*3+num); //前m_yPY行都要填充为黑色          
		m_pImagePlace=0;                  //图像处事位置为(0,0),把该点像素平移过去 
		int countWidth=0;                 //记录每行的像素个数,满行时变回0
		int number=0;                     //数字记录使用的像素行数,平移时使用

		for(int i=0 ; i<sfSize ; i++ )  
        {  
            /*第一部分：到平移后像素位置前面的所有像素点赋值为黑色*/  
            if(i<Place) 
			{  
                ImageSize[i]=black;     //赋值为黑色  
                continue;  
            }  
              
            /*第二部分：平移区域的左边部分赋值为黑色*/  
            else if(i>=Place && countWidth<dlg.m_xPY*3)  //RGB乘3
			{   
                ImageSize[i]=black;     //赋值为黑色  
                countWidth++;  
                continue;  
            }  
          
            /*第三部分：图像像素平移区域*/  
            else if(i>=Place && countWidth>=dlg.m_xPY*3)  
            {  
                ImageSize[i]=m_pImage[m_pImagePlace];       
                m_pImagePlace++;  
                countWidth++;  
                if(countWidth==m_nWidth*3)  
                {  
					if(num==0)
					{
						countWidth=0;
						number++;  
						m_pImagePlace=number*m_nWidth*3; 
					}
					else //num为补0
					{
						for(int j=0;j<num;j++)
						{
							i++;
							ImageSize[i]=other;
						}
						countWidth=0;
						number++;  
						m_pImagePlace=number*(m_nWidth*3+num); 
					}
                }  
            }  
        }  
          
        fwrite(ImageSize,sfSize,1,fpw);    
        fclose(fpo);  
        fclose(fpw);  
        numPicture = 2;  
        level=200;        //200表示几何变换  
        Invalidate();  
    }     
}

/* 几何变换 图像翻转：自己对这个功能比较感兴趣,做个图像反转 */
void CImageProcessingView::OnJhbhFz() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能空间反转!",MB_OK,0);
		return;
	}
	AfxMessageBox("图片空间变换-反转图像!",MB_OK,0);

	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);
	
	/*new和delete有效的进行动态内存的分配和释放*/
	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];    
	int countWidth=0;        //记录每行的像素个数,满行时变回0
	int Place;               //记录图像每行的位置,便于图像反转
	int number=0;            //数字记录使用的像素行数
	Place=m_nWidth*3-1;

	//翻转矩阵: y=y0 x=width-x0-1
	for(int i=0 ; i<m_nImage ; i++ )
	{
		if(countWidth==m_nWidth*3)
		{
			countWidth=0;
		}
		ImageSize[i]=m_pImage[Place]; //(0,0)赋值(0,width*3-1)像素
		Place--;
		countWidth++;
		if(countWidth==m_nWidth*3)
		{
			number++;
			Place=number*m_nWidth*3-1;
		}
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=200;                      
	Invalidate();
}

/* 几何变换 图像倒转 */
void CImageProcessingView::OnJhbhDz() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能空间反转!",MB_OK,0);
		return;
	}
	AfxMessageBox("图片空间变换-反转图像!",MB_OK,0);

	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);
	
	/*new和delete有效的进行动态内存的分配和释放*/
	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];    
	int countWidth=0;                   //记录每行像素个数,满行时变回0
	int Place;                          //每列位置
	int number=0;                       //像素行数
	Place=(m_nWidth*3)*(m_nHeight-1-1); //0行存储

	//翻转矩阵: x=x0 y=height-y0-1 
	for(int i=0 ; i<m_nImage ; i++ )
	{
		ImageSize[i]=m_pImage[Place]; //(0,0)赋值(0,0)像素
		Place++;
		countWidth++;
		if(countWidth==m_nWidth*3)
		{
			countWidth=0;
			number++;
			Place=(m_nWidth*3)*(m_nHeight-number-1);
		}
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=200;                      
	Invalidate();
	
}

/**********************************************************/
/* 几何变换：图片旋转                                 
/* 先添加对话框:IDD_JHBH_TXXZ(图像旋转),创建新类CImageXZDlg  
/* 创建输入度数的:m_xzds Member variables 为int 0-360间 
/**********************************************************/

void CImageProcessingView::OnJhbhTxxz() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能空间旋转!",MB_OK,0);
		return;
	}
	
	//定义对话框并调用对话框
	CImageXZDlg dlg;    
	if( dlg.DoModal()==IDOK ) //显示对话框
	{
		AfxMessageBox("图片空间变换-旋转图像!",MB_OK,0);
		//读写文件
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
		fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
		fread(m_pImage,m_nImage,1,fpo);
		
		/*new和delete有效的进行动态内存的分配和释放*/
		unsigned char *ImageSize;      
		ImageSize=new unsigned char[m_nImage];    
		int Place;          //记录图像每行的位置,便于图像旋转

		/*定义PA=3.14时使用的方法是arcsin(1.0/2)*6即为π*/
		double PA;
		PA=asin(0.5)*6;
		
		/*把输入的0-360的正整数度数转换为角度,30度=π/6*/
		double degree; 
		degree=PA*dlg.m_xzds/180;   //调用dlg.m_xzds(旋转度数)
		
		//对应的二维矩阵 注意图像矩阵从左下角开始处理 它最终要转换成一维存储
		int X,Y;               //图像变换前通过一维矩阵转换为二维
		int XPlace,YPlace;

		//输出转换为的角度
		CString str;
		str.Format("转换后的角度=%f",degree);
		AfxMessageBox(str);

		//图像旋转处理
		for(int i=0 ; i<m_nImage ; i++ )
		{
			//原图：一维矩阵转换为二维矩阵
			X=(i/3)%m_nWidth;
			Y=(i/3)/m_nWidth;
			//注意错误：X=i/m_nHeight Y=i%m_nWidth; 只输出最后1/3

			//图像旋转为：a(x,y)=x*cos-y*sin b(x,y)=x*sin+y*cos
			XPlace=(int)(X*cos(degree)-Y*sin(degree));
			YPlace=(int)(X*sin(degree)+Y*cos(degree));
			
			//在转换为一维图想输出
			if( (XPlace>=0 && XPlace<=m_nWidth) && (YPlace>=0 && YPlace<=m_nHeight) )
			{
				Place=YPlace*m_nWidth*3+XPlace*3;
				//在图像范围内赋值为该像素
				if(Place+2<m_nImage) 
				{
					ImageSize[i]=m_pImage[Place];
					i++;
					ImageSize[i]=m_pImage[Place+1];
					i++;
					ImageSize[i]=m_pImage[Place+2];
				}
				//否则赋值为黑色
				else 
				{
					ImageSize[i]=0; 
					i++;
					ImageSize[i]=0;
					i++;
					ImageSize[i]=0;
				}
			}
			//否则赋值为黑色
			else
			{
				ImageSize[i]=0;
				i++;
				ImageSize[i]=0;
				i++;
				ImageSize[i]=0;
			}
		}
	
		fwrite(ImageSize,m_nImage,1,fpw);  
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level=200;        //几何变换              
		Invalidate();
	}
}


/*******************************************************************/
/* ID_JHBH_SF: 几何运算-缩放-最近邻插值算法               
/* 算法思想:输出图像的灰度等于离它所映射位置最近的输入图像的灰度值 
/* 先计算出放大缩小后的长宽，根据它计算找原图中的点灰度，四舍五入  
/*******************************************************************/

void CImageProcessingView::OnJhbhSf() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能几何缩放图像!",MB_OK,0);
		return;
	}

	CImageSFDlg dlg;           //定义缩放对话框
	if( dlg.DoModal()==IDOK )
	{
		//采样坐标最初为图片的自身像素  m_sfbs(缩放倍数)
		if( dlg.m_sfbs==0 ) {
			AfxMessageBox("输入图片缩放倍数不能为0!",MB_OK,0);
			return;
		}
		
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
		
		/*先求缩放后的长宽*/
		int sfWidth,sfHeight;                            //缩放后的长宽
		int sfSize;                                      //缩放后的图像大小
		sfWidth=(int)(m_nWidth*(dlg.m_sfbs*1.0)/100);    //24位图像RGB必须是3的倍数 循环中读取时为R G B
		sfHeight=(int)(m_nHeight*(dlg.m_sfbs*1.0)/100);
		int number;                                      //记录每行多余的图像素数个数

		//重点:图像的每行像素都必须是4的倍数：1*1的图像为 r g b 00H 
		if(sfWidth*3%4!=0) {
			number=(4-sfWidth*3%4);
			sfSize=(sfWidth*3+(4-sfWidth*3%4))*sfHeight;
		}
		else {
			number=0;
			sfSize=sfWidth*sfHeight*3;
		}
		//注意:假如最后一行像素不足,我默认处理为完整的一行,不足补00H
		//总之处理后的图像总是m*n且为4倍数,每行都完整存在
	
		/*更改文件头信息 定义临时文件头结构变量*/
		BITMAPFILEHEADER bfhsf;
		BITMAPINFOHEADER bihsf;                //缩放(sf)
		bfhsf=bfh;
		bihsf=bih;

		bfhsf.bfSize=sfSize+54;		
		bihsf.biWidth=sfWidth;
		bihsf.biHeight=sfHeight;

		//显示部分m_nDrawWidth<650显示原图,否则显示
		flagSF=1;                         //图像缩放为1标识变量
		m_nDrawWidthSF=sfWidth;
		m_nDrawHeightSF=sfHeight;

		fwrite(&bfhsf,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bihsf,sizeof(BITMAPINFOHEADER),1,fpw);

		fread(m_pImage,m_nImage,1,fpo);	
		
		unsigned char red,green,blue;
		unsigned char other=0;                       //补码00H='\0'
		int placeX;                                  //记录在原图中的第几行的位置
		int placeY;									 //记录在原图中的位置(x,y)
		int placeBH;                                 //记录变换后在变换图中的位置

		/*new和delete有效的进行动态内存的分配和释放*/
		unsigned char *ImageSize;      
		ImageSize=new unsigned char[sfSize]; 

		/*读取文件像素信息 缩放注意:1.找最近灰度 2.四舍五入法(算法+0.5)*/
		for(int i=0; i<sfHeight ; i++ )                  //行
		{
			placeX=(int)(i/(dlg.m_sfbs*1.0/100)+0.5)*bih.biWidth*3;
			for(int j=0; j<sfWidth ; j++ )               //列
			{
				red=green=blue=0;
				//放大倍数为(dlg.m_sfbs*1.0/100)
				placeY=placeX+(int)(j/(dlg.m_sfbs*1.0/100)+0.5)*3;    
				//重点是:number*i补充00H,如果是numer图像会被切成2块
				placeBH=(i*sfWidth*3+number*i)+j*3;                  
				if(placeY+2<m_nImage)
				{
					ImageSize[placeBH]=m_pImage[placeY];
					ImageSize[placeBH+1]=m_pImage[placeY+1];
					ImageSize[placeBH+2]=m_pImage[placeY+2];
				}
				else
				{
					ImageSize[placeBH]=0;
					ImageSize[placeBH+1]=0;
					ImageSize[placeBH+2]=0;
				}
			}
		}
		
		fwrite(ImageSize,sfSize,1,fpw);
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level=200;
		Invalidate();
	}
}



/**************************************************
  第九章--图像增强    
  图像平滑 普通平滑 模板
 
float H1[3][3]={{1.0/10,1.0/10,1.0/10}, //模板一:系数1/10
			   {1.0/10,2.0/10,1.0/10},
			   {1.0/10,1.0/10,1.0/10}};
		
float H2[3][3]={{1.0/16,2.0/16,1.0/16}, //模板二:系数1/16
			   {2.0/16,4.0/16,2.0/16},
			   {1.0/16,2.0/16,1.0/16}};

float H3[3][3]={{1.0/8,1.0/8,1.0/8},    //模板三:系数1/8,此种情况为把点转为空心矩形
			   {1.0/8,0.0/8,1.0/8},
			   {1.0/8,1.0/8,1.0/8}};

float H4[3][3]={{0.0,1.0/8,0.0},        //模板四:系数乘数据后的矩阵
			   {1.0/8,1.0/2,1.0/8},
			   {0.0,1.0/8,0.0}};

/**************************************************/


void CImageProcessingView::OnTxzqPtph1() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:普通平滑 模板一",MB_OK,0);

	/******************************************************************/
	/* 图想平滑的算法：                                               
	/*   1.定义常用的四个模板,它们的维数均为3,矩阵的个数均为9个数据   
	/*   2.它的思想是把一个点分散到这周围的9个点上,这样使图像更模糊   
	/*   3.通过卷积计算围绕该点的矩阵像素和,计算其平均值(除9)赋值给点 
	/*   4.模块不同,处理后的图像也各不相同                           
	/******************************************************************/

	/*第一步：先定义数据模板*/
	int HWS=3;                                //模板维数:此四个模板均为3维的
	float H1[3][3]={{1.0/10,1.0/10,1.0/10},   //模板一:系数1/10
					{1.0/10,2.0/10,1.0/10},
					{1.0/10,1.0/10,1.0/10}};
	
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new和delete有效的进行动态内存的分配和释放
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[m_nImage];    
	float red,green,blue;
	int X,Y;               //一维坐标转换为二维坐标
	int TR,TG,TB;          //记录红绿蓝坐标位置

	//图像增强:平滑 它要获取源图像周围9个点的矩阵乘以模板9个点的矩阵,故一维图像转二维
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		//原图：一维矩阵转换为二维矩阵
		X=(i/3)%m_nWidth;    //图像在X列
		Y=(i/3)/m_nWidth;    //图像在Y行

		//赋值为黑色,相当于清零
		red=green=blue=0;

		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //防止越界
				{			
					//模板一 进行模板平均,把该点像素分散到四周
					TR=j*m_nWidth*3+k*3;	
					red+=H1[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H1[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H1[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		ImageSize[i]=(unsigned char)(red);
		ImageSize[i+1]=(unsigned char)(green);
		ImageSize[i+2]=(unsigned char)(blue);
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;
	Invalidate();
}

void CImageProcessingView::OnTxzqPtph2() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:普通平滑 模板二",MB_OK,0);

	/*第一步：先定义数据模板*/
	int HWS=3;
	float H2[3][3]={{1.0/8,1.0/8,1.0/8},    //模板三:系数1/8 此种情况为把点转为空心矩形
					{1.0/8,0.0/8,1.0/8},
					{1.0/8,1.0/8,1.0/8}};
	
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	
	//重点:图像的每行像素都必须是4的倍数：1*1的图像为 r g b 00H   
	int num;            //记录每行多余的图像素数个数  
	int sfSize;         //补齐后的图像大小  
    if(m_nWidth*3%4!=0) {  
        num=(4-m_nWidth*3%4);  
        sfSize=(m_nWidth*3+num)*m_nHeight; //每行多number个  
    }  
    else {  
        num=0;  
        sfSize=m_nWidth*m_nHeight*3;  
    }  
  
    /*更改文件头信息 定义临时文件头结构变量*/  
    BITMAPFILEHEADER bfhsf;  
    BITMAPINFOHEADER bihsf;         
    bfhsf=bfh;  
    bihsf=bih;  
    bfhsf.bfSize=sfSize+54;  
    fwrite(&bfhsf,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bihsf,sizeof(BITMAPINFOHEADER),1,fpw);  
    fread(m_pImage,m_nImage,1,fpo);  

	//new和delete有效的进行动态内存的分配和释放
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[sfSize];    
	float red,green,blue;
	int X,Y;               //一维坐标转换为二维坐标
	int TR,TG,TB;          //记录红绿蓝坐标位置  
    int countWidth=0;      //记录每行的像素个数,满行时变回0  
	int place=0;           //建立临时坐标 记录起始坐标(0,0)平移过来的位置 

	//图像增强 平滑
	for(int i=0; i<m_nImage; )
	{
		//原图一维矩阵转换为二维矩阵
		X=(i/3)%m_nWidth;    //图像在X列
		Y=(i/3)/m_nWidth;    //图像在Y行

		//赋值为黑色,相当于清零
		red=green=blue=0;

		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //防止越界
				{			
					//模板二 进行模板平均,把该点像素分散到四周
					TR=j*m_nWidth*3+k*3;	
					red+=H2[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H2[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H2[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		//通过变量place赋值变换后的图像 i始终指向原图3的倍数 为了补0而添加place变量
		ImageSize[place]=(unsigned char)(red);
		i++; place++;
		ImageSize[place]=(unsigned char)(green);
		i++; place++;
		ImageSize[place]=(unsigned char)(blue);
		i++; place++;
		countWidth=countWidth+3;
		
		if(countWidth==m_nWidth*3)    
        {    
			if(num==0)  
            {  
                countWidth=0;    
                place=Y*m_nWidth*3;
            }  
            else //num为补0  
            {  
                for(int n=0;n<num;n++)  
                {    
                    ImageSize[place]=0;  
					place++;  
                }  
                countWidth=0;   
                place=Y*(m_nWidth*3+num); //重点 添加Num  
            }  
		} 
	}
		
	fwrite(ImageSize,sfSize,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture=2;
	level=400;
	Invalidate();
}

//高斯平滑
void CImageProcessingView::OnTxzqGsph() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:高斯平滑",MB_OK,0);

	/*第一步：先定义数据模板*/
	int HWS=3;                                //模板维数为3维
	float H[3][3]={{1.0/16,2.0/16,1.0/16},    //高斯模板 系数1/16
				   {2.0/16,4.0/16,2.0/16},
				   {1.0/16,2.0/16,1.0/16}};
	
	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new和delete有效的进行动态内存的分配和释放
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[m_nImage];    
	float red,green,blue;
	int X,Y;               //一维坐标转换为二维坐标
	int TR,TG,TB;          //记录红绿蓝坐标位置

	//图像增强:平滑 
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		//原图：一维矩阵转换为二维矩阵
		X=(i/3)%m_nWidth;    //图像在X列
		Y=(i/3)/m_nWidth;    //图像在Y行

		//赋值为黑色,相当于清零
		red=green=blue=0;

		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //防止越界
				{			
					//模板二 进行模板平均,把该点像素分散到四周
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		ImageSize[i]=(unsigned char)(red);
		ImageSize[i+1]=(unsigned char)(green);
		ImageSize[i+2]=(unsigned char)(blue);
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;
	Invalidate();
}

//中值滤波
void CImageProcessingView::OnTxzqZzlb() 
{
	if(numPicture==0) {
		AfxMessageBox("载入图片后才能图像增强(平滑)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(平滑)!选取的模板为:中值滤波",MB_OK,0);

	//打开临时的图片
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new和delete有效的进行动态内存的分配和释放
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[m_nImage];    
	int X,Y;               //一维坐标转换为二维坐标
	int TR,TG,TB;          //记录红绿蓝坐标位置

	//选取它为中心的周围9个点像素（注意一个点为RGB）
	int H[9]={0,0,0,0,0,0,0,0,0};    
	int HWS=3;             //维数为三维

	//图像增强:平滑 它要获取源图像周围9个点的矩阵乘以模板9个点的矩阵,故一维图像转二维
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		//原图：一维矩阵转换为二维矩阵
		X=(i/3)%m_nWidth;    //图像在X列
		Y=(i/3)/m_nWidth;    //图像在Y行
		
		//第一行 第一列 最后一行 最后一列 直接复制
		if(X==0 || Y==0 || X==m_nWidth*3 || Y==m_nHeight) 
		{
			if(i+2>m_nImage) break;
			ImageSize[i] = m_pImage[i];
			ImageSize[i+1] = m_pImage[i+1];
			ImageSize[i+2] = m_pImage[i+2];
			continue;
		}

		//对图像进行像素求和并取平均值 HWS维数
		int num=0;
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //防止越界
				{			
					//获取当前位置Red像素 k一次增加RGB三个像素 R=G=B
					TR = j*m_nWidth*3+k*3;	
					H[num] = m_pImage[TR];
					num++;
				}
			}
		}
		//排序获取中间值
		int temp=0;
		for(int x=0;x<9;x++)
		{
			for(int y=x;y<9;y++)
			{
				if(H[x]>=H[y])
				{
					temp=H[x];
					H[x]=H[y];
					H[y]=temp;
				}
			}
		}
		//CString str;
		//str.Format("矩阵:%d %d %d, %d %d %d, %d %d %d",H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7],H[8]);
		//AfxMessageBox(str);

		//对新图像赋值 灰度图像RGB相同
		ImageSize[i]=H[4];
		ImageSize[i+1]=H[4];
		ImageSize[i+2]=H[4];
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;
	Invalidate();
}

/*****************************************/
/* 图像锐化:我在menu中创建5个子的menu    */
/* 防止出现平滑错误,一次只调用一个下拉单 */
/* ID_RH_Laplacian Laplacian拉普拉斯算子 */
/* ID_RH_Sobel Sobel算子                 */
/* ID_RH_Prewitt Prewitt算子             */
/* ID_RH_Isotropic Isotropic算子         */
/* ID_RH_GTMB 高通模板H2                 */
/*****************************************/

void CImageProcessingView::OnRHLaplacian() 
{
	if(numPicture==0) 
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用拉普拉斯(Laplacian)算子!");

	//模板维数:此四个模板均为3维的
	int HWS=3;  
	
	int H[3][3]={{0,-1,0},    //模板为拉普拉斯算子(中心为4的Laplacian)
				{-1,4,-1},
				{0,-1,0}};

	//读写文件
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new和delete有效的进行动态内存的分配和释放
	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int red,green,blue;
	int X,Y;       //一维坐标转换为二维坐标
	int TR,TG,TB;  //记录红绿蓝坐标位置
	
	//图像增强 锐化
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X列
		Y=(i/3)/m_nWidth;    //Y行
		red=green=blue=0;
		
		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		if(red>=0 && red<256) ImageSize[i]=red;
		else if(red<0) ImageSize[i]=0;      //ImageSize[i]=-red;
		else ImageSize[i]=0;
		
		if(green>=0 && green<256) ImageSize[i+1]=green;
		else if(green<0) ImageSize[i+1]=0;  //ImageSize[i+1]=-green;
		else ImageSize[i+1]=0;
		
		if(blue>=0 && blue<256) ImageSize[i+2]=blue;
		else if(blue<0) ImageSize[i+2]=0;   //ImageSize[i+2]=-blue;
		else ImageSize[i+2]=0;
	}
	
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}

//高通模板
void CImageProcessingView::OnRhGtmb() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用高通模板!");

	int HWS=3;                                
	int H[3][3]={{-1,-1,-1},    
				{-1,8,-1},
				{-1,-1,-1}};

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int red,green,blue;
	int X,Y;       
	int TR,TG,TB; 
	
	//图像增强 锐化
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X列
		Y=(i/3)/m_nWidth;    //Y行
		red=green=blue=0;
		
		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		
		//对新图像赋值
		if(red>=0 && red<256) ImageSize[i]=red;
		else if(red<0) ImageSize[i]=0;      //ImageSize[i]=-red;
		else ImageSize[i]=0;
		
		if(green>=0 && green<256) ImageSize[i+1]=green;
		else if(green<0) ImageSize[i+1]=0;  //ImageSize[i+1]=-green;
		else ImageSize[i+1]=0;
		
		if(blue>=0 && blue<256) ImageSize[i+2]=blue;
		else if(blue<0) ImageSize[i+2]=0;   //ImageSize[i+2]=-blue;
		else ImageSize[i+2]=0;
	}
	
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();	
}

//Sobel算子采用PPT上的d(x) d(y)模板
void CImageProcessingView::OnRHSobel() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用Sobel算子!");

	int HWS=3;                                
	//模板为Sobel算子
	int HX[3][3]={{1,0,-1},{2,0,-2},{1,0,-1}};
	int HY[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);	
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int redX,greenX,blueX;
	int redY,greenY,blueY;
	int X,Y;       
	int TR,TG,TB;  
	
	//图像增强 锐化
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X列
		Y=(i/3)/m_nWidth;    //Y行
		redX=greenX=blueX=0;
		redY=greenY=blueY=0;
		
		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					redX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					redY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					greenX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					greenY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blueX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
					blueY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		//s=(d(x)*d(x)+d(y)*d(y))开根号
		int R,G,B;
		R=(int)(sqrt(redX*redX*1.0+redY*redY*1.0));
		G=(int)(sqrt(greenX*greenX*1.0+greenY*greenY*1.0));
		B=(int)(sqrt(blueX*blueX*1.0+blueY*blueY*1.0));

		if(redX<0 && redY<0) ImageSize[i]=0;
		else if(R>255) ImageSize[i]=255;
		else ImageSize[i]=R;
		
		if(greenX<0 && greenY<0) ImageSize[i+1]=0;
		else if(G>255) ImageSize[i+1]=255;
		else ImageSize[i+1]=G;

		if(blueX<0 && blueY<0) ImageSize[i+2]=0;
		else if(B>255) ImageSize[i+2]=255;
		else ImageSize[i+2]=B;
	}
	
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}

//Isotropic算子采用PPT上的d(x)模板 d(y)
void CImageProcessingView::OnRHIsotropic() 
{
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!",MB_OK,0);
		return;
	}

	AfxMessageBox("图像增强(锐化):采用Isotropic算子!");

	int HWS=3;                               
	//模板为Isotropic算子
	float HX[3][3]={{1,0,-1},
					{sqrt(2.0),0,-sqrt(2.0)}, 
					{1,0,-1} };
	float HY[3][3]={{-1,-sqrt(2.0),-1},
					{0,0,0}, 
					{1,sqrt(2.0),1} };

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	float redX,greenX,blueX;
	float redY,greenY,blueY;
	int X,Y;      
	int TR,TG,TB;  
	
	//图像增强
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X列
		Y=(i/3)/m_nWidth;    //Y行
		redX=greenX=blueX=0;
		redY=greenY=blueY=0;
		
		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					redX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					redY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					greenX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					greenY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blueX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
					blueY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值 s=(d(x)*d(x)+d(y)*d(y))开根号
		int R,G,B;
		R=(int)(sqrt(redX*redX*1.0+redY*redY*1.0));
		G=(int)(sqrt(greenX*greenX*1.0+greenY*greenY*1.0));
		B=(int)(sqrt(blueX*blueX*1.0+blueY*blueY*1.0));

		if(redX<0 && redY<0) ImageSize[i]=0;
		else if(R>255) ImageSize[i]=255;
		else ImageSize[i]=R;
		
		if(greenX<0 && greenY<0) ImageSize[i+1]=0;
		else if(G>255) ImageSize[i+1]=255;
		else ImageSize[i+1]=G;

		if(blueX<0 && blueY<0) ImageSize[i+2]=0;
		else if(B>255) ImageSize[i+2]=255;
		else ImageSize[i+2]=B;
	}
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}

//Prewitt算子采用PPT上的d(x)模板,不是d(y)
void CImageProcessingView::OnRHPrewitt() 
{
	
	if(numPicture==0)
	{
		AfxMessageBox("载入图片后才能图像增强(锐化)!",MB_OK,0);
		return;
	}
	AfxMessageBox("图像增强(锐化):采用Prewitt算子!");

	int HWS=3;                               
	int H[3][3]={{1,0,-1},    //模板为Prewitt算子
				{1,0,-1},
				{1,0,-1}};

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int red,green,blue;
	int X,Y;      
	int TR,TG,TB; 
	
	//图像增强:平滑
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X列
		Y=(i/3)/m_nWidth;    //Y行
		red=green=blue=0;
		
		//对图像进行像素求和并取平均值 HWS维数
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //第j行
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //第k列
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		//对新图像赋值
		if(red>=0 && red<256) ImageSize[i]=red;
		else if(red<0) ImageSize[i]=0;      //ImageSize[i]=-red;
		else ImageSize[i]=0;
		
		if(green>=0 && green<256) ImageSize[i+1]=green;
		else if(green<0) ImageSize[i+1]=0;  //ImageSize[i+1]=-green;
		else ImageSize[i+1]=0;
		
		if(blue>=0 && blue<256) ImageSize[i+2]=blue;
		else if(blue<0) ImageSize[i+2]=0;   //ImageSize[i+2]=-blue;
		else ImageSize[i+2]=0;	
	}
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}
