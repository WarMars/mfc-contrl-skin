#include "stdafx.h"
#include "ComboboxCtrlSkin.h"
#include "utils.hpp"
#include "ImageManager.h"
#include "GlobalUiManager.h"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{

CComboBoxCtrlSkin::CComboBoxCtrlSkin( )
{

}

void CComboBoxCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRefPtr pBitmap = ImagePool( ).CreateBitmap(
			TEXT("ui\\skin\\ComboBox.bmp") );
		int nXOffset = 0,nYOffset = 0;
		int nSize = 48;
		m_pBmpBorder = Util::CreateSubBitmap( pBitmap,
			nXOffset,nYOffset+nSize,nSize,nSize );

		m_pBmpThumb[CParamReference::CheckDisabled] = 
			Util::CreateSubBitmap( pBitmap,
			nXOffset,nYOffset,nSize,nSize );
		m_pBmpThumb[CParamReference::CheckNormal] = 
			Util::CreateSubBitmap( pBitmap,
			nXOffset += nSize, nYOffset, nSize, nSize );
		m_pBmpThumb[CParamReference::CheckHover] = 
			Util::CreateSubBitmap( pBitmap,
			nXOffset += nSize, nYOffset, nSize, nSize );
		m_pBmpThumb[CParamReference::CheckPressed] =
			Util::CreateSubBitmap( pBitmap,
			nXOffset += nSize, nYOffset, nSize, nSize );
		m_pBmpThumb[CParamReference::CheckFocused] =
			Util::CreateSubBitmap(  pBitmap,
			nXOffset += nSize, nYOffset, nSize, nSize  );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpBorder = 
		pConfig ->GetBitmap( TEXT("combobox/border") );

	m_pBmpThumb[CParamReference::CheckDisabled] = 
		pConfig ->GetBitmap( TEXT("combobox/down-arrow/disabled") );
	m_pBmpThumb[CParamReference::CheckNormal] = 
		pConfig ->GetBitmap( TEXT("combobox/down-arrow/normal") );
	m_pBmpThumb[CParamReference::CheckHover] = 
		pConfig ->GetBitmap( TEXT("combobox/down-arrow/hover") );
	m_pBmpThumb[CParamReference::CheckPressed] =
		pConfig ->GetBitmap( TEXT("combobox/down-arrow/pressed") );
	m_pBmpThumb[CParamReference::CheckFocused] =
		pConfig ->GetBitmap( TEXT("combobox/down-arrow/focused") );
#endif
}

CComboBoxCtrlSkin::~CComboBoxCtrlSkin( )
{

}
LRESULT CComboBoxCtrlSkin::OnWndProc( 
	UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint();
		return 0;
		break;
	case WM_NCPAINT:
		OnNcPaint( (HRGN)wParam );
		return 0;
		break;
	case WM_MOUSEMOVE:
		OnMouseMove( (UINT)wParam,
			CPoint(LOWORD(lParam), HIWORD(lParam)) );
		return 0;
	case WM_MOUSELEAVE:
		OnMouseLeave( );
		return 0;
	case WM_LBUTTONDOWN:
		OnLButtonDown((UINT)wParam,
			CPoint(LOWORD(lParam), HIWORD(lParam)) );
		return 0;
	case WM_LBUTTONUP:
		OnLButtonUp((UINT)wParam,
			CPoint(LOWORD(lParam), HIWORD(lParam)) );
		return 0;
	case WM_CTLCOLORLISTBOX:
		 return OnCtrlColor( wParam, lParam );
		 break;
	case WM_NCCALCSIZE:
		OnNcCalcSize( 0==wParam?FALSE:TRUE, (NCCALCSIZE_PARAMS*)lParam );
		break;
	case WM_SETFOCUS:
		OnSetFocus( (HWND)wParam );
		break;
	case WM_KILLFOCUS:
		OnKillFocus( (HWND) wParam );
		break;
	case WM_SETTEXT:
		OnSetText(wParam, lParam );
		break;
	default:
		return OnPreviousWndProc( GetCurHwnd( ), nMsg, wParam, lParam );
		break;
	}
	return 0;
}
/** 
 * @brief 获取当前的窗口类名
 */
LPCTSTR CComboBoxCtrlSkin::GetHwndClassName( )
{
	return TEXT("ComboBox");
}

/** 
 * @brief 接管控件皮肤之前
 */
CComboBoxCtrlSkin::CParamReference* CComboBoxCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* pParam = new CParamReference;
	long lStyle	  = GetWindowLong( hWnd, GWL_STYLE );
	long lExStyle = GetWindowLong( hWnd,GWL_EXSTYLE );
	/* 初始化参数设置 */
	pParam ->m_nState = CComboboxCtrlParameter::COMBOX_NORMAL;
	pParam ->m_nHScrollBar = lStyle & WS_HSCROLL;
	pParam ->m_nVScrollBar = lStyle & WS_VSCROLL;
	pParam ->m_bHitThumb = false;
	pParam ->m_bTouchedListBox = false;
	return pParam;
}


void CComboBoxCtrlSkin::OnMouseLeave()
{
	if( IsNull() )
	{
		return;
	}
	/* 加入按下和鼠标滑过状态 */
	GetCurParam( ) ->m_nState &= ~CComboboxCtrlParameter::COMBOX_PRESSED;
	GetCurParam( ) ->m_nState &= ~CComboboxCtrlParameter::COMBOX_HOVER;

	Redraw( );
}
void CComboBoxCtrlSkin::OnSetFocus(HWND hWnd)
{
	OnAutoDefaultWndProc( );
	Redraw( );
}
void CComboBoxCtrlSkin::OnKillFocus(HWND hWnd)
{
	OnAutoDefaultWndProc( );
	Redraw( );
}
void CComboBoxCtrlSkin::OnSetText(WPARAM wp,LPARAM lp)
{
	OnAutoDefaultWndProc( );
	Redraw( );
}

void CComboBoxCtrlSkin::Redraw( bool bDrawBorder )
{
	CWnd *pWnd = CWnd::FromHandle(GetCurHwnd( ));
	if( NULL == pWnd )
	{
		return;
	}
	CDC* pDC = pWnd->GetDC( );
	if( NULL == pDC )
	{
		return;
	}
	/* 绘制组合框 */
	DrawComboBox(pDC);

	/* 绘制边框 */
	if( bDrawBorder )
	{
		CRect r;
		pWnd ->GetClientRect( &r );
		if( m_pBmpBorder.valid())
		{
			CBrush brush;
			brush.CreatePatternBrush( m_pBmpBorder );
			pDC ->FrameRect( r, &brush );
		}
		else
		{
			COLORREF color =::GetSysColor(CTLCOLOR_BTN);
			pDC->Draw3dRect(r,color,color);
		}
	}
	pWnd ->ReleaseDC( pDC );
}
LRESULT CComboBoxCtrlSkin::OnCtrlColor( WPARAM wParam, LPARAM lParam )
{
	if( IsValid( ) )
	{
		/* 重绘 */
		Redraw( );
		/* 是否已经关联了列表框 */
		if( !GetCurParam( ) ->m_bTouchedListBox )
		{
			GetCurParam( ) ->m_bTouchedListBox = 
				CGlobalUiManager::GetPtr()->Add( (HWND)lParam );
		}
	}
	return OnAutoDefaultWndProc( );
}
void CComboBoxCtrlSkin::OnMouseMove( UINT nFlags, const CPoint& point )
{
	if( IsNull() )
	{
		return;
	}
	OnAutoDefaultWndProc( );

	if(( GetCurParam( ) ->m_nState == CComboboxCtrlParameter::COMBOX_NORMAL) && 
		( 0 == ( nFlags & MK_LBUTTON) ) )
	{/* 当前状态为无操作状态，且未按下左键 */
		TRACKMOUSEEVENT tme;
		/* 当前鼠标经过发生变化 */
		GetCurParam( ) ->m_bHitThumb = HitTestThumb(point);
		GetCurParam( ) ->m_nState |= CComboboxCtrlParameter::COMBOX_HOVER;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = GetCurHwnd( );
		/* 追踪后续操作 */
		TrackMouseEvent(&tme);
	}
	else if( 0 != (nFlags & MK_LBUTTON) )
	{
		TRACKMOUSEEVENT tme;
		/* 当前点击发生变化 */
		GetCurParam( ) ->m_bHitThumb  = HitTestThumb(point);
		GetCurParam( ) ->m_nState |= CComboboxCtrlParameter::COMBOX_PRESSED;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = GetCurHwnd( );
		/* 追踪后续操作 */
		TrackMouseEvent(&tme);
	}
	Redraw( );
}
void CComboBoxCtrlSkin::OnLButtonDown( UINT nFlags , const CPoint& point )
{
	OnAutoDefaultWndProc();
	if( IsNull() )
	{
		return;
	}
	/* 左键按下，加入按下状态 */
	GetCurParam( ) ->m_nState |= CComboboxCtrlParameter::COMBOX_PRESSED;
	Redraw();
}
void CComboBoxCtrlSkin::OnLButtonUp( UINT nFlags, const CPoint& point )
{
	OnAutoDefaultWndProc();
	if( IsNull() )
	{
		return;
	}
	/* 左键弹起，去掉按下状态 */
	GetCurParam( ) ->m_nState &= ~CComboboxCtrlParameter::COMBOX_PRESSED;
	Redraw();
}
void CComboBoxCtrlSkin::OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	/* 直接使用默认的 */
	OnAutoDefaultWndProc();
	return;
	if( IsNull() )
	{
		return;
	}
	DWORD style		= GetWindowLong( GetCurHwnd( ), GWL_STYLE );
	GetCurParam( ) -> m_nHScrollBar = style & WS_HSCROLL;
	GetCurParam( ) -> m_nVScrollBar = style & WS_VSCROLL;

	LPRECT lpRect = &(lpncsp->rgrc[0]);
	if(FALSE)
	{
		lpncsp->rgrc[0].left += 1;
		lpncsp->rgrc[0].top += 1;
		lpncsp->rgrc[0].right -= 1;
		lpncsp->rgrc[0].bottom -= 1;

		lpncsp->rgrc[1] = lpncsp->rgrc[0];
	}
}
void CComboBoxCtrlSkin::OnNcPaint(HRGN rgn1)
{
	OnAutoDefaultWndProc();
}
void CComboBoxCtrlSkin::OnPaint()
{
	OnAutoDefaultWndProc( );
	/* 重绘 */
	Redraw( true );
}

bool CComboBoxCtrlSkin::HitTestThumb( const CPoint& point )
{
	/* 坐标点是否位于组合框的下拉箭头上 */
	CRect rtThumb ;	
	COMBOBOXINFO comboInfo;
	comboInfo.cbSize = sizeof(comboInfo);
	GetComboBoxInfo(GetCurHwnd( ),&comboInfo);

	rtThumb = comboInfo.rcButton;

	return TRUE == rtThumb.PtInRect(point);
}
void CComboBoxCtrlSkin::DrawComboBox(CDC *pDC)
{
	if( IsNull() )
	{
		return;
	}
	/* 获取组合框下拉箭头的位置和大小 */
	COMBOBOXINFO ci;
	ci.cbSize = sizeof(ci);
	GetComboBoxInfo( GetCurHwnd( ),&ci );

	CRect rectThumb(ci.rcButton);

	
	/* 根据不同的状态，绘制不同的滑块 */
	if( GetCurParam( ) -> m_nState & CComboboxCtrlParameter::COMBOX_DISABLED)
	{
		if(!DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckDisabled ] ) )
		{
			DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckNormal ] );
		}
	}
	if( GetCurParam( ) -> m_nState & CComboboxCtrlParameter::COMBOX_PRESSED)
	{
		if(!DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckPressed ] ) )
		{
			DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckNormal ] );
		}
	}
	else if( GetCurParam( ) -> m_nState & CComboboxCtrlParameter::COMBOX_HOVER)
	{
		if(!DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckHover ] ) )
		{
			DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckNormal ] );
		}
	}
	else
	{
		DrawBmp(pDC,rectThumb, m_pBmpThumb[ CComboboxCtrlParameter::CheckNormal ] );
	}

}

}