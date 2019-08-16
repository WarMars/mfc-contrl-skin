#pragma once
#include "CtrlWithScrollBar.h"

/*  tree �ؼ� */
namespace GlobalSkin
{
	struct CTreeCtrlParameter:public CCtrlWithScrollBarParameter
	{

	};

	/* ��ʱֻʵ�ֹ������ķ�� */
	class CTreeCtrlSkin:public CCtrlWithScrollBar<CTreeCtrlParameter>
	{

		void LoadSkin( const CSkinConfig* pConfig );
		/** 
		 * @brief overide
		 */
		LPCTSTR GetHwndClassName( );
		
		/** 
		 * @brief overide
		 */
		bool OnInitSkinParam( HWND hWnd, CParamReference* pParam ) ;
	};

}


