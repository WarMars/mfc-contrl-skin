#pragma  once
#include "CtrlWithScrollBar.h"

namespace GlobalSkin
{
	struct sListBoxCtrlParameter:public sCtrlWithScrollBar
	{
	public:
		bool			m_bMenu;

		int				m_nHScrollPos;
		int				m_nVScrollPos;

		bool			m_bTrans;
		COLORREF		m_colorTrans;
		DWORD			m_dwStyle;
		DWORD			m_dwExStyle;

		UINT			m_nScrollHitTest;
		bool			m_bScrollVertical;
		bool			m_bMovingThumb;

		HWND			m_hScrollTracking ;
		int				m_nTrackingBar ;
		int				m_nTrackingPos ;
		int				m_nTrackingVal ;
		CRect			m_rtMenu;
	};
	
	class CListBoxCtrlSkin:public CCtrlWithScrollBar<sListBoxCtrlParameter>
	{
	public:
		CListBoxCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CListBoxCtrlSkin( );

		/** 
		 * @brief 获取当前的窗口类名
		 */
		LPCTSTR GetHwndClassName( );

		
		/*!
		 * @brief override
		 * @param 
		 * @return 
		 * @note
		 */
		bool OnInitSkinParam( HWND hWnd, CParamReference* pParam );

		/*!
		 * @brief override
		 * @param 
		 * @return 
		 * @note
		 */
		LRESULT OnWndOtherProc( UINT nMsg, WPARAM wParam, LPARAM lParam );
		
		/** 
		 * @ brief 重绘 
		 */
		void OnPaint( );
	};
}