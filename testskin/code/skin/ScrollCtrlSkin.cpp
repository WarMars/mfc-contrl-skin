#include "stdafx.h"
#include "ScrollCtrlSkin.h"
#include "GlobalSkinUtil.h"
#include "utils.hpp"
#include "ScrollBarCtrlSkin.h"

namespace GlobalSkin
{
	
	CScrollCtrlSkin::CScrollCtrlSkin(void)
	{

	}
	

	void CScrollCtrlSkin::LoadSkin( const CSkinConfig* /*pConfig*/ )
	{

	}

	/** 
	 * @brief 获取当前的窗口类名
	 */
	LPCTSTR CScrollCtrlSkin::GetHwndClassName( )
	{
		return TEXT("ScrollBar");
	}

	/** 
	 * @brief 接管控件皮肤之前
	 */
	CScrollCtrlSkin::CParamReference* CScrollCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
	{
		CParamReference* pParam = new CParamReference;
		long lStyle = GetWindowLong( hWnd, GWL_STYLE );
		pParam ->SetVScroll( (lStyle & SBS_VERT) == SBS_VERT );
		DynamicParam::CScrollBarCtrlParameterRef* pScrollParam = 
			new DynamicParam::CScrollBarCtrlParameterRef;

		/* 获取水平滚动条信息 */
		pScrollParam ->m_hBar.nArrowState1 = CPE::SBS_Normal;
		pScrollParam ->m_hBar.nArrowState2 = CPE::SBS_Normal;
		pScrollParam ->m_hBar.nThumbState = CPE::SBS_Normal;

		SCROLLINFO * pScrollInfo = &pScrollParam ->m_hBar.sysInfo;
		pScrollInfo ->cbSize = sizeof(SCROLLINFO);
		pScrollInfo ->fMask  = SIF_ALL;
		GetScrollInfo( hWnd, SB_CTL,  pScrollInfo );


		/* 垂直滚动条信息 */
		pScrollParam ->m_vBar.nArrowState1 = CPE::SBS_Normal;
		pScrollParam ->m_vBar.nArrowState2 = CPE::SBS_Normal;
		pScrollParam ->m_vBar.nThumbState = CPE::SBS_Normal;
		pScrollInfo = &pScrollParam ->m_vBar.sysInfo;
		pScrollInfo ->cbSize = sizeof(SCROLLINFO);
		pScrollInfo ->fMask  = SIF_ALL;
		GetScrollInfo( hWnd, SB_CTL,  pScrollInfo );
		pScrollParam ->m_hBar.bVisible = !pParam ->IsVScroll( );
		pScrollParam ->m_vBar.bVisible = pParam ->IsVScroll( );
		pParam ->SetScrollParam( pScrollParam );
		return pParam;
	}

	/** 
	 * @brief 消息处理过程
	 */
	LRESULT CScrollCtrlSkin::OnWndProc(UINT nMsg,WPARAM wParam,LPARAM lParam )
	{
		switch( nMsg )
		{
		case WM_MOUSEMOVE:
			OnMouseMove( (UINT)wParam , Lparam2Point( lParam) );
			break;
		case WM_LBUTTONDOWN:
			OnLButtonDown( (UINT)wParam , Lparam2Point( lParam) );
			break;
		case WM_LBUTTONUP:
			OnLButtonUp( (UINT)wParam , Lparam2Point( lParam) );
			break;
		case WM_LBUTTONDBLCLK:
			OnLButtonDblClk( (UINT)wParam , Lparam2Point( lParam) );
			break;
		case WM_MOUSELEAVE:
			OnMouseLeave();
			break;
		case WM_PAINT:
			OnPaint();
			break;
		default:
			return OnPreviousWndProc( GetCurHwnd(), nMsg, wParam, lParam );
		}
		return 0;
	}

	void CScrollCtrlSkin::OnMouseMove(UINT nFlags, const POINT& point)
	{
		OnAutoDefaultWndProc( );

		HWND hWnd = GetCurHwnd( );
		CParamReference* p = GetCurParam( );

		RECT rtClient;
		GetClientRect( hWnd, &rtClient );
		if( p ->IsVScroll() )
		{
			CPE::ScrollBarHitTest test =  
				GetScrollBarCtrlSkin().ScrollHitTest( hWnd,SB_CTL,point,FALSE);
			DynamicParam::CScrollBarBasic& scrollParam = p ->GetScrollParam()->GetVBar();
			if(test == CPE::SBHT_TopArrow)
			{
				scrollParam.SetArrowState1( CPE::SBS_Hover );
				scrollParam.SetArrowState2( CPE::SBS_Normal );
				scrollParam.SetThumbState( CPE::SBS_Normal );
				DrawVScrollBar( Util::CTempWindowDC(hWnd) );
			}
			else if(test == CPE::SBHT_BottomArrow)
			{
				scrollParam.SetArrowState1( CPE::SBS_Normal );
				scrollParam.SetArrowState2( CPE::SBS_Hover );
				scrollParam.SetThumbState( CPE::SBS_Normal );
				DrawVScrollBar( Util::CTempWindowDC(hWnd) );
			}
			else if(test == CPE::SBHT_Thumb)
			{
				scrollParam.SetArrowState1( CPE::SBS_Normal );
				scrollParam.SetArrowState2( CPE::SBS_Normal );
				scrollParam.SetThumbState( CPE::SBS_Hover );
				DrawVScrollBar( Util::CTempWindowDC(hWnd) );
			}
			else
			{
				scrollParam.SetArrowState1( CPE::SBS_Normal );
				scrollParam.SetArrowState2( CPE::SBS_Normal );
				scrollParam.SetThumbState( CPE::SBS_Normal );
				DrawVScrollBar( Util::CTempWindowDC(hWnd) );
			}
		}
		else
		{
			CPE::ScrollBarHitTest test =
				GetScrollBarCtrlSkin().ScrollHitTest( hWnd,SB_CTL,point,FALSE);

			DynamicParam::CScrollBarBasic& scrollParam = p ->GetScrollParam()->GetHBar();
			if(test == CPE::SBHT_TopArrow)
			{
				scrollParam.SetArrowState1( CPE::SBS_Hover );
				scrollParam.SetArrowState2( CPE::SBS_Normal );
				scrollParam.SetThumbState( CPE::SBS_Normal );
				DrawHScrollBar( Util::CTempWindowDC(hWnd) );
			}
			else if(test == CPE::SBHT_BottomArrow)
			{
				scrollParam.SetArrowState1( CPE::SBS_Normal );
				scrollParam.SetArrowState2( CPE::SBS_Hover );
				scrollParam.SetThumbState( CPE::SBS_Normal );
				DrawHScrollBar( Util::CTempWindowDC(hWnd) );
			}
			else if(test == CPE::SBHT_Thumb)
			{
				scrollParam.SetArrowState1( CPE::SBS_Normal );
				scrollParam.SetArrowState2( CPE::SBS_Normal );
				scrollParam.SetThumbState( CPE::SBS_Hover );
				DrawHScrollBar( Util::CTempWindowDC(hWnd) );
			}
			else
			{
				scrollParam.SetArrowState1( CPE::SBS_Normal );
				scrollParam.SetArrowState2( CPE::SBS_Normal );
				scrollParam.SetThumbState( CPE::SBS_Normal );
				DrawHScrollBar( Util::CTempWindowDC(hWnd) );
			}
		}
		if(PtInRect(&rtClient,point) && ((nFlags & MK_LBUTTON) == 0) )
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);
		}
	}

	void CScrollCtrlSkin::OnLButtonDown(UINT nFlags, const POINT& point)
	{
		GetScrollBarCtrlSkin().TrackScrollBar(
			GetCurHwnd(),GetCurParam()->GetScrollParam(), SB_CTL,point );
	}

	void CScrollCtrlSkin::OnLButtonUp(UINT nFlags, const POINT& point)
	{
		OnAutoDefaultWndProc( );
	}

	void CScrollCtrlSkin::OnLButtonDblClk(UINT nFlags, const POINT& point)
	{
		OnLButtonDown(nFlags,point);
	}

	void CScrollCtrlSkin::OnMouseLeave()
	{
		CParamReference* p = GetCurParam();
		if( GetCurParam() ->IsVScroll() )
		{
			DynamicParam::CScrollBarBasic& scrollParam =
				p ->GetScrollParam( ) ->GetVBar();
			scrollParam.SetArrowState1( CPE::SBS_Normal );
			scrollParam.SetArrowState2( CPE::SBS_Normal );
			scrollParam.SetThumbState( CPE::SBS_Normal );
			DrawVScrollBar( Util::CTempWindowDC(GetCurHwnd()) );
		}
		else
		{
			DynamicParam::CScrollBarBasic& scrollParam =
				p ->GetScrollParam( ) ->GetHBar();
			scrollParam.SetArrowState1( CPE::SBS_Normal );
			scrollParam.SetArrowState2( CPE::SBS_Normal );
			scrollParam.SetThumbState( CPE::SBS_Normal );
			DrawHScrollBar( Util::CTempWindowDC(GetCurHwnd()) );
		}

	}

	void CScrollCtrlSkin::OnPaint()
	{
		if( GetCurParam() ->IsVScroll() )
		{
			DrawVScrollBar( Util::CTempPaintDC( GetCurHwnd() ) );
		}
		else
		{
			DrawHScrollBar( Util::CTempPaintDC( GetCurHwnd() ) );
		}
	}

	void CScrollCtrlSkin::DrawHScrollBar( HDC hDC )
	{
		HWND hWnd = GetCurHwnd( );
		CParamReference* p = GetCurParam( );
		const CRect& rtWindow = Util::CTempRelativeWindowRect(hWnd);
		CRect rtPos;
		int nArrowSize;
		int nThumbSize;
		int nThumbPos;

		DynamicParam::GetScrollRect(hWnd,
			SB_CTL,&rtPos,&nArrowSize,&nThumbSize,&nThumbPos );
		Util::CTempCompatibleDC tdc( hDC, rtPos.Width(), rtPos.Height() );
		HDC hDrawDC = tdc;
		DynamicParam::CScrollBarCtrlSkin& scrollBarCtrlSkin = GetScrollBarCtrlSkin( );
		DynamicParam::CScrollBarBasic& hBar = p ->GetScrollParam() ->GetHBar();
		scrollBarCtrlSkin.DrawHBackground( hDrawDC, rtPos );
		scrollBarCtrlSkin.DrawHLeftArrow( hDrawDC,
			CRect(rtPos.left,rtPos.top,rtPos.left + nArrowSize,rtPos.bottom),hBar.GetArrowState1() );
		scrollBarCtrlSkin.DrawHRightArrow( hDrawDC,
			CRect(rtPos.right - nArrowSize,rtPos.top,rtPos.right,rtPos.bottom),hBar.GetArrowState2() );
		if( 0 != nThumbPos && 0!= nThumbSize )
		{
			scrollBarCtrlSkin.DrawHThumb( hDrawDC,
				CRect(rtPos.left + nThumbPos,rtPos.top,rtPos.left +nThumbPos + nThumbSize,rtPos.bottom),
				hBar.GetThumbState() );
		}
	}

	void CScrollCtrlSkin::DrawVScrollBar( HDC hDC )
	{
		HWND hWnd = GetCurHwnd( );
		CParamReference* p = GetCurParam( );
		const CRect& rtWindow = Util::CTempRelativeWindowRect(hWnd);
		CRect rtPos;
		int nArrowSize;
		int nThumbSize;
		int nThumbPos;

		DynamicParam::GetScrollRect( hWnd,
			SB_CTL,&rtPos,&nArrowSize,&nThumbSize,&nThumbPos );
		DynamicParam::CScrollBarCtrlSkin& scrollBarCtrlSkin = GetScrollBarCtrlSkin( );

		Util::CTempCompatibleDC tdc( hDC, rtPos.Width(), rtPos.Height() );
		HDC hDrawDC = tdc;
		DynamicParam::CScrollBarBasic& vBar = p ->GetScrollParam() ->GetHBar();
		scrollBarCtrlSkin.DrawVBackground( hDrawDC,rtPos);
		scrollBarCtrlSkin.DrawVTopArrow( hDrawDC,
			CRect(rtPos.left,rtPos.top,rtPos.right ,rtPos.top + nArrowSize),vBar.GetArrowState1() );
		scrollBarCtrlSkin.DrawVBotArrow( hDrawDC,
			CRect(rtPos.left,rtPos.bottom - nArrowSize,rtPos.right,rtPos.bottom),vBar.GetArrowState2() );
		if( 0 != nThumbPos && 0 != nThumbSize )
		{
			scrollBarCtrlSkin.DrawVThumb( hDrawDC,
				CRect(rtPos.left,rtPos.top +nThumbPos,rtPos.right ,rtPos.top + +nThumbPos + nThumbSize),
				vBar.GetThumbState() );
		}
	}


	void CScrollCtrlParameter::SetScrollParam( DynamicParam::CScrollBarCtrlParameterRefPtr pParam )
	{
		m_pParam = pParam;
	}

	DynamicParam::CScrollBarCtrlParameterRefPtr CScrollCtrlParameter::GetScrollParam( ) const
	{
		return m_pParam;
	}


	bool CScrollCtrlParameter::SetVScroll( bool bVScroll )
	{
		if( bVScroll != m_bVScroll )
		{
			m_bVScroll = bVScroll;
			return true;
		}
		return false;
	}

	bool CScrollCtrlParameter::IsVScroll( ) const
	{
		return m_bVScroll;
	}

}
