#include "stdafx.h"
#include "SliderCtrlSkin.h"
#include "GlobalSkinUtil.h"
#include "utils.hpp"
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{

CSilderCtrlSkin::CSilderCtrlSkin( )
{

}


void CSilderCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
    if( NULL == pConfig )
#endif
    {
        CBitmapRef* pBmp = ImagePool( ).GetBitmap(
                    TEXT("ui\\skin\\SliderBar.bmp") );
        const int nXBase = 0;
        const int nYBase = 0;
        int nXOffset = nXBase;
        int nYOffset = nYBase;
        int nCX = 40;
        int nCY = 40;
        m_pBmpHBk = Util::CreateSubBitmap(
                    pBmp, nXOffset, nYOffset, nCX*4, nCY );
        nYOffset += nCY;
        m_pBmpHLine = Util::CreateSubBitmap(
                    pBmp, nXOffset, nYOffset, nCX*4, nCY/2 );
        nYOffset += nCY/2;
        m_pBmpHSlider = Util::CreateSubBitmap(
                    pBmp, nXOffset, nYOffset, nCX, nCY );
        nXOffset += nCX;
        m_pBmpVSlider = Util::CreateSubBitmap(
                    pBmp, nXOffset, nYOffset, nCX, nCY );
		m_pBmpVBk = m_pBmpHBk;
		m_pBmpHSlider = m_pBmpVSlider;
        return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpHBk = pConfig ->GetBitmap( TEXT("slider/horizontal/background") );
	m_pBmpVBk = pConfig ->GetBitmap( TEXT("slider/vertical/background") );
	m_pBmpHLine = pConfig ->GetBitmap( TEXT("slider/horizontal/line") );
	m_pBmpVLine = pConfig ->GetBitmap( TEXT("slider/vertical/line") );
	m_pBmpHSlider = pConfig ->GetBitmap( TEXT("slider/horizontal/slider") );
	m_pBmpVSlider = pConfig ->GetBitmap( TEXT("slider/vertical/slider") );
#endif
}

CSilderCtrlSkin::~CSilderCtrlSkin( )
{

}
/**
        * @brief overide
        */
LPCTSTR CSilderCtrlSkin::GetHwndClassName( )
{
    return TEXT("msctls_trackbar32");
}

/**
        * @brief overide
        */
CSilderCtrlSkin::CParamReference*
CSilderCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
    CParamReference* p = new CParamReference;
    DWORD lStyle		= GetWindowLong( hWnd, GWL_STYLE );

    /* 是否是垂直的 */
    p ->SetVertical( i2b(lStyle & TBS_VERT) );

    return p;
}

/**
        * @brief overide
        */
LRESULT	CSilderCtrlSkin::OnWndProc(
        UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    switch( nMsg )
    {
    case WM_PAINT:
        OnPaint( );
        break;
    default:
        return OnPreviousWndProc(
                    GetCurHwnd( ), nMsg, wParam, lParam );
    }
    return 0;
}

void CSilderCtrlSkin::OnPaint( )
{
    /* 绘制 */
    Draw( Util::CTempPaintDC( GetCurHwnd()) );
}

void CSilderCtrlSkin::Draw( HDC hDC )
{
    HWND hWnd = GetCurHwnd( );
    CParamReference* p = GetCurParam( );
    CRect rectClient,rectLine,rectSlider;
    GetClientRect(hWnd, rectClient);

    /* 获取中间线的大小和位置信息 */
    ::SendMessage(hWnd, TBM_GETCHANNELRECT, 0, (LPARAM)&rectLine );

    /* 获取滑块大小和位置信息 */
    ::SendMessage(hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&rectSlider);

	if(  p ->IsVertical() )
	{
		/* 背景 */
		DrawBmp( hDC, rectClient, m_pBmpVBk );

		/* 中间线 */
		DrawBmp( hDC, rectLine, m_pBmpVLine );

		/* 滑块 */
		DrawBmp( hDC, rectSlider, m_pBmpVSlider );
	}
	else
	{
		/* 背景 */
		DrawBmp( hDC, rectClient, m_pBmpHBk );

		/* 中间线 */
		DrawBmp( hDC, rectLine, m_pBmpHLine );

		/* 滑块 */
		DrawBmp( hDC, rectSlider, m_pBmpHSlider );
	}
}

bool sSliderCtrlParameter::IsVertical( ) const
{
    return m_bIsVertical;
}

bool sSliderCtrlParameter::SetVertical( bool bNew )
{
    if( m_bIsVertical != bNew )
    {
        m_bIsVertical = bNew;
        return true;
    }
    return false;
}

}
