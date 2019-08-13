#pragma once
#include "CtrlWithScrollBar.h"

namespace GlobalSkin
{
	struct sListCtrlParameter : public sCtrlWithScrollBar
	{

	};
	/** 
	 * @brief list控件皮肤
	 */
	class CListCtrlSkin:public CCtrlWithScrollBar<sListCtrlParameter>
	{
	public:
		CListCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CListCtrlSkin( );
		/** 
		 * @brief 获取当前的窗口类名
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief 接管控件皮肤之前
		 */
		bool OnInitSkinParam( HWND hWnd, CParamReference* pParam );

		/** 
		 * @brief 消息处理过程
		 */
		LRESULT OnWndOtherProc(UINT msg,WPARAM wp,LPARAM lp);

	};
}
