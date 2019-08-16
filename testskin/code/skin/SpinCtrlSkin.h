#pragma  once

#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief spin控件的皮肤绘制
///
namespace GlobalSkin
{
	namespace CPE
	{
		
		/* spin的按钮类型 */
		enum SpinCtrlButton	
		{
			SCB_Up = 0,				/* 向上箭头 */
			SCB_Down,				/* 向下箭头 */
			SCB_Left = SCB_Up,		/* 向左箭头 */
			SCB_Right = SCB_Down,	/* 向右箭头 */
			SCB_None,				/* 无箭头 */
			SCB_Size
		};
		
		/* 按钮状态 */
		enum SpinCtrlButtonState
		{
			SCBS_Normal = 0,	/* 无操作 */
			SCBS_Hot,			/* 当前操作的热点项 */
			SCBS_Pressed,		/* 按下的项 */
			SCBS_Disabled,		/* 禁用的项 */
			SCBS_Size
		};
	}

	///
	/// @brief spin控件的参数
	///
	struct CSpinCtrlParameter:public CCtrlParameter
	{
	public:
		CPE::SpinCtrlButton	GetPressedButton( ) const;
		bool SetPressedButton( CPE::SpinCtrlButton nType );

		CPE::SpinCtrlButton	GetHotButton( ) const;
		bool SetHotButton( CPE::SpinCtrlButton nType );

		bool IsVertical( ) const;
		void SetVertical( bool bNew );
	private:
		
		/* 按下的按钮 */
		CPE::SpinCtrlButton		m_nPressedButton; 
		
		/* 热点按钮 */
		CPE::SpinCtrlButton		m_nHotButton;

		/* 是否是垂直的 */
		bool					m_bVertical;

	};

	///
	/// @brief spin的皮肤
	///
	class CSpinCtrlSkin:public CCtrlSkinPackage<CSpinCtrlParameter>
	{
	public:
		CSpinCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CSpinCtrlSkin( );
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
		 * @brief WM_PAINT 消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();
		
		/*!
		 * @brief WM_ERASEBKGND消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		BOOL OnEraseBkgnd(HDC hDC);
		
		/*!
		 * @brief WM_MOUSEMOVE消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseMove(WPARAM wKeyType, const POINT& point);
		
		/*!
		 * @brief WM_LBUTTONDOWN消息处理过程
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
		 * @brief WM_MOUSELEAVE消息处理过程
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();

		
		/*!
		 * @brief  点击消息处理过程
		 * @param  点击的坐标点
		 * @return 点击的按钮
		 * @note
		 */
		CPE::SpinCtrlButton HitTest( const POINT& point);

		
		/*!
		 * @brief 绘制spin按钮
		 * @param 
		 * @return 
		 * @note
		 */
		void DrawSpin(HDC hDC);

	private:
		
		/* 向上箭头的贴图 */
		CBitmapRefPtr	m_pBmpUpArrow[CPE::SCBS_Size];
		
		/* 向下箭头的贴图 */
		CBitmapRefPtr	m_pBmpDownArrow[CPE::SCBS_Size];
		
		/* 向左箭头的贴图 */
		CBitmapRefPtr	m_pBmpLeftArrow[CPE::SCBS_Size];
		
		/* 向右箭头的贴图 */
		CBitmapRefPtr	m_pBmpRightArrow[CPE::SCBS_Size];
	
	};

}
