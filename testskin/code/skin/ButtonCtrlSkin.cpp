#include "StdAfx.h"
#include "ButtonCtrlSkin.h"
namespace GlobalSkin
{ 

bool CButtonCtrlSkin::SetState(int &nState, int nSet, bool bIsSet )
{
	int nOldState = nState;
	return ( nOldState != ( (bIsSet) ? (nState |= nSet) : 
		(nState &= ~nSet) ) );
}

/** 
 * @brief 获取当前的窗口类名
 */
LPCTSTR CButtonCtrlSkin::GetHwndClassName( )
{
	return TEXT("Button");
}

/** 
 * @brief 接管控件皮肤之前
 */
CButtonCtrlSkin::CParamReference* CButtonCtrlSkin::OnPreTakeOverSkin( HWND hWnd )
{
	DWORD style     = GetWindowLong( hWnd, GWL_STYLE );
	DWORD exstyle	= GetWindowLong( hWnd, GWL_EXSTYLE );
	if( !OnHandleStyleType( style, exstyle ) )
	{
		return NULL;
	}
	// 创建按钮状态数据
	CParamReference* pStatus = new CParamReference;
	pStatus ->m_nID = ::GetDlgCtrlID(hWnd);
	pStatus ->m_nButtonState = 0;
	pStatus ->m_CaptureState = CButtonCtrlStatus::NO_CAPTURE_OR_UP_RELEASE;
	// 获取初始按钮状态
	if(style & WS_DISABLED)
	{
		SetState(
			pStatus ->m_nButtonState, 
			CButtonCtrlStatus::BUTTON_DISABLED );
	}
	pStatus ->m_bIcon = style & BS_ICON;
	DWORD dwState = (LONG) SendMessage(hWnd, BM_GETCHECK, 0, 0);
	
	SetState( pStatus ->m_nButtonState, 
			CParamReference::BUTTON_CHECKED, 
			BST_CHECKED == dwState );
	SetState( pStatus ->m_nButtonState,
			CParamReference::BUTTON_INDETERMINATE,
			dwState == BST_INDETERMINATE );

	return pStatus;
}


CButtonCtrlSkin::CButtonCtrlSkin( void )
{
}

CButtonCtrlSkin::~CButtonCtrlSkin(void)
{
}

UINT CButtonCtrlSkin::ButtonStyle2Format(DWORD style)
{
	// 在绘制文本之前，先确定文本绘制的flag.

	// 不会有裁剪
	UINT dtStyle = DT_NOCLIP;

	// 是否是多行
	if (!(style & BS_MULTILINE))
	{
		dtStyle |= DT_SINGLELINE;
	}
	else
	{ //多行允许换行
		dtStyle |= DT_WORDBREAK;
	}
	// 文本对齐方式
	switch (style & BS_CENTER)
	{
	case BS_LEFT:
		{ //左对齐
			dtStyle |= DT_LEFT;       
		}
		break;
	case BS_RIGHT:
		{//右对齐
			dtStyle |= DT_RIGHT;  
		}
		break;
	case BS_CENTER:
		{ //居中对齐
			dtStyle |= DT_CENTER | DT_VCENTER; 
		}
		break;
	default:
		{
			dtStyle |= DT_CENTER | DT_VCENTER;
		}
		break;
	}

	return dtStyle;
}
LRESULT CButtonCtrlSkin::OnWndProc(UINT msg,WPARAM wp,LPARAM lp)
{
	// 按钮消息处理
	switch(msg)
	{
	case BM_SETSTATE:
		OnSetState(wp,lp);
		return 0;
	case BM_SETCHECK:
		OnSetCheck(wp, lp);
		return 0;
	case BM_SETSTYLE:
		OnSetStyle(wp,lp);
		return 0;
	case WM_MOUSELEAVE:
		OnMouseLeave();
		return 0;

	case WM_PAINT:
		OnPaint();
		return 0;
	case WM_LBUTTONUP: //备份参数
		m_wParamOnDown = wp;
		m_lParamOnDown = lp;
		OnLButtonUp((UINT)wp, 
			CPoint(GET_X_LPARAM(lp), GET_Y_LPARAM(lp)));
		return 0;
	case WM_LBUTTONDOWN:
		OnLButtonDown((UINT)wp, 
			CPoint(GET_X_LPARAM(lp), GET_Y_LPARAM(lp)));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove( (UINT)wp,
			CPoint(GET_X_LPARAM(lp), GET_Y_LPARAM(lp)));
		return 0;
	case WM_SETFOCUS:
		OnSetFocus( );
		return 0;
	case WM_KILLFOCUS:
		OnKillFocus( );
		return 0;
	case WM_ENABLE:
		OnEnable((BOOL)wp);
		return 0;
	default:
		break;
	}

	return OnPreviousWndProc( GetCurHwnd( ), msg,wp,lp );
}
void CButtonCtrlSkin::OnSetState(WPARAM wp,LPARAM lp)
{
	OnAutoDefaultWndProc( );
	if( IsNull() )
	{
		return;
	}
	// 更新按下状态
	if( SetState( GetCurParam( ) ->m_nButtonState,
		CButtonCtrlStatus::BUTTON_PRESSED, 0!=wp ) )
	{
		Redraw( );
	}
}

void CButtonCtrlSkin::OnSetCheck(WPARAM wp, LPARAM lp )
{
	OnAutoDefaultWndProc();
	bool bRet1 = false;
	bool bRet2 = false;
	switch( wp )
	{
	case BST_CHECKED:
		{
			bRet1 = SetState( GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_CHECKED,
				true );

			bRet2 = SetState( GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_INDETERMINATE,
				false );
		}
		break;
	case BST_INDETERMINATE:
		{
			bRet1 = SetState( GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_CHECKED,
				false );

			bRet2 = SetState( GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_INDETERMINATE,
				true );
		}
		break;
	default:
		{
			bRet1 = SetState( GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_CHECKED,
				false );

			bRet2 = SetState( GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_INDETERMINATE,
				false );
		}
		break;
	}

	if( bRet1 || bRet2 )
	{
		Redraw( );
	}
}

bool CButtonCtrlSkin::GetPreviousWndProc( WNDPROC& pProc ) const
{
	if( IsNull( ) )
	{
		return false;
	}
	pProc = GetCurParam( )->m_pPreviousProc;
	return true;
}

void CButtonCtrlSkin::OnSetStyle(WPARAM wp,LPARAM lp)
{
	OnAutoDefaultWndProc( );

	// 风格主要处理是否是对话框的默认的“确定”按钮
	if( SetState( 
		GetCurParam( ) ->m_nButtonState,
		CButtonCtrlStatus::BUTTON_DEFAULT,
		wp & BS_DEFPUSHBUTTON ) )
	{
		Redraw( );
	}
}


void CButtonCtrlSkin::OnMouseMove( UINT nFlags, CPoint point )
{
	if( IsNull( ) )
	{
		return;
	}
	bool bNeedRedraw = false;
	if(( GetCurParam( ) ->m_nButtonState & 
		CButtonCtrlStatus::BUTTON_HOVER) == 0 && ((nFlags & MK_LBUTTON) == 0) )
	{ // 鼠标普通的移入按钮（没有按键）
		bNeedRedraw = SetState( 
			GetCurParam( ) ->m_nButtonState, 
			CButtonCtrlStatus::BUTTON_HOVER, true);

		// 继续跟踪鼠标，不调用将出错
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = GetCurHwnd( );
		CheckFunc( TrackMouseEvent(&tme) );
	}

	if(( GetCurParam( ) ->m_CaptureState == 
		CButtonCtrlStatus::RELEASE_IN_LEAVE ) )
	{ // 如果上次处于鼠标弹起的状态离开按钮，
	  // 模拟一次鼠标按下，保持按钮状态追踪的完整性
		if((nFlags & MK_LBUTTON) != 0)
		{
			::SendMessage(
				GetCurHwnd( ), WM_LBUTTONDOWN, 
				m_wParamOnDown, m_lParamOnDown );
		}
		else
		{// 没有按键按下的普通鼠标
			GetCurParam( ) -> m_CaptureState = 
				CButtonCtrlStatus::NO_CAPTURE_OR_UP_RELEASE;
		    bNeedRedraw = true;
		}
	}

	RECT rect;
	CheckFunc( GetWindowRect( GetCurHwnd( ), &rect ) );
	CheckFunc( ClientToScreen( GetCurHwnd( ), &point ) );
	
	if(!PtInRect(&rect, point))
	{ // 鼠标离开按钮的状态，由MouseLeave处理
		SendMessage(GetCurHwnd( ), WM_MOUSELEAVE, 0, 0);
	}
	if( bNeedRedraw )
	{
		Redraw( );
	}
}

void CButtonCtrlSkin::OnLButtonDown( UINT nFlags, const CPoint& point )
{
	if( IsNull( ) )
	{
		return;
	}
	// 捕获输入 
	SetCapture( GetCurHwnd( ) );

	GetCurParam( ) ->m_CaptureState = CButtonCtrlStatus::CAPTURE_IN_DOWN;

	// 捕获鼠标焦点
	SetFocus( GetCurHwnd( ) );

	// 状态为按下按钮
	bool b = SetState( GetCurParam( ) ->m_nButtonState, 
		CButtonCtrlStatus::BUTTON_PRESSED, TRUE );

	// 默认的处理
	OnAutoDefaultWndProc();
	if( b )
	{
		Redraw( );
	}
}
void CButtonCtrlSkin::OnMouseLeave()
{
	if( IsNull( ) )
	{
		return;
	}

	if( GetCurParam( ) ->m_CaptureState == 
		CButtonCtrlStatus::CAPTURE_IN_DOWN )
	{ // 鼠标没有在按钮内移动，直接弹起
		CheckFunc( ReleaseCapture() );
		GetCurParam( ) ->m_CaptureState = 
			CButtonCtrlStatus::RELEASE_IN_LEAVE;
	}
	// 取消鼠标移动状态
	bool bRet1 = SetState( GetCurParam( ) ->m_nButtonState, 
		(CButtonCtrlStatus::BUTTON_HOVER | 
		CButtonCtrlStatus::BUTTON_PRESSED ), false );

	// 鼠标恢复正常
	bool bRet2 = SetState( GetCurParam( ) ->m_nButtonState, 
		CButtonCtrlStatus::BUTTON_NORMAL, true );
	if( bRet1 || bRet2 )
	{
		Redraw( );
	}
}
void CButtonCtrlSkin::OnSetFocus( )
{
	OnAutoDefaultWndProc( );
	if( IsNull( ) )
	{
		return;
	}
	// 获取焦点
	if( SetState( GetCurParam( ) ->m_nButtonState, 
		CButtonCtrlStatus::BUTTON_FOCUS, true) )
	{
		Redraw( );
	}
}
void CButtonCtrlSkin::OnKillFocus( )
{
	OnAutoDefaultWndProc( );
	if( IsNull( ) )
	{
		return;
	}
	// 失去焦点
	if( SetState(
		GetCurParam( ) ->m_nButtonState, 
		CButtonCtrlStatus::BUTTON_FOCUS, false ) )
	{
		Redraw( );
	}
}
void CButtonCtrlSkin::OnEnable(BOOL bEnable)
{
	if( IsNull( ) )
	{
		return;
	}
	// 按钮可用状态变化
	if( SetState( GetCurParam( ) ->m_nButtonState, 
		CButtonCtrlStatus::BUTTON_DISABLED, !bEnable ) )
	{
		Redraw( );
	}
}

void CButtonCtrlSkin::OnLButtonUp( UINT nFlags, const CPoint& point )
{
	OnAutoDefaultWndProc();

	CheckFunc( ReleaseCapture() );
	if( IsNull( ) )
	{
		return;
	}
	// 鼠标抬起
	GetCurParam( ) ->m_CaptureState = 
		CButtonCtrlStatus::NO_CAPTURE_OR_UP_RELEASE;

}

void CButtonCtrlSkin::Redraw( )
{
	CWnd *pWnd = CWnd::FromHandle(GetCurHwnd( ));
	if( NULL == pWnd )
	{
		return;
	}
	CDC* pDC = pWnd->GetDC();
	if( NULL == pDC )
	{
		return;
	}
	UpdateCheckStatus();
	OnDrawButton(pDC);
	CheckFunc( pWnd ->ReleaseDC( pDC ) );

}
void CButtonCtrlSkin::OnPaint()
{
	CWnd *pButton = CWnd::FromHandle(GetCurHwnd( ));
	CPaintDC dc(pButton);
	UpdateCheckStatus( );
	OnDrawButton(&dc);
}

bool CButtonCtrlSkin::UpdateCheckStatus()
{
	if( IsNull() )
	{
		return false;
	}

	LRESULT lResult = SendMessage(
		GetCurHwnd( ), BM_GETCHECK, 0, 0);
	bool bRet1 = false;
	bool bRet2 = false;
	switch( lResult )
	{
	case BST_CHECKED:
		{
			bRet1 = SetState(
				GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_CHECKED, true);
			bRet2 = SetState(GetCurParam( ) ->m_nButtonState,
				CButtonCtrlStatus::BUTTON_INDETERMINATE, false );
		}
		break;
	case BST_INDETERMINATE:
		{
			bRet1 = SetState(
				GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_CHECKED, false );
			bRet2 = SetState(GetCurParam( ) ->m_nButtonState,
				CButtonCtrlStatus::BUTTON_INDETERMINATE, false );
		}
		break;
	default:
		{
			bRet1 = SetState(
				GetCurParam( ) ->m_nButtonState, 
				CButtonCtrlStatus::BUTTON_CHECKED, false);
			bRet2 = SetState(GetCurParam( ) ->m_nButtonState,
				CButtonCtrlStatus::BUTTON_INDETERMINATE, false );
		}
		break;

	}
	return ( bRet1 || bRet2 );
}

void CButtonCtrlSkin::DrawText(CDC *pDC, const CRect& rectDest)
{
	if( IsNull( ) )
	{
		return;
	}
	CRect rectIcon,rectText;
	HWND hWnd = GetCurHwnd( );
	CButton *pButton = (CButton*)CWnd::FromHandle( hWnd );
	if( NULL == pButton )
	{
		return;
	}
	HICON hIcon = pButton->GetIcon();
	ICONINFO piconinfo;
	DWORD dwStyle;
	dwStyle = (DWORD)GetWindowLong(GetCurHwnd( ), GWL_STYLE);
	rectText = rectDest;
	if( 0 != GetCurParam( ) ->m_bIcon )
	{
		CheckFunc( GetIconInfo(hIcon,&piconinfo) ); //取图标信息
		rectIcon = rectDest;
		if (dwStyle & BS_TOP) //文字置顶
			rectIcon.top = rectDest.bottom - piconinfo.yHotspot*2 - 4;
		else if (dwStyle & BS_VCENTER)//文字置中
			rectIcon.top = (rectDest.bottom-rectDest.top)/2-piconinfo.yHotspot;
		else
			rectIcon.top = rectDest.top+4;

		if (dwStyle & BS_RIGHT) //文字置右
			rectIcon.left = 4;
		else if(dwStyle & BS_LEFT)//文字置左
			rectIcon.left = rectDest.right - (piconinfo.yHotspot*2 + 4);
		else
			rectIcon.left = (rectDest.right - rectDest.left)/2-piconinfo.yHotspot + 2;
		CheckFunc( pDC->DrawIcon( rectIcon.left,rectIcon.top, hIcon) );
		if( NULL != piconinfo.hbmColor )
		{
			CheckFunc( DeleteObject(piconinfo.hbmColor) );
		}
		if( NULL != piconinfo.hbmMask )
		{
			DeleteObject(piconinfo.hbmMask);
		}
	}
	else
	{
		CString strText;
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		UINT uFormat = ButtonStyle2Format(dwStyle);
		pButton->GetWindowText(strText);
		HFONT hFont = (HFONT)SendMessage( hWnd, WM_GETFONT, 0,0);
		bool bSystemFont = (0 == hFont);
		if( bSystemFont )
		{
			NONCLIENTMETRICS  metrics = {0};
			metrics.cbSize = sizeof(metrics);
			SystemParametersInfo(
				SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);

			hFont = CreateFontIndirect(&metrics.lfCaptionFont);
		}
		HGDIOBJ hOldFont = SelectObject( pDC ->GetSafeHdc(),hFont);
		pDC->DrawText(strText,rectText,uFormat);
		pDC->SetBkMode(nOldMode);
		SelectObject( pDC ->GetSafeHdc(), hOldFont );
		if( bSystemFont )
		{
			CheckFunc( DeleteObject( hFont ) );
		}
	}

}

}
