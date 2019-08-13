#include "stdafx.h"
#include "SpinCtrlSkin.h"
#include "ImageManager.h"
#include "utils.hpp"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
CSpinCtrlSkin::CSpinCtrlSkin( )
{

}

void CSpinCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRef* pBitmap = ImagePool( ).GetBitmap(
			TEXT("ui\\skin\\SpinBox.bmp") );
		const int nXBase = 0;
		const int nYBase = 0;
		int nXOffset = 0;
		int nYOffset = 0;
		const int nCX = 40;
		const int nCY = 40;
		m_pBmpUpArrow[CPE::SCBS_Normal] = Util::CreateSubBitmap( 
			pBitmap, nXOffset,nYOffset,nCX,nCY );
		m_pBmpUpArrow[CPE::SCBS_Hot] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpUpArrow[CPE::SCBS_Pressed] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpUpArrow[CPE::SCBS_Disabled] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		nXOffset = nXBase;
		nYOffset += nCY;
		m_pBmpDownArrow[CPE::SCBS_Normal] = Util::CreateSubBitmap( 
			pBitmap, nXOffset,nYOffset,nCX,nCY );
		m_pBmpDownArrow[CPE::SCBS_Hot] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpDownArrow[CPE::SCBS_Pressed] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpDownArrow[CPE::SCBS_Disabled] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		nXOffset = nXBase;
		nYOffset += nCY;
		m_pBmpLeftArrow[CPE::SCBS_Normal] = Util::CreateSubBitmap( 
			pBitmap, nXOffset,nYOffset,nCX,nCY );	
		m_pBmpLeftArrow[CPE::SCBS_Hot] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpLeftArrow[CPE::SCBS_Pressed] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpLeftArrow[CPE::SCBS_Disabled] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );

		nXOffset = nXBase;
		nYOffset += nCY;
		m_pBmpRightArrow[CPE::SCBS_Normal] = Util::CreateSubBitmap( 
			pBitmap, nXOffset,nYOffset,nCX,nCY );	
		m_pBmpRightArrow[CPE::SCBS_Hot] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpRightArrow[CPE::SCBS_Pressed] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		m_pBmpRightArrow[CPE::SCBS_Disabled] = Util::CreateSubBitmap( 
			pBitmap, nXOffset+=nCX,nYOffset,nCX,nCY );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpUpArrow[CPE::SCBS_Normal] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/up/background/normal"));
	m_pBmpUpArrow[CPE::SCBS_Hot] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/up/background/hot"));
	m_pBmpUpArrow[CPE::SCBS_Pressed] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/up/background/pressed"));
	m_pBmpUpArrow[CPE::SCBS_Disabled] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/up/background/disabled"));
	////////////////////////////////////
	m_pBmpDownArrow[CPE::SCBS_Normal] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/normal"));
	m_pBmpDownArrow[CPE::SCBS_Hot] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/hot"));
	m_pBmpDownArrow[CPE::SCBS_Pressed] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/pressed"));
	m_pBmpDownArrow[CPE::SCBS_Disabled] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/disabled"));
	/////////////////////////////////////
	m_pBmpLeftArrow[CPE::SCBS_Normal] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/normal"));	
	m_pBmpLeftArrow[CPE::SCBS_Hot] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/hot"));
	m_pBmpLeftArrow[CPE::SCBS_Pressed] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/pressed"));
	m_pBmpLeftArrow[CPE::SCBS_Disabled] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/down/background/disabled"));
	//////////////////////////////////////
	m_pBmpRightArrow[CPE::SCBS_Normal] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/right/background/normal"));
	m_pBmpRightArrow[CPE::SCBS_Hot] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/right/background/hot"));
	m_pBmpRightArrow[CPE::SCBS_Pressed] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/right/background/pressed"));
	m_pBmpRightArrow[CPE::SCBS_Disabled] = 
		pConfig ->GetBitmap( TEXT("spin/arrow/right/background/disabled"));
#endif
}

CSpinCtrlSkin::~CSpinCtrlSkin( )
{

}

/** 
 * @brief overide
 */
LPCTSTR  CSpinCtrlSkin::GetHwndClassName( )
{
	return TEXT("msctls_updown32");
}
		
/** 
 * @brief overide
 */
CSpinCtrlSkin::CParamReference* CSpinCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	CParamReference* pParam = new CParamReference;
	return pParam;
}
		
/** 
	* @brief overide
	*/
LRESULT	CSpinCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint();
		break;
	case WM_ERASEBKGND:
		return OnEraseBkgnd( HDC(wParam) );
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
		return OnPreviousWndProc( 
			GetCurHwnd(), nMsg, wParam, lParam );
		break;
	}
	return 0;
}
		
void CSpinCtrlSkin::OnPaint()
{
	/* 绘制 */
	DrawSpin( Util::CTempClientDC( GetCurHwnd() ) );
}

BOOL CSpinCtrlSkin::OnEraseBkgnd(HDC hDC)
{
	/* 擦除背景 */
	return TRUE;
}

void CSpinCtrlSkin::OnMouseMove(WPARAM wKeyType, const POINT& point)
{
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd( );
	bool bNeedRedraw = false;
	if(( p ->GetHotButton( ) == CPE::SCB_None) &&
		( (wKeyType & MK_LBUTTON) == 0) )
	{
		
		/* 左键按下 */
		if( p ->SetHotButton( HitTest(point) ) )
		{
			bNeedRedraw = true;
		}
		if( p ->SetPressedButton( CPE::SCB_None ) )
		{
			if( !bNeedRedraw )
			{
				bNeedRedraw = true;
			}
		}
		
		/* 追踪后续消息 */
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		TrackMouseEvent(&tme);
	}
	else if( i2b(wKeyType & MK_LBUTTON) )
	{
		
		/* 之前无按下的按键 */
		if( p ->SetHotButton( CPE::SCB_None ) )
		{
			bNeedRedraw = true;
		}
		if( p ->SetPressedButton( HitTest(point) ) )
		{
			if( !bNeedRedraw )
			{
				bNeedRedraw = true;
			}
		}
		
		/* 后续的消息追踪 */
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		TrackMouseEvent(&tme);
	}
	
	/* 重绘 */
	if( bNeedRedraw )
	{
		DrawSpin( Util::CTempClientDC( hWnd ) );
	}
}

void CSpinCtrlSkin::OnLButtonDown(WPARAM wKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	
	/* 设置按下按钮和焦点按钮 */
	bool bRet1 =  p ->SetPressedButton( HitTest(point) );
	bool bRet2 = p ->SetHotButton( CPE::SCB_None );
	if( bRet1 || bRet2 )
	{
		/* 变化则重绘 */
		DrawSpin( Util::CTempClientDC(GetCurHwnd()) );
	}
}

void CSpinCtrlSkin::OnLButtonUp(WPARAM wKeyType, const POINT& point)
{
	OnAutoDefaultWndProc( );
	CParamReference* p = GetCurParam( );
	
	/* 取消按下状态 */
	bool bRet1 =  p ->SetPressedButton( CPE::SCB_None );
	if( bRet1  )
	{
		DrawSpin( Util::CTempClientDC(GetCurHwnd()) );
	}
}

void CSpinCtrlSkin::OnMouseLeave()
{
	OnAutoDefaultWndProc( );
	CParamReference* p = GetCurParam( );
	
	/* 状态复位 */
	bool bRet1 =  p ->SetPressedButton( CPE::SCB_None );
	bool bRet2 = p ->SetHotButton( CPE::SCB_None );
	if( bRet1 || bRet2 )
	{
	/* 有变化则重绘 */
		DrawSpin( Util::CTempClientDC(GetCurHwnd()) );
	}
}

CPE::SpinCtrlButton CSpinCtrlSkin::HitTest( const POINT& point)
{
	HWND hWnd = GetCurHwnd();
	CRect rectClient;
	GetClientRect( hWnd, rectClient);
	CRect rectUp,rectDown;
	
	/* 计算上下（左右）2个按钮的坐标尺寸 */
	rectUp = rectClient;
	rectDown = rectClient;
	if( GetCurParam() ->IsVertical( ) )
	{//垂直情况
		rectUp.bottom = (rectClient.top + rectClient.bottom)/2;
		rectDown.top = (rectClient.top + rectClient.bottom)/2;
	}
	else
	{
	/* 水平情况 */
		rectUp.right = (rectClient.left + rectClient.right)/2;
		rectDown.left = (rectClient.left + rectClient.right)/2;
	}

	if( TRUE == rectUp.PtInRect(point))
	{
		/* 点击上（左）按钮 */
		return CPE::SCB_Up;
	}
	if( TRUE == rectDown.PtInRect(point))
	{
		/* 点击下（右）按钮 */
		return CPE::SCB_Down;
	}
	
	/* 无按钮点击 */
	return CPE::SCB_None;
}

void CSpinCtrlSkin::DrawSpin(HDC hDC)
{
	if( IsNull() )
	{
		return;
	}
	HWND hWnd = GetCurHwnd();
	CParamReference* p = GetCurParam( );

	CRect rectClient;
	GetClientRect(hWnd,&rectClient);
	rectClient.DeflateRect(2,0,1,0);

	CRect rectUp,rectDown;
	rectUp = rectClient;
	rectDown = rectClient;
	
	/* 焦点和按下的按钮 */
	CPE::SpinCtrlButton nHotButtonType = p ->GetHotButton();
	CPE::SpinCtrlButton nPressedButtonType = p ->GetPressedButton( );
	bool bIsDisabled = (TRUE != IsWindowEnabled(hWnd) );
	if(p ->IsVertical())
	{
		/* 垂直 */
		rectUp.bottom = (rectClient.top + rectClient.bottom)/2;
		rectDown.top = (rectClient.top + rectClient.bottom)/2;
		if(bIsDisabled )
		{
			
			/* 禁用 */
			DrawBmp( hDC, rectUp, m_pBmpUpArrow[CPE::SCBS_Disabled] );

			DrawBmp( hDC, rectDown, m_pBmpDownArrow[CPE::SCBS_Disabled] );
		}
		else
		{
			/* 根据状态绘制 */
			DrawBmp( hDC, rectUp, m_pBmpUpArrow[ 
				nHotButtonType==CPE::SCB_Up?CPE::SCBS_Hot:
					(nPressedButtonType==CPE::SCB_Up?CPE::SCBS_Pressed:CPE::SCBS_Normal )] );

			DrawBmp( hDC, rectDown, m_pBmpDownArrow[ 
				nHotButtonType==CPE::SCB_Down?CPE::SCBS_Hot:
					(nPressedButtonType==CPE::SCB_Down?CPE::SCBS_Pressed:CPE::SCBS_Normal )] );
		}
	
	}
	else
	{
		
		/* 水平 */
		rectUp.right = (rectClient.left + rectClient.right)/2;
		rectDown.left = (rectClient.left + rectClient.right)/2;		
		if(bIsDisabled )
		{
		/* 禁用 */
			DrawBmp( hDC, rectUp, m_pBmpUpArrow[CPE::SCBS_Disabled] );

			DrawBmp( hDC, rectDown, m_pBmpDownArrow[CPE::SCBS_Disabled] );
		}
		else
		{ 
			
			/* 非禁用：根据状态绘制 */
			DrawBmp( hDC, rectUp, m_pBmpLeftArrow[ 
				nHotButtonType==CPE::SCB_Left?CPE::SCBS_Hot:
					(nPressedButtonType==CPE::SCB_Left?CPE::SCBS_Pressed:CPE::SCBS_Normal )] );

			DrawBmp( hDC, rectDown, m_pBmpRightArrow[ 
				nHotButtonType==CPE::SCB_Right?CPE::SCBS_Hot:
					(nPressedButtonType==CPE::SCB_Right?CPE::SCBS_Pressed:CPE::SCBS_Normal )] );
		}
	}

}
CPE::SpinCtrlButton	sSpinCtrlParameter::GetPressedButton( ) const
{
	return  m_nPressedButton;
}

bool sSpinCtrlParameter::SetPressedButton( CPE::SpinCtrlButton nType )
{
	if( m_nPressedButton != nType )
	{
		m_nPressedButton = nType;
		return true;
	}
	return false;
}

CPE::SpinCtrlButton	sSpinCtrlParameter::GetHotButton( ) const
{
	return m_nHotButton;
}

bool sSpinCtrlParameter::SetHotButton( CPE::SpinCtrlButton nType )
{
	if( m_nHotButton != nType )
	{
		m_nHotButton = nType;
		return true;
	}
	return false;
}

bool sSpinCtrlParameter::IsVertical( ) const
{
	return m_bVertical;
}

void sSpinCtrlParameter::SetVertical( bool bNew )
{
	m_bVertical = bNew;
}

}