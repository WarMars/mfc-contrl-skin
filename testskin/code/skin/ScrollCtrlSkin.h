#pragma once
#include "CtrlSkinPackage.hpp"
#include "ScrollBarCtrlSkin.h"
namespace GlobalSkin
{

/** 
 * @brief 滚动条控件状态
 */
class CScrollCtrlParameter:public CCtrlParameter
{
public:

	bool SetVScroll( bool bVScroll );
	bool IsVScroll( ) const; 
	void SetScrollParam( DynamicParam::CScrollBarCtrlParameterRefPtr pParam );
	DynamicParam::CScrollBarCtrlParameterRefPtr GetScrollParam( ) const;
public:
	//CPE::ScrollCtrlState m_nArrow1State;
	//CPE::ScrollCtrlState m_nArrow2State;
	//CPE::ScrollCtrlState m_nThumbState;
	bool	m_bVScroll;
	DynamicParam::CScrollBarCtrlParameterRefPtr m_pParam;
};

DECLARE_REF_PTR( CScrollCtrlParameter );

/** 
 * @brief 按钮控件皮肤
 */
class CScrollCtrlSkin:public CCtrlSkinPackage<CScrollCtrlParameter>
{
public:

	CScrollCtrlSkin(void);
	
	
	/** 
	 * @brief 获取当前的窗口类名
	 */
	LPCTSTR GetHwndClassName( );

	/** 
	 * @brief 接管控件皮肤之前
	 */
	CParamReference* OnPreTakeOverSkin( HWND hWnd );

	/** 
	 * @brief 消息处理过程
	 */
	LRESULT OnWndProc(UINT nMsg,WPARAM wParam,LPARAM lParam );
	
	void LoadSkin( const CSkinConfig* pConfig );
protected:
	void OnMouseMove(UINT nFlags, const POINT& point);
	void OnLButtonDown(UINT nFlags, const POINT& point);
	void OnLButtonUp(UINT nFlags, const POINT& point);
	void OnLButtonDblClk(UINT nFlags, const POINT& point);
	void OnMouseLeave();
	void OnPaint();

	void DrawHScrollBar( HDC hDC );
	void DrawVScrollBar( HDC hDC );
};

}

