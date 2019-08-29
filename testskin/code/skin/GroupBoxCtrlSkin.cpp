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
			CBitmapRefPtr pBitmap = ImagePool( ).CreateBitmap(
				TEXT("ui\\skin\\GroupBox.bmp") );
			int nXOffset = 0;
			int nYOffset = 0;
			int nSize = 48;
			m_pBmpCaption = Util::CreateSubBitmap(pBitmap,
				nXOffset,nYOffset,nSize,nSize );
			m_pBmpBorder = Util::CreateSubBitmap(pBitmap,
				nXOffset,nYOffset+nSize,nSize,nSize );
			return;
		}
#ifdef USING_CONFIG_FILE
		m_pBmpCaption = 
			pConfig ->GetBitmap(TEXT("group/caption/background") );
		m_pBmpBorder = 
			pConfig ->GetBitmap(TEXT("group/border/background") );
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

		/* 标题 */
		TCHAR szCaption[MAX_PATH] = {0};
		GetWindowText(GetCurHwnd( ), szCaption, sizeof(szCaption) );
		CSize size =  pDC->GetTextExtent( szCaption );

		rtWindow.top += size.cy/2 ;
		CBrush brushBk;
		/* 边框 */
		brushBk.CreatePatternBrush( m_pBmpBorder );
		pDC ->FrameRect( &rtWindow, &brushBk );
		CRect rtCaption;
		rtCaption.left = 5;
		rtCaption.right = rtCaption.left + size.cx + 5;
		rtCaption.top = 0;
		rtCaption.bottom = rtCaption.top + size.cy+2;

		/* 绘制标题 */
		DrawBmp( pDC, rtCaption, m_pBmpCaption );

		/* 获取字体 */
		HFONT hFont = (HFONT)SendMessage( hWnd, WM_GETFONT,0,0);
		HGDIOBJ hOldFont = SelectObject( pDC ->GetSafeHdc(), hFont );

		int oldMode = pDC->SetBkMode(TRANSPARENT);
		rtCaption.left += 2;

		/* 加入居中对其 */
		pDC->DrawText(szCaption,
			rtCaption,
			DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		SelectObject( pDC ->GetSafeHdc(), hFont );
		pDC->SetBkMode(oldMode);

	}
}

