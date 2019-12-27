// CPictureButton.cpp : 实现文件
//
#include "stdafx.h"
#include "PictureButton.h"

#include "utils.hpp"
#include "skin/GlobalSkinUtil.h"
#include "ImageManager.h"

// CPictureButton

IMPLEMENT_DYNAMIC(CPictureButton, CButton)

CPictureButton::CPictureButton()
{
	m_bOver = false;	//鼠标位于按钮之上时该值为true，反之为flase
	m_bTracking = false;	//在鼠标按下没有释放时该值为true
	m_bSelected = false;	//按钮被按下是该值为true
	m_bFocus = false;	//按钮为当前焦点所在时该值为true
	m_bBoldFont = false;
	m_nFontOffset = INT_MAX;
	m_imgNormal = NULL;//加载初始状态的图片
	m_imgPressed = NULL;//按下状态的图片
	m_imgDisabled = NULL;//按钮被禁用
	m_imgHover = NULL;  //鼠标经过
	m_bChecked = false;
	m_nTextLeftSpacing = 0;
	m_pPartner = NULL;
}

CPictureButton::~CPictureButton()
{
	for(std::size_t i = 0; i < m_vOwnerDeleted.size(); ++i )
	{
		delete m_vOwnerDeleted.at(i);
	}
	m_vOwnerDeleted.clear();
}


BEGIN_MESSAGE_MAP(CPictureButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CPictureButton 消息处理程序




void CPictureButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 100;//光标停在按钮上，改变状态的时间，以1毫秒为单位
		m_bTracking = _TrackMouseEvent(&tme);
	}	CButton::OnMouseMove(nFlags, point);
	
}


void CPictureButton::OnMouseLeave()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_bOver = FALSE; //   鼠标没位于按钮之上     
	m_bTracking = FALSE;           //鼠标离开按钮       
	InvalidateRect(NULL, FALSE);  //让按钮重画

	if( NULL != m_pPartner )
	{
		m_pPartner ->SetHover( m_bOver );
		m_pPartner ->InvalidateRect( NULL,FALSE );
	}
	CButton::OnMouseLeave();
}


void CPictureButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	m_bOver = TRUE;  //鼠标盘旋在按钮上空
	if( NULL != m_pPartner )
	{
		m_pPartner ->SetHover( m_bOver );
		m_pPartner ->InvalidateRect( NULL );
	}
	InvalidateRect(NULL); //重画！
	
	CButton::OnMouseHover(nFlags, point);
}

bool CPictureButton::SetHover( bool bHover )
{
	if( m_bOver != bHover )
	{
		m_bOver = bHover;
		if( NULL != m_pPartner )
		{
			m_pPartner ->SetHover( bHover );
		}
		return true;
	}
	return false;
}

void CPictureButton::SetChecked( bool bChecked )
{ 
	if( bChecked != m_bChecked )
	{
		m_bChecked = bChecked; 
		if( NULL != m_pPartner )
		{
			m_pPartner ->SetChecked( bChecked );
		}
	}

}

void CPictureButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rect = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;
	//pDC->FillRect( rect, CBrush::FromHandle( (HBRUSH)GetStockObject(NULL_BRUSH) ) );

	bool bIsDisabled = (FALSE == IsWindowEnabled( ) );
	//根据按钮的状态贴图

	//(以下贴按钮状态图，分以下几种情况来贴，，，和我们平常贴背景图片一样的做法)
	//鼠标停留按钮的状态
	//pDC ->FillSolidRect( rect, RGB(255,0,0) );
	if( bIsDisabled && NULL != m_imgDisabled )
	{
		DrawImage( pDC ->GetSafeHdc(), m_imgDisabled, rect  );

	}
	else if ( ( IsChecked() || m_bSelected || state & ODS_SELECTED) && NULL != m_imgPressed )
	{ //按钮被按下(选中)

		DrawImage( pDC ->GetSafeHdc(), m_imgPressed, rect  );

	}
	else if ( m_bOver && NULL != m_imgHover )
	{
		DrawImage( pDC ->GetSafeHdc(), m_imgHover, rect  );

	}
	else if( NULL != m_imgNormal )
	{
		//初始状态

		DrawImage( pDC ->GetSafeHdc(), m_imgNormal, rect  );

	}
	CString strTitle;
	GetWindowText( strTitle );
	CGdiObject* pOldFont = NULL;
	CFont newFont;
	LOGFONT logFont = {0};

	if( m_bBoldFont || INT_MAX != m_nFontOffset )
	{
		CFont* pFont = pDC ->GetCurrentFont( );
		pFont ->GetLogFont( &logFont );
		if( m_bBoldFont )
		{
			logFont.lfWeight = FW_BOLD;
		}
		if( INT_MAX != m_nFontOffset )
		{
			logFont.lfHeight -= m_nFontOffset;
		}
		newFont.CreateFontIndirect( &logFont );
		pOldFont = pDC ->SelectObject(&newFont);
	}
	rect.left += m_nTextLeftSpacing;
	pDC ->SetBkMode( TRANSPARENT );
	if( bIsDisabled )
	{
		COLORREF crfText = pDC ->GetTextColor( );
		pDC ->SetTextColor( RGB(  
			GetRValue(crfText) +120,
			GetGValue(crfText) +120,
			GetBValue(crfText) +120) );

		pDC ->DrawText( strTitle, &rect, DT_CENTER |DT_SINGLELINE | DT_VCENTER );
		pDC ->SetTextColor( crfText );
	}
	else
	{
		pDC ->DrawText( strTitle, &rect, DT_CENTER |DT_SINGLELINE | DT_VCENTER );
	}

	if( NULL != pOldFont )
	{
		pDC ->SelectObject( pOldFont );
	}
	// TODO:  添加您的代码以绘制指定项
}
void CPictureButton::SetBitmap(
	Image*  bmpNormal,
	Image*  bmpHover, 
	Image*  bmpPressed,
	Image*  bmpFocused)
{
	Set3StateBitmap( bmpNormal, bmpHover, bmpPressed );
	SetDisabledBitmap( bmpFocused );
}


void CPictureButton::Set3StateBitmap( 
	Image*  bmpNormal,
	Image*  bmpHover, 
	Image*  bmpPressed )
{
	Set2StateBitmap( bmpNormal,bmpHover );
	SetPressedBitmap( bmpPressed );
}

void CPictureButton::Set2StateBitmap( 
	Image*  bmpNormal, 
	Image*  bmpHover )
{
	SetNormalBitmap( bmpNormal );
	SetHoverBitmap( bmpHover );
}

void CPictureButton::SetNormalBitmap(Image*  bmp)
{
	m_imgNormal = bmp;
}
void CPictureButton::SetHoverBitmap(Image*  bmp)
{
	m_imgHover = bmp;
}

void CPictureButton::SetPressedBitmap(Image*  bmp)
{
	m_imgPressed = bmp;
}

void CPictureButton::SetDisabledBitmap( Image*  bmp )
{
	m_imgDisabled = bmp;
}

void CPictureButton::SetFontBold( bool bBold )
{
	m_bBoldFont = bBold;
}

void CPictureButton::SetFontSizeOffset( int nSize )
{
	m_nFontOffset = nSize;
}

void CPictureButton::Set2StateAndDisabledBitmap( LPCTSTR lpszUiFilePath  )
{
	Gdiplus::Image* pBitmap = ImagePool( ).GetImage( lpszUiFilePath );
	if( NULL == pBitmap )
	{
		return;
	}
	const CSize szBmp(pBitmap->GetWidth(),pBitmap ->GetHeight());
	int nAverageWidth = szBmp.cx/3;
	Gdiplus::Image* pImage1;
	Gdiplus::Image* pImage2;
	Set2StateBitmap(
		pImage1 = CreateSubBitmap( pBitmap, 0,0,
		nAverageWidth, szBmp.cy ),
		pImage2 = CreateSubBitmap( pBitmap,
		nAverageWidth,0,
		nAverageWidth, szBmp.cy )
		);
	m_vOwnerDeleted.push_back(pImage1);
	m_vOwnerDeleted.push_back(pImage2);
	SetDisabledBitmap(
		pImage1 = CreateSubBitmap( pBitmap,
		nAverageWidth*2,0,
		nAverageWidth, szBmp.cy ) );
	m_vOwnerDeleted.push_back(pImage1);
}

void CPictureButton::Set2StateBitmap( LPCTSTR lpszUiFilePath )
{
	Gdiplus::Image* pBitmap = ImagePool( ).GetImage( lpszUiFilePath );
	if( !pBitmap )
	{
		return;
	}
	const CSize szBmp( pBitmap->GetWidth(), pBitmap->GetHeight());
	int nAverageWidth = szBmp.cx/2;
	Gdiplus::Image* pImage1;
	Gdiplus::Image* pImage2;
	Set2StateBitmap(
		pImage1 = CreateSubBitmap( pBitmap, 0,0,
		nAverageWidth, szBmp.cy ),
		pImage2 = CreateSubBitmap( pBitmap,
		nAverageWidth,0,
		nAverageWidth, szBmp.cy )
		);	
	m_vOwnerDeleted.push_back(pImage1);
	m_vOwnerDeleted.push_back(pImage2);

}
void CPictureButton::ShareUiWith( CPictureButton& rhs )
{
	m_nFontOffset = rhs.m_nFontOffset;
	m_bBoldFont = rhs.m_bBoldFont;
	m_imgNormal = rhs.m_imgNormal;
	m_imgPressed = rhs.m_imgPressed;
	m_imgDisabled = rhs.m_imgDisabled;
	m_imgHover = rhs.m_imgHover;
}

void CPictureButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if( !m_bSelected )
	{ 
		m_bSelected = true;
		InvalidateRect( NULL );
		if( NULL != m_pPartner )
		{
			m_pPartner ->SetSelected( true );
			m_pPartner ->InvalidateRect( NULL );
		}
	}
	__super::OnLButtonDown(nFlags, point);
}


void CPictureButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if( m_bSelected )
	{ 
		m_bSelected = false;
		InvalidateRect( NULL );
		if( NULL != m_pPartner )
		{
			m_pPartner ->SetSelected( false );
			m_pPartner ->InvalidateRect( NULL );
		}
	}
	__super::OnLButtonUp(nFlags, point);
}
void CPictureButton::SetSelected( bool bSelected )
{
	if( m_bSelected != bSelected )
	{
		m_bSelected = bSelected;
		if( NULL != m_pPartner )
		{
			m_pPartner ->SetSelected( bSelected );
		}
	}
}

