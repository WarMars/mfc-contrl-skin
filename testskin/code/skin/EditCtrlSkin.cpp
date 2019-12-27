#include "stdafx.h"
#include "EditCtrlSkin.h"
#include <Windows.h>
#include "ImageManager.h"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE


namespace GlobalSkin
{

CEditCtrlSkin::CEditCtrlSkin()
{

}

void CEditCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		m_pBorderBmp = ImagePool( ).GetBitmap( 
			TEXT("ui\\skin\\edit.bmp") );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBorderBmp = pConfig ->GetBitmap(TEXT("edit/border/background") );
#endif
}

void CEditCtrlSkin::SetBorderBmp( CBitmapRefPtr pBitmap )
{
	m_pBorderBmp = pBitmap;
}
/** 
	* @brief 窗口过程处理
	*/
LRESULT	CEditCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint();
		return 0;
		break;
	case WM_SIZE:
	case WM_SETFONT:
		{
			LRESULT lResult =
				OnPreviousWndProc( GetCurHwnd( ), nMsg, wParam, lParam );
			UpdateTextCenter( );
			return lResult;
		}
		break;
	case WM_KILLFOCUS:
		{
			HWND hWnd = GetCurHwnd( );
			LRESULT lResult =
				OnPreviousWndProc( hWnd, nMsg, wParam, lParam );
			InvalidateRect( hWnd, NULL, TRUE );
			UpdateWindow( hWnd );
			return lResult;
		}
	default:
		break;
	}
	return OnPreviousWndProc( GetCurHwnd( ), nMsg, wParam, lParam );
}
		

void CEditCtrlSkin::UpdateTextCenter( )
{
	HWND hWnd = GetCurHwnd();
	CRect rc; 
	GetClientRect(hWnd,&rc); 
	Util::CTempWindowDC wdc(hWnd);

	HFONT hWindowFont = (HFONT)SendMessage( hWnd, WM_GETFONT,0,0);
	LOGFONT logFont;
	GetObject( hWindowFont, sizeof(LOGFONT),&logFont);
	HGDIOBJ hOldFont = SelectObject( wdc, hWindowFont );
	SIZE size;
	GetTextExtentPoint32W (wdc, L"f", 1, &size) ;
	SelectObject( wdc, hOldFont );
	int nFontHeight =size.cy; 
	//
	int nMargin = (rc.Height() - nFontHeight)/2; 
	rc.DeflateRect(0, nMargin); 
	SendMessage(hWnd, EM_SETRECT, 0, (LPARAM)&rc );
}

void CEditCtrlSkin::OnPaint( )
{
#if !0
	
	OnAutoDefaultWndProc();
#else
	HWND hWnd = GetCurHwnd();
	Util::CTempPaintDC dcPaint( hWnd );
	CRect Irect;
	GetClientRect( hWnd,&Irect); 
	CString strText;
	HBRUSH hOldBrush = NULL;
	bool bUseCtlColor = false;
	HWND hParent = GetParent(hWnd );
	if( NULL != hParent )
	{
		HBRUSH hBrush = (HBRUSH)SendMessage(
			hParent,WM_CTLCOLOREDIT,
			(WPARAM)(HDC)dcPaint, (LPARAM)hWnd );
		if( NULL != hBrush )
		{
			bUseCtlColor = true;
			hOldBrush =(HBRUSH) 
			SelectObject( dcPaint, hBrush );
		}
	}
	int nLen = ::GetWindowTextLength(hWnd);
	::GetWindowText(hWnd, strText.GetBufferSetLength(nLen), nLen+1);
	strText.ReleaseBuffer();
	SIZE sizeText;
	::GetTextExtentPoint32( dcPaint, strText, (int)strText.GetLength(), &sizeText);

	::ExtTextOut( dcPaint,Irect.left + ((Irect.Width()+sizeText.cx)/2), Irect.top + 
		((Irect.Height()-sizeText.cy)/2), 
		ETO_CLIPPED | ETO_OPAQUE, &Irect, strText, strText.GetLength(), NULL); 
	if( bUseCtlColor )
	{
		SelectObject( dcPaint, hOldBrush );
	}
#endif
	if( IsNull() )
	{
		return;
	}
	/* 如果没有边框直接返回 */
	if( !GetCurParam() ->HasBorder() )
	{
		return;
	}
	if( NULL == GetCurHwnd( ) )
	{
		return;
	}
	HDC hDC=::GetWindowDC(GetCurHwnd( ));
	if( NULL == hDC )
	{
		return;
	}
	//TRACE("CALLING ME\n");
	//if( m_pCurParam ->m_bBorder )
	{
		CRect rectWindow;
		::GetWindowRect(GetCurHwnd( ),&rectWindow );
		rectWindow.OffsetRect( 
			-rectWindow.left, 
			-rectWindow.top );
		
		HBRUSH hBrush = ::CreatePatternBrush(
			(HBITMAP)m_pBorderBmp->GetSafeHandle() );
		/* 绘制边框 */
		::FrameRect(hDC,&rectWindow, hBrush);
		rectWindow.InflateRect(-1,-1);
		/* 边框太细，内侧再绘制一层：
		   这种方案优劣保留，如果不合适，去掉！
		 */
		::FrameRect(hDC, &rectWindow, hBrush );
		DeleteObject( hBrush );
		::ReleaseDC(GetCurHwnd( ),hDC);
	}
	OnNcPaint( NULL );

}

/** 
	* @brief 获取当前的窗口类名
	*/
LPCTSTR CEditCtrlSkin::GetHwndClassName( )
{
	return TEXT("Edit");
}

/** 
	* @brief 接管控件皮肤之前
	*/
bool CEditCtrlSkin::OnInitSkinParam( HWND hWnd, CParamReference* pParam )
{
	//LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
	//pParam ->SetHasBorder(
	//	0 != ( lStyle & (WS_THICKFRAME | 
	//	WS_DLGFRAME | WS_BORDER) ) );
	UNUSED(hWnd);
	UNUSED(pParam);
	return true;
}

CEditCtrlSkin::~CEditCtrlSkin()
{

}


}


