#include "stdafx.h"
#include "ListBoxCtrlSkin.h"
#include "utils.hpp"

namespace GlobalSkin
{
CListBoxCtrlSkin::CListBoxCtrlSkin( )
{

}

void CListBoxCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{

}

CListBoxCtrlSkin::~CListBoxCtrlSkin( )
{

}
/** 
 * @brief 获取当前的窗口类名
 */
LPCTSTR CListBoxCtrlSkin::GetHwndClassName( )
{
	return TEXT("Listbox");
}

bool CListBoxCtrlSkin::OnInitSkinParam(  HWND hWnd, CParamReference* pParam )
{
	UNUSED( hWnd );
	UNUSED( pParam );
	return true;
}


LRESULT CListBoxCtrlSkin::OnWndOtherProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//TRACE(_T(__FUNCTION__ )   _T("\n") );
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint( );
		break;
	default:
		return OnAutoDefaultWndProc();
	}
	return 0;
}


void CListBoxCtrlSkin::OnPaint()
{
	OnAutoDefaultWndProc( );
	OnNcPaint(NULL);
}

}
