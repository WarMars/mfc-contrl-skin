#include "stdafx.h"
#include "DialogBoxSkin.h"
#include "GlobalSkinUtil.h"
#include "utils.hpp"
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE


namespace GlobalSkin
{

LPCTSTR CDialogBoxSkin::GetHwndClassName( )
{
    return TEXT("#32770");
}

/**
         * @brief 接管控件皮肤之前
         */
bool CDialogBoxSkin::OnInitSkinParam( HWND hWnd, CParamReference* pParam )
{
    pParam ->SetMenuBarParamPtr(
                DynamicParam::CreateMenuBarSkinParameter( hWnd ) );
	CParamReference* p = pParam;

	p ->SetSizable( false );
	p ->SetHasMinButton( false );
	p ->SetHasMaxButton( false );
	p ->SetHasCloseButton( false );
	p ->SetMargin(CRect(4,24,4,4) );
	p ->SetHasMenu( false );
	p ->SetHasBorder(false);
	p ->SetHasTitle( false );

    return true;
}

CDialogBoxSkin::CDialogBoxSkin( )
{
    // 初始参数设置
    m_paramButtons[CPE::WB_Close].SetPosRect( CRect(380, 4, 396,20) );
    m_paramButtons[CPE::WB_Close].SetOffsetRect( CRect(-20, 4, -4,20) );
    m_paramButtons[CPE::WB_Close].SetAnchorRect( CRect(100, 0, 100,0) );

    m_paramButtons[CPE::WB_Min].SetPosRect( CRect(346, 4, 362,20) );
    m_paramButtons[CPE::WB_Min].SetOffsetRect( CRect(-54, 4, -38,20) );
    m_paramButtons[CPE::WB_Min].SetAnchorRect( CRect(100, 0, 100,0) );
    ////// 最小化

    m_paramButtons[CPE::WB_Max].SetPosRect( CRect(363, 4, 379,20) );
    m_paramButtons[CPE::WB_Max].SetOffsetRect( CRect(-37, 4, -21,20) );
    m_paramButtons[CPE::WB_Max].SetAnchorRect( CRect(100, 0, 100,0) );
    // 恢复

	//CPE::WHT中的restore按钮和最大化按钮参数相同
	m_paramButtons[CPE::WB_Restore] = m_paramButtons[CPE::WB_Max];

    m_paramButtons[CPE::WB_System].SetPosRect( CRect(6, 4, 20,20) );
    m_paramButtons[CPE::WB_System].SetOffsetRect( CRect(6, 4, 20,20) );
    m_paramButtons[CPE::WB_System].SetAnchorRect( CRect(0, 0, 0,0) );

    // 系统按钮
    // 系统按钮

    // 暂时不考虑帮助按钮。
    //m_paramButtons[CPE::WB_Help] = m_paramButtons[CPE::WB_Max];
    for( int i = 0; i < CPE::WB_Size; ++i )
    {
        m_paramButtons[i].UpdateOffsetByRelativeRect(CRect(0,0,400,300) );
    }

 
}	

void CDialogBoxSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		// 初始参数设置
		CBitmapRefPtr pBmpTitleButton = ImagePool( ).CreateBitmap(
			TEXT("ui\\skin\\DialogBox_TitleButton.bmp") );
		int nXOffset = 0;
		int nYOffset = 0;
		int nUnitSize = 20;

		////// 最小化
		//nYOffset += nUnitSize;
		m_paramButtons[CPE::WB_Min].SetStateBitmap(
			CPE::WBS_Normal,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Min].SetStateBitmap(
			CPE::WBS_Hover,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*1, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Min].SetStateBitmap(
			CPE::WBS_Pressed,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*2, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Min].SetStateBitmap(
			CPE::WBS_Disabled,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*3, nYOffset, nUnitSize, nUnitSize ) );
	
		// 最大化
		nYOffset += nUnitSize;
		m_paramButtons[CPE::WB_Max].SetStateBitmap(
			CPE::WBS_Normal,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Max].SetStateBitmap(
			CPE::WBS_Hover,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*1, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Max].SetStateBitmap(
			CPE::WBS_Pressed,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*2, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Max].SetStateBitmap(
			CPE::WBS_Disabled,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*3, nYOffset, nUnitSize, nUnitSize ) );
		// 最大化

		nYOffset += nUnitSize;
		m_paramButtons[CPE::WB_Close].SetStateBitmap(
			CPE::WBS_Normal,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Close].SetStateBitmap(
			CPE::WBS_Hover,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*1, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Close].SetStateBitmap(
			CPE::WBS_Pressed,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*2, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Close].SetStateBitmap(
			CPE::WBS_Disabled,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*3, nYOffset, nUnitSize, nUnitSize ) );

		// 恢复
		nYOffset += nUnitSize;
		m_paramButtons[CPE::WB_Restore].SetStateBitmap(
			CPE::WBS_Normal,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Restore].SetStateBitmap(
			CPE::WBS_Hover,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*1, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Restore].SetStateBitmap(
			CPE::WBS_Pressed,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*2, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_Restore].SetStateBitmap(
			CPE::WBS_Disabled,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*3, nYOffset, nUnitSize, nUnitSize ) );
		// 恢复

		nYOffset += nUnitSize;
		m_paramButtons[CPE::WB_System].SetStateBitmap(
			CPE::WBS_Normal,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_System].SetStateBitmap(
			CPE::WBS_Hover,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*1, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_System].SetStateBitmap(
			CPE::WBS_Pressed,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*2, nYOffset, nUnitSize, nUnitSize ) );
		m_paramButtons[CPE::WB_System].SetStateBitmap(
			CPE::WBS_Disabled,
			Util::CreateSubBitmap( pBmpTitleButton,
			nXOffset+nUnitSize*3, nYOffset, nUnitSize, nUnitSize ) );
		// 系统按钮

		CBitmapRefPtr pBorderBitmap = ImagePool( ).CreateBitmap(
			TEXT("ui\\skin\\DialogBox_Border.bmp") );
		nXOffset = 0;
		nYOffset = 0;

		// 边框的背景图
		m_pBmpActiveNcBk[CPE::WBKIP_Top] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset, nUnitSize, nUnitSize );
		m_pBmpUnActiveNcBk[CPE::WBKIP_Top] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset+nUnitSize,
			nUnitSize, nUnitSize );
		// left
		nXOffset += nUnitSize;
		m_pBmpActiveNcBk[CPE::WBKIP_Left] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset, nUnitSize, nUnitSize );
		m_pBmpUnActiveNcBk[CPE::WBKIP_Left] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset+nUnitSize,
			nUnitSize, nUnitSize );
		// left
		// right
		nXOffset += nUnitSize;
		m_pBmpActiveNcBk[CPE::WBKIP_Right] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset, nUnitSize, nUnitSize );
		m_pBmpUnActiveNcBk[CPE::WBKIP_Right] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset+nUnitSize,
			nUnitSize, nUnitSize );
		// right
		// bottom
		nXOffset += nUnitSize;
		m_pBmpActiveNcBk[CPE::WBKIP_Bottom] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset, nUnitSize, nUnitSize );
		m_pBmpUnActiveNcBk[CPE::WBKIP_Bottom] = Util::CreateSubBitmap(
			pBorderBitmap, nXOffset, nYOffset+nUnitSize,
			nUnitSize, nUnitSize );
		// bottom
		return;
	}

#ifdef USING_CONFIG_FILE
	m_paramButtons[CPE::WB_Close].SetStateBitmap(
		CPE::WBS_Normal,
		pConfig ->GetBitmap(TEXT("dialog/button/close/normal/background") ) );
	m_paramButtons[CPE::WB_Close].SetStateBitmap(
		CPE::WBS_Hover,
		pConfig ->GetBitmap(TEXT("dialog/button/close/hover/background") ) );
	m_paramButtons[CPE::WB_Close].SetStateBitmap(
		CPE::WBS_Pressed,
		pConfig ->GetBitmap(TEXT("dialog/button/close/pressed/background") )  );
	m_paramButtons[CPE::WB_Close].SetStateBitmap(
		CPE::WBS_Disabled,
		pConfig ->GetBitmap(TEXT("dialog/button/close/disabled/background") )  );

	// 最大化
	m_paramButtons[CPE::WB_Max].SetStateBitmap(
		CPE::WBS_Normal,
		pConfig ->GetBitmap(TEXT("dialog/button/maximum/normal/background") )  );
	m_paramButtons[CPE::WB_Max].SetStateBitmap(
		CPE::WBS_Hover,
		pConfig ->GetBitmap(TEXT("dialog/button/maximum/hover/background") )  );
	m_paramButtons[CPE::WB_Max].SetStateBitmap(
		CPE::WBS_Pressed,
		pConfig ->GetBitmap(TEXT("dialog/button/maximum/pressed/background") )  );
	m_paramButtons[CPE::WB_Max].SetStateBitmap(
		CPE::WBS_Disabled,
		pConfig ->GetBitmap(TEXT("dialog/button/maximum/disabled/background") )  );
	// 最大化

	m_paramButtons[CPE::WB_Min].SetStateBitmap(
		CPE::WBS_Normal,
		pConfig ->GetBitmap(TEXT("dialog/button/minimum/normal/background") ) );
	m_paramButtons[CPE::WB_Min].SetStateBitmap(
		CPE::WBS_Hover,
		pConfig ->GetBitmap(TEXT("dialog/button/minimum/hover/background") )  );
	m_paramButtons[CPE::WB_Min].SetStateBitmap(
		CPE::WBS_Pressed,
		pConfig ->GetBitmap(TEXT("dialog/button/minimum/pressed/background") )  );
	m_paramButtons[CPE::WB_Min].SetStateBitmap(
		CPE::WBS_Disabled,
		pConfig ->GetBitmap(TEXT("dialog/button/minimum/disabled/background") ) );

	// 恢复
	m_paramButtons[CPE::WB_Restore].SetStateBitmap(
		CPE::WBS_Normal,
		pConfig ->GetBitmap(TEXT("dialog/button/restore/normal/background") )  );
	m_paramButtons[CPE::WB_Restore].SetStateBitmap(
		CPE::WBS_Hover,
		pConfig ->GetBitmap(TEXT("dialog/button/restore/hover/background") )  );
	m_paramButtons[CPE::WB_Restore].SetStateBitmap(
		CPE::WBS_Pressed,
		pConfig ->GetBitmap(TEXT("dialog/button/restore/pressed/background") )  );
	m_paramButtons[CPE::WB_Restore].SetStateBitmap(
		CPE::WBS_Disabled,
		pConfig ->GetBitmap(TEXT("dialog/button/restore/disabled/background") )  );
	// 恢复

	m_paramButtons[CPE::WB_System].SetStateBitmap(
		CPE::WBS_Normal,
		pConfig ->GetBitmap(TEXT("dialog/button/system/normal/background") ) );
	m_paramButtons[CPE::WB_System].SetStateBitmap(
		CPE::WBS_Hover,
		pConfig ->GetBitmap(TEXT("dialog/button/system/hover/background") ) );
	m_paramButtons[CPE::WB_System].SetStateBitmap(
		CPE::WBS_Pressed,
		pConfig ->GetBitmap(TEXT("dialog/button/system/pressed/background") ) );
	m_paramButtons[CPE::WB_System].SetStateBitmap(
		CPE::WBS_Disabled,
		pConfig ->GetBitmap(TEXT("dialog/button/system/disabled/background") ));
	// 系统按钮

	m_paramButtons[CPE::WB_Help].SetStateBitmap(
		CPE::WBS_Normal,
		pConfig ->GetBitmap(TEXT("dialog/button/help/normal/background") ) );
	m_paramButtons[CPE::WB_Help].SetStateBitmap(
		CPE::WBS_Hover,
		pConfig ->GetBitmap(TEXT("dialog/button/help/hover/background") ) );
	m_paramButtons[CPE::WB_Help].SetStateBitmap(
		CPE::WBS_Pressed,
		pConfig ->GetBitmap(TEXT("dialog/button/help/pressed/background") ) );
	m_paramButtons[CPE::WB_Help].SetStateBitmap(
		CPE::WBS_Disabled,
		pConfig ->GetBitmap(TEXT("dialog/button/help/disabled/background") ) );


	// 边框的背景图
	m_pBmpActiveNcBk[CPE::WBKIP_Top] = 
		pConfig ->GetBitmap(TEXT("dialog/border/top/active/background") ) ;
	m_pBmpUnActiveNcBk[CPE::WBKIP_Top] = 
		pConfig ->GetBitmap(TEXT("dialog/border/top/unactive/background") ) ;
	// left
	m_pBmpActiveNcBk[CPE::WBKIP_Left] =
		pConfig ->GetBitmap(TEXT("dialog/border/left/active/background") ) ;
	m_pBmpUnActiveNcBk[CPE::WBKIP_Left] = 
		pConfig ->GetBitmap(TEXT("dialog/border/left/unactive/background") ) ;
	// left
	// right
	m_pBmpActiveNcBk[CPE::WBKIP_Right] = 
		pConfig ->GetBitmap(TEXT("dialog/border/right/active/background") ) ;
	m_pBmpUnActiveNcBk[CPE::WBKIP_Right] = 
		pConfig ->GetBitmap(TEXT("dialog/border/right/unactive/background") ) ;
	// right
	// bottom
	m_pBmpActiveNcBk[CPE::WBKIP_Bottom] = 
		pConfig ->GetBitmap(TEXT("dialog/border/bottom/active/background") ) ;
	m_pBmpUnActiveNcBk[CPE::WBKIP_Bottom] = 
		pConfig ->GetBitmap(TEXT("dialog/border/bottom/unactive/background") ) ;
#endif
}

CDialogBoxSkin::~CDialogBoxSkin()
{

}

LRESULT CDialogBoxSkin::OnWndOtherProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    // TRACE("START:%d(%d)\n",nMsg, sizeof(CParamReference));
    // int nCounter1 = 0;
    // for( std::map<HWND,CParamReferencePtr>::const_iterator
    // it = m_mapCtrlParameterPack.begin(); it != m_mapCtrlParameterPack.end( ); ++it )
    // {
    // TRACE("[%d]=0X%x\n",++nCounter1,int(it ->second ->GetMenuBarParamPtr().get()) );
    // }
    // TRACE("END\n");
    //return OnAutoDefaultWndProc();
    switch( nMsg )
    {
	case WM_CREATE:
		OnCreate( (LPCREATESTRUCT)lParam );
		break;
	case WM_INITDIALOG:
		OnInitDialog( );
		break;
    case WM_NCLBUTTONUP:
        OnNcLButtonUp( UINT(wParam),
                       CPoint( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) ) );
        break;
    case WM_NCRBUTTONDOWN:
        OnNcRButtonDown(UINT(wParam),
                        CPoint( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) ) );
        break;
    case WM_NCACTIVATE:
        return (LRESULT)OnNcActivate( (BOOL)wParam );
        break;
    case WM_SYSCOMMAND:
        OnSysCommand(UINT(wParam), lParam );
        break;
    case WM_ERASEBKGND:
        return OnEraseBkgnd(HDC(wParam) );
        break;
    case WM_SIZE:
        OnSize(UINT(wParam),LOWORD(lParam),HIWORD(lParam) );
        break;
    case WM_SETTEXT:
        OnSetText( wParam, lParam );
        break;
    case WM_SETICON:
        return OnSetIcon(UINT(wParam),HICON(lParam));
        break;
    case WM_ENABLE:
        OnEnable( BOOL(wParam) );
        break;
    case WM_TIMER:
        OnTimer(UINT_PTR(wParam) );
        break;
    default:
        return OnPreviousWndProc(GetCurHwnd( ),nMsg,wParam, lParam);
    }
    return 0;
}

void CDialogBoxSkin::OnInitDialog( )
{
	OnAutoDefaultWndProc( );
	if( IsNull() )
	{
		return;
	}
	CParamReference* p = GetCurParam( );
	HWND hWnd = GetCurHwnd();

	DWORD lStyle   = GetWindowLong( hWnd, GWL_STYLE );
	DWORD lExstyle = GetWindowLong( hWnd,GWL_EXSTYLE);
	bool bIsChild = i2b(lStyle & WS_CHILD);
	if( !bIsChild )
	{ 
		p ->SetSizable(
			i2b(lStyle& WS_THICKFRAME) &&
			( (lStyle & (WS_DLGFRAME|WS_BORDER)) == WS_DLGFRAME) );
		p ->SetHasMinButton( i2b(lStyle & WS_MINIMIZEBOX) );
		p ->SetHasMaxButton( i2b(lStyle & WS_MAXIMIZEBOX) );
		if( i2b( lStyle ) )
		{
			HMENU hMenu = GetSystemMenu( hWnd, FALSE );
			//pMenu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED);  // 关闭按钮会无效
			BOOL nState = EnableMenuItem(hMenu,SC_CLOSE,MF_DISABLED);     //关闭按钮变灰
			if( -1 != nState )
			{
				if( i2b(nState&MF_DISABLED ) || i2b( nState & MF_GRAYED ) )
				{
					p ->SetCloseButtonState( CPE::WBS_Disabled );
				}
				else
				{
					p ->SetCloseButtonState( CPE::WBS_Normal );
				}
				EnableMenuItem( hMenu, SC_CLOSE,nState );
				p ->SetHasCloseButton( true );
			}
			else
			{
				p ->SetHasCloseButton( false );
			}


		}
		else
		{
			p ->SetHasCloseButton( false );
		}
		
		p ->SetHasTitle( i2b( lStyle & WS_CAPTION ) );
		p ->SetHasBorder( ( 
			( 0 != (( lStyle) & (WS_THICKFRAME | 
			WS_DLGFRAME | WS_BORDER)) ) ||
			( 0 != (( lExstyle ) & WS_EX_DLGMODALFRAME) ) ) );
		p ->SetMinButtonState( CPE::WBS_Normal );
		p ->SetMaxButtonState( CPE::WBS_Normal );
		//p ->SetCloseButtonState( CPE::WBS_Normal );
		p ->SetHelpButtonState( CPE::WBS_Normal );
		p ->SetMargin(CRect(4,24,4,4) );
		HMENU  hMenu = GetMenu(hWnd);
		p ->SetHasMenu (
			( (lStyle & (WS_CHILD | WS_POPUP) )!= WS_CHILD) && NULL != hMenu );

		LoadMenuBarCtrlSkin( ).SetMenu( hMenu, p ->GetMargin() );
		//TRACE("[%02d]created menu addr:0x%016X|0x%016X\n",
		//      ++nCounter,
		//      (int)(pParam ->GetMenuBarParamPtr().get()),
		//      (int)pParam);
		if( p ->HasMinButton() )
		{
			lStyle &= ~WS_MINIMIZEBOX;
		}
		if( p ->HasMaxButton() )
		{
			lStyle &= ~WS_MAXIMIZEBOX;
		}
		if( p ->HasCloseButton() )
		{
			lStyle &= ~WS_SYSMENU;
		}
		lStyle &= ~WS_THICKFRAME;
		lStyle &= ~WS_CAPTION;
		lStyle &= ~WS_BORDER;
		lStyle &= ~WS_DLGFRAME;
		lExstyle &= ~WS_EX_DLGMODALFRAME;
		SetWindowLong( hWnd, GWL_STYLE, lStyle );
		SetWindowLong( hWnd, GWL_EXSTYLE, lExstyle );
		if( p ->HasMenu() )
		{
			//取消菜单 
			SetMenu(hWnd, NULL );
		}
	}
}
void CDialogBoxSkin::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	OnAutoDefaultWndProc();
}
void CDialogBoxSkin::OnNcMouseMove( UINT nHitTest, const CPoint& ptLast )
{
    if( IsNull() )
    {
        OnAutoDefaultWndProc();
        return;
    }

	//LONG lStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	//LONG lEStyle = GetWindowLong( m_hWnd, GWL_EXSTYLE );
    CParamReference* p = GetCurParam();
    CPoint point = ptLast;
    switch(nHitTest)
    {
    case HTMAXBUTTON:
		// 存在标题切存在最大化按钮
        if( !p ->HasTitle( ) ||
                !p ->HasMaxButton() )
        {
            return;
        }
        if( p ->GetMaxButtonState( ) != CPE::WBS_Hover )
        {
            p ->SetMaxButtonState( CPE::WBS_Hover );
            p ->SetMinButtonState( CPE::WBS_Normal );
            p ->SetCloseButtonState( CPE::WBS_Normal );
            p ->SetHelpButtonState( CPE::WBS_Normal );

            DrawWindowButton( );

        }
        break;
    case HTMINBUTTON:
		// 有最小化按钮
        if(!p ->HasTitle() || !p ->HasMinButton() )
        {
            return;
        }

        if(p ->GetMinButtonState() != CPE::WBS_Hover)
        {
            p ->SetMinButtonState( CPE::WBS_Hover );
            p ->SetMaxButtonState( CPE::WBS_Normal );
            p ->SetCloseButtonState( CPE::WBS_Normal );
            p ->SetHelpButtonState( CPE::WBS_Normal );

            DrawWindowButton( );
        }
        break;
    case HTCLOSE:
		// 有关闭按钮
        if(!p ->HasTitle( ) || !p ->HasCloseButton( ) )
            return;
        if(p ->GetCloseButtonState( ) != CPE::WBS_Hover)
        {
            p ->SetCloseButtonState( CPE::WBS_Hover );
            p ->SetMaxButtonState( CPE::WBS_Normal );
            p ->SetMinButtonState( CPE::WBS_Normal );
            p ->SetHelpButtonState( CPE::WBS_Normal );

            DrawWindowButton( );

        }

        break;
    case HTHELP:
        if(!p ->HasTitle() || !p ->HasCloseButton() )
        {
            return;
        }
        if(p ->GetHelpButtonState( ) != CPE::WBS_Hover )
        {
            p ->SetHelpButtonState( CPE::WBS_Hover );
            p ->SetMaxButtonState( CPE::WBS_Normal );
            p ->SetMinButtonState( CPE::WBS_Normal );
            p ->SetCloseButtonState( CPE::WBS_Normal );

            DrawWindowButton( );

        }
        break;
    case HTHSCROLL:
    case HTVSCROLL:
        CCtrlWithScrollBar::OnNcMouseMove(nHitTest,ptLast );
        break;
    case HTMENU:
    {
        CRect rtWindow = Util::CTempRelativeWindowRect(GetCurHwnd( ));
        point.Offset(-rtWindow.left,-rtWindow.top);

        LoadMenuBarCtrlSkin( )
                .OnMouseMove( HTMENU,point );
        if( !p ->IsInMenu() )
        {
            SetTimer(GetCurHwnd( ),MenuTrackTimerId,20,NULL);
            p ->SetInMenu( true );
        }
    }
        break;
	default: //在窗口的其它位置移动鼠标
	{
		DynamicParam::CMenubarCtrlSkinParameterRef*
				pMenuBar = p->GetMenuBarParamPtr( );
		if(p->HasMenu( ) &&(
					NULL != pMenuBar ->GetHot( ) ||
					NULL != pMenuBar ->GetPressed( ) ) )
		{ //有菜单，且焦点和点击发生了变化
			pMenuBar ->SetHot( NULL );
			pMenuBar ->SetPressed( NULL );
			LoadMenuBarCtrlSkin( ).DrawMenuBar( );
		}

		// 按钮或滚动条之前存在操作状态，也会被取消

		bool bNeedRedraw = false;

		if( p ->GetCloseButtonState( ) != CPE::WBS_Normal )
		{
			p ->SetCloseButtonState( CPE::WBS_Normal );
			bNeedRedraw = p ->HasCloseButton();
		}
		if( p ->GetMaxButtonState( ) != CPE::WBS_Normal )
		{
			p ->SetMaxButtonState( CPE::WBS_Normal );
			bNeedRedraw = p ->HasMaxButton();
		}
		if( p ->GetMinButtonState( ) != CPE::WBS_Normal )
		{
			p ->SetMinButtonState( CPE::WBS_Normal );
			bNeedRedraw = p ->HasMinButton();

		}
		if( p ->GetHelpButtonState( ) != CPE::WBS_Normal)
		{
			p ->SetHelpButtonState( CPE::WBS_Normal );
			bNeedRedraw = p ->HasCloseButton();
		}

		if( bNeedRedraw )
		{
			DrawWindowButton( );
			bNeedRedraw = false;
		}

		DynamicParam::CScrollBarBasic& hBar = p ->GetScrollBarParam( )
			->GetHBar();
		if( hBar.GetLeftArrowState( ) != CPE::SBS_Normal )
		{
		   hBar.SetLeftArrowState( CPE::SBS_Normal );
		   bNeedRedraw = true;
		}
		if( hBar.GetRightArrowState( )  != CPE::SBS_Normal )
		{
			hBar.SetRightArrowState( CPE::SBS_Normal );
			bNeedRedraw = true;
		}
		if( hBar.GetThumbState( ) != CPE::SBS_Normal )
		{
			hBar.SetThumbState( CPE::SBS_Normal );
			bNeedRedraw = true;
		}
		if( bNeedRedraw)
		{
			if( hBar.IsVisible( ) )
			{
				GetScrollBarCtrlSkin()
					.DrawHScrollBar(
					GetCurHwnd( ), p ->GetScrollBarParam( ) );
			}
			bNeedRedraw = false;
		}
		DynamicParam::CScrollBarBasic& vBar = p ->GetScrollBarParam( )
			->GetVBar();
		if( vBar.GetTopArrowState( ) != CPE::SBS_Normal )
		{
			vBar.SetTopArrowState( CPE::SBS_Normal );
			bNeedRedraw = true;
		}
		if( vBar.GetBotArrowState( ) != CPE::SBS_Normal )
		{
			vBar.SetBotArrowState( CPE::SBS_Normal );
			bNeedRedraw = true;
		}
		if( vBar.GetThumbState( ) != CPE::SBS_Normal )
		{
			vBar.SetThumbState( CPE::SBS_Normal );
			bNeedRedraw = true;
		}
		if( bNeedRedraw )
		{
			if( vBar.IsVisible( ) )
			{
				GetScrollBarCtrlSkin( ).DrawVScrollBar(
							GetCurHwnd( ), p ->GetScrollBarParam( ) );
			}
			bNeedRedraw = false;
		}
	}
        break;
	}
}

void CDialogBoxSkin::OnMouseMove(UINT nFlags, const CPoint& point)
{
    OnAutoDefaultWndProc();
    if( IsNull() )
    {
        return;
    }
    CParamReference* p = GetCurParam( );

	// 菜单
    if( p ->HasMenu( ) &&(
                NULL != p->GetMenuBarParamPtr() ->GetHot( ) ||
                NULL != p ->GetMenuBarParamPtr() ->GetPressed( ) ) )
    {
        p ->GetMenuBarParamPtr() ->SetHot(NULL);
        p ->GetMenuBarParamPtr() ->SetPressed( NULL );
        LoadMenuBarCtrlSkin( ).DrawMenuBar( );
    }
	// 窗口按钮
    if( p ->GetCloseButtonState( ) != CPE::WBS_Normal ||
            p ->GetMaxButtonState( ) != CPE::WBS_Normal  ||
            p ->GetHelpButtonState( ) != CPE::WBS_Normal ||
            p ->GetMinButtonState( ) != CPE::WBS_Normal )
    {
        p ->SetCloseButtonState( CPE::WBS_Normal );
        p ->SetMaxButtonState( CPE::WBS_Normal );
        p ->SetMinButtonState( CPE::WBS_Normal );
        p ->SetHelpButtonState( CPE::WBS_Normal );
        DrawWindowButton( );
    }

	// 水平滚动条
	DynamicParam::CScrollBarBasic& hBar = p ->GetScrollBarParam( )
		->GetHBar();
    if( hBar.GetLeftArrowState( ) != CPE::SBS_Normal ||
            hBar.GetRightArrowState( ) != CPE::SBS_Normal ||
            hBar.GetThumbState( ) != CPE::SBS_Normal )
    {
        hBar.SetLeftArrowState( CPE::SBS_Normal );
        hBar.SetRightArrowState( CPE::SBS_Normal );
        hBar.SetThumbState( CPE::SBS_Normal );
        if( hBar.IsVisible( ) )
        {
            GetScrollBarCtrlSkin( ).DrawHScrollBar(
                        GetCurHwnd(), p ->GetScrollBarParam( ) );
        }
	}

	// 垂直滚动条
	DynamicParam::CScrollBarBasic& vBar = p ->GetScrollBarParam( )
		->GetVBar();
    if( vBar.GetLeftArrowState( ) != CPE::SBS_Normal ||
            vBar.GetRightArrowState( ) != CPE::SBS_Normal ||
            vBar.GetThumbState( ) != CPE::SBS_Normal )
    {
        vBar.SetLeftArrowState( CPE::SBS_Normal );
        vBar.SetRightArrowState( CPE::SBS_Normal );
        vBar.SetThumbState( CPE::SBS_Normal );

        if( vBar.IsVisible( ) )
        {
            GetScrollBarCtrlSkin( ).DrawVScrollBar(
                        GetCurHwnd( ), p ->GetScrollBarParam( ) );
        }
    }
}

void CDialogBoxSkin::OnNcLButtonUp( UINT nHitTest, const CPoint& point )
{
    OnAutoDefaultWndProc();
    return;
}

void CDialogBoxSkin::OnNcLButtonDown( UINT nHitTest, const CPoint& point )
{
    if( IsNull() )
    {
        return;
    }
	//TRACE("点击测试区域:%d\n", nHitTest );
	CParamReference* p = GetCurParam( );
    LRESULT result = 0;
    MSG msg;
    UINT nCurrentHit = HTNOWHERE;
#ifdef BUTTON_TRACK
#	error "BUTTON_TRACK macro has been defined"
#endif

#define BUTTON_TRACK( HasFun, WBType, SetStateFun,GetStateFun,HitBtn,SendMWp ) \
    if( !p ->HasFun() ) \
    { \
    return; \
} \
    p ->SetSelectedButtonType( WBType ); \
    p ->SetStateFun( CPE::WBS_Pressed ); \
    DrawWindowButton( ); \
    SetCapture( GetCurHwnd( ) ); \
    while(true) \
    { \
    CPE::WindowButtonState nOldMaxBtnState = p ->GetStateFun( ); \
    if ( FALSE == GetMessage( &msg, 0, WM_MOUSEFIRST, WM_MOUSELAST ) ) \
    { \
    break; \
} \
    if ( TRUE == CallMsgFilter( &msg, MSGF_MAX ) ) \
    { \
    continue; \
} \
    if( WM_LBUTTONUP == msg.message ) \
    { \
    nCurrentHit = (UINT)OnNcHitTest( msg.pt ); \
    p ->SetStateFun( \
    HitBtn == nCurrentHit? \
    CPE::WBS_Hover : CPE::WBS_Normal ); \
    if ( p ->GetStateFun( ) != nOldMaxBtnState) \
    { \
    DrawWindowButton( ); \
} \
    break; \
} \
    if( WM_MOUSEMOVE != msg.message ) \
    { \
    continue; \
} \
    p ->SetStateFun(  \
    ( (UINT)OnNcHitTest( msg.pt ) == nHitTest )? \
    CPE::WBS_Pressed:CPE::WBS_Normal ); \
    if ( p ->GetStateFun( ) != nOldMaxBtnState) \
    { \
    DrawWindowButton( ); \
} \
} \
    if(HitBtn == nCurrentHit) \
    { \
    SendMessage(  \
    GetCurHwnd( ), \
    WM_SYSCOMMAND, \
    SendMWp,  \
    MAKELONG(msg.pt.x,msg.pt.y) ); \
} \
    p ->SetStateFun( CPE::WBS_Normal); \
    DrawWindowButton( ); \
    ReleaseCapture( );
    switch(nHitTest)
    {
    case HTMAXBUTTON:
    {
        BUTTON_TRACK(
                    HasMaxButton,
                    CPE::WHT_Max,
                    SetMaxButtonState,
                    GetMaxButtonState,
                    HTMAXBUTTON,
                    ( ( TRUE == IsZoomed(GetCurHwnd( ) ) )?
                          SC_RESTORE:SC_MAXIMIZE) );
    }
        break;
    case HTMINBUTTON:
    {
        BUTTON_TRACK(
                    HasMinButton,
                    CPE::WHT_Min,
                    SetMinButtonState,
                    GetMinButtonState,
                    HTMINBUTTON,
                    SC_MINIMIZE );
    }
        break;
    case HTCLOSE:
    {
#if !0
        BUTTON_TRACK(
                    HasCloseButton,
                    CPE::WHT_Close,
                    SetCloseButtonState,
                    GetCloseButtonState,
                    HTCLOSE,
                    SC_CLOSE );
#else
		if( !p ->HasCloseButton() )
		{
			return;
		}
		p ->SetSelectedButtonType( CPE::WHT_Close );
		p ->SetCloseButtonState( CPE::WBS_Pressed );
		DrawWindowButton( );
		SetCapture(m_hWnd);

		while(TRUE)
		{
			int nOldCloseBtnState = p ->GetCloseButtonState( );
			if (!GetMessage( &msg, 0, WM_MOUSEFIRST, WM_MOUSELAST )) break;
			if (CallMsgFilter( &msg, MSGF_MAX )) continue;

			if(msg.message == WM_LBUTTONUP)
			{
				nCurrentHit = OnNcHitTest(msg.pt);
				if(nCurrentHit == HTCLOSE)
					p ->SetCloseButtonState( CPE::WBS_Hover );
				else
					p ->SetCloseButtonState( CPE::WBS_Normal );
				if ( p ->GetCloseButtonState() != nOldCloseBtnState)
					DrawWindowButton( );
				break;
			}

			if(msg.message != WM_MOUSEMOVE)
				continue;

			if(OnNcHitTest( msg.pt ) == nHitTest)
				p ->SetCloseButtonState( CPE::WBS_Pressed );
			else
				p ->SetCloseButtonState( CPE::WBS_Normal );
			if ( p ->GetCloseButtonState() != nOldCloseBtnState)
				DrawWindowButton( );
		}
		if (nCurrentHit == HTCLOSE)
			SendMessage(m_hWnd, WM_SYSCOMMAND,
			SC_CLOSE, MAKELONG(msg.pt.x,msg.pt.y) );
		ReleaseCapture();
		break;

#endif
    }
        break;
#undef BUTTON_TRACK
    case HTHELP:
    {
        GetCurParam( ) ->SetNcMouseState( CPE::MS_Down );
        GetCurParam( ) ->SetSelectedButtonType( CPE::WHT_Help );
        GetCurParam( ) ->SetHelpButtonState( CPE::WBS_Pressed );
        DrawWindowButton( );
        SetCapture(GetCurHwnd( ));

        while(true)
        {
            CPE::WindowButtonState nOldHelpBtnState =
                    GetCurParam( ) ->GetHelpButtonState( );
            if (FALSE ==GetMessage( &msg, 0, WM_MOUSEFIRST, WM_MOUSELAST ))
            {
                break;
            }
            if (TRUE == CallMsgFilter( &msg, MSGF_MAX ))
            {
                continue;
            }

            if(msg.message == WM_LBUTTONUP)
            {
                GetCurParam() ->SetNcMouseState( CPE::MS_Normal );
                nCurrentHit = (UINT)OnNcHitTest(msg.pt);
                GetCurParam() ->SetHelpButtonState(
                            (nCurrentHit == HTHELP)?
                                CPE::WBS_Hover : CPE::WBS_Normal );
                if ( GetCurParam() ->GetHelpButtonState( )
                     != nOldHelpBtnState)
                {
                    DrawWindowButton( );
                }
                break;
            }

            if(msg.message != WM_MOUSEMOVE)
            {
                continue;
            }

            if(OnNcHitTest( msg.pt ) == nHitTest)
                GetCurParam() ->SetHelpButtonState(
                            ( OnNcHitTest( msg.pt ) == nHitTest)?
                                CPE::WBS_Pressed : CPE::WBS_Normal  );
            if (GetCurParam() ->GetHelpButtonState( ) != nOldHelpBtnState)
            {
                DrawWindowButton( );
            }
        }
        ReleaseCapture();
    }
        break;

    case HTHSCROLL:
	{
		//TRACE("水平滚动条\n");
        SendMessage(
                    GetCurHwnd( ),
                    WM_SYSCOMMAND,
                    (WPARAM)SC_HSCROLL,
                    MAKELPARAM(point.x,point.y) );
    }
        break;
    case HTVSCROLL:
    {
		//TRACE("垂直滚动条\n");
        SendMessage(
                    GetCurHwnd( ),
                    WM_SYSCOMMAND,
                    (WPARAM)SC_VSCROLL,
                    MAKELPARAM(point.x,point.y) );
    }
        break;
    case HTMENU:
    {
        SendMessage(
                    GetCurHwnd( ),
                    WM_SYSCOMMAND,
                    (WPARAM)SC_MOUSEMENU,
                    MAKELPARAM(point.x,point.y) );
    }
        break;
    default:
        OnAutoDefaultWndProc();
        break;
    }
}

void CDialogBoxSkin::OnNcRButtonDown(UINT nHitTest, const CPoint& point)
{
    switch(nHitTest)
    {
    case HTCAPTION:
    case HTSYSMENU:
    {
        HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
        HMENU hSysMenuCopy = DynamicParam::CopyMenu(hMenu);

        int nID = TrackPopupMenu(hSysMenuCopy,
                                 TPM_RIGHTBUTTON | TPM_RETURNCMD,
                                 point.x, point.y, 0, m_hWnd, NULL);
        if(nID > 0)
        {
            SendMessage(m_hWnd, WM_SYSCOMMAND, nID, 0);
        }
        DestroyMenu(hSysMenuCopy);
        OnAutoDefaultWndProc( );
    }
        break;
    default:
        OnAutoDefaultWndProc( );
        break;
    }
}

void CDialogBoxSkin::OnNcLButtonDblClk( UINT nHitTest, const CPoint& point )
{
    if( IsNull() )
    {
        return;
    }
    if ( TRUE==IsIconic( GetCurHwnd() ) )
    {
        // 窗口最小化
        SendMessage(m_hWnd,WM_SYSCOMMAND, SC_RESTORE, 0);
        return;
    }
    if ( nHitTest == HTCAPTION && GetCurParam( ) ->IsSizable() )
    {
        SendMessage(
                    GetCurHwnd(),
                    WM_SYSCOMMAND,
                    TRUE == IsZoomed(m_hWnd)?
                        SC_RESTORE:SC_MAXIMIZE, 0 );
        OnNcPaint(0);
    }
    else if(nHitTest == HTHSCROLL)
	{
        SendMessage(
                    GetCurHwnd(),
                    WM_SYSCOMMAND,
                    (WPARAM)SC_HSCROLL,
                    MAKELPARAM(point.x,point.y) );
    }
    else if(nHitTest == HTVSCROLL)
    {
        SendMessage(
                    GetCurHwnd(),
                    WM_SYSCOMMAND,
                    (WPARAM)SC_VSCROLL,
                    MAKELPARAM(point.x,point.y) );
    }
    else
    {
        OnAutoDefaultWndProc( );
    }
}

LRESULT CDialogBoxSkin::OnNcHitTest( const CPoint& point )
{
    DWORD style	 = GetWindowLong( m_hWnd, GWL_STYLE );
    if( i2b(style & WS_MINIMIZE) )
    {
		//TRACE("点击标题\n");
        return HTCAPTION;
    }
    CParamReference* p = GetCurParam();
    CRect rtWindow;
    CRect rtClient;
    CRect rtMargin = p ->GetMargin( );

    int nHHeight = GetSystemMetrics(SM_CYHSCROLL);
    int nVWidth = GetSystemMetrics(SM_CXVSCROLL);
    GetWindowRect( GetCurHwnd(),&rtWindow);
    GetClientRect( GetCurHwnd(),&rtClient);
    ClientToScreen(GetCurHwnd(),&rtClient);
    p ->UpdatePartRect(rtWindow);
    p ->UpdateButtonRect( rtWindow, m_paramButtons );

    if(rtClient.PtInRect(point))
	{
		//TRACE("点击客户区\n");
        return HTCLIENT;
    }
    DynamicParam::CScrollBarCtrlParameterRefPtr& pScrollParam =
            p ->GetScrollBarParam( ) ;
    if( pScrollParam ->GetVBar( ).IsVisible( ) )
    {
        if( pScrollParam ->IsLeftScrollBar() )
        {
            pScrollParam ->SetVScrollRect(
                        CRect(rtClient.left - nVWidth,rtClient.top,
						rtClient.left,rtClient.bottom ) );		
			
			const CRect& r = pScrollParam ->GetVScrollRect( );
			//TRACE("special:%d,%d,%d,%d(%d-%d)\n",
			//	r.top,r.left,r.bottom,r.right,
			//	point.x,point.y );
        }
        else
        {
			
            pScrollParam ->SetVScrollRect(
                        CRect(rtClient.right,rtClient.top,
                              rtClient.right + nVWidth,rtClient.bottom) );
			//const CRect& r = pScrollParam ->GetVScrollRect( );
			//TRACE("normal:%d,%d,%d,%d(%d-%d)\n",
			//	r.top,r.left,r.bottom,r.right,
			//	point.x,point.y );
        }
        if( TRUE == pScrollParam ->GetVScrollRect().PtInRect(point) )
		{
			//TRACE("点击垂直滚动条\n");
            return HTVSCROLL;
        }
    }
	else
	{
		//TRACE("无垂直滚动条\n");
	}
    if( pScrollParam ->GetHBar( ).IsVisible() )
    {
        pScrollParam ->SetHScrollRect(
                    CRect(rtClient.left,rtClient.bottom,
                          rtClient.right,rtClient.bottom + nHHeight) );

        if( TRUE == pScrollParam ->GetHScrollRect().PtInRect(point) )
		{
			//TRACE("点击水平滚动条\n");
            return HTHSCROLL;
        }
    }
	else
	{
		//TRACE("无水平滚动条点击水平滚动条\n");
	}

    if( p ->HasMenu() )
    {
        int nMenuHeight = GetSystemMetrics(SM_CYMENU);
        p ->SetMenuRect(
                    CRect(rtWindow.left + rtMargin.left,
                          rtWindow.top+ rtMargin.top,rtWindow.right - rtMargin.right,
                          rtWindow.top + rtMargin.top + nMenuHeight ) );
        if( TRUE == p ->GetMenuRect().PtInRect(point))
		{
			//TRACE("点击按钮\n");
            return HTMENU;
        }
    }

    // 判断点击了哪个系统按钮
    UINT nHitTest = p ->HitButtonTest( point);
    if(!p ->HasTitle() )
    {
        if( nHitTest == HTSYSMENU ||
                nHitTest == HTHELP ||
                nHitTest == HTMINBUTTON ||
                nHitTest == HTMAXBUTTON ||
                nHitTest == HTCLOSE ||
                nHitTest == HTCAPTION  )
		{
			//TRACE("点击边框1\n");
            return HTBORDER;
        }
    }
    if(!p ->IsSizable() )
    {
        if(nHitTest == HTTOPLEFT ||
                nHitTest == HTTOPRIGHT ||
                nHitTest == HTLEFT ||
                nHitTest == HTRIGHT ||
                nHitTest == HTBOTTOMLEFT ||
                nHitTest == HTBOTTOM ||
                nHitTest == HTBOTTOMRIGHT )
		{
			//TRACE("点击边框2\n");
            //nHitTest = HTBORDER;
			return HTBORDER;
        }
    }
	//TRACE("点击其它:0x%0X\n",nHitTest);
    return nHitTest;
}

BOOL CDialogBoxSkin::OnNcActivate( BOOL bActive )
{
    if( IsNull() )
    {
        return FALSE;
    }
	// 
    bool bStatus = i2b( bActive );
    GetCurParam( ) ->SetActivated( bStatus );
    if( FALSE == IsIconic(m_hWnd))
    {
        OnNcPaint(0);
    }
    return bStatus?FALSE:TRUE;
}

void CDialogBoxSkin::OnNcCalcSize( bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if( IsNull() )
	{
		OnAutoDefaultWndProc();
		return;
	}
    LPRECT lpRect = &(lpncsp->rgrc[0]);
	CParamReference* p = GetCurParam();
	HWND hWnd = GetCurHwnd();
    DynamicParam::SetScrollBarParamVisible(
                hWnd,
				p ->GetScrollBarParam( ) );

    if( p ->HasBorder( ) )
    {
        const CRect& rectMargin = p ->GetMargin( );
        lpncsp->rgrc[0].left += rectMargin.left;
        lpncsp->rgrc[0].top += rectMargin.top;
        lpncsp->rgrc[0].right -= rectMargin.right;
        lpncsp->rgrc[0].bottom -= rectMargin.bottom;

        lpncsp->rgrc[1] = lpncsp->rgrc[0];
    }

    if ( p ->HasMenu( ) )
    {
        lpRect->top += GetSystemMetrics(SM_CYMENU);
    }
    DynamicParam::CScrollBarBasic& vBar =
            GetCurParam( ) ->GetScrollBarParam( ) ->GetVBar( );

    if( vBar.IsVisible() )
    {
		int nVScollWidth = GetSystemMetrics(SM_CXVSCROLL);
        if( lpRect->right - lpRect->left >= nVScollWidth )
        {
            if( p ->GetScrollBarParam( ) ->IsLeftScrollBar() )
            {
                lpRect->left  += nVScollWidth;
            }
            else
            {
                lpRect->right -= nVScollWidth;
            }
        }
    }
    DynamicParam::CScrollBarBasic& hBar =
            GetCurParam( ) ->GetScrollBarParam( ) ->GetHBar( );
    if ( hBar.IsVisible() )
    {
		int nVBarHeight = GetSystemMetrics(SM_CYHSCROLL);
        if( lpRect->bottom - lpRect->top > nVBarHeight )
		{
			//lpRect->top = lpRect ->bottom - nVBarHeight;
            lpRect->bottom -= nVBarHeight;
		}
    }

}

void CDialogBoxSkin::OnNcPaint(HRGN rgn1)
{
    if(IsNull() )
    {
        return;
    }
    DynamicParam::SetScrollBarParamVisible(
                GetCurHwnd(), GetCurParam( ) ->GetScrollBarParam( ) );

    CRect rtWindow;
    GetWindowRect( m_hWnd, &rtWindow );
    CRect rtClient;
    GetClientRect( m_hWnd ,&rtClient);
    ClientToScreen( m_hWnd ,&rtClient);
    rtClient.OffsetRect(-rtWindow.left,-rtWindow.top);

    rtWindow.OffsetRect(-rtWindow.left,-rtWindow.top);

    Util::CTempWindowDC wdc(m_hWnd);
    HDC hdc = wdc;
    int nOldMode = SetBkMode( hdc, TRANSPARENT );
    //DWORD dwErrorCode = GetLastError( );
    HRGN hRgn = CreateNcRgn(hdc,rtWindow);
    //dwErrorCode = GetLastError( );
    //	SelectClipRgn( hdc ,hRgn );
    if( GetCurParam( ) ->HasTitle( ) )
    {
        DrawCaption( hdc );
    }

    if( GetCurParam( ) ->HasMenu( ) )
    {
        DrawMenuBar( hdc );
    }
    if( GetCurParam( ) ->GetScrollBarParam( ) ->GetHBar( ).IsVisible( ) )
    {
        GetScrollBarCtrlSkin().DrawHScrollBar(
                    GetCurHwnd(), GetCurParam( ) ->GetScrollBarParam( ) );
    }
    if( GetCurParam( ) ->GetScrollBarParam( ) ->GetVBar( ).IsVisible( ) )
    {
        GetScrollBarCtrlSkin().DrawVScrollBar(
                    GetCurHwnd(), GetCurParam( ) ->GetScrollBarParam( ) );
    }
    if( GetCurParam() ->HasBorder() )
    {
        DrawNcMargin( hdc, rtWindow, GetCurParam() ->IsActivated(),
                      CPE::WBKIP_Left );

        DrawNcMargin( hdc, rtWindow, GetCurParam() ->IsActivated(),
                      CPE::WBKIP_Bottom );

        DrawNcMargin( hdc, rtWindow, GetCurParam() ->IsActivated(),
                      CPE::WBKIP_Right );
    }
    DynamicParam::CScrollBarCtrlParameterRefPtr& pScrollBar =
            GetCurParam() ->GetScrollBarParam();
    if( pScrollBar ->GetHBar().IsVisible() &&
            pScrollBar ->GetVBar().IsVisible() )
    {
        CRect rtSizing;
        if( pScrollBar ->IsLeftScrollBar() )
        {
            rtSizing = CRect(
                        rtClient.right - GetSystemMetrics(SM_CXVSCROLL),
                        rtClient.bottom,
                        rtClient.right,
                        rtClient.bottom + GetSystemMetrics(SM_CYHSCROLL) );
        }
        else
        {
            rtSizing = CRect(
                        rtClient.right,
                        rtClient.bottom,
                        rtClient.right + GetSystemMetrics(SM_CXVSCROLL),
                        rtClient.bottom + GetSystemMetrics(SM_CYHSCROLL) );
        }
        GetScrollBarCtrlSkin().DrawSizing(
                    GetCurHwnd(), rtSizing );
    }
    DeleteObject( hRgn );
}

HRGN CDialogBoxSkin::CreateNcRgn(  HDC hdc, const CRect& rect )
{
    if( NULL == hdc || TRUE == rect.IsRectEmpty( ))
    {
        return NULL;
    }
    HDC hMemDC = CreateCompatibleDC( hdc );
    HBITMAP hMemBmp = CreateCompatibleBitmap(
                hdc, rect.right, rect.bottom );
    HGDIOBJ hOldBmp = SelectObject(  hMemDC, hMemBmp );

    const CRect& rectMargins = GetCurParam() ->GetMargin( );
    CRect			rectNcPart;
    // 顶部
    rectNcPart.left	= rect.left + rectMargins.left;
    rectNcPart.top		= rect.top;
    rectNcPart.right	= rect.right - rectMargins.right;
    rectNcPart.bottom	= rect.top + rectMargins.top;
    DrawBmp( hMemDC,rectNcPart, m_pBmpActiveNcBk[CPE::WBKIP_Top] );

    rectNcPart.left	= rect.right - rectMargins.right;
    rectNcPart.top		= rect.top ;
    rectNcPart.right	= rect.right;
    rectNcPart.bottom	= rect.bottom;
    DrawBmp( hMemDC,rectNcPart, m_pBmpActiveNcBk[CPE::WBKIP_Right] );

    rectNcPart.left	= rect.left;
    rectNcPart.top		= rect.top ;
    rectNcPart.right	= rect.left + rectMargins.left;
    rectNcPart.bottom	= rect.bottom;
    DrawBmp( hMemDC,rectNcPart,m_pBmpActiveNcBk[CPE::WBKIP_Left]);

    rectNcPart.left	= rect.left + rectMargins.left;
    rectNcPart.top		= rect.bottom - rectMargins.bottom;
    rectNcPart.right	= rect.right - rectMargins.right;
    rectNcPart.bottom	= rect.bottom;
    DrawBmp( hMemDC,rectNcPart,m_pBmpActiveNcBk[CPE::WBKIP_Bottom]);

    HRGN hRgn = Util::CreateRegionByBitmap( hMemBmp, RGB(255,0,255) );

    SelectObject( hMemDC, hOldBmp );
    DeleteDC( hMemDC );
    DeleteObject( hMemBmp );

    return hRgn;
}

void CDialogBoxSkin::DrawNcMargin( 
        HDC hdc, const CRect& r, bool bIsActive, CPE::WindowBackgroundImagePart nPart )
{
    CRect rectBk = r;
    const CRect& rectMargin = GetCurParam( ) ->GetMargin( );
    switch( nPart )
    {
    case CPE::WBKIP_Top:
        rectBk.left += rectMargin.left;
        rectBk.right -= rectMargin.right;
        rectBk.bottom = rectBk.top + rectMargin.top;
        break;
    case CPE::WBKIP_Left:
        rectBk.right	= rectBk.left + rectMargin.left;
        break;
    case CPE::WBKIP_Bottom:
        rectBk.left	+= rectMargin.left;
        rectBk.top	= rectBk.bottom - rectMargin.bottom;
        rectBk.right -= rectMargin.right;
        break;
    case CPE::WBKIP_Right:
        rectBk.left = rectBk.right- rectMargin.right;
        break;
    default:
        ASSERT(nPart >= CPE::WBKIP_Top &&
               nPart < CPE::WBKIP_Size );
        return;
        break;
    }
    DrawBmp( hdc, rectBk, bIsActive?
                 m_pBmpActiveNcBk[nPart]:m_pBmpUnActiveNcBk[nPart] );
}

void CDialogBoxSkin::OnSysCommand(UINT nID,LPARAM lParem)
{
    switch ( nID )
    {
    case SC_VSCROLL:
    {
        // 垂直滚动事件追踪
        GetScrollBarCtrlSkin()
                .TrackScrollBar(
                    GetCurHwnd(),
                    GetCurParam() ->GetScrollBarParam(),
                    SB_VERT,
                    CPoint(LOWORD(lParem),HIWORD(lParem) ) );
    }
        break;
    case SC_HSCROLL:
    {
        // 水平滚动事件追踪
        GetScrollBarCtrlSkin()
                .TrackScrollBar(
                    GetCurHwnd(),
                    GetCurParam() ->GetScrollBarParam(),
                    SB_HORZ,
                    CPoint(LOWORD(lParem),HIWORD(lParem) ) );
    }
        break;
    case SC_MOUSEMENU:
    {
        HWND hWnd = GetCurHwnd();
        CPoint pt(LOWORD(lParem),HIWORD(lParem));
        CRect rtWindow;
        GetWindowRect( hWnd,&rtWindow);
        pt.Offset(-rtWindow.left,-rtWindow.top);
        LoadMenuBarCtrlSkin( )
                .OnLButtonDown(HTMENU,pt);

    }
        break;
    case SC_MINIMIZE: //最大化
    {
        HWND hWnd = GetCurHwnd();
        // 是当前的窗口
        if ( hWnd == GetForegroundWindow() )
        { // 显示菜单
            ShowOwnedPopups(hWnd,FALSE);
        }
        ShowWindow( hWnd, SW_MINIMIZE );
    }
        break;
    case SC_MAXIMIZE:
    {
        HWND hWnd = GetCurHwnd();
        if ( TRUE == IsIconic(hWnd) && hWnd == GetForegroundWindow())
        {
            ShowOwnedPopups(hWnd,TRUE);
        }
        ShowWindow( hWnd, SW_MAXIMIZE );
    }
        break;
    case SC_RESTORE:
    {
        HWND hWnd = GetCurHwnd();
        // 图标最小化 + 当前窗口
        if ( TRUE == IsIconic(hWnd) &&
             m_hWnd == GetForegroundWindow())
        {
            //
            ShowOwnedPopups(hWnd,TRUE);
        }
        ShowWindow( hWnd, SW_RESTORE );
    }
        break;
    case SC_CLOSE:
    {
        // 关闭
		SendMessage( GetCurHwnd(), WM_CLOSE, 0, 0 );
        return ;
    }
    default:
        OnAutoDefaultWndProc();
        break;
    }

    return;


}

BOOL CDialogBoxSkin::OnEraseBkgnd(HDC hdc )
{
    OnAutoDefaultWndProc( );
    return TRUE;
}

void CDialogBoxSkin::OnSize(UINT nType,int cx,int cy)
{
    OnNcPaint( NULL );
    OnAutoDefaultWndProc( );
}

void CDialogBoxSkin::OnSetText(WPARAM wp,LPARAM lp)
{
    OnAutoDefaultWndProc( );
    //	DrawCaption(pDC);
    OnNcPaint(NULL);
}

LRESULT CDialogBoxSkin::OnSetIcon(UINT nFlag,HICON hIcon)
{
    OnAutoDefaultWndProc( );
    DrawCaption( Util::CTempWindowDC(m_hWnd) );
    return 0;
}

void CDialogBoxSkin::OnEnable(BOOL bEnable)
{
    OnAutoDefaultWndProc( );
}

void CDialogBoxSkin::OnTimer(UINT_PTR nIDEvent)
{
    if( !IsNull() && MenuTrackTimerId == nIDEvent )
    {
        HWND hWnd = GetCurHwnd();
        CParamReference* p = GetCurParam();
        CPoint pt;
        GetCursorPos(&pt);
        const LRESULT nHit = OnNcHitTest(pt);
        if( nHit != HTMENU)
        {
            DynamicParam::CMenubarCtrlSkinParameterRefPtr
                    pMenBar = p ->GetMenuBarParamPtr( );
            KillTimer(m_hWnd,MenuTrackTimerId);
            pMenBar ->SetHot( NULL );
            pMenBar ->SetPressed( NULL );
            LoadMenuBarCtrlSkin( ).DrawMenuBar( );
            p ->SetInMenu( false );
        }
    }
    OnAutoDefaultWndProc( );
}


void CDialogBoxSkin::HandleMenuBarEvent(UINT msg,  const CPoint& pt)
{

}

void CDialogBoxSkin::TrackMenuBar(const CPoint& point)
{
    if( IsNull() )
    {
        return;
    }
    HWND hWnd = GetCurHwnd();
    const CRect& rtWindow =
            Util::CTempRelativeWindowRect( hWnd );

    LoadMenuBarCtrlSkin( )
            .OnLButtonDown( HTMENU,
                            CPoint(
                                point.x -rtWindow.left,
                                point.y - rtWindow.top ) );
}

void CDialogBoxSkin::DrawFrame( HDC hdc )
{

}

void CDialogBoxSkin::DrawCaption( HDC hdc )
{
    if( IsNull() )
    {
        return;
    }
    HWND hWnd = GetCurHwnd( );
    CParamReference* p = GetCurParam();
    CRect rtWindow = Util::CTempAbsoluteWindowRect( hWnd );


    const CRect& rtMargins = p->GetMargin( );
    CRect			rtParts(
                rtWindow.left + rtMargins.left,
                rtWindow.top,
                rtWindow.right - rtMargins.right,
                rtWindow.top + rtMargins.top );
    HDC hMemDC =  hdc;
    //CreateCompatibleDC( hdc );
    //HBITMAP hMemBmp = CreateCompatibleBitmap(
    //	hdc, rtParts.Width(),rtParts.Height() );

    DrawNcMargin(
                hMemDC,
                rtWindow,
                p ->IsActivated(),
                CPE::WBKIP_Top );

    if( p ->HasCloseButton() )
    { // 绘制关闭按钮
        DrawWindowButton( hMemDC, rtWindow, CPE::WB_Close,
                          p ->GetCloseButtonState() );
    }
    if( true )
    {
        if( p ->HasMaxButton() )
        { // 绘制最大化/恢复按钮
            if(IsZoomed(m_hWnd))
            {
                DrawWindowButton(
                            hMemDC,
                            rtWindow,
                            CPE::WB_Restore,
                            p ->GetMaxButtonState() );
            }
            else
            {
                DrawWindowButton(
                            hMemDC,
                            rtWindow,
                            CPE::WB_Max,
                            p ->GetMaxButtonState() );
            }
        }
        if( p ->HasMinButton() )
        { // 绘制最小化按钮
            DrawWindowButton(
                        hMemDC,
                        rtWindow,
                        CPE::WB_Min,
                        p ->GetMinButtonState() );
        }

        // 获取左上角图标
        HICON hIcon = (HICON)::SendMessage(m_hWnd, WM_GETICON, 0, 0);;
        if( NULL == hIcon )
        {
#ifdef _WIN64
            hIcon = (HICON)GetClassLongPtr(m_hWnd,GCLP_HICONSM );
#else
            hIcon = (HICON)GetClassLong(m_hWnd,GCL_HICONSM );
#endif
        }
        CRect rtTitleText;
        if( NULL != hIcon )
        {
            CPoint pt;
            pt.x = rtParts.left + 2;
            pt.y = (rtParts.bottom + rtParts.top - GetSystemMetrics(SM_CYSMICON)) / 2;
            DrawIconEx(
                        hMemDC,
                        pt.x,pt.y,
                        hIcon,
                        GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),
                        0, 0, DI_NORMAL );
            rtTitleText = rtParts;
            rtTitleText.left = rtParts.bottom - rtParts.top;
        }
        else
        {
            rtTitleText = rtParts;
            rtTitleText.left = 5;
        }


        int nOldMode = SetBkMode( hMemDC,TRANSPARENT);
        TCHAR szBuf[MAX_PATH] = {0};
        GetWindowText(hWnd, szBuf, sizeof(szBuf)/sizeof(TCHAR) );

        NONCLIENTMETRICS nif;
        nif.cbSize = sizeof(nif);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),&nif,0);
        HFONT hFont = CreateFontIndirect(&nif.lfSmCaptionFont);
        SelectObject(hMemDC, hFont );


        // 绘制窗口标题
        SetTextColor( hMemDC, RGB(0,0,0) );
        DrawText( hMemDC, szBuf,-1,
                  &rtTitleText,
                  DT_LEFT | DT_VCENTER|DT_SINGLELINE);
    }
    //OpenClipboard( NULL );
    //EmptyClipboard( );
    //SetClipboardData( CF_BITMAP, hMemBmp );
    //CloseClipboard();

    //BitBlt( hdc, rtParts.left, rtParts.top,
    //	rtParts.Width(),rtParts.Height(),
    //	hMemDC, rtParts.left, rtParts.Height(),
    //	SRCCOPY );
    //DeleteDC( hMemDC );
    //DeleteObject( hMemBmp );

    if( p ->HasMenu() )
    { // 绘制菜单栏
        DrawMenuBar( hdc );
    }
}

void CDialogBoxSkin::DrawWindowButton( )
{
    Util::CTempWindowDC wdc(GetCurHwnd( ));
    DrawWindowButton( wdc );
}

void CDialogBoxSkin::DrawWindowButton( HDC hdc )
{
    if( IsNull() )
    {
        return;
    }
    HWND hWnd = GetCurHwnd();
    //窗口尺寸
    CRect rectWindow = Util::CTempAbsoluteWindowRect(hWnd);
    CParamReference* p = GetCurParam( );
    // 有标题
    if( p ->HasTitle( ) )
    {
        // 关闭按钮
        if( p ->HasCloseButton() )
        {
            DrawWindowButton( hdc, rectWindow,
                              CPE::WB_Close, p ->GetCloseButtonState() );
        }

        // 最大化按钮
        if( p ->HasMaxButton())
        {
            if(TRUE == IsZoomed(hWnd))
            { // 处于最小化，恢复按钮
                DrawWindowButton( hdc, rectWindow,
                                  CPE::WB_Restore, p ->GetMaxButtonState() );
            }
            else
            {
                DrawWindowButton( hdc, rectWindow,
                                  CPE::WB_Max, p ->GetMaxButtonState() );
            }
        }

        // 最小化按钮
        if( p ->HasMinButton() )
        {
            DrawWindowButton( hdc, rectWindow,
                              CPE::WB_Min, p ->GetMinButtonState() );
        }
    }
}


void CDialogBoxSkin::DrawWindowButton(
        HDC hdc, const CRect rectWindow,
        CPE::WindowButton buttonType,
        CPE::WindowButtonState buttonState )
{
    CWindowButtonParam& buttonParam = m_paramButtons[buttonType];
    const CRect& r = buttonParam.GetWindowButtonRect( rectWindow );
    buttonParam.GetStateBitmap( buttonState );

	//CRect rectTemp = r;
	//ClientToScreen( m_hWnd, &rectTemp );
 //   TRACE("draw-CLOSE-RECT:%d,%d,%d,%d\n",
 //         rectTemp.left,rectTemp.top,rectTemp.bottom,rectTemp.right);

    DrawBmp( hdc,
             buttonParam.GetWindowButtonRect( rectWindow ),
             buttonParam.GetStateBitmap( buttonState ) );
}

void CDialogBoxSkin::DrawMenuBar( HDC hdc )
{
    LoadMenuBarCtrlSkin( ).DrawMenuBar();
}

DynamicParam::CMenubarCtrlSkin& CDialogBoxSkin::LoadMenuBarCtrlSkin( )
{
	DynamicParam::CMenubarCtrlSkin& skin = GetMenuBarCtrlSkin( );
	skin.Init( GetCurHwnd(), GetCurParam() ->GetMenuBarParamPtr() );
	return skin;
}
bool CDialogBoxParameter::HasMaxButton() const
{
    return m_bMaxBtn;
}

void CDialogBoxParameter::SetHasMaxButton(bool bHasMaxButton)
{
    m_bMaxBtn = bHasMaxButton;
}

bool CDialogBoxParameter::HasMinButton() const
{
    return m_bMinBtn;
}

void CDialogBoxParameter::SetHasMinButton(bool bHasMinButton)
{
    m_bMinBtn = bHasMinButton;
}


bool CDialogBoxParameter::HasCloseButton( ) const
{
    return m_bCloseBtn;
}

void CDialogBoxParameter::SetHasCloseButton( bool bHasCloseButton )
{
    m_bCloseBtn = bHasCloseButton;
}


bool CDialogBoxParameter::IsActivated( ) const
{
    return m_bIsActivated;
}

void CDialogBoxParameter::SetActivated( bool bActivated )
{
    m_bIsActivated = bActivated;
}

CPE::MouseState CDialogBoxParameter::GetNcMouseState( ) const
{
    return m_nNcMouseState;
}

void CDialogBoxParameter::SetNcMouseState( CPE::MouseState state )
{
    m_nNcMouseState = state;
}

CPE::WindowButtonState CDialogBoxParameter::GetMaxButtonState() const
{
    return m_nMaxBtnState;
}

void CDialogBoxParameter::SetMaxButtonState(CPE::WindowButtonState nMaxButtonState)
{
    m_nMaxBtnState = nMaxButtonState;
}

CPE::WindowButtonState CDialogBoxParameter::GetMinButtonState() const
{
    return m_nMinBtnState;
}

void CDialogBoxParameter::SetMinButtonState(CPE::WindowButtonState nMinButtonState)
{
    m_nMinBtnState = nMinButtonState;
}

CPE::WindowButtonState CDialogBoxParameter::GetCloseButtonState() const
{
    return m_nCloseBtnState;
}

void CDialogBoxParameter::SetCloseButtonState(CPE::WindowButtonState nCloseButtonState)
{
    m_nCloseBtnState = nCloseButtonState;
}

CPE::WindowButtonState CDialogBoxParameter::GetHelpButtonState() const
{
    return m_nHelpBtnState;
}

void CDialogBoxParameter::SetHelpButtonState(CPE::WindowButtonState nHelpButtonState)
{
    m_nHelpBtnState = nHelpButtonState;
}

CPE::WindowHitType CDialogBoxParameter::GetSelelectedButtonType() const
{
    return m_nSelBtnType;
}

void CDialogBoxParameter::SetSelectedButtonType(CPE::WindowHitType nSelelectedButtonType)
{
    m_nSelBtnType = nSelelectedButtonType;
}


bool CDialogBoxParameter::IsSizable( ) const
{
    return m_bSizable;
}

void CDialogBoxParameter::SetSizable( bool bSizable )
{
    m_bSizable = bSizable;
}

bool CDialogBoxParameter::IsInMenu() const
{
    return m_bInMenu;
}

void CDialogBoxParameter::SetInMenu(bool bInMenu)
{
    m_bInMenu = bInMenu;
}

DynamicParam::CMenubarCtrlSkinParameterRefPtr
CDialogBoxParameter::GetMenuBarParamPtr()
{
    return m_pMenuBarParam;
}

const DynamicParam::CMenubarCtrlSkinParameterRefPtr
CDialogBoxParameter::GetMenuBarParamPtr() const
{
    return m_pMenuBarParam;
}

void CDialogBoxParameter::SetMenuBarParamPtr(
        const DynamicParam::CMenubarCtrlSkinParameterRefPtr pMenuBarParam)
{
    if( 0x0000054100000004 == int( pMenuBarParam.get()) )
    {
        int i = 0;
        ++i;
    }
    m_pMenuBarParam = pMenuBarParam;
}

bool CDialogBoxParameter::HasMenu() const
{
    return m_bHasMenu;
}

void CDialogBoxParameter::SetHasMenu(bool bMenu)
{
    m_bHasMenu = bMenu;
}

const CRect& CDialogBoxParameter::GetWindowRect( ) const
{
    return m_rectWindow;
}

CRect& CDialogBoxParameter::GetWindowRect( )
{
    return m_rectWindow;
}

void CDialogBoxParameter::SetWindowRect( const CRect& rectWindow )
{
    m_rectWindow = rectWindow;
}

const CRect& CDialogBoxParameter::GetMargin( )const
{
    return m_rectMargins;
}

CRect& CDialogBoxParameter::GetMargin( )
{
    return m_rectMargins;
}

void CDialogBoxParameter::SetMargin( const CRect& rectMargin )
{
    m_rectMargins = rectMargin;
}

bool CDialogBoxParameter::HasTitle() const
{
    return m_bTitle;
}

void CDialogBoxParameter::SetHasTitle(bool bHasTitle)
{
    m_bTitle = bHasTitle;
}



void CDialogBoxParameter::UpdatePartRect( const CRect& rectWindow )
{
    if(m_rectWindow == rectWindow )
    {
        return;
    }
    m_rectWindow = rectWindow;

    m_rectParts[CPE::WP_TopLeft].SetRect(
                rectWindow.left, rectWindow.top, //左，上
                rectWindow.left + m_rectMargins.left, //右
                rectWindow.top + m_rectMargins.top ); //下

    m_rectParts[CPE::WP_Top].SetRect(
                rectWindow.left + m_rectMargins.left,
                rectWindow.top,
                rectWindow.right - m_rectMargins.right,
                rectWindow.top + m_rectMargins.top );

    m_rectParts[CPE::WP_TopBorder] = m_rectParts[CPE::WP_Top];
    m_rectParts[CPE::WP_TopBorder].bottom =
            m_rectParts[CPE::WP_TopBorder].top + m_rectMargins.bottom;

    m_rectParts[CPE::WP_TopRight].SetRect(
                rectWindow.right - m_rectMargins.right,
                rectWindow.top, rectWindow.right,
                rectWindow.top + m_rectMargins.top );

    m_rectParts[CPE::WP_Left].SetRect(
                rectWindow.left,
                rectWindow.top + m_rectMargins.top,
                rectWindow.left + m_rectMargins.left,
                rectWindow.bottom - m_rectMargins.bottom );

    m_rectParts[CPE::WP_Right].SetRect(
                rectWindow.right - m_rectMargins.right,
                rectWindow.top + m_rectMargins.top,
                rectWindow.right,
                rectWindow.bottom - m_rectMargins.bottom );

    m_rectParts[CPE::WP_BottomLeft].SetRect(
                rectWindow.left,
                rectWindow.bottom - m_rectMargins.bottom,
                rectWindow.left + m_rectMargins.left,
                rectWindow.bottom );

    m_rectParts[CPE::WP_Bottom].SetRect(
                rectWindow.left + m_rectMargins.left,
                rectWindow.bottom - m_rectMargins.bottom,
                rectWindow.right - m_rectMargins.right,
                rectWindow.bottom );

    m_rectParts[CPE::WP_BottomRight].SetRect(
                rectWindow.right - m_rectMargins.right,
                rectWindow.bottom - m_rectMargins.bottom,
                rectWindow.right,
                rectWindow.bottom );
}

const CRect& CDialogBoxParameter::GetPartRect( CPE::WindowPart wp ) const
{
    ASSERT( wp >= CPE::WP_TopLeft && wp < CPE::WP_Size );
    return m_rectParts[wp];
}

CRect& CDialogBoxParameter::GetPartRect( CPE::WindowPart wp )
{
    ASSERT( wp >= CPE::WP_TopLeft && wp < CPE::WP_Size );
    return m_rectParts[wp];
}

void CDialogBoxParameter::SetPartRect( CPE::WindowPart wp, const CRect& rect )
{
    ASSERT( wp >= CPE::WP_TopLeft && wp < CPE::WP_Size );
    m_rectParts[wp] = rect;
}
void CDialogBoxParameter::UpdateButtonRect(
        const CRect& rectWindow,
        const CWindowButtonParam (&paramButtons)[CPE::WB_Size] )
{
    for( int i = 0; i < CPE::WB_Size; ++i )
    {
        m_rectButtons[i] = paramButtons[i].GetWindowButtonRect( rectWindow);
    }
}

const CRect& CDialogBoxParameter::GetButtonRect( CPE::WindowButton wb ) const
{
    ASSERT( wb >= CPE::WB_System && wb < CPE::WB_Size );
    return m_rectButtons[wb];
}
CRect& CDialogBoxParameter::GetButtonRect( CPE::WindowButton wb )
{
    ASSERT( wb >= CPE::WB_System && wb < CPE::WB_Size );
    return m_rectButtons[wb];
}

void CDialogBoxParameter::SetButtonRect( CPE::WindowButton wb, const CRect& rect )
{

    ASSERT( wb >= CPE::WB_System && wb < CPE::WB_Size );
    m_rectButtons[wb] = rect;
}
UINT CDialogBoxParameter::HitButtonTest( const CPoint& pt )
{
    //TRACE("[hit-Test]rect(%d,%d,%d-%d),point:%d,%d\n",
    //      m_rectButtons[CPE::WB_Close].left,
    //        m_rectButtons[CPE::WB_Close].top,
    //        m_rectButtons[CPE::WB_Close].bottom,
    //        m_rectButtons[CPE::WB_Close].right,
    //        pt.x, pt.y );
    if( TRUE == m_rectButtons[CPE::WB_System].PtInRect(pt))
    {
        return HTSYSMENU;
    }
    else if( TRUE == m_rectButtons[CPE::WB_Help].PtInRect(pt) )
    {
        return HTHELP;
    }
    else if( TRUE == m_rectButtons[CPE::WB_Min].PtInRect(pt))
    {
        return HTMINBUTTON;
    }
    else if( TRUE == m_rectButtons[CPE::WB_Max].PtInRect(pt))
    {
        return HTMAXBUTTON;
    }
    else if( TRUE == m_rectButtons[CPE::WB_Close].PtInRect(pt))
    {
        return HTCLOSE;
    }
    else if( TRUE == m_rectParts[CPE::WP_TopLeft].PtInRect(pt))
    {
        return HTTOPLEFT;
    }
    else if( TRUE == m_rectParts[CPE::WP_TopBorder].PtInRect(pt))
    {
        return HTTOP;
    }
    else if( TRUE == m_rectParts[CPE::WP_Top].PtInRect(pt))
    {
        return HTCAPTION;
    }
    else if( TRUE == m_rectParts[CPE::WP_TopRight].PtInRect(pt))
    {
        return HTTOPRIGHT;
    }
    else if( TRUE == m_rectParts[CPE::WP_Left].PtInRect(pt))
    {
        return HTLEFT;
    }
    else if( TRUE == m_rectParts[CPE::WP_Right].PtInRect(pt))
    {
        return HTRIGHT;
    }
    else if( TRUE == m_rectParts[CPE::WP_BottomLeft].PtInRect(pt))
    {
        return HTBOTTOMLEFT;
    }
    else if( TRUE == m_rectParts[CPE::WP_Bottom].PtInRect(pt))
    {
        return HTBOTTOM;
    }
    else if( TRUE == m_rectParts[CPE::WP_BottomRight].PtInRect(pt))
    {
        return HTBOTTOMRIGHT;
    }
    return HTNOWHERE;
}

const CRect& CDialogBoxParameter::GetMenuRect( ) const
{
    return m_rectMenu;
}

void CDialogBoxParameter::SetMenuRect( const CRect& rect )
{
    m_rectMenu = rect;
}

void CWindowButtonParam::SetPosRect( const CRect& rectPos )
{
    m_rectPos = rectPos;
}

const CRect& CWindowButtonParam::GetPosRect( ) const
{
    return m_rectPos;
}

CRect& CWindowButtonParam::GetPosRect( )
{
    return m_rectPos;
}

void CWindowButtonParam::SetOffsetRect( const CRect& rectOffset )
{
    m_rectOffset = rectOffset;
}

const CRect& CWindowButtonParam::GetOffsetRect( ) const
{
    return m_rectOffset;
}

CRect& CWindowButtonParam::GetOffsetRect( )
{
    return m_rectOffset;
}

void CWindowButtonParam::SetAnchorRect( const CRect& rectAnchor )
{
    m_rectAnchor = rectAnchor;
}

const CRect& CWindowButtonParam::GetAnchorRect( ) const
{
    return m_rectAnchor;
}

CRect& CWindowButtonParam::GetAnchorRect( )
{
    return m_rectAnchor;
}

void CWindowButtonParam::UpdateOffsetByRelativeRect( const CRect& rectRelative )
{
    m_rectOffset.left = m_rectPos.left - rectRelative.Width()
            * m_rectAnchor.left/100;
    m_rectOffset.top = m_rectPos.top - rectRelative.Height()
            * m_rectAnchor.top/100;
    m_rectOffset.right	= m_rectPos.right - rectRelative.Width()
            * m_rectAnchor.right/100;
    m_rectOffset.bottom	= m_rectPos.bottom - rectRelative.Height()
            * m_rectAnchor.bottom/100;
}

CRect CWindowButtonParam::GetWindowButtonRect( const CRect& rectWindow ) const
{
    CRect rectPosition;
    rectPosition.left = rectWindow.Width() *
            m_rectAnchor.left/100 + m_rectOffset.left;
    rectPosition.top =
            rectWindow.Height() * m_rectAnchor.top/100 + m_rectOffset.top;
    rectPosition.right	=
            rectWindow.Width() * m_rectAnchor.right/100 + m_rectOffset.right;
    rectPosition.bottom	=
            rectWindow.Height() * m_rectAnchor.bottom/100 + m_rectOffset.bottom;
    rectPosition.OffsetRect(
                rectWindow.left,
                rectWindow.top );
    return rectPosition;
}
CBitmap* CWindowButtonParam::GetStateBitmap( CPE::WindowButtonState state ) const
{
    ASSERT( state >= CPE::WBS_Normal &&
            state < CPE::WBS_Size );
    return m_pBmpState[state];
}

void CWindowButtonParam::SetStateBitmap( CPE::WindowButtonState state, 
                                         const CBitmapRefPtr& pBitmap )
{
    ASSERT( state >= CPE::WBS_Normal &&
            state < CPE::WBS_Size );
    m_pBmpState[state] = pBitmap;
}

}
