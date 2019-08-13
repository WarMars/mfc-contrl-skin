#pragma once
#include "CtrlWithScrollBar.h"
#include "gdiobj_ptr.hpp"

///
/// @brief Edit 控件
///
namespace GlobalSkin
{
	struct sEditParameter:public sCtrlWithScrollBar
	{

	};

	class CEditCtrlSkin:public CCtrlWithScrollBar<sEditParameter>
	{
	public:
		CEditCtrlSkin();

		void LoadSkin( const CSkinConfig* pConfig );
		/** 
		 * @brief 窗口过程处理
		 */
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		/*!
		 * @brief 设置边框的贴图
		 * @param 位图指针
		 * @return 
		 * @note
		 */
		void SetBorderBmp( CBitmapRefPtr pBitmap );
	protected:

		/** 
		 * @brief 获取当前的窗口类名
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief 接管控件皮肤之前
		 */
		bool OnInitSkinParam( HWND hWnd, CParamReference* pParam );

		
		/*!
		 * @brief WM_PAINT消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint( );

		~CEditCtrlSkin();
	private:
		/* 边框贴图 */
		CBitmapRefPtr	m_pBorderBmp;
	};
}


