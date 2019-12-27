#include "stdafx.h"
#include "PushButtonCtrlSkin.h"
#include "utils.hpp"
#include "ImageManager.h"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
CPushButtonCtrl::CPushButtonCtrl( )
{

}

void CPushButtonCtrl::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		int nXOffset = 0;
		int nYOffset = 0;
		int nXSize = 143;
		int nYSize = 60;
		CBitmapRefPtr pBitmap = 
			ImagePool( ).CreateBitmap( TEXT("ui\\skin\\Button.bmp") );
		// 默认的贴图
		m_pBmpNormal = Util::CreateSubBitmap( 
			pBitmap, nXOffset,nYOffset,nXSize,nYSize );
		m_pBmpPressed = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nXSize,nYOffset,nXSize,nYSize );
		m_pBmpDisabled = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nXSize,nYOffset,nXSize,nYSize );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpNormal = pConfig ->GetBitmap(TEXT("button/background/normal") );
	m_pBmpPressed = pConfig ->GetBitmap(TEXT("button/background/pressed") );
	m_pBmpDisabled = pConfig ->GetBitmap(TEXT("button/background/disabled") );
	m_pBmpHover = pConfig ->GetBitmap(TEXT("button/background/hover") );
	m_clrNormalText = pConfig ->GetRGBColor( TEXT("button/text/normal") );
	m_clrHoverText = pConfig ->GetRGBColor( TEXT("button/text/hover") );
	m_clrPressedText = pConfig ->GetRGBColor( TEXT("button/text/pressed") );
	m_clrDisableText = pConfig ->GetRGBColor( TEXT("button/text/disabled") );
#endif
}

CPushButtonCtrl::~CPushButtonCtrl( )
{

}

bool CPushButtonCtrl::OnHandleStyleType( UINT nStype, UINT nExStyle )
{
	switch (nStype & SS_TYPEMASK)
	{
	case BS_OWNERDRAW:  
		//跳过自绘制按钮
		return false;
	case BS_PUSHBUTTON:
	case BS_DEFPUSHBUTTON:
	case 0x0000000AL:		
		return true;

	case BS_CHECKBOX:			
	case BS_AUTOCHECKBOX:		
	case BS_3STATE:				
	case BS_AUTO3STATE:
	case BS_RADIOBUTTON:		
	case BS_AUTORADIOBUTTON:
		return ( 0 != (nStype & BS_PUSHLIKE) );
	default:
		//其它类型的按钮暂时不支持
		break;
	}
	return false;
}

void CPushButtonCtrl::OnDrawButton(CDC *pDC)
{
	HWND hWnd = GetCurHwnd( );
	CRect rectWindow = Util::CTempAbsoluteWindowRect(hWnd);
	CButtonCtrlStatus* pParam = GetCurParam();
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap( pDC, rectWindow.Width(),
		rectWindow.Height() );
	CBitmap* pOldBmp = dcMem.SelectObject( &bmp );
	/* 绘制背景 */
	DrawBackground( &dcMem,rectWindow );
	/* 绘制文本 */
	
	COLORREF clrOld = 0;

	CButton *pButton = (CButton*)CWnd::FromHandle( hWnd );
	bool bDisabled = ( FALSE == IsWindowEnabled( hWnd ) );
	if ( bDisabled )
	{
		/* 禁用 */
		clrOld = dcMem.SetTextColor( m_clrDisableText );
		
	}
	else if ( i2b( pParam -> m_nButtonState & 
		CButtonCtrlStatus::BUTTON_PRESSED) ||
		i2b(  pParam -> m_nButtonState & 
		CButtonCtrlStatus::BUTTON_CHECKED ) )
	{	
		/* 按下 */
		clrOld = dcMem.SetTextColor( m_clrPressedText );
	}
	else if( 
		i2b( GetCurParam( ) ->m_nButtonState & 
		CButtonCtrlStatus::BUTTON_HOVER)  )
	{
		clrOld = dcMem.SetTextColor( m_clrHoverText );
	}
	else
	{
		/* 无操作 */
		clrOld = dcMem.SetTextColor( m_clrNormalText );
	}
	DrawText( &dcMem, rectWindow );

	pDC ->BitBlt( rectWindow.left,rectWindow.top,
		rectWindow.Width(), rectWindow.Height(),
		&dcMem, 0, 0, SRCCOPY );
	dcMem.SelectObject( pOldBmp );

}


void CPushButtonCtrl::DrawBackground(CDC *pDC,const CRect& destRect )
{
	if( NULL == pDC )
	{
		return;
	}
	if( IsNull( ) )
	{
		return;
	}
	HWND hWnd = GetCurHwnd();
	CButton *pButton = (CButton*)CWnd::FromHandle( hWnd );
	bool bDisabled = ( FALSE == IsWindowEnabled( hWnd ) );
	if( !bDisabled )
	{
		HWND hWndParent = GetParent( hWnd );
		if( NULL != hWndParent )
		{
			bDisabled = (FALSE == IsWindowEnabled( hWndParent) );
		}
	}

	CButtonCtrlStatus* pParam = GetCurParam();

	if ( bDisabled )
	{
		/* 禁用 */
		DrawBmp( pDC, destRect, m_pBmpDisabled );
	}
	else if ( i2b( pParam -> m_nButtonState & 
		CButtonCtrlStatus::BUTTON_PRESSED)  ||
		i2b(  pParam -> m_nButtonState & 
		CButtonCtrlStatus::BUTTON_CHECKED ) )
	{	
		/* 按下 */
		DrawBmp( pDC, destRect, m_pBmpPressed );
	}
	else if( 
		i2b( pParam ->m_nButtonState & 
		CButtonCtrlStatus::BUTTON_HOVER)  )
	{
		DrawBmp( pDC, destRect, m_pBmpHover );
	}
	else
	{
		/* 无操作 */
		DrawBmp( pDC, destRect, m_pBmpNormal );
	}
}

}