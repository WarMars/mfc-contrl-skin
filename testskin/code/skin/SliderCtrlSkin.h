#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief 滑块控件皮肤
///
namespace GlobalSkin
{
	struct CSliderCtrlParameter:public CCtrlParameter
	{
	public:
		bool IsVertical( ) const;
		bool SetVertical( bool bNew );
	private:
		
		/* 是否是垂直的 */
		bool	m_bIsVertical;
	};
	///
	/// @brief 滑块控件的皮肤
	///
	class CSilderCtrlSkin:public CCtrlSkinPackage<CSliderCtrlParameter>
	{
	public:
		CSilderCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CSilderCtrlSkin( );
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
		 * @brief WM_PAINT消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint( );
		
		/*!
		 * @brief 绘制滑块
		 * @param  dc
		 * @return 
		 * @note 绘制滑块的背景等
		 */
		void Draw( HDC hDC );

	private:
		
		/* 水平背景贴图 */
		CBitmapRefPtr	m_pBmpHBk;

		/* 垂直背景贴图 */
		CBitmapRefPtr	m_pBmpVBk;
		
		/* 水平滑块 */
		CBitmapRefPtr	m_pBmpHSlider;
		
		/* 垂直滑块 */
		CBitmapRefPtr	m_pBmpVSlider;
		
		/* 水平中线贴图 */
		CBitmapRefPtr	m_pBmpHLine;

		/* 垂直中线贴图 */
		CBitmapRefPtr	m_pBmpVLine;
	};

}
