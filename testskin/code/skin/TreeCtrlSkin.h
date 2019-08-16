#pragma once
#include "CtrlWithScrollBar.h"

/*  tree 控件 */
namespace GlobalSkin
{
	struct CTreeCtrlParameter:public CCtrlWithScrollBarParameter
	{

	};

	/* 暂时只实现滚动条的风格 */
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


