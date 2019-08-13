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
		// Ĭ�ϵ���ͼ
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
		//�����Ի��ư�ť
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
		//�������͵İ�ť��ʱ��֧��
		break;
	}
	return false;
}

void CPushButtonCtrl::OnDrawButton(CDC *pDC)
{
	CRect rectWindow;
	HWND hWnd = GetCurHwnd( );
	GetWindowRect(hWnd,&rectWindow);
	rectWindow.OffsetRect( 
		-rectWindow.left, -rectWindow.top );
	
	/* ���Ʊ��� */
	DrawBackground( pDC,rectWindow );
	/* �����ı� */
	DrawText( pDC, rectWindow );
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

	CButton *pButton = (CButton*)CWnd::FromHandle(GetCurHwnd( ));
	bool bDisabled = ( 0 != ( GetCurParam( ) -> m_nButtonState & 
		sButtonCtrlStatus::BUTTON_DISABLED ) );
	if ( bDisabled )
	{
		/* ���� */
		DrawBmp( pDC, destRect, m_pBmpDisabled );
	}
	else if ( 0!=( GetCurParam( ) -> m_nButtonState & 
		sButtonCtrlStatus::BUTTON_PRESSED) ||
		0!=( GetCurParam( ) ->m_nButtonState & 
		sButtonCtrlStatus::BUTTON_HOVER) )
	{	
		/* ���� */
		DrawBmp( pDC, destRect, m_pBmpPressed );
	}
	else
	{
		/* �޲��� */
		DrawBmp( pDC, destRect, m_pBmpNormal );
	}
}

}