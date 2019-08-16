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
		CBitmapRef* pBitmap = ImagePool( ).GetBitmap( 
			TEXT("ui\\skin\\TabCtrl.bmp") );
		const int nStartPosX = 0;
		const int nStartPosY = 0;
		int nXOffset = nStartPosX;
		int nYOffset = nStartPosY;
		int nSize = 40;
		m_pBmpItem[CPE::TabIS_Normal] = Util::CreateSubBitmap(
			pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_pBmpItem[CPE::TabIs_Hover] = Util::CreateSubBitmap(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_pBmpItem[CPE::TabIS_Pressed] = Util::CreateSubBitmap(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_pBmkBk = Util::CreateSubBitmap( 
			pBitmap, nXOffset = nStartPosX,nYOffset+= nSize,
			nSize*3,nSize );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpItem[CPE::TabIS_Normal]  =
		pConfig ->GetBitmap(TEXT("tab/item/background/normal") );
	m_pBmpItem[CPE::TabIs_Hover] = 
		pConfig ->GetBitmap(TEXT("tab/item/background/hover") );
	m_pBmpItem[CPE::TabIS_Pressed] = 
		pConfig ->GetBitmap(TEXT("tab/item/background/pressed") ) ;
	m_pBmkBk = pConfig ->GetBitmap(TEXT("tab/background") ) ;
#endif
}

CTablCtrlSkin::~CTablCtrlSkin( )
{

}

/** 
 * @brief override �ؼ��Ĵ���������
 */
LPCTSTR CTablCtrlSkin::GetHwndClassName( )
{
	return _T("SysTabControl32");
}

/** 
 * @brief override	�ӹ�֮ǰ��������
 */
CTablCtrlSkin::CParamReference* CTablCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* p ( new CParamReference);
	
	/* ��ʼ�İ�����ͽ����� */
	p ->SetHotIndex( -1 );
	p ->SetPressedIndex( -1 );
	return p;
}

/** 
 * @brief override	�ؼ���Ϣ����
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
	
	/* ʹ��ͬһ�Ļ��� */
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
		
		/* ���·����仯 */
		p ->SetPressedIndex( HitTest(point) );
		p ->SetHotIndex( -1 );
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = hWnd;
		TrackMouseEvent(&tme);
	}
	else
	{
		
		/* ���㷢���仯 */
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
	
	/* ������仯 */
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
	
	/* ������仯 */
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
	
	/* ״̬��ԭ */
	p ->SetPressedIndex( -1 );
	p ->SetHotIndex( -1 );
	DrawTab( Util::CTempWindowDC(GetCurHwnd()) );
}


int CTablCtrlSkin::HitTest( const POINT& point)
{
	/* ϵͳĬ�ϵļ�� */
	TCHITTESTINFO hti;
	hti.pt = point;
	return (int)::SendMessage(m_hWnd, TCM_HITTEST, 0, (LPARAM)&hti );
}

void CTablCtrlSkin::DrawTab( HDC hdc )
{
	if( IsNull() )
	{
		return;
	}
	
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd();
	CRect rtClient;
	GetClientRect( hWnd,rtClient);

	/* ��ȡtab��Ŀ */
	int nItemCount = (int)SendMessage( hWnd, TCM_GETITEMCOUNT, 0, 0L);
	if(nItemCount <= 0)
	{ 
		return;
	} 
	// ���Ʊ���
	DrawBmp( hdc, rtClient, m_pBmkBk );
	CRect rcItem;
	DWORD dwStyle = GetWindowLong( hWnd, GWL_STYLE );
	int nOldBkMode = SetBkMode( hdc, TRANSPARENT);
	
	/* ��ȡ���� */
	HFONT hFont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);
	HGDIOBJ hOldFont = SelectObject( hdc, hFont );

	const int nPressedIndex = p ->GetPressedIndex();
	const int nHotIndex = p ->GetHotIndex();
	
	for(int i = 0 ; i < nItemCount ; i++)
	{
		
		/* ��ȡtab�ĳߴ���Ϣ */
		SendMessage( hWnd, TCM_GETITEMRECT, i, (LPARAM)&rcItem );
		if(nPressedIndex == i)
		{
			
			/* ���� */
			DrawItemEntry(hdc,i,rcItem,CPE::TabIS_Pressed);
		}
		else if(nHotIndex == i)
		{
			/* ��꾭�� */
			DrawItemEntry(hdc,i,rcItem,CPE::TabIs_Hover);
		}
		else
		{
			/* �޲��� */
			DrawItemEntry(hdc,i,rcItem,CPE::TabIS_Normal );
		}
		TCHAR szItemText[256] = {0};
		TCITEM tim;
		tim.mask = TCIF_IMAGE | TCIF_STATE | TCIF_TEXT;
		tim.pszText = szItemText;
		tim.cchTextMax = sizeof(szItemText)/sizeof(TCHAR);
		
		/* ��ȡ�ı� */
		SendMessage(m_hWnd, TCM_GETITEM, i, (LPARAM)&tim);

		CRect rtText = rcItem;
		rtText.left = rtText.left +3;
		
		/* �����ı� */
		DrawText( hdc, szItemText,
			(int)_tcslen(szItemText),&rtText,
			DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );
	}
	SetBkMode( hdc, nOldBkMode );
	SelectObject( hdc, hOldFont );
}

void CTablCtrlSkin::DrawItemEntry( HDC hdc, int nIndex, const CRect& rcItem, CPE::TabItemState nState)
{
	
	/* ����״̬���Ʋ�ͬ�ı���ͼ */
	ASSERT( nState >= CPE::TabIS_Normal &&
		nState < CPE::TabIS_Size );
	DrawBmp( hdc, rcItem, m_pBmpItem[nState] );
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