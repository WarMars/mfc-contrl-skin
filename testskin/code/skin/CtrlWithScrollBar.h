#pragma once
#include "CtrlSkinPackage.hpp"
#include "ScrollBarCtrlSkin.h"

namespace GlobalSkin
{
	struct CCtrlWithScrollBarParameter:public CCtrlParameter
	{
		bool		    m_bBorder;
		DynamicParam::CScrollBarCtrlParameterRefPtr	m_pScrollBarParam;
		inline const DynamicParam::CScrollBarCtrlParameterRefPtr& GetScrollBarParam( ) const
		{
			return m_pScrollBarParam;
		}
		inline DynamicParam::CScrollBarCtrlParameterRefPtr& GetScrollBarParam( )
		{
			return m_pScrollBarParam;
		}
		inline bool HasBorder( ) const{ return m_bBorder; }
		inline void SetHasBorder( bool bBorder ){ m_bBorder = bBorder; } 
	};

	/** 
	 * @brief T必须是一种CListCtrlParameter
	 */
	template<typename T>
	class CCtrlWithScrollBar: public CCtrlSkinPackage<T>
	{
	protected:
		CCtrlWithScrollBar( );
		~CCtrlWithScrollBar( );
		
		/** 
		 * @brief 接管控件皮肤之前
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/** 
		 * @brief 初始化其它参数
		 */
		virtual bool OnInitSkinParam( HWND hWnd, CParamReference* pParam ) = 0;

		/** 
		 * @brief 消息处理过程
		 */
		LRESULT OnWndProc(UINT msg,WPARAM wp,LPARAM lp);

		/** 
		 * @brief 滚动条之外的窗口过程处理
		 */
		virtual LRESULT OnWndOtherProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		virtual void OnNcMouseMove( UINT nHitTest, const CPoint& point );
		virtual void OnMouseMove(UINT nFlags, const CPoint& point);
		virtual void OnNcLButtonDown( UINT nHitTest, const CPoint& point );
		virtual void OnNcLButtonDblClk( UINT nHitTest, const CPoint& point );
		virtual void OnNcCalcSize( bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
		virtual LRESULT OnNcHitTest( const CPoint& point );
		virtual void OnNcPaint(HRGN rgn1);
	};
}
#include "CtrlWithScrollBar.template_imp"

