#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief 进度条贴图
///
namespace GlobalSkin
{
	struct sProgressBarCtrlParameter:public sCtrlParameter
	{
	public:
		bool IsVertical( ) const;
		bool SetVertical( bool bNew );
	private:
		///
		/// @brief 是否是垂直进度条
		///
		bool	m_bIsVertical;
	};

	class CProgressBarCtrlSkin:public CCtrlSkinPackage<sProgressBarCtrlParameter>
	{
	public:
		CProgressBarCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CProgressBarCtrlSkin( );
		/** 
		 * @brief overide
		 */
		LPCTSTR GetHwndClassName( );
		
		/** 
		 * @brief overide
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );
		
		/** 
		 * @brief overide
		 */
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		/*!
		 * @brief 绘制
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();
		
		/*!
		 * @brief WM_ERASEBKGND 绘制背景
		 * @param hdc dc
		 * @return 
		 * @note
		 */
		BOOL OnEraseBkgnd( HDC hdc );

		
		/*!
		 * @brief 获取滑块位置
		 * @param 输出的位置
		 * @return 成功返回true,否则返回false.
		 * @note
		 */
		BOOL GetPosRect( RECT &rtPos );
	private:
		///
		/// @brief 背景图
		///
		CBitmapRefPtr	m_pBmpHBk;
		CBitmapRefPtr	m_pBmpVBk;

		///
		/// @brief 进度条贴图
		///
		CBitmapRefPtr	m_pBmpHProgress;
		CBitmapRefPtr	m_pBmpVProgress;
	};

}
