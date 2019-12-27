// PictureStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "testskin.h"
#include "PictureStatic.h"

#include "utils.hpp"
// CPictureStatus

IMPLEMENT_DYNAMIC(CPictureStatic, CStatic)

CPictureStatic::CPictureStatic( Gdiplus::Image* pImgBk )
	:m_pImgBk(pImgBk)
{
	ASSERT(NULL != m_pImgBk );
}

CPictureStatic::~CPictureStatic()
{
}


BEGIN_MESSAGE_MAP(CPictureStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CPictureStatus 消息处理程序




void CPictureStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	//CDC dcMem;
	//dcMem.CreateCompatibleDC( &dc );
	//CBitmap bmpMem;
	CRect rectClient;
	GetClientRect( rectClient );
#if 0
	//bmpMem.CreateCompatibleBitmap(
	//	&dc, rectClient.Width(), rectClient.Height() );
	//CBitmap* pOldBmp = dcMem.SelectObject( &bmpMem );
	//dcMem.FillRect( rectClient, 
	//	CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)) );
	Gdiplus::Graphics graph( dc.GetSafeHdc() );
	graph.SetPageUnit(Gdiplus::UnitPixel);
	graph.DrawImage( m_pImgBk, 
		rectClient.left, 
		rectClient.top,
		rectClient.Width(),
		rectClient.Height() );
	graph.ReleaseHDC( dc.GetSafeHdc() );
#else
	DrawImage( dc.GetSafeHdc(),
		_T("E:\\printer\\PrintClient\\Debug\\ui\\image\\login\\prefix_password.png"),
		rectClient );
#endif
	//dc.BitBlt( 0,0,rectClient.Width(),rectClient.Height(),&dcMem,0,0,SRCCOPY );
	//dcMem.SelectObject( pOldBmp );
}


BOOL CPictureStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//return FALSE;
	return CStatic::OnEraseBkgnd(pDC);
}
