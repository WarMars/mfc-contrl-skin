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
	 * @brief ��ȡ��ǰ�Ĵ�������
	 */
	LPCTSTR CListCtrlSkin::GetHwndClassName( )
	{
		return TEXT("SysListView32");
	}

	
	/** 
		* @brief �ӹܿؼ�Ƥ��֮ǰ
		*/
	bool CListCtrlSkin::OnInitSkinParam( HWND hWnd, CParamReference* pParam )
	{
		UNUSED(hWnd);
		UNUSED(pParam);
		return true;
	}

	/** 
		* @brief ��Ϣ�������
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
