#include "StdAfx.h"
#include "GlobalUiManager.h"
#include "ButtonCtrlSkin.h"
#include "EditCtrlSkin.h"
#include "ComboboxCtrlSkin.h"
#include "ListBoxCtrlSkin.h"
#include "ComboLBoxCtrlSkin.h"
#include "CheckBoxCtrlSkin.h"
#include "RadioButtonCtrlSkin.h"
#include "PushButtonCtrlSkin.h"
#include "GroupBoxCtrlSkin.h"
#include "ListCtrlSkin.h"
#include "SysHeaderSkin.h"
#include "DialogBoxSkin.h"
#include "PopupMenuCtrlSkin.h"
#include "TabCtrlSkin.h"
#include "StatusBarCtrlSkin.h"
#include "ToolBarCtrlSkin.h"
#include "TreeCtrlSkin.h"
#include "SpinCtrlSkin.h"
#include "SliderCtrlSkin.h"
#include "ProgressBarCtrlskin.h"
#include "ScrollBarCtrlSkin.h"
#include "MenuBarCtrlSkin.h"

namespace GlobalSkin
{

/** 
 * @brief 当前子窗口中列举其中的按钮
 */
static BOOL CALLBACK ChildWndEnumProc(HWND hWnd, LPARAM lParam)
{
	CGlobalUiManager* pManager = (CGlobalUiManager*)lParam;
	if( NULL != pManager )
	{
		pManager ->Add( hWnd );
	}
	EnumChildWindows(hWnd, ChildWndEnumProc, lParam );
	return TRUE;
}

/** 
 * @brief 查找当前窗口
 */
static BOOL CALLBACK  WndEnumProc(HWND hWnd, LPARAM lParam)
{
	CGlobalUiManager* pManager = (CGlobalUiManager*)lParam;
	if( NULL != pManager )
	{
		pManager ->Add( hWnd );
	}
	EnumChildWindows(hWnd, ChildWndEnumProc, lParam );
	return TRUE;
}

/** 
 * @brief 窗口过程钩子
 */
static LRESULT CALLBACK WndHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = CallNextHookEx( 
		CGlobalUiManager::GetPtr() ->m_pPreviosHook,
		code, wParam, lParam );
	if ((((CWPSTRUCT *) lParam)->message == WM_CREATE) && (code >= 0))
	{
		PCWPSTRUCT pMsg = PCWPSTRUCT (lParam);
		//过滤新窗口创建
		WNDPROC pOldProc = NULL;
		CGlobalUiManager::GetPtr( ) ->Add ( pMsg ->hwnd, &pOldProc );
		if( NULL != pOldProc )
		{
			//pOldProc( pMsg ->hwnd, pMsg ->message, pMsg ->wParam, pMsg ->lParam);
		}
	}
	return lResult;
}

/** 
 * @brief 皮肤的处理过程
 */
static LRESULT CALLBACK ControlSkinProc(
	HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	if( WM_CREATE == nMsg )
	{
		int i = 0;
		++i;
	}
	return ( NULL != CGlobalUiManager::s_pSkinManager )?
	CGlobalUiManager::s_pSkinManager ->HandleWndProc(
			hWnd, nMsg, wParam, lParam ):
	AfxWndProc( hWnd, nMsg, wParam, lParam );
	
}
CGlobalUiManager* CGlobalUiManager::s_pSkinManager = NULL;
CGlobalUiManager::CGlobalUiManager( const CSkinConfig* pConfig )
{
	if( NULL != s_pSkinManager )
	{
		AfxMessageBox(_T("皮肤管理器暂时不允许同时存在多个实例"));
		return;
	}
	s_pSkinManager = this;
	InstallSkin( pConfig );
}

CGlobalUiManager::CGlobalUiManager( const CSkinConfig& config )
{
	if( NULL != s_pSkinManager )
	{
		AfxMessageBox(_T("皮肤管理器暂时不允许同时存在多个实例"));
		return;
	}
	s_pSkinManager = this;
	InstallSkin( &config );
}

CGlobalUiManager::~CGlobalUiManager( )
{
	UninstallSkin( );
	s_pSkinManager = NULL;
}
/** 
 * @brief 安装皮肤
 */
void CGlobalUiManager::InstallSkin( const CSkinConfig* pConfig )
{
	// 如果需要安装新的皮肤，请在这里添加新皮肤即可

	m_vectorCtrlSkins.push_back( new CPushButtonCtrl );      // 按钮皮肤
	m_vectorCtrlSkins.push_back( new CEditCtrlSkin );        // 文本框皮肤
	m_vectorCtrlSkins.push_back( new CComboBoxCtrlSkin );    // 组合框皮肤
	m_vectorCtrlSkins.push_back( new CListBoxCtrlSkin );     // 列表框皮肤
	m_vectorCtrlSkins.push_back( new CComboLBoxCtrlSkin );   // 组合框中的列表框
	m_vectorCtrlSkins.push_back( new CCheckBoxCtrlSkin );    // 复选框
	m_vectorCtrlSkins.push_back( new CRadioButtonCtrlSkin ); // 单选框
	m_vectorCtrlSkins.push_back( new CGroupBoxCtrlSkin );    // groupbox
	m_vectorCtrlSkins.push_back( new CListCtrlSkin );		 // 表格
	m_vectorCtrlSkins.push_back( new CSysHeaderSkin );		 // 标题
	m_vectorCtrlSkins.push_back( new CDialogBoxSkin );		 // 对话框
	m_vectorCtrlSkins.push_back( new CPopupMenuCtrlSkin );	 // 弹出菜单
	m_vectorCtrlSkins.push_back( new CTablCtrlSkin );		 // tab控件
	m_vectorCtrlSkins.push_back( new CTreeCtrlSkin );		 // 树状控件
	m_vectorCtrlSkins.push_back( new CStatusBarCtrlSkin );   // 状态栏
	m_vectorCtrlSkins.push_back( new CToolBarCtrlSkin );     // 工具栏
	m_vectorCtrlSkins.push_back( new CSpinCtrlSkin );		 // Spin
	m_vectorCtrlSkins.push_back( new CSilderCtrlSkin );		 // 滑块
	m_vectorCtrlSkins.push_back( new CProgressBarCtrlSkin ); // 进度条

	m_pScrollBarCtrlSkin = new DynamicParam::CScrollBarCtrlSkin;
	m_pMenuBarCtrlSkin = new DynamicParam::CMenubarCtrlSkin;
	m_pScrollBarCtrlSkin ->LoadSkin(pConfig);
	m_pMenuBarCtrlSkin ->LoadSkin( pConfig );
	void* p1 = &m_pScrollBarCtrlSkin;
	void* p2 = &m_pMenuBarCtrlSkin;
	int nSize = sizeof(p1);
	for( std::size_t i = 0; i< m_vectorCtrlSkins.size(); ++i )
	{
		CCtrlSkin* pCtrl = m_vectorCtrlSkins.at(i);
		pCtrl ->SetUiManager( this );
		pCtrl ->LoadSkin( pConfig );
	}
	// 替换当前窗口的控件
	EnumThreadWindows(GetCurrentThreadId(), WndEnumProc, (LPARAM)this ); 

	// 新增窗口替换
	m_pPreviosHook  = SetWindowsHookEx(
		WH_CALLWNDPROC,  WndHookProc , NULL,  GetCurrentThreadId() );
}

/** 
 * @brief 卸载皮肤
 */
void CGlobalUiManager::UninstallSkin( )
{
	if(FALSE == UnhookWindowsHookEx(m_pPreviosHook) )
	{
		TRACE(_T("UnhokkWindowsHookEx失败:%d"),GetLastError() );
	}
	m_pPreviosHook = NULL;
	m_vectorCtrlSkins.clear();
}

bool CGlobalUiManager::Add( HWND hWnd,WNDPROC* pOldProc )
{
	switch ( GetWindowLong( hWnd, GWL_STYLE ) & SS_TYPEMASK)
	{
	case BS_OWNERDRAW:  
		//跳过自绘制按钮
		return NULL;
	}

	for( std::vector<CCtrlSkinPtr>::iterator it = m_vectorCtrlSkins.begin();
		it != m_vectorCtrlSkins.end(); ++it )
	{
		if( (*it)->AddControl( hWnd, ControlSkinProc,pOldProc ) )
		{
			return true;
		}
	}
	return false;
}

bool CGlobalUiManager::Remove( HWND hWnd )
{

	for( std::vector<CCtrlSkinPtr>::iterator it = m_vectorCtrlSkins.begin();
		it != m_vectorCtrlSkins.end(); ++it )
	{
		if( (*it) ->RemoveControl( hWnd) )
		{
			return true;
		}
	}
	return false;
}


DynamicParam::CScrollBarCtrlSkin* CGlobalUiManager::GetScrollBarCtrlSkin( )
{
	return m_pScrollBarCtrlSkin;
}

DynamicParam::CMenubarCtrlSkin* CGlobalUiManager::GetMenuBarCtrlSkin( )
{
	return m_pMenuBarCtrlSkin;
}

LRESULT CGlobalUiManager::HandleWndProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//查找
	sCtrlParameter* pParam = NULL;
	CCtrlSkin* pSkin = NULL;
	for( std::vector<CCtrlSkinPtr>::iterator it = m_vectorCtrlSkins.begin();
		it != m_vectorCtrlSkins.end(); ++it )
	{
		if( (*it) ->CheckOwner( hWnd, pParam ) )
		{
			pSkin = it->get();
			break;
		}
	}
	if( NULL == pParam || NULL == pSkin )
	{
		//这里意味着设计出错，此处永远不应被执行
		return AfxWndProc( hWnd,
			nMsg, wParam,lParam );
	}

	switch (nMsg)
	{
	case WM_NCDESTROY: 
		{ //控件销毁
			WNDPROC lpProc = pParam ->m_pPreviousProc;
			Remove( hWnd );
			
			return ::CallWindowProc(
				lpProc,
				hWnd, nMsg, wParam, lParam );
		} 
		break;
	default:
		break;
	}
	//为方便后续调用，备份
	MSG& msgLast = AfxGetThreadState()->m_lastSentMsg;
	MSG  msgCur = msgLast;  
	msgLast.hwnd = hWnd;
	msgLast.message = nMsg;
	msgLast.wParam  = wParam;
	msgLast.lParam  = lParam;

	//找到按钮数据
	LRESULT lResult;

	//其它事件正常处理
	lResult = pSkin ->OnWndProc( nMsg, wParam, lParam );

	// 恢复状态
	msgLast = msgCur;			
	return lResult;
}

}