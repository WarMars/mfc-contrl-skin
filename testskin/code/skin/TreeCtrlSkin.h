#pragma once
#include "CtrlWithScrollBar.h"

/*  tree �ؼ� */
namespace GlobalSkin
{
	struct sTreeCtrlParameter:public sCtrlWithScrollBar
	{

	};

	/* ��ʱֻʵ�ֹ������ķ�� */
	class CTreeCtrlSkin:public CCtrlWithScrollBar<sTreeCtrlParameter>
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


