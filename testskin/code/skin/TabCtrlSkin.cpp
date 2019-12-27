#include "stdafx.h"
#include "TabCtrlSkin.h"
#include "GlobalSkinUtil.h"
#include "utils.hpp"
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
CTablCtrlSkin::CTablCtrlSkin( )
{

}

void CTablCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		Gdiplus::Image* pBitmap = ImagePool( ).GetImage( 
			TEXT("ui\\skin\\TabCtrl.bmp") );
		const int nStartPosX = 0;
		const int nStartPosY = 0;
		int nXOffset = nStartPosX;
		int nYOffset = nStartPosY;
		int nSize = 40;
		m_pBmpItem[CPE::TabIS_Normal] = Util::CreateSubImage(
			pBitmap, nXOffset,nYOffset,nSize,nSize );
		CImagePool( ).AddImage( _T("tab-item-normal"),
			m_pBmpItem[CPE::TabIS_Normal] );
		m_pBmpItem[CPE::TabIs_Hover] = Util::CreateSubImage(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		CImagePool( ).AddImage( _T("tab-item-hover"),
			m_pBmpItem[CPE::TabIs_Hover] );
		m_pBmpItem[CPE::TabIS_Pressed] = Util::CreateSubImage(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		CImagePool( ).AddImage( _T("tab-item-pressed"),
			m_pBmpItem[CPE::TabIS_Pressed] );
		m_pBmkBk = Util::CreateSubImage( 
			pBitmap, nXOffset = nStartPosX,nYOffset+= nSize,
			nSize*3,nSize );
		CImagePool( ).AddImage( _T("tab-bk"), m_pBmkBk );
		m_clrText[CPE::TabIS_Normal]  = RGB(0,0,0);
		m_clrText[CPE::TabIs_Hover]  = RGB(0,0,0);
		m_clrText[CPE::TabIS_Pressed] = RGB(0,0,0);
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpItem[CPE::TabIS_Normal]  =
		pConfig ->GetImage(TEXT("tab/item/background/normal") );
	m_pBmpItem[CPE::TabIs_Hover] = 
		pConfig ->GetImage(TEXT("tab/item/background/hover") );
	m_pBmpItem[CPE::TabIS_Pressed] = 
		pConfig ->GetImage(TEXT("tab/item/background/pressed") ) ;
	m_pBmkBk = pConfig ->GetImage(TEXT("tab/background") ) ;

	m_pTabRightBk = pConfig ->GetImage(TEXT("tab/tab-right-bk") ) ;
	m_clrText[CPE::TabIS_Normal]  =
		pConfig ->GetRGBColor(TEXT("tab/item/text/normal") );
	m_clrText[CPE::TabIs_Hover]  =
		pConfig ->GetRGBColor(TEXT("tab/item/text/hover") );
	m_clrText[CPE::TabIS_Pressed]  =
		pConfig ->GetRGBColor(TEXT("tab/item/text/pressed") );
#endif
}

CTablCtrlSkin::~CTablCtrlSkin( )
{

}

/** 
 * @brief override 控件的窗口类名称
 */
LPCTSTR CTablCtrlSkin::GetHwndClassName( )
{
	return _T("SysTabControl32");
}

/** 
 * @brief override	接管之前创建参数
 */
CTablCtrlSkin::CParamReference* CTablCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* p ( new CParamReference);
	
	/* 初始的按下项和焦点项 */
	p ->SetHotIndex( -1 );
	p ->SetPressedIndex( -1 );
	return p;
}

/** 
 * @brief override	控件消息处理
 */
LRESULT	CTablCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint( );
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(
			(UINT)wParam,
			CPoint( GET_X_LPARAM(lParam),
			GET_Y_LPARAM(lParam ) ) );
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(
			(UINT)wParam, 
			CPoint( GET_X_LPARAM(lParam ),
			GET_Y_LPARAM(lParam)  ) );
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(
			(UINT)wParam, 
			CPoint( GET_X_LPARAM(lParam ),
			GET_Y_LPARAM(lParam)  ) );
		break;
	case WM_MOUSELEAVE:
		OnMouseLeave( );
		break;
	default:
		return OnAutoDefaultWndProc( );
	}
	return 0;
}

void CTablCtrlSkin::OnPaint()
{
	if( IsNull() )
	{
		return;
	}
	Util::CTempPaintDC pdc( GetCurHwnd() );
	
	/* 使用同一的绘制 */
	DrawTab( pdc );
}

void CTablCtrlSkin::OnMouseMove(UINT nKeyType, const POINT& point)
{
	OnAutoDefaultWndProc();
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	if( i2b(nKeyType & MK_LBUTTON) )
	{		
		TRACKMOUSEEVENT tme;
		
		/* 按下发生变化 */
		p ->SetPressedIndex( HitTest(point) );
		p ->SetHotIndex( -1 );
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = hWnd;
		TrackMouseEvent(&tme);
	}
	else
	{
		
		/* 焦点发生变化 */
		p ->SetPressedIndex( -1 );
		p ->SetHotIndex( HitTest(point) );
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = hWnd;
		TrackMouseEvent(&tme);
	}
	DrawTab( Util::CTempWindowDC(hWnd) );
}

void CTablCtrlSkin::OnLButtonDown(UINT nKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	
	/* 按下项变化 */
	p ->SetPressedIndex( HitTest(point) );
	p ->SetHotIndex( -1 );
	DrawTab( Util::CTempWindowDC( GetCurHwnd() ) );
}

void CTablCtrlSkin::OnLButtonUp(UINT nKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	if( IsNull() )
	{
		return;
	}

	CParamReference* p = GetCurParam( );
	
	/* 焦点项变化 */
	p ->SetPressedIndex( -1 );
	p ->SetHotIndex( HitTest(point) );

	DrawTab( Util::CTempWindowDC(GetCurHwnd()) );
}

void CTablCtrlSkin::OnMouseLeave()
{
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	
	/* 状态复原 */
	p ->SetPressedIndex( -1 );
	p ->SetHotIndex( -1 );
	DrawTab( Util::CTempWindowDC(GetCurHwnd()) );
}


int CTablCtrlSkin::HitTest( const POINT& point)
{
	/* 系统默认的检测 */
	TCHITTESTINFO hti;
	hti.pt = point;
	return (int)::SendMessage(
		GetCurHwnd(),
		TCM_HITTEST, 0, (LPARAM)&hti );
}

void CTablCtrlSkin::DrawTab( HDC hdcSrc )
{
	if( IsNull() )
	{
		return;
	}
	
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd();
	CRect rtClient = Util::CTempAbsoluteWindowRect(hWnd);
	//GetClientRect( hWnd,rtClient);


	Util::CTempCompatibleDC tdc( hdcSrc, rtClient.Width(), rtClient.Height() );
	HDC hdc = tdc;

	CBrush brush( RGB(255,255,0) );
	FillRect( tdc, &rtClient, (HBRUSH)brush.GetSafeHandle() );
	// 绘制背景
	Util::DrawImage( tdc, m_pBmkBk, rtClient );
	/* 获取tab数目 */
	int nItemCount = (int)SendMessage( hWnd, TCM_GETITEMCOUNT, 0, 0L);
	if(nItemCount <= 0)
	{ 
		return;
	} 
	CRect rcItem;
	int nOldBkMode = SetBkMode( tdc, TRANSPARENT);
	
	/* 获取字体 */
	HFONT hFont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);
	HGDIOBJ hOldFont = SelectObject( tdc, hFont );

	const int nPressedIndex = p ->GetPressedIndex();
	const int nHotIndex = p ->GetHotIndex();
	int nSelected = (int)::SendMessage(hWnd, TCM_GETCURSEL, 0, 0L);
	const int nSpace = 5;
	for(int i = 0 ; i < nItemCount ; i++)
	{
		COLORREF clrOldColor = 0;
		/* 获取tab的尺寸信息 */
		SendMessage( hWnd, TCM_GETITEMRECT, i, (LPARAM)&rcItem );
		//rcItem.left += ( 0==i?0:nSpace);
		//rcItem.right += ( 0==i?0:nSpace);
		const int nXOffset = 0;//i * nSpace;
		rcItem.left += nXOffset;
		rcItem.right += nXOffset;
		if(nPressedIndex == i || nSelected == i )
		{
			
			/* 按下 */
	//		if( 0 != i )
			{ 
				DrawItemEntry(tdc,i,rcItem,CPE::TabIS_Pressed);
			}
			int nLeft = rcItem.CenterPoint().x;
			int nTop = rcItem.bottom-2;
			const int nWidth = 5;
			CPoint ptTriangle[] = 
			{
				CPoint( nLeft+nWidth*2, nTop ),
				CPoint( nLeft, nTop + nWidth * 17 /10 ),
				CPoint( nLeft - nWidth*2, nTop ),
				CPoint(  nLeft+nWidth*2, nTop )
			};

			HBRUSH hBrush = CreateSolidBrush(RGB(1,173,255) );
			HPEN hPen = (HPEN)GetStockObject( NULL_PEN );
			HGDIOBJ hOldPen = SelectObject( tdc, hPen );
			HGDIOBJ hOldBrush = SelectObject( tdc, hBrush );
			Polygon( tdc,ptTriangle, sizeof(ptTriangle)/sizeof(CPoint)  );
			SelectObject( tdc, hOldPen );
			SelectObject( tdc, hOldBrush );
			DeleteObject( hBrush );
			DeleteObject( hPen );
			
			clrOldColor = SetTextColor( tdc, m_clrText[CPE::TabIS_Pressed] );
		}
		else if(nHotIndex == i)
		{
			/* 鼠标经过 */
	//		if( 0 != i )
			{ 
				DrawItemEntry(tdc,i,rcItem,CPE::TabIs_Hover);
			}
			clrOldColor = SetTextColor( tdc, m_clrText[CPE::TabIs_Hover] );
		}
		else
		{
			/* 无操作 */
	//		if( 0 != i )
			{ 
				DrawItemEntry(tdc,i,rcItem,CPE::TabIS_Normal );
			}
			clrOldColor = SetTextColor( tdc, m_clrText[CPE::TabIS_Normal] );
		}
		TCHAR szItemText[256] = {0};
		TCITEM tim;
		tim.mask = TCIF_IMAGE | TCIF_STATE | TCIF_TEXT;
		tim.pszText = szItemText;
		tim.cchTextMax = sizeof(szItemText)/sizeof(TCHAR);
		
		/* 获取文本 */
		SendMessage(hWnd, TCM_GETITEM, i, (LPARAM)&tim);

		CRect rtText = rcItem;
		rtText.left = rtText.left/* +10*/;
		/* 绘制文本 */
		DrawText( tdc, szItemText,
			(int)_tcslen(szItemText),&rtText,
			DT_CENTER
			/*DT_RIGHT*/ | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );
		SetTextColor( tdc, clrOldColor );
	}

	ASSERT(rcItem.right < rtClient.right && rcItem.bottom > rcItem.top );
	Util::DrawImage( tdc, m_pTabRightBk,
		CRect(rcItem.right,rcItem.top, rtClient.right,
		rcItem.bottom ) );
	SetBkMode( tdc, nOldBkMode );
	SelectObject( tdc, hOldFont );
}

void CTablCtrlSkin::DrawItemEntry( HDC hdc, int nIndex, const CRect& rcItem, CPE::TabItemState nState)
{
	
	/* 根据状态绘制不同的背景图 */
	ASSERT( nState >= CPE::TabIS_Normal &&
		nState < CPE::TabIS_Size );

	Util::DrawImage( hdc, m_pBmpItem[nState], rcItem );
}

int	CTabCtrlSkinParameter::GetPressedIndex( ) const
{
	return m_nPressedIndex;
}

void CTabCtrlSkinParameter::SetPressedIndex( int nIndex )
{
	m_nPressedIndex = nIndex;
}

int CTabCtrlSkinParameter::GetHotIndex( ) const
{
	return m_nHotIndex;
}

void CTabCtrlSkinParameter::SetHotIndex( int nIndex )
{
	m_nHotIndex = nIndex;
}


}