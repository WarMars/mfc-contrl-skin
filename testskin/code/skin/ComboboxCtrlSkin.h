#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief 组合框控件
///
namespace GlobalSkin
{
	/*!
	 * @brief 组合框的控件参数
	 */
	struct CComboboxCtrlParameter:public CCtrlParameter
	{
		enum
		{
			COMBOX_NORMAL	= 0x00000080L, // 正常状态
			COMBOX_DISABLED = 0x00000001L, // 禁用状态
			COMBOX_PRESSED	= 0x00000002L, // 按下状态
			COMBOX_HOVER	= 0x00000004L, // 高亮状态 (鼠标在该窗口上)
			COMBOX_FOCUS	= 0x00000008L  // 具有键盘输入焦点
		};

		/*!
		 * @brief 下拉的箭头的状态
		 */
		enum ThumbBoxState
		{
			CheckNormal = 0,	/* 无操作状态 */
			CheckHover,			/* 鼠标经过 */
			CheckPressed,		/* 鼠标按下 */
			CheckFocused,		/* 有焦点 */
			CheckDisabled,		/* 禁用 */
			CheckBoxStateSize,	/*  */
		};

		INT		m_nState;		// 当前状态
		LONG	m_nHScrollBar;  // 水平滚动条
		LONG	m_nVScrollBar;	// 垂直滚动条
		bool	m_bHitThumb;	// 是否点击了下拉的箭头
		bool	m_bTouchedListBox; // 是否已经关联了下拉列表
	};

	/*!
	 * @brief 组合框的控件皮肤
	 */
	class CComboBoxCtrlSkin: public CCtrlSkinPackage<CComboboxCtrlParameter>
	{
	public:
		CComboBoxCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CComboBoxCtrlSkin( );

		/**
		 * @brief override
		 */
		LRESULT OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		/** 
		 * @brief 获取当前的窗口类名
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief 接管控件皮肤之前
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/*!
		 * @brief  WM_CTLCOLOR 消息的处理过程。
		 *		   在没有关联下拉列表控件的情况下进行关联。
		 * @param wParam HDC
		 * @param lParam HWND
		 * @return 背景的HBRUSH
		 * @note 参见系统的消息说明
		 */
		LRESULT OnCtrlColor( WPARAM wParam, LPARAM lParam );

		/*!
		 * @brief  WM_MOUSEMOVE消息的处理过程。
		 *		   记录操作状态，为绘制做准备。
		 * @param  nFlags 按键
		 * @param  point 鼠标坐标点
		 * @note 参见系统的消息说明
		 */
		void OnMouseMove(UINT nFlags, const CPoint& point);

		/*!
		 * @brief  WM_LBUTTONDOWN消息的处理过程
		 * @param  nFlags 按下时的其它系统按键标志
		 * @param  point 按下时的做小
		 * @return 
		 * @note 追踪控件的状态，为绘制做准备
		 */
		void OnLButtonDown(UINT nFlags , const CPoint& point); //
		void OnLButtonUp(UINT nFlags, const CPoint& point); //
		void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp); //
		void OnNcPaint(HRGN rgn1); //
		void OnPaint();//
		void OnSetFocus(HWND hWnd); //
		void OnKillFocus(HWND hWnd); //
		/*!
		 * @brief 
		 * @param 
		 * @return 
		 * @note
		 */
		void OnSetText(WPARAM wp,LPARAM lp); //
		void OnMouseLeave(); //
		
		/*!
		 * @brief 绘制
		 * @param 画笔
		 * @return 
		 * @note
		 */
		void DrawComboBox(CDC *pDC);

		/*!
		 * @brief 点击下拉箭头的检测
		 * @param 坐标点
		 * @return 点击下拉箭头返回true,否则返回false
		 * @note
		 */
		bool HitTestThumb( const CPoint& point );
		void OnSize( int cx, int cy );
	private:
		void Redraw( bool bDrawBorder = false );

	private:
		/* 边框图 */
		CBitmapRefPtr	m_pBmpBorder;
		/* 下拉箭头的状态贴图 */
		CBitmapRefPtr	m_pBmpThumb[CComboboxCtrlParameter::CheckBoxStateSize];
	};

}