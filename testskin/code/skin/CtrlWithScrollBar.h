#pragma once
#include "CtrlSkinPackage.hpp"
#include "ScrollBarCtrlSkin.h"

namespace GlobalSkin
{
	struct sCtrlWithScrollBar:public sCtrlParameter
	{
		bool		    m_bBorder;
		DynamicParam::CsScrollBarCtrlParameterRefPtr	m_pScrollBarParam;
		inline const DynamicParam::CsScrollBarCtrlParameterRefPtr& GetScrollBarParam( ) const
		{
			return m_pScrollBarParam;
		}
		inline DynamicParam::CsScrollBarCtrlParameterRefPtr& GetScrollBarParam( )
		{
			return m_pScrollBarParam;
		}
		inline bool HasBorder( ) const{ return m_bBorder; }
		inline void SetHasBorder( bool bBorder ){ m_bBorder = bBorder; } 
	};

	/** 
	 * @brief T������һ��sListCtrlParameter
	 */
	template<typename T>
	class CCtrlWithScrollBar: public CCtrlSkinPackage<T>
	{
	protected:
		CCtrlWithScrollBar( );
		~CCtrlWithScrollBar( );
		
		/** 
		 * @brief �ӹܿؼ�Ƥ��֮ǰ
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/** 
		 * @brief ��ʼ����������
		 */
		virtual bool OnInitSkinParam( HWND hWnd, CParamReference* pParam ) = 0;

		/** 
		 * @brief ��Ϣ�������
		 */
		LRESULT OnWndProc(UINT msg,WPARAM wp,LPARAM lp);

		/** 
		 * @brief ������֮��Ĵ��ڹ��̴���
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

