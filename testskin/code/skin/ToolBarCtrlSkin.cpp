#include "stdafx.h"
#include "ToolBarCtrlSkin.h"
#include "utils.hpp"
#include "GlobalSkinUtil.h"
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
CToolBarCtrlSkin::CToolBarCtrlSkin( )
{

}

void CToolBarCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRef* pBitmap = ImagePool( ).GetBitmap(
			TEXT("ui\\skin\\ToolBar.bmp") );
		const int nBaseX = 0;
		const int nBaseY = 0;
		int nXOffset = 0;
		int nYOffset = 0;
		int nSize = 40;
		m_pBmpItemBk[CPE::TBIS_Normal] = Util::CreateSubBitmap(
			pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_pBmpItemBk[CPE::TBIS_Hover] = Util::CreateSubBitmap(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_pBmpItemBk[CPE::TBIS_Pressed] = Util::CreateSubBitmap(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_pBmpItemBk[CPE::TBIS_Disabled] = Util::CreateSubBitmap(
			pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_pBmpBk =  Util::CreateSubBitmap(
			pBitmap, nBaseX, nBaseY+nSize,nSize*4,nSize );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpItemBk[CPE::TBIS_Normal] = pConfig ->GetBitmap(
		TEXT("toolbar/item/background/normal") );
	m_pBmpItemBk[CPE::TBIS_Hover] = pConfig ->GetBitmap(
		TEXT("toolbar/item/background/hover") );
	m_pBmpItemBk[CPE::TBIS_Pressed] = pConfig ->GetBitmap(
		TEXT("toolbar/item/background/pressed") );
	m_pBmpItemBk[CPE::TBIS_Disabled] = pConfig ->GetBitmap(
		TEXT("toolbar/item/background/disabled") );
	m_pBmpBk =  pConfig ->GetBitmap( 
		TEXT("toolbar/background") );
#endif

}

CToolBarCtrlSkin::~CToolBarCtrlSkin( )
{

}
/** 
 * @brief overide
 */
LPCTSTR CToolBarCtrlSkin::GetHwndClassName( )
{
	return TEXT("ToolbarWindow32");
}
		
/** 
 * @brief overide
 */
CToolBarCtrlSkin::CParamReference* 
	CToolBarCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* pParam = new CParamReference;

	return pParam;
}
		
/** 
 * @brief overide
 */
LRESULT	CToolBarCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch(nMsg)
	{
	case WM_PAINT:
		OnPaint();
		break;
	case WM_NCPAINT:
		OnNcPaint( HRGN(wParam) );
		break;
	case WM_MOUSEMOVE:
		OnMouseMove( wParam, Lparam2Point(lParam) );
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown( wParam, Lparam2Point(lParam) );
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(wParam, Lparam2Point(lParam) );
		break;
	case WM_MOUSELEAVE:
		OnMouseLeave();
		break;
	default:
		return OnAutoDefaultWndProc();
		break;
	}
	return 0;
}
void CToolBarCtrlSkin::OnPaint()
{
	
	/* ���� */
	DrawToolBar( Util::CTempPaintDC( GetCurHwnd() ) );
}

void CToolBarCtrlSkin::OnNcPaint(HRGN rgn1)
{
	if( IsNull() )
	{
		return;
	}
	HWND hWnd = GetCurHwnd();
	Util::CTempWindowDC wdc( hWnd );
	CRect rectWindow = Util::CTempAbsoluteWindowRect(hWnd);

	HWND hWndParent = ::GetParent(hWnd);
	if( NULL != hWndParent )
	{
		CRect rectParent;
		::GetWindowRect( hWndParent,rectParent );
		rectWindow.right = rectParent.right;
	}
	
	/* ���Ʊ��� */
	DrawBmp( wdc, rectWindow, m_pBmpBk );
	
	/* �������� */
	DrawToolBar( Util::CTempClientDC(hWnd) );
}

void CToolBarCtrlSkin::OnMouseMove(WPARAM wKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	/* ������� */
	if( i2b(wKeyType & MK_LBUTTON) )
	{
		TRACKMOUSEEVENT tme;
		
		/* ���ð����� */
		p ->SetPressedItem( HitTest(point) );
		p ->SetHotItem( -1 );
		
		/* ׷�ٺ�����Ϣ */
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = hWnd;
		TrackMouseEvent(&tme);
	}
	else
	{
		TRACKMOUSEEVENT tme;
		/* ����������ֻ�ᵼ�µ�ǰ������仯 */
		p ->SetHotItem( HitTest(point) );
		p ->SetPressedItem( -1 );
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = hWnd;
		TrackMouseEvent(&tme);
	}
	
	/* ���� */
	DrawToolBar( Util::CTempClientDC(GetCurHwnd())  );
}

void CToolBarCtrlSkin::OnLButtonDown(WPARAM wKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	if(IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	
	/* ��ǰ��������仯 */
	p ->SetPressedItem( HitTest(point) );
	p ->SetHotItem( -1 );
	DrawToolBar( Util::CTempClientDC(GetCurHwnd()) );
}

void CToolBarCtrlSkin::OnLButtonUp(WPARAM wKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	if(IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	
	/* ��ǰ�����ʧ����������� */
	p ->SetPressedItem( -1 );
	p ->SetHotItem( HitTest(point) );
	DrawToolBar( Util::CTempClientDC(GetCurHwnd()) );
}

void CToolBarCtrlSkin::OnMouseLeave()
{
	if(IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	
	/* �ָ�Ĭ��״̬ */
	p ->SetPressedItem( -1 );
	p ->SetHotItem( -1 );
	DrawToolBar( Util::CTempClientDC(GetCurHwnd()) );
}

int CToolBarCtrlSkin::HitTest(const POINT& point)
{
	
	/* ʹ��ϵͳ�ļ�� */
	return (int)SendMessage(
		GetCurHwnd(), TB_HITTEST, 0, (LPARAM)&point );
}

void CToolBarCtrlSkin::DrawToolBar(HDC hDC )
{
	HWND hWnd = GetCurHwnd();
	CParamReference* p = GetCurParam( );
	CRect rectClient;
	GetClientRect( hWnd, &rectClient );

	Util::CTempCompatibleDC tdc(
		hDC,rectClient.Width(),rectClient.Height() );
	
	/* ��ȡ���� */
	HFONT hFont = (HFONT)SendMessage( hWnd, WM_GETFONT, 0,0 );
	HGDIOBJ hOldFont = SelectObject( tdc, hFont );

	// ��ȡ��ť��Ŀ
	int nItemCount = (int)SendMessage( hWnd, TB_BUTTONCOUNT, 0, 0);
	if(nItemCount <= 0)
	{ 
		return;
	}
	
	/* ���Ʊ��� */
	DrawBmp( tdc, rectClient, m_pBmpBk );
	
	CRect rectItem;
	DWORD dwStyle = GetWindowLong( hWnd, GWL_STYLE );
	int OldBkMode = SetBkMode(tdc, TRANSPARENT);
	
	/* ��ȡͼ���б�� */
	HIMAGELIST hImageList = (HIMAGELIST)SendMessage(
		hWnd, TB_GETIMAGELIST, 0, 0L);
	HIMAGELIST hHotImageList =(HIMAGELIST)SendMessage(
		hWnd, TB_GETHOTIMAGELIST, 0, 0);
	HIMAGELIST hDisabledImageList= (HIMAGELIST)SendMessage(
		hWnd, TB_GETDISABLEDIMAGELIST, 0, 0);

	TBBUTTON tbb;
	const int nPressedIndex = p ->GetPressedItem();
	const int nHotIndex = p ->GetHotItem();
	for(int i = 0 ; i < nItemCount ; i++)
	{
		
		/* ��ȡÿһ����ť����ϸ�����Լ�λ����Ϣ */
		memset( &tbb, 0, sizeof(tbb) );
		SendMessage( hWnd, TB_GETBUTTON, i, (LPARAM)&tbb );
		SendMessage( hWnd, TB_GETITEMRECT, i, (LPARAM)&rectItem );
		int nState = SendMessage( hWnd, TB_GETSTATE, tbb.idCommand, 0L);
		//TRACE("[%02d]rect:(%d-%d,%d-%d)\n",
		//	i,
		//	rectItem.top, rectItem.left,
		//	rectItem.bottom, rectItem.right );
		if( (nState & TBSTATE_ENABLED)  == TBSTATE_ENABLED)
		{
			if(nPressedIndex == i)
			{ 
			/* ��ǰ������ */
				DrawItemEntry(tdc, rectItem,CPE::TBIS_Pressed );
			}
			else if(nHotIndex == i)
			{
			/* ��ǰѡ���� */
				DrawItemEntry(tdc, rectItem,CPE::TBIS_Hover );
			}
			else
			{
			/* �޲����� */
				DrawItemEntry(tdc, rectItem,CPE::TBIS_Normal );	
			}
		}
		else
		{
			
			/* ���� */
			DrawItemEntry( tdc, rectItem, CPE::TBIS_Disabled );
		}

		if( i2b( tbb.fsStyle & TBSTYLE_SEP)&& 0 == tbb.idCommand )
		{ //�ָ���
			continue;
		}

		
		/* �������ͼ�꣬�����ͼ�� */
		HICON hIcon = AfxImageList_ExtractIcon(NULL, hImageList, tbb.iBitmap);

		CSize szExtent;
		if ( NULL != hIcon )
		{
			ICONINFO iconinfo;
			/* ͼ����ϸ��Ϣ */
			if ( TRUE == GetIconInfo(hIcon,&iconinfo) )
			{
				BITMAP bmp;
				if ( 0 != GetObject(iconinfo.hbmMask, sizeof(bmp), &bmp) )
				{
					
					/* ͼ����� */
					szExtent.cx = (int)bmp.bmWidth;
					szExtent.cy = (int)bmp.bmHeight;
					if ( NULL != iconinfo.hbmColor )
					{
						szExtent.cy /= 2;
					}
				}
				if ( NULL != iconinfo.hbmMask )
				{
					::DeleteObject(iconinfo.hbmMask);
				}
				if (iconinfo.hbmColor)
				{
					::DeleteObject(iconinfo.hbmColor);
				}
			}
		}
		
		/* �Ƿ�����Ч���ı� */
		bool bHasText = ( NULL != tbb.iString && tbb.iString != -1 );
		int x = rectItem.left + rectItem.Width() /2 -(szExtent.cx+1)/2;
		int y = /*( bHasText?*/
			(rectItem.top +3)/*:
			(rectItem.top +rectItem.Height() /2 -(szExtent.cy+1)/2) )*/;

		if(  (!i2b( tbb.fsStyle & TBSTYLE_SEP) || 0 == tbb.idCommand )  &&
			NULL != hImageList )
		{
			
			/* ���ƾ��е�ͼ�� */
			AfxImageList_Draw(
			hImageList,
			tbb.iBitmap,
			tdc,
			x,y,
			ILD_TRANSPARENT);
		}


		if ( bHasText )
		{
			/* �������� */
			CRect rectText = rectItem;
			rectText.top = y + szExtent.cy;
			if( FALSE == IS_INTRESOURCE( tbb.iString ) )
			{
				DrawTextW( tdc, (LPCWSTR)tbb.iString,-1,rectText,
					DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_NOPREFIX);
			}
			else
			{
				TCHAR szBuf[256] = {0};
				LoadStringW( NULL, tbb.iString, szBuf,
					sizeof(szBuf) / sizeof(TCHAR ) );

				DrawText( tdc, szBuf,-1,rectText,
					DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_NOPREFIX);
			}

		}
	}
	SelectObject( tdc, hOldFont );
}

void CToolBarCtrlSkin::DrawItemEntry( HDC hDC, const CRect& rectItem, 
	CPE::ToolBarItemState nState)
{
	
	/* ����״ֵ̬��������Ӧ�ı��� */
	ASSERT(nState >= CPE::TBIS_Normal && 
		nState < CPE::TBIS_Size );
	DrawBmp( hDC, rectItem, m_pBmpItemBk[nState] );
}

int CToolBarCtrlParameter::GetPressedItem( ) const
{
	return m_nPressedItem;
}
void CToolBarCtrlParameter::SetPressedItem( int nIndex )
{
	m_nPressedItem = nIndex;
}

int CToolBarCtrlParameter::GetHotItem( ) const
{
	return m_nHotItem;
}

void CToolBarCtrlParameter::SetHotItem( int nIndex )
{
	m_nHotItem = nIndex;
}


}

