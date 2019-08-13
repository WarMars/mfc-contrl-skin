#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief tab控件皮肤
///
namespace GlobalSkin
{
	namespace CPE /* control parameter enumeration 控件参数枚举 */
	{
		enum TabItemState /* tab控件项的状态 */
		{
			TabIS_Normal = 0,	//无操作
			TabIs_Hover,		//鼠标滑过
			TabIS_Pressed,      //按下
			TabIS_Size
		};
	}

	///
	/// @brief tab的参数
	///
	struct sTabCtrlSkinParameter:public sCtrlParameter
	{
	public:
		int	GetPressedIndex( ) const;
		void SetPressedIndex( int nIndex );

		int GetHotIndex( ) const;
		void SetHotIndex( int nIndex );
	private:
		
		// 按下的项的id
		int m_nPressedIndex;
		// 选中的项的id
		int	m_nHotIndex;
	};

	/** 
	 * @brief tab控件皮肤
	 */
	class CTablCtrlSkin:public CCtrlSkinPackage<sTabCtrlSkinParameter>
	{
	public:
		CTablCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CTablCtrlSkin( );
		/** 
		 * @brief override 控件的窗口类名称
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief override	接管之前创建参数
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/** 
		 * @brief override	控件消息处理
		 */
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		
		/*!
		 * @brief WM_PAINT消息的处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();

		
		/*!
		 * @brief WM_MOUSEMOVE消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseMove(UINT nKeyType, const POINT& point);

		
		/*!
		 * @brief WM_LBUTTONDOWN消息处理过程性
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonDown(UINT nKeyType, const POINT& point);

		
		/*!
		 * @brief WM_LBUTTONUP消息的处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonUp(UINT nFlags, const POINT& point);
		
		/*!
		 * @brief WM_MOUSELEAVE消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();

		
		/*!
		 * @brief 点击测试
		 * @param 点击的坐标点
		 * @return 点击的tab项的索引
		 * @note
		 */
		int HitTest( const POINT& point);

		
		/*!
		 * @brief  绘制tab
		 * @param  hdc dc
		 * @param  nIndex 编号
		 * @param  rcItem 子项的位置矩形
		 * @return 
		 * @note
		 */
		void DrawTab( HDC hdc );
		
		/*!
		 * @brief 绘制子项
		 * @param hdc dc
		 * @param rcItem 子项的位置矩形
		 * @param nState 子项的状态
		 * @return 
		 * @note
		 */
		void DrawItemEntry( HDC hdc, int nIndex, const CRect& rcItem, CPE::TabItemState nState);

	private:

		/* 背景 */
		CBitmapRefPtr		m_pBmkBk;

		/* 按下项的背景 */
		CBitmapRefPtr		m_pBmpItem[CPE::TabIS_Size];
	};
}

