#include "stdafx.h"
#include "CtrlSkin.h"
#include "GlobalUiManager.h"

namespace GlobalSkin
{
	
bool	CCtrlSkin::AddControl( HWND hWnd, WNDPROC pProc, WNDPROC* pOldProcPtr )
{
	if( NULL == hWnd )
	{
		return false;
	}
	TCHAR szClassName[MAX_CLASS_NAME] = {0};

	GetClassName( hWnd,szClassName, sizeof(szClassName) );
	CCtrlParameter* pParam = NULL;
	if( !CheckHwnd( hWnd, szClassName, pParam ) )
	{
		return false;
	}
	if( NULL == pParam )
	{
		return true;
	}
	// 覆盖窗口过程
#ifdef _WIN64
	WNDPROC  pOldProc = (WNDPROC)SetWindowLongPtr(
		hWnd, GWLP_WNDPROC,(LONG_PTR)pProc );
#else
	WNDPROC pOldProc = (WNDPROC)SetWindowLong(
		hWnd, GWL_WNDPROC, (LONG)pProc  );
#endif
	pParam ->m_pPreviousProc = pOldProc;
	// 刷新一次
	//SetWindowPos( hWnd,NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | 
	//	SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	RedrawWindow(
		hWnd, 
		NULL, NULL,
		RDW_FRAME | /*RDW_UPDATENOW |*/ RDW_NOCHILDREN);
	if( NULL != pOldProcPtr )
	{
		*pOldProcPtr = pOldProc;
	}
	return true;
}

/** 
* @brief 删除一个控件
*/
bool	CCtrlSkin::RemoveControl( HWND hWnd )
{
	WNDPROC pProc;
	if( !RemoveHwnd( hWnd, pProc) )
	{
		false;
	}

	// 恢复
#ifdef _WIN64
	SetWindowLongPtr( hWnd, GWLP_WNDPROC,
		(LONG_PTR)(pProc) );
#else
	SetWindowLong( hWnd, GWL_WNDPROC,
		(LONG)(pProc)  );
#endif
	return true;
}
void CCtrlSkin::SetCurrentWindow( HWND hWnd )
{
	m_stackWnd.push( hWnd );
}
void CCtrlSkin::ResetCurrentWindow( )
{
	if( m_stackWnd.empty() )
	{
		return;
	}
	m_stackWnd.pop( );
}

LRESULT CCtrlSkin::OnAutoDefaultWndProc( )
{
	// 备份的参数
	MSG& lastMsg = AfxGetThreadState()->m_lastSentMsg;
	return OnPreviousWndProc(
		lastMsg.hwnd,
		lastMsg.message, 
		lastMsg.wParam, 
		lastMsg.lParam );
}

LRESULT CCtrlSkin::OnPreviousWndProc( HWND hWnd, UINT nMsg, WPARAM wParam ,LPARAM lParam )
{
	WNDPROC pProc = NULL;
	if( !GetPreviousWndProc( pProc ) )
	{ //参数非法
		return 0L;
	}
	// 旧的处理过程
	if( NULL != pProc )
	{
		return CallWindowProc( pProc,
			hWnd, nMsg, wParam, lParam );
	}
	return 0L;
}

CCtrlSkin::~CCtrlSkin( )
{

}

void CCtrlSkin::SetUiManager( CGlobalUiManager* pManager )
{
	m_pManager = pManager;
}

DynamicParam::CScrollBarCtrlSkin& CCtrlSkin::GetScrollBarCtrlSkin( )
{
	return *(m_pManager ->GetScrollBarCtrlSkin( ));
}

DynamicParam::CMenubarCtrlSkin& CCtrlSkin::GetMenuBarCtrlSkin( )
{
	DynamicParam::CMenubarCtrlSkin& skin = *(m_pManager ->GetMenuBarCtrlSkin( ));
	return skin;
}

}

