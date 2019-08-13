#include "stdafx.h"
#include "PopupMenuCtrlSkin.h"
#include "GlobalSkinUtil.h"
#include <ImagePool>
#include "utils.hpp"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
	namespace FileVariable
	{
		struct sColorMapping
		{
			int nSrcColorIndex;
			CPE::PopupMenuColor nDstColorIndex;
		};
	#if 0
	{ COLOR_WINDOWTEXT, COLOR_WINDOWTEXT },
    { COLOR_GRAYTEXT, COLOR_GRAYTEXT },
    { COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHTTEXT },
    { COLOR_3DHILIGHT, COLOR_MENU/*COLOR_3DHILIGHT*/ },
    	//{ COLOR_3DDKSHADOW, COLOR_MENU },
    { COLOR_3DSHADOW, COLOR_3DSHADOW },
    { COLOR_3DFACE, COLOR_MENU/*COLOR_3DFACE*/ },
    { COLOR_MENU, COLOR_MENU },
    { 0xf1f1f1, COLOR_MENU},
	#endif
		static sColorMapping g_colors[] = 
		{
			{ COLOR_WINDOWTEXT, CPE::PMC_TextNormal },		//标题
			{ COLOR_GRAYTEXT, CPE::PMC_TextDisabled },	//禁用
			{ COLOR_HIGHLIGHTTEXT, CPE::PMC_TextFocused },		// 文本高亮
			{ COLOR_3DHILIGHT, CPE::PMC_Background },		// 高亮
			{ COLOR_3DSHADOW , CPE::PMC_Seperator },		// 引用
			{ COLOR_3DFACE, CPE::PMC_Background },			// 表面
			{ COLOR_MENU , CPE::PMC_Background  },		// 菜单
			{ CPE::PMC_Special, CPE::PMC_Background},			// 其它
		};
	}
CPopupMenuCtrlSkin::CPopupMenuCtrlSkin( )
{
	m_PopupColor[CPE::PMC_3DHightLight]=
		GetSysColor( COLOR_3DHILIGHT );
	m_PopupColor[CPE::PMC_3DFace]=
		GetSysColor( COLOR_3DFACE );
	m_PopupColor[CPE::PMC_Special]=	RGB(0xF1,0xF1,0xF1);
	InitFont( );
}

void CPopupMenuCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRef* pBmp = 
			ImagePool( ).CreateBitmap(
			TEXT("ui\\skin\\PopupMenu.bmp") );
		int nXOffset = 5;
		int nYOffset = 5;
		int nStep = 10;
		m_PopupColor[CPE::PMC_ParentBackground]=
			Util::GetBitmapPixelColor( pBmp, nXOffset,nYOffset );
		m_PopupColor[CPE::PMC_TextNormal]=
			Util::GetBitmapPixelColor( pBmp, nXOffset,nYOffset += nStep );
		m_PopupColor[CPE::PMC_TextDisabled]=
			Util::GetBitmapPixelColor( pBmp, nXOffset,nYOffset += nStep );
		m_PopupColor[CPE::PMC_TextFocused]=	
			Util::GetBitmapPixelColor( pBmp, nXOffset,nYOffset += nStep );
		m_PopupColor[CPE::PMC_Seperator]=
			Util::GetBitmapPixelColor( pBmp, nXOffset,nYOffset += nStep );
		m_PopupColor[CPE::PMC_Background]=
			Util::GetBitmapPixelColor( pBmp, nXOffset,nYOffset += nStep );
		return;
	}

#ifdef USING_CONFIG_FILE
	m_PopupColor[CPE::PMC_ParentBackground]=
		pConfig ->GetRGBColor( TEXT("popupmenu/color/parentbk") );
	m_PopupColor[CPE::PMC_TextNormal]=
		pConfig ->GetRGBColor( TEXT("popupmenu/color/text/normal") );
	m_PopupColor[CPE::PMC_TextDisabled]=
		pConfig ->GetRGBColor( TEXT("popupmenu/color/text/disabled") );
	m_PopupColor[CPE::PMC_TextFocused]=	
		pConfig ->GetRGBColor( TEXT("popupmenu/color/text/focused") );
	m_PopupColor[CPE::PMC_Seperator]=
		pConfig ->GetRGBColor( TEXT("popupmenu/color/text/seperator") );
	m_PopupColor[CPE::PMC_Background]=
		pConfig ->GetRGBColor( TEXT("popupmenu/color/text/background") );
	return;
#endif
}

CPopupMenuCtrlSkin::~CPopupMenuCtrlSkin( )
{
	if( NULL != m_hMenuFont )
	{
		DeleteObject( m_hMenuFont );
	}
}

/** 
 * @override
 */
LPCTSTR CPopupMenuCtrlSkin::GetHwndClassName( )
{
	return TEXT("#32768");
}
		
/** 
 * @override
 */
CPopupMenuCtrlSkin::CParamReference* CPopupMenuCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* pParam = new CParamReference;
	pParam ->SetSelectedIndex( CPE::PMSS_ReDrawAll );
	pParam ->SetHMenu( NULL );
	pParam ->SetStyle( CPE::PMS_SiderBar | CPE::PMS_Flat );
	pParam ->SetFirstRedraw( false );
	pParam ->SetParent( NULL );
	pParam ->SetGradient( true );
	pParam ->SetFirstShow( true );

	pParam ->SetSideBar( );
	pParam ->SetFlat( );
	BOOL bAnmiated = FALSE;
	SystemParametersInfo(SPI_GETMENUANIMATION, 0, &bAnmiated, 0);
	pParam ->SetAnimatedMenus( TRUE == bAnmiated?true:false );
	UpdateWindow( hWnd );
	return pParam;

}

/** 
 * @override
 */
LRESULT CPopupMenuCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//TRACE("nMsg:0x%08x\n", nMsg );
	if( IsNull() )
	{
		return OnAutoDefaultWndProc( );
	}
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	LRESULT lResult = 0;
	//return OnPreviousWndProc( hWnd, nMsg, wParam, lParam );
	switch( nMsg )
	{
	case WM_NCPAINT:
		{ 
			if (!p ->IsAnimatedMenus() || ! p ->IsFirstRedraw( ) )
			{
				Util::CTempWindowDC wdc(hWnd);
				OnNcPaint( wdc );
				return 0;
			}
		}
		break;

	case WM_PRINT: 
		{
			lResult = OnAutoDefaultWndProc( );
			OnNcPaint( 
				//Util::CTempWindowDC(hWnd)
				(HDC)wParam
				);
			// TRACE("wm_print message\n");
			return lResult;
		}
	case WM_PRINTCLIENT:
		OnPrintClient( 
			/* Util::CTempWindowDC(hWnd)*/
			(HDC)wParam, 
			lParam );
		return 0;

	case WM_PAINT:
		{
			Util::CTempPaintDC pdc(m_hWnd);
			SendMessage(
				hWnd, WM_PRINTCLIENT, 
				(WPARAM)(HDC)pdc, 
				PRF_CLIENT | PRF_CHECKVISIBLE );
			return 0;
		}
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_UP:
		case VK_DOWN:
		case VK_RIGHT:
			//  左栏要复杂得多，因为如果当前选择的是左栏
			//	我们必须始终使用默认的绘图，再基于此图的修改。
		case VK_LEFT:
			if (NULL == p ->GetHMenu() )
			{
				if ( wParam != VK_LEFT) 
				{
					SendRedrawMsg( FALSE );
				}

				lResult = OnAutoDefaultWndProc();

				if ( wParam != VK_LEFT)
				{
					SendRedrawMsg(TRUE);
				}

				p ->SetSelectedIndex( -1 );

				InvalidateRect( hWnd, NULL, FALSE );
				UpdateWindow( hWnd );
				p ->SetFirstRedraw( false );
			}
			else // have menu handle
			{
				int nPrevSel = GetCurSel();

				if ( wParam != VK_LEFT) 
				{
					SendRedrawMsg( FALSE );
				}

				lResult = OnAutoDefaultWndProc( );

				if ( wParam != VK_LEFT )
				{
					SendRedrawMsg( TRUE );
				}
				//如果我们有菜单的句柄
				//我们可以选择重画，否则我们必须重画
				
				int nCurSel = GetCurSel();
				p ->SetSelectedIndex( nCurSel );

				if ( nCurSel != nPrevSel)
				{
					CRect rectInvalid;
					GetInvalidRect( nCurSel, nPrevSel, rectInvalid);

					InvalidateRect( hWnd, rectInvalid, FALSE);
					UpdateWindow( hWnd );

					p ->SetFirstRedraw( false );
				}
			}
			return lResult;
		}
		break;

	case 0x1e5: 

		if ( p ->GetSelectedIndex() != (int)wParam )
		{
			//进行部分绘制
			CRect rInvalid;

			if ( NULL != p ->GetHMenu() )
			{
				GetInvalidRect(
					(int)wParam,
					p ->GetSelectedIndex( ),
					rInvalid );
			}
			else
			{
				GetClientRect( hWnd, rInvalid);
			}
			//防止在缺省消息处理期间重绘
			//否则，这个项就会被重绘而被覆盖
			SendRedrawMsg( FALSE );
			lResult = OnAutoDefaultWndProc( );
			SendRedrawMsg(TRUE);

			p ->SetSelectedIndex( wParam );
			// TRACE("selected:%d\n", wParam);
			InvalidateRect( hWnd, rInvalid, FALSE);

			if (! p ->IsFirstRedraw() )
			{
				UpdateWindow( hWnd );
			}
		}

		if( p ->IsFirstRedraw() )
		{ 
			//第一次绘制
			if ( p ->IsAnimatedMenus( ) )
			{
				/* 绘制边框等 */
				OnNcPaint( Util::CTempWindowDC(hWnd) );
			}

			p ->SetFirstRedraw(false);
		}
		return lResult;
	case WM_NCCALCSIZE:
		if ( p ->HasSideBar() )
		{
			lResult = OnAutoDefaultWndProc( );
			/* 有边栏的情况，需要加上边栏宽度 */
			LPRECT pRect = i2b(wParam) ? 
				&((LPNCCALCSIZE_PARAMS)lParam)->rgrc[0] :
			(LPRECT)lParam;
			pRect->left += CPE::CONST_SiderBarWidth;
			return lResult;

		}
		break;

	case WM_WINDOWPOSCHANGING:
		{
			WINDOWPOS* pWP = (WINDOWPOS*)lParam;

			// 调整侧边栏宽度
			if ( p ->HasSideBar() && !i2b(pWP->flags & SWP_NOSIZE) )
			{
				pWP->cx += CPE::CONST_SiderBarWidth;
			}

			//如果我们有一个父菜单，我们可能需要调整我们的
			//pos避免客户重绘问题
			sPopupMenuCtrlParameter* pParent = p ->GetParent();
			if ( NULL != pParent && !i2b(pWP->flags & SWP_NOMOVE))
			{
				//如果在父窗口右侧
				//需要调整以避免出客户端rect
				CRect rectParentWindow;
				HWND hParentHwnd = pParent ->GetHwnd( );
				::GetWindowRect( hParentHwnd, rectParentWindow);

				if (pWP->x > rectParentWindow.left) // right
				{
					CRect rParentClient;
					::GetClientRect( hParentHwnd, rParentClient);

					ClientToScreen(hParentHwnd,&rParentClient);

					pWP->x = rParentClient.right;
				}
			}
		}
		break;

	case WM_ERASEBKGND: 
		return TRUE; 
		break;
	default:
		break;
	}
	return OnPreviousWndProc( hWnd, nMsg, wParam, lParam );
}

void CPopupMenuCtrlSkin::OnNcPaint(HDC hdc)
{
	if( IsNull() )
	{
		return;
	}
	HWND hWnd( GetCurHwnd() );
	CParamReference* p( GetCurParam() );

	bool bIRender = true;

	CRect rWindow, rClient;
	GetDrawRect(rWindow, rClient);

	/* 获取系统默认的裁剪区域 */
	CRect rClip;
	GetClipBox( hdc,rClip );

	HBITMAP hMemBmp = CreateCompatibleBitmap(
		hdc, rWindow.right, rWindow.bottom);

	HDC hMemDc = CreateCompatibleDC(NULL);

	HGDIOBJ hOldBmp = SelectObject(hMemDc, hMemBmp );
	COLORREF crColorMenu = GetColor(CPE::PMC_Background);

	CRect rSidebar(rWindow);
	rSidebar.DeflateRect(3, 3);
	rSidebar.right = rSidebar.left + CPE::CONST_SiderBarWidth;
	
	/* 绘制边栏 */
	if ( p ->HasSideBar() && !DrawMenuSidebar( hMemDc, rSidebar) )
	{
		Util::FillSolid( hMemDc, rSidebar, 
			Util::ColorMultiply(GetColor(CPE::PMC_Seperator), 0.9f));
	}
	
	/* 裁剪 */
	ExcludeClipRect( 
		hMemDc,
		rSidebar.left, rSidebar.top,
		rSidebar.right,rSidebar.bottom );

	/* 绘制背景 */
	if (!bIRender || !DrawMenuNonClientBkgnd( hMemDc, rWindow))
	{
		Util::FillSolid(hMemDc,rWindow, crColorMenu);
	}

	// 绘制边框
	if (!bIRender || !DrawMenuBorder( hMemDc, rWindow) )
	{
		COLORREF crShadow = GetColor(CPE::PMC_Seperator);

		if ( p ->IsFlat( ) )
		{
			Util::Draw3D( hMemDc,rWindow, crShadow, crShadow);
		}
		else
		{
			Util::Draw3D( hMemDc,rWindow, GetColor(CPE::PMC_TextFocused), crShadow);
		}
	}

	int nSaveState = SaveDC( hdc );
	
	ExcludeClipRect(hdc,
		rClient.left, rClient.top, rClient.right, rClient.bottom );
	BitBlt( hdc, 0, 0, rWindow.right, rWindow.bottom, hMemDc, 0, 0, SRCCOPY);
	
	RestoreDC( hdc,nSaveState );

	SelectObject( hMemDc, hOldBmp );
	DeleteObject( hMemBmp );
	DeleteDC( hMemDc );
	
}

void CPopupMenuCtrlSkin::SendRedrawMsg( BOOL bRedraw ) const
{ 
	/* 控制菜单是否重绘，菜单并不总是需要全部重绘 */
	::SendMessage(m_hWnd, WM_SETREDRAW, bRedraw, 0);
}
void CPopupMenuCtrlSkin::GetDrawRect(LPRECT pWindow, LPRECT pClient )
{
	HWND hWnd = GetCurHwnd( );
	CRect rWindow;
	GetWindowRect( hWnd, &rWindow );

	if (NULL != pClient)
	{
		/* 客户区坐标 */
		GetClientRect( hWnd, pClient );
		ClientToScreen( hWnd, pClient );
		::OffsetRect(pClient, -rWindow.left, -rWindow.top);
	}

	if (NULL != pWindow)
	{
		/* 窗口坐标 */
		rWindow.OffsetRect(-rWindow.TopLeft());
		*pWindow = rWindow;
	}
}

void CPopupMenuCtrlSkin::GetInvalidRect(int nCurSel, int nPrevSel, LPRECT lpRect) // in client coords
{
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	HMENU hMenu = p ->GetHMenu( );
	if ( NULL != hMenu || 
		nCurSel == CPE::PMSS_ReDrawAll ||
		nPrevSel == CPE::PMSS_ReDrawAll )
	{
		/* 整个菜单全部重绘 */
		GetClientRect(hWnd,lpRect);
	}
	else if ( NULL !=hMenu )
	{
		::SetRectEmpty(lpRect);

		if (nCurSel >= 0 || nPrevSel >= 0)
		{
			if (nCurSel >= 0)
			{
				/* 获取当前项的矩形区域 */
				GetMenuItemRect(NULL, hMenu, nCurSel, lpRect);
			}

			if (nPrevSel >= 0)
			{
				CRect rTemp;
				/* 上一个菜单项的位置矩形 */
				GetMenuItemRect(NULL, hMenu, nPrevSel, rTemp);
				/* 计算得到在当前客户区中的位置坐标和尺寸信息等 */
				::UnionRect(lpRect, lpRect, rTemp);
			}
			/* 得到客户区坐标 */
			ScreenToClient(hWnd,lpRect);
		}
	}
}

int CPopupMenuCtrlSkin::GetCurSel()
{
	if(IsNull() )
	{
		return -1;
	}

	HMENU hMenu = GetCurParam() ->GetHMenu( );
	
	/* 总共的菜单项数 */
	int nItem = GetMenuItemCount(hMenu);

	while ( 0 != nItem-- )
	{
		/* 如果当前的菜单项处于高亮度状态则为选中 */
		if (i2b(GetMenuState(hMenu, nItem, MF_BYPOSITION) & MF_HILITE) )
		{
			return nItem;
		}
	}

	return -1;


}

COLORREF CPopupMenuCtrlSkin::GetColor(CPE::PopupMenuColor nIndex )
{
	ASSERT( nIndex >= CPE::PMC_ParentBackground &&
		nIndex < CPE::PMC_Size );
	return m_PopupColor[nIndex];

}
HFONT CPopupMenuCtrlSkin::GetFont( CPE::FontType type )
{
	switch( type )
	{
	case CPE::FT_Menu:
		return m_hMenuFont;
	default:
		break;
	}
	return NULL;
}
HDC CPopupMenuCtrlSkin::ReplaceSystemColors(HDC hdcSrc, HDC hdcDest, LPRECT pRect, LPRECT pClip)
{
	std::map<COLORREF,int> mapColors;

	// 替代背景色
	const COLORREF COLORMENU = GetColor( CPE::PMC_Background );

	COLORREF crDest = COLORMENU;
	CParamReference* p = GetCurParam( );
	COLORREF crSrc = GetPixel(hdcSrc, pRect->right-1,  
			(p ->GetSelectedIndex( ) != 0 ?
			pRect->top:pRect->bottom ));

	if ( p ->IsFirstShow() ) // 第一次显示时保存非客户
	{
		int x = GetSystemMetrics(SM_CXMENUCHECK) + 11 ;
		p ->SetButtonColor( GetPixel( hdcSrc, x, 1) );
		p ->SetFirstShow( false );
	}
	// 检查颜色是否需要替代
	if ( crSrc != -1)
	{
		// 绘制新背景
		if ( DrawMenuClientBkgnd(hdcDest, pRect, pClip) )
		{
			int nWidth = pRect->right - pRect->left;
			int nHeight = pRect->bottom - pRect->top;
			Util::TransparentBitBlt( hdcDest, pRect->left, pRect->top, 
				nWidth, nHeight,
				hdcSrc, 0, 0,nWidth, nHeight, crSrc );
			std::swap( hdcSrc, hdcDest );
		}
		else if ( Util::ReplaceColor(hdcSrc, crSrc, hdcSrc, crDest, *pRect, pClip) )
		{		
			std::swap( hdcSrc, hdcDest);
		}
		// 完成替代
		mapColors[crSrc] = 1;
	}
	//  取代其它颜色
	int nColor = sizeof( FileVariable::g_colors ) / 
		sizeof(FileVariable::sColorMapping);

	while ( 0 != nColor--)
	{

		if( 0 == nColor )
		{
			nColor = nColor;
		}
		if ( FileVariable::g_colors[nColor].nSrcColorIndex == 
			CPE::PMC_Special )
		{
			crSrc = Util::IsGreaterThanXP() ? 
				p ->GetButtonColor() : GetSysColor(COLOR_MENU);
		}
		else
		{
			crSrc = GetSysColor( 
				FileVariable::g_colors[nColor].nSrcColorIndex );
		}
		if (mapColors.end() != mapColors.find(crSrc ) )
		{
			continue;
		}
		crDest = GetColor( FileVariable::g_colors[nColor].nDstColorIndex );
		if (crDest == COLORMENU && DrawMenuClientBkgnd(hdcDest, pRect, pClip))
		{ // 和背景色一致，则覆盖背景色
			Util::TransparentBitBlt( hdcDest, pRect->left, pRect->top, 
				pRect->right - pRect->left, 
				pRect->bottom - pRect->top, hdcSrc, 0, 0, crSrc );

			std::swap(hdcSrc, hdcDest );
		}
		else if ( Util::ReplaceColor(hdcSrc, crSrc, hdcDest, crDest, *pRect, pClip))
		{ // 普通的颜色替换
			std::swap(hdcSrc, hdcDest );
		}
		mapColors[crSrc] = 1;
	}

	return hdcDest;
}

void CPopupMenuCtrlSkin::InitFont( )
{
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm,sizeof(ncm));
	ncm.cbSize = sizeof(ncm);

	// 获取非客户区的信息
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, (PVOID)&ncm, FALSE);

	// 创建此字体
	
	// 为了显示中文，不直接使用ANSI字符集
	if (ncm.lfMenuFont.lfCharSet == ANSI_CHARSET)
	{
		ncm.lfMenuFont.lfCharSet = DEFAULT_CHARSET;
	}

	ncm.lfMenuFont.lfQuality = ANTIALIASED_QUALITY;
	ncm.lfMenuFont.lfOutPrecision = OUT_TT_PRECIS;

	/* 创建字体 */
	m_hMenuFont = CreateFont(
		ncm.lfMenuFont.lfHeight,0,0,0,
		ncm.lfMenuFont.lfWeight,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET ,	/* 默认系统字符集：支持中文 */
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH, 
		ncm.lfMenuFont.lfFaceName );

}
void CPopupMenuCtrlSkin::OnPrintClient(HDC hdc, DWORD dwFlags)
{
	if( IsNull() )
	{
		return;
	}

	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	CRect rectClient;
	GetClientRect( hWnd, &rectClient );

	CRect rectClip(rectClient);

	HDC hMemDC1 = CreateCompatibleDC( NULL );
	HDC hMemDC2 = CreateCompatibleDC(NULL);

	HDC hDesktopDC = GetDC( NULL );

	HBITMAP hMemBmp1 = CreateCompatibleBitmap(hDesktopDC, 
		rectClient.right, rectClient.bottom);
	HBITMAP hMemBmp2 =CreateCompatibleBitmap(hDesktopDC,
		rectClient.right, rectClient.bottom) ;
	ReleaseDC( NULL, hDesktopDC );

	// 初始化dc
	SetBkMode(hMemDC1,TRANSPARENT);
	SetBkColor(hMemDC1, (COLORREF)GetSysColor(COLOR_MENU) );

	HGDIOBJ hOldBmp1 = SelectObject(hMemDC1, hMemBmp1 );
	HGDIOBJ hOldFont = SelectObject( hMemDC1, GetFont(CPE::FT_Menu) );
	HGDIOBJ hOldBmp2 = SelectObject( hMemDC2, hMemBmp2 );

	/* 裁剪区域小于客户区 */
	if (i2b(rectClip.top) )
	{
		ExcludeClipRect(hMemDC1,0, 0, rectClient.right, rectClip.top);
	}
	if (rectClip.bottom < rectClient.bottom)
	{
		/* 从dc中去掉此案件区域 */
		ExcludeClipRect(hMemDC1, 0, rectClip.bottom,
			rectClient.right, rectClient.bottom );
	}
	/* 填充裁剪区域矩形 */
	Util::FillSolid(hMemDC1, rectClip, (COLORREF)GetSysColor(COLOR_MENU));

	// 系统默认绘制
	OnPreviousWndProc( 
		hWnd, WM_PRINTCLIENT, (WPARAM)(HDC)hMemDC1, (LPARAM)dwFlags );
	if( p ->GetSelectedIndex() >= 0)
	{
		Util::ShowCurBitmapInClipboard( hMemDC1 );
		int i = 0;
		++i;
	}
	// 在系统绘制的基础上，使用自定义颜色取代系统颜色
	HDC hSrcDC = ReplaceSystemColors( hMemDC1, hMemDC2, rectClient, rectClip);
	if( p ->GetSelectedIndex() >= 0)
	{
		Util::ShowCurBitmapInClipboard( hSrcDC );
		int i = 0;
		++i;
	}
	// 完成绘制
	BitBlt(
		hdc, rectClip.left, rectClip.top, 
		rectClip.Width(), rectClip.Height(), 
		hSrcDC, rectClip.left, rectClip.top, SRCCOPY );
		

	SelectObject(hMemDC1,hOldBmp1 );
	SelectObject(hMemDC1,hOldFont );
	DeleteDC( hMemDC1 );
	DeleteObject(hMemBmp1);

	SelectObject(hMemDC2,hOldBmp2 );
	DeleteDC( hMemDC2 );
	DeleteObject(hMemBmp2 );
}
void CPopupMenuCtrlSkin::OnPaint(HDC hdc)
{
	if( IsNull() )
	{
		return;
	}
	HWND hWnd = GetCurHwnd( );
	CRect rClient;
	GetClientRect( hWnd, &rClient );

	HBITMAP hMemBmp = 
		CreateCompatibleBitmap(hdc, rClient.right, rClient.bottom);

	HDC hMemDC = CreateCompatibleDC(NULL);

	SetBkMode(hMemDC,TRANSPARENT);
	SetBkColor(hMemDC,GetSysColor(COLOR_MENU));
	HGDIOBJ hOldBmp = SelectObject(hMemDC,hMemBmp);
	HGDIOBJ hOldFont = SelectObject(hMemDC,GetFont(CPE::FT_Menu) );

	// 填充背景
	Util::FillSolid(hMemDC,rClient, GetSysColor(COLOR_MENU));

	// 使用系统绘制
	OnPreviousWndProc( hWnd, WM_PAINT, (WPARAM)(HDC)hMemDC, 0);

	HDC hMemDC2 = CreateCompatibleDC(NULL);

	HBITMAP hMemBmp2 = CreateCompatibleBitmap(hdc, rClient.right, rClient.bottom);
	HGDIOBJ hOldBmp2 = SelectObject(hMemDC2,hMemBmp2);

	// 替换颜色
	HDC hSrcDC = ReplaceSystemColors( hMemDC, hMemDC2, rClient, NULL);

	// 覆盖
	BitBlt(hdc, 0, 0, rClient.right, rClient.bottom, hSrcDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC,hOldBmp);
	SelectObject(hMemDC,hOldFont);
	DeleteDC(hMemDC);
	DeleteObject(hMemBmp);

	SelectObject(hMemDC2,hOldBmp2 );
	DeleteDC(hMemDC2);
	DeleteObject(hMemBmp2);
}

bool CPopupMenuCtrlSkin::DrawMenuNonClientBkgnd(HDC hdc, LPRECT pRect)
{
	if( IsNull() )
	{
		return false;
	}

	if ( GetCurParam() ->IsGradient( ) )
	{
		/* 渐变背景 */
		DrawGradientBkgnd( hdc, pRect, NULL);
		return true;
	}
	else
	{
		return false;
	}
}
bool CPopupMenuCtrlSkin::DrawMenuClientBkgnd(HDC hdc, LPRECT pRect, LPRECT pClip)
{
	if( IsNull() )
	{
		return false;
	}
	if ( GetCurParam() ->IsGradient() )
	{
		/* 使用渐变，则绘制渐变背景 */
		DrawGradientBkgnd( hdc, pRect, pClip );
		return true;
	}
	return false;
}
bool CPopupMenuCtrlSkin::DrawMenuSidebar(HDC hdc, LPRECT pRect, LPCTSTR szTitle)
{
	if( IsNull() )
	{
		return false;
	}
	CParamReference* p = GetCurParam( );
	if ( p ->IsGradient() )
	{
		/* 绘制渐变色 */
		COLORREF crColor = GetColor( CPE::PMC_Seperator );

		COLORREF crFrom = crColor;
		COLORREF crTo = Util::ColorMultiply(crFrom, 2.0f);

		Util::FillColor(hdc,*pRect, crFrom, crTo, false );
		return true;
	}
	COLORREF crColor = GetColor( CPE::PMC_Seperator );
	/* 绘制分割颜色 */
	Util::FillColor(hdc,*pRect, crColor);
	return true;
}

bool CPopupMenuCtrlSkin::DrawMenuBorder(HDC hdc, LPRECT pRect)
{
	return false;
}

void CPopupMenuCtrlSkin::DrawGradientBkgnd(HDC hdc, LPRECT pRect, LPRECT pClip)
{
	/* 背景色 -->白色的渐变 */
	COLORREF clrFrom = GetColor( CPE::PMC_Background );
	COLORREF clrTo = RGB(255, 255, 255);

	if ( NULL != pClip )
	{
		CRect rectClip(pClip), rect(pRect);

		/* 不能完全渐变，我们选取100作为基数 */
		if (rectClip.Height() < 100 && rect.Height() > 100)
		{
			rectClip.InflateRect(0, (min(rect.Height(), 100) - rectClip.Height()) / 2 );

			if (rectClip.top < rect.top)
			{
				rectClip.OffsetRect(0, rect.top - rectClip.top);
			}

			else if (rectClip.bottom > rect.bottom)
			{
				rectClip.OffsetRect(0, rect.bottom - rectClip.bottom);
			}
		}

		float fHeight = (float)rect.Height();
		/* 计算颜色变化比例 */
		float fFromFactor = (pRect->bottom - rectClip.top) / fHeight;
		float fToFactor = (pRect->bottom - rectClip.bottom) / fHeight;

		clrFrom = Util::BlendColor(clrFrom, clrTo, fFromFactor);
		clrTo = Util::BlendColor(clrFrom, clrTo, fToFactor);
		
		/* 绘制渐变 */
		Util::FillColor( hdc, rectClip, clrFrom, clrTo, false );
	}
	else
	{
		/* 全部绘制 */
		Util::FillColor( hdc, *pRect, clrFrom, clrTo, false );
	}
}

bool sPopupMenuCtrlParameter::IsAnimatedMenus( ) const
{
	return m_bAnimatedMenus;
}

void sPopupMenuCtrlParameter::SetAnimatedMenus( bool b )
{
	m_bAnimatedMenus = b;
}

bool sPopupMenuCtrlParameter::IsFirstRedraw( ) const
{
	return m_bFirstRedraw;
}

void sPopupMenuCtrlParameter::SetFirstRedraw( bool b )
{
	m_bFirstRedraw = b;
}
void sPopupMenuCtrlParameter::SetHMenu( HMENU hMenu )
{
	m_hMenu = hMenu;
}

HMENU sPopupMenuCtrlParameter::GetHMenu( ) const
{
	return m_hMenu;
}

void sPopupMenuCtrlParameter::SetSelectedIndex( int nIndex )
{
	m_nSelectedIndex = nIndex;
}

int  sPopupMenuCtrlParameter::GetSelectedIndex( ) const
{
	return m_nSelectedIndex;
}

HWND sPopupMenuCtrlParameter::GetHwnd( ) const
{
	return m_hWnd;
}

void sPopupMenuCtrlParameter::SetHwnd( HWND hWnd )
{
	m_hWnd = hWnd;
}

void sPopupMenuCtrlParameter::SetParent(sPopupMenuCtrlParameter* pParent )
{
	m_pParent = pParent;
}

sPopupMenuCtrlParameter* sPopupMenuCtrlParameter::GetParent( ) const
{
	return m_pParent;
}

bool sPopupMenuCtrlParameter::IsGradient( ) const
{
	return m_bGradient;
}

void sPopupMenuCtrlParameter::SetGradient( bool b )
{
	m_bGradient = b;
}

bool sPopupMenuCtrlParameter::IsFirstShow( ) const
{
	return m_bFirstShown;
}

void sPopupMenuCtrlParameter::SetFirstShow( bool b )
{
	m_bFirstShown = b;
}

COLORREF sPopupMenuCtrlParameter::GetButtonColor( ) const
{
	return m_clrBtn;
}

void sPopupMenuCtrlParameter::SetButtonColor( COLORREF color )
{
	m_clrBtn = color;
}


bool sPopupMenuCtrlParameter::HasRoundCorner( ) const
{
	return i2b( m_byStyle & CPE::PMS_RoundCorner );
}

bool sPopupMenuCtrlParameter::HasSideBar( ) const
{
	return i2b( m_byStyle & CPE::PMS_SiderBar );
}

bool sPopupMenuCtrlParameter::IsFlat( ) const
{
	return i2b( m_byStyle & CPE::PMS_Flat );
}

void sPopupMenuCtrlParameter::SetRoundCorner( bool bAdd )
{
	if( bAdd )
	{
		m_byStyle |= CPE::PMS_RoundCorner;
	}
	else
	{
		m_byStyle &= ~CPE::PMS_RoundCorner;
	}
}

void sPopupMenuCtrlParameter::SetSideBar( bool bAdd )
{
	if( bAdd )
	{
		m_byStyle |= CPE::PMS_SiderBar;
	}
	else
	{
		m_byStyle &= ~CPE::PMS_SiderBar;
	}
}

void sPopupMenuCtrlParameter::SetFlat( bool bAdd )
{
	if( bAdd )
	{
		m_byStyle |= CPE::PMS_Flat;
	}
	else
	{
		m_byStyle &= ~CPE::PMS_Flat;
	}
}

void sPopupMenuCtrlParameter::SetStyle( BYTE byStyle )
{
	m_byStyle = 0;
}


}
