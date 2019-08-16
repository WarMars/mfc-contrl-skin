#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

namespace GlobalSkin
{
	struct CSysHeaderParameter: public CCtrlParameter
	{
		/* 标题头按下状态 */
		enum HeaderItemState
		{
			HIS_Normal=0,	/* 无任何操作 */
			HIS_Hover,		/* 鼠标经过 */
			HIS_Press,		/* 鼠标按下 */
			HIS_State		/*  */
		};
		
		/* 当前操作项编号 */
		UINT m_nHotItem;
		
		/* 按下的项的编号 */
		UINT m_nPressedItem;
	};

	
	/* 标题头的皮肤 */
	class CSysHeaderSkin: public CCtrlSkinPackage<CSysHeaderParameter>
	{
	public:
		CSysHeaderSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CSysHeaderSkin( );
		
		/** 
		 * @brief 获取当前的窗口类名
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief 接管控件皮肤之前
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		
		/*!
		 * @brief 窗口过程
		 * @param 
		 * @return 
		 * @note
		 */
		LRESULT OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		
		/*!
		 * @brief	WM_PAINT消息处理
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();

		
		/*!
		 * @brief WM_ERASEBKGND 消息的处理
		 * @param 
		 * @return 
		 * @note
		 */
		BOOL OnEraseBkgnd( HDC hdc );
		
		/*!
		 * @brief WM_MOUSEMOVE消息
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseMove(UINT nFlags, const CPoint& point);

		
		/*!
		 * @brief WM_LBUTTONDOWN消息
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonDown(UINT nFlags, const CPoint& point);

		
		/*!
		 * @brief WM_LBUTTONUP消息
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonUp(UINT nFlags, const CPoint& point);

		
		/*!
		 * @brief	WM_MOUSEMOVE消息
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();

		
		/*!
		 * @brief  点击测试
		 * @param  坐标点
		 * @return 具体点击的子项的编号
		 * @note
		 */
		int HitTest( const CPoint& point);

		
		/*!
		 * @brief 绘制标题头.根据当前操作的项和当前点击的项目。
		 *		  为标题头不同的位置绘制不同的背景灯颜色。
		 * @param dc
		 * @return 
		 * @note
		 */
		void DrawHeader(HDC hdc );
		
		/*!
		 * @brief 绘制子项
		 * @param dc
		 * @param nIndex 子项的编号
		 * @param rectItem 子项的矩形
		 * @param state 要绘制的状态
		 * @return 
		 * @note
		 */
		void DrawItemEntry( HDC hdc, LRESULT nIndex, 
			const CRect& rectItem,
			CSysHeaderParameter::HeaderItemState state);

		
		/*!
		 * @brief  重绘
		 * @param 
		 * @return 
		 * @note
		 */
		void Redraw( );
	private:
		
		/* 背景图 */
		CBitmapRefPtr		m_pBmpBk;
		
		/* 子项的背景图 */
		CBitmapRefPtr		m_pBmpItem[CSysHeaderParameter::HIS_State];
	};
}


