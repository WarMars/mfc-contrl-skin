#include "stdafx.h"
#include "StatusBarCtrlSkin.h"
#include "GlobalSkinUtil.h"
#include "utils.hpp"
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{

	CStatusBarCtrlSkin::CStatusBarCtrlSkin( )
	{

	}

	void CStatusBarCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
	{
#ifdef USING_CONFIG_FILE
		if( NULL == pConfig )
#endif
		{
			CBitmapRef* pBmp = ImagePool( ).CreateBitmap(
				TEXT("ui\\skin\\StatusBar.bmp") );
			int nXOffset = 0;
			int nYOffset = 0;
			int nSize  = 40;
			m_pBmpItemBk = Util::CreateSubBitmap(
				pBmp, nXOffset, nYOffset, nSize,nSize ); 
			m_pBmpBk = Util::CreateSubBitmap(
				pBmp, nXOffset, nYOffset+=nSize, nSize,nSize ); 
			return;
		}
#ifdef USING_CONFIG_FILE
		m_pBmpItemBk = pConfig ->GetBitmap( TEXT("statusbar/item/background") ); 
		m_pBmpBk = pConfig ->GetBitmap( TEXT("tab/background") ); 
#endif
	}

	CStatusBarCtrlSkin::~CStatusBarCtrlSkin( )
	{

	}
	/** 
	* @brief overide
	*/
	LPCTSTR CStatusBarCtrlSkin::GetHwndClassName( )
	{
		return TEXT("msctls_statusbar32");
	}

	/** 
	* @brief overide
	*/
	CStatusBarCtrlSkin::CParamReference* 
		CStatusBarCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
	{
		CParamReference* pParam = new CParamReference;

		return pParam;
	}
	/** 
	* @brief overide
	*/
	LRESULT	CStatusBarCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
	{
		switch(nMsg)
		{
		case WM_PAINT:
			OnPaint( );
			break;
		case WM_ERASEBKGND:
			return OnEraseBkgnd( (HDC) wParam );
		case WM_SETTEXT:
			return OnSetText(wParam,lParam);
			break;
		default:
			return OnPreviousWndProc( GetCurHwnd(), nMsg, wParam,lParam );
			break;
		}
		return 0;
	}

	void CStatusBarCtrlSkin::OnPaint( )
	{
		//OnAutoDefaultWndProc();
		
		/* 绘制状态栏 */
		DrawStatusBar( Util::CTempPaintDC(GetCurHwnd()) );
	}

	BOOL CStatusBarCtrlSkin::OnEraseBkgnd( HDC hdc )
	{	
		if( IsNull() )
		{
			return OnAutoDefaultWndProc();
		}
		HWND hWnd = GetCurHwnd();
		RECT rectWindow = Util::CTempAbsoluteWindowRect( hWnd );
		
		/* 绘制背景 */
		DrawBmp( hdc, rectWindow, m_pBmpBk );
		return TRUE;
	}

	LRESULT CStatusBarCtrlSkin::OnSetText(WPARAM wParam, LPARAM lParam )
	{
		HWND hWnd = GetCurHwnd();
		LRESULT lResult = 
			OnPreviousWndProc( hWnd, WM_SETTEXT, wParam, lParam );
		
		/* 重绘 */
		InvalidateRect( hWnd, NULL, TRUE );
		return lResult;
	}


	void CStatusBarCtrlSkin::DrawStatusBar( HDC  hdc )
	{
		if( IsNull() )
		{
			return;
		}
		HWND hWnd = GetCurHwnd( );
		CRect rectClient;
		GetClientRect( hWnd, &rectClient );
		DrawBmp( hdc,rectClient, m_pBmpBk );

		//int nPart[255];
		
		/* 获取子项数目 */
		int nCount = SendMessage(
			hWnd, 
			SB_GETPARTS,
			0,0
			);
		CRect rectItem;
		TCHAR szItemText[512] = {0};
		
		/* 获取字体 */
		HFONT hFont = (HFONT)::SendMessage(hWnd, WM_GETFONT, 0, 0 );
		HGDIOBJ hOldFont = SelectObject( hdc, hFont );
		int nOldMode = SetBkMode(hdc,TRANSPARENT);

		TEXTMETRIC Metrics;
		GetTextMetrics( hdc, &Metrics);
		for ( int i = 0; i < nCount; i++ )
		{
			/* 获取项的尺寸位置信息 */
			::SendMessage(hWnd, SB_GETRECT, i, (LPARAM)&rectItem );
			if(i == nCount - 1)
			{
				//让左右一项的宽度延伸到的状态栏最右边，
				//这种改动：调整默认的状态栏不合理的地方
				if(rectItem.right < rectClient.right )
				{
					rectItem.right = rectClient.right;

				}
			}
			//背景
			DrawBmp( hdc, rectItem, m_pBmpItemBk );

			//边框
			Util::Draw3D(
				hdc,rectItem,
				GetSysColor(COLOR_3DSHADOW),
				RGB(255,255,255) );

			//设置文本位置
			rectItem.SetRect(
				rectItem.left + 1,
				rectItem.top + 1,
				rectItem.right - 1,
				rectItem.bottom - 1 );
			//int nLength = LOWORD(::SendMessage(m_hWnd, SB_GETTEXTLENGTH,
			//	(WPARAM)i, 0L));
			
			/* 获取文本 */
			LRESULT dw = ::SendMessage(
				hWnd, 
				SB_GETTEXT, (WPARAM)i,
				(LPARAM)szItemText );
			if( 0 == _tcslen(szItemText) )
			{
				continue;
			}
			
			/* 居中绘制文本 */
			rectItem.top +=(rectItem.Height() - Metrics.tmHeight)/2;
			DrawText(hdc, szItemText,-1,&rectItem,
				DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_NOPREFIX);
		}
		SelectObject( hdc, hOldFont );
		SetBkMode( hdc, nOldMode );

	}
}