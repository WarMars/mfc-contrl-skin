#include "stdafx.h"
#include "ProgressBarCtrlskin.h"
#include "GlobalSkinUtil.h"
#include "utils.hpp"
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
CProgressBarCtrlSkin::CProgressBarCtrlSkin( )
{

}

void CProgressBarCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRef* pBmp = ImagePool( ).GetBitmap(
			TEXT("ui\\skin\\ProgressBar.bmp") );
		int nXBase = 0;
		int nYBase = 0;
		int nXOffset = nXBase;
		int nYOffset = nYBase;
		int nCX = 40;
		int nCY = 40;
		m_pBmpHBk = Util::CreateSubBitmap(
			pBmp, nXOffset,nYOffset,nCX,nCY );
		m_pBmpHProgress = Util::CreateSubBitmap(
			pBmp, nXOffset,nYOffset+=nCY,nCX,nCY );
		m_pBmpVBk = m_pBmpHBk;
		m_pBmpVProgress = m_pBmpHProgress;
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpHBk = pConfig ->GetBitmap(TEXT("progress/horizontal/background") );
	m_pBmpHProgress = pConfig ->GetBitmap(TEXT("progress/horizontal/progress") );
	m_pBmpVBk = pConfig ->GetBitmap(TEXT("progress/vertical/background") );
	m_pBmpVProgress = pConfig ->GetBitmap(TEXT("progress/vertical/progress") );
#endif
}

CProgressBarCtrlSkin::~CProgressBarCtrlSkin( )
{

}

/** 
 * @brief overide
 */
LPCTSTR CProgressBarCtrlSkin::GetHwndClassName( )
{
	return TEXT("msctls_progress32");
}
		
/** 
 * @brief overide
 */
CProgressBarCtrlSkin::CParamReference* 
	CProgressBarCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* p = new CParamReference;
	long lStyle = GetWindowLong( hWnd, GWL_STYLE );
	p ->SetVertical( i2b(lStyle & PBS_VERTICAL) );
	return p;
}
		
/** 
 * @brief overide
 */
LRESULT	CProgressBarCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint( );
		break;
	case WM_ERASEBKGND:
		return OnEraseBkgnd( (HDC)wParam );
		break;
	default:
		return OnPreviousWndProc(GetCurHwnd(), nMsg,wParam,lParam );
		break;
	}
	return 0;
}

void CProgressBarCtrlSkin::OnPaint()
{
	if( IsNull() )
	{
		OnAutoDefaultWndProc();
		return;
	}
	HWND hWnd = GetCurHwnd( );

	Util::CTempPaintDC pdc(hWnd);
	CRect rectClient;
	GetClientRect(hWnd,&rectClient );

	CRect rectPos;
	GetPosRect(rectPos);
	if( GetCurParam() ->IsVertical() )
	{
		/* 绘制背景 */
		DrawBmp( pdc, rectClient, m_pBmpHBk );

		/* 绘制进度 */
		DrawBmp( pdc, rectPos, m_pBmpHProgress );
	}
	else
	{
		/* 绘制背景 */
		DrawBmp( pdc, rectClient, m_pBmpVBk );

		/* 绘制进度 */
		DrawBmp( pdc, rectPos, m_pBmpVProgress );
	}
}

BOOL CProgressBarCtrlSkin::OnEraseBkgnd( HDC hdc )
{
	if( IsNull() )
	{
		return OnAutoDefaultWndProc( );
	}
	HWND hWnd = GetCurHwnd( );
	CRect rectClient;
	GetClientRect(hWnd,rectClient);
	/* 绘制背景 */
	DrawBmp( hdc, rectClient, GetCurParam() ->IsVertical()?
		m_pBmpVBk:m_pBmpHBk );
	return TRUE;
}	

BOOL CProgressBarCtrlSkin::GetPosRect( RECT &rectPos )
{
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	CRect rectClient;
	GetClientRect(hWnd,&rectClient);
	int nUpper;
	int nLower;
	{
		/* 获取最大值和最小值 */
		PBRANGE range;
		::SendMessage(hWnd, PBM_GETRANGE, (WPARAM) FALSE, (LPARAM) &range);
		nUpper = range.iHigh;
		nLower = range.iLow;
	}
	
	/* 岗前位置 */
	int nPos = (int)SendMessage(hWnd, PBM_GETPOS, 0, 0);;

	if(nLower > nUpper)
	{
		int temp = nLower;
		nLower = nUpper;
		nUpper = temp;
	}

	if(nPos > nUpper)
	{
		nPos = nUpper;
	}
	if(nPos < nLower)
	{
		nPos = nLower;
	}


	/* 根据当前值、最大值、最小值，计算滑块的绘制位置 */
	if( !p ->IsVertical( ) )
	{
		rectPos = rectClient;
		rectPos.right = rectPos.left + rectClient.Width() * nPos/(nUpper - nLower);
	}
	else
	{
		rectPos = rectClient;
		rectPos.bottom = rectPos.top + rectClient.Height() * nPos/(nUpper - nLower);
	}

	return TRUE;
}

bool sProgressBarCtrlParameter::IsVertical( ) const
{
	return m_bIsVertical;
}

bool sProgressBarCtrlParameter::SetVertical( bool bNew )
{
	if( m_bIsVertical != bNew )
	{
		m_bIsVertical = bNew;
		return true;
	}
	return false;
}

}
