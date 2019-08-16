#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

namespace GlobalSkin
{
	namespace CPE /* Control Parameter Enumeration 控件参数枚举量*/
	{
		/*!
		 * @brief 工具栏子项状态
		 */
		enum ToolBarItemState
		{
			TBIS_Normal = 0,	/* 无操作 */
			TBIS_Hover,			/* 鼠标经过 */
			TBIS_Pressed,		/* 鼠标按下 */
			TBIS_Disabled,		/* 鼠标禁用 */
			TBIS_Size
		};
	}

	/*!
	 * @brief 工具栏控件参数
	 */
	struct CToolBarCtrlParameter:public CCtrlParameter
	{
	public:

		int GetPressedItem( ) const;
		void SetPressedItem( int nIndex );

		int GetHotItem( ) const;
		void SetHotItem( int nIndex );
	private:
		/* 当前按下的子项 */
		int m_nPressedItem;
		/* 当前焦点子项 */
		int	m_nHotItem;
	};

	/* 工具栏控件皮肤 */
	class CToolBarCtrlSkin:public CCtrlSkinPackage<CToolBarCtrlParameter>
	{
	public:
		CToolBarCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CToolBarCtrlSkin( );
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
		void OnPaint();

		/*!
		 * @brief WM_NCPAINT消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnNcPaint(HRGN rgn1);

		
		/*!
		 * @brief WM_MOUSEMOVE消息处理过程
		 * @param  
		 * @return 
		 * @note
		 */
		void OnMouseMove(WPARAM wKeyType, const POINT& point);
		
		/*!
		 * @brief  WM_LBUTTONDOWN消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonDown(WPARAM wKeyType, const POINT& point);

		
		/*!
		 * @brief WM_LBUTTONUP消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonUp(WPARAM wKeyType, const POINT& point);

		
		/*!
		 * @brief WM_MOUSELEAVE消息处理
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();
		
		/*!
		 * @brief 点击toolbar的子项目的检测
		 * @param 坐标点
		 * @return 子项的索引
		 * @note 用于确定当前点击了哪个按钮
		 */
		int HitTest(const POINT& point);

		
		/*!
		 * @brief 绘制工具栏
		 * @param 
		 * @return 
		 * @note
		 */
		void DrawToolBar(HDC hDC);

		
		/*!
		 * @brief 绘制工具栏子项
		 * @param hdc dc
		 * @param rcItem 子项的位置矩形
		 * @param nState 子项的状态
		 * @return 
		 * @note
		 */
		void DrawItemEntry(HDC hDC, const CRect& rcItem, CPE::ToolBarItemState nState );

	private:
		
		/* 背景图 */
		CBitmapRefPtr	m_pBmpBk;

		/* 工具栏按钮项的背景 */
		CBitmapRefPtr	m_pBmpItemBk[CPE::TBIS_Size];
	};

}
