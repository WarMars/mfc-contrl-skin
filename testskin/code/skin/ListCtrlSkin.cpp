#include "stdafx.h"
#include "ListCtrlSkin.h"
#include "utils.hpp"
#include "ImageManager.h"

namespace GlobalSkin
{

	CListCtrlSkin::CListCtrlSkin( )
	{
	}


	void CListCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
	{
		return;
	}

	CListCtrlSkin::~CListCtrlSkin( )
	{
	}
	/** 
	 * @brief 获取当前的窗口类名
	 */
	LPCTSTR CListCtrlSkin::GetHwndClassName( )
	{
		return TEXT("SysListView32");
	}

	
	/** 
		* @brief 接管控件皮肤之前
		*/
	bool CListCtrlSkin::OnInitSkinParam( HWND hWnd, CParamReference* pParam )
	{
		UNUSED(hWnd);
		UNUSED(pParam);
		return true;
	}

	/** 
		* @brief 消息处理过程
		*/
	LRESULT CListCtrlSkin::OnWndOtherProc(UINT msg,WPARAM wp,LPARAM lp)
	{
		//switch(msg)
		//{
		//default:
		//	break;
		//}
		return OnPreviousWndProc( GetCurHwnd( ), msg, wp, lp );
	}

}
