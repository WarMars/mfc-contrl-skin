#include "stdafx.h"
#include "GroupBoxCtrlSkin.h"
#include "utils.hpp"
#include "ImageManager.h"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{

	CGroupBoxCtrlSkin::CGroupBoxCtrlSkin( )
	{
	}


	void CGroupBoxCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
	{
#ifdef USING_CONFIG_FILE
		if( NULL == pConfig )
#endif
		{
			Gdiplus::Image* pBitmap = ImagePool( ).GetImage(
				TEXT("ui\\skin\\GroupBox.bmp") );
			int nXOffset = 0;
			int nYOffset = 0;
			int nSize = 48;
			m_pBmpCaption = Util::CreateSubImage(pBitmap,
				nXOffset,nYOffset,nSize,nSize );
			CImagePool( ).AddImage(TEXT("groupbox-caption"),m_pBmpCaption );
			//m_clrBorder = Util::GetBitmapPixelColor( Util::CreateSubImage(pBitmap,
			//	nXOffset,nYOffset+nSize,nSize,nSize );
			//CImagePool( ).AddImage(TEXT("groupbox-caption"),m_pBmpCaption ),0,0);
			return;
		}
#ifdef USING_CONFIG_FILE
		m_pBmpCaption = 
			pConfig ->GetImage(TEXT("group/caption/background") );
		m_clrBorder = 
			pConfig ->GetRGBColor(TEXT("group/border/background") );
		
#endif
	}

	CGroupBoxCtrlSkin::~CGroupBoxCtrlSkin( )
	{

	}

	bool CGroupBoxCtrlSkin::OnHandleStyleType( UINT nStype, UINT nExStyle )
	{
		switch (nStype & SS_TYPEMASK)
		{
		case BS_OWNERDRAW:          
			return false;
		case BS_GROUPBOX:	
			return true;
			break;
		default:	
			break;
		}
		return false;
	}

	void CGroupBoxCtrlSkin::OnDrawButton(CDC *pDC)
	{
		if( IsNull() || NULL == pDC )
		{
			return;
		}
		CRect rtWindow;
		HWND hWnd = GetCurHwnd( );
		GetWindowRect( hWnd, &rtWindow);
		rtWindow.OffsetRect(-rtWindow.left,-rtWindow.top);

		//	CMemDC memDC(pDC,rtWindow);

		/* ���� */
		TCHAR szCaption[MAX_PATH] = {0};
		GetWindowText(GetCurHwnd( ), szCaption, sizeof(szCaption) );

		/* ��ȡ���� */
		HFONT hFont = (HFONT)SendMessage( hWnd, WM_GETFONT,0,0);
		HWND hParent = GetParent( GetCurHwnd() );

		HGDIOBJ hOldFont = SelectObject( pDC ->GetSafeHdc(), hFont );
		CSize size =  pDC->GetTextExtent( szCaption );
		
		rtWindow.top += size.cy/2 ;
#if 0
		CBrush brushBk;
		/* �߿� */

		brushBk.CreatePatternBrush( m_pBmpBorder );
		pDC ->FrameRect( &rtWindow, &brushBk );
#else
		//Util::DrawImage(pDC ->GetSafeHdc(), m_pBmpBorder, rtWindow );
		if( !false )
		{
			CBrush brush( m_clrBorder );
			::FrameRect( pDC ->GetSafeHdc(), 
				CRect( rtWindow.left, rtWindow.top + 7,
				rtWindow.right, rtWindow.bottom ), brush );
		}
#endif
		CRect rtCaption;
		rtCaption.left = 5;
		rtCaption.right = rtCaption.left + size.cx + 5;
		rtCaption.top = 0;
		rtCaption.bottom = rtCaption.top + size.cy+2;

		

		rtCaption.left += 2;

		if( NULL != hParent )
		{ 
			HBRUSH hBrush = (HBRUSH)SendMessage(hParent, WM_CTLCOLORSTATIC, (WPARAM)(pDC ->GetSafeHdc()),
				(LPARAM)(GetCurHwnd()) );
			HGDIOBJ hOldBrush = (NULL != hBrush?pDC ->SelectObject( hBrush):NULL);
			/* ������ж��� */
			pDC->DrawText(szCaption,
				rtCaption,
				DT_LEFT|DT_TOP|DT_SINGLELINE);
			if( NULL != hOldBrush )
			{
				pDC ->SelectObject( hOldBrush );
			}
		}
		else
		{
			/* ���Ʊ��� */
#if 0
			DrawBmp( pDC, rtCaption, m_pBmpCaption );
#else
			Util::DrawImage( pDC ->GetSafeHdc(), m_pBmpCaption, rtCaption );
#endif

			int oldMode = pDC->SetBkMode(TRANSPARENT);
			/* ������ж��� */
			pDC->DrawText(szCaption,
				rtCaption,
				DT_LEFT|DT_TOP|DT_SINGLELINE);
			pDC->SetBkMode(oldMode);
		}
		
		
		SelectObject( pDC ->GetSafeHdc(), hFont );

	}
}

