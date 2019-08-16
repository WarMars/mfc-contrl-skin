#pragma once
#include "CtrlSkinPackage.hpp"
namespace GlobalSkin
{
	namespace CPE /* control parameter enumeration */
	{
		enum
		{
			CONST_SiderBarWidth = 5, /*侧边栏宽度*/
			CONST_OTHER				 /* 其它参数 */
		};
		enum FontType
		{
			FT_MarLeft,		/* 左侧边界 */
			FT_Tip,			/* 提示 */
			FT_Menu,		/* 菜单 */
			FT_Message,		/* 消息 */
			FT_Caption,		/* 标题 */
		};

		///
		/// @brief 菜单风格
		///
		enum PopupMenuStyle
		{
			PMS_RoundCorner = 0x0001,	/* 圆角 */
			PMS_SiderBar = 0x0002,		/* 滑块 */
			PMS_Flat = 0x0004,			/* 平 */

		};

		///
		/// @brief 菜单颜色
		///
		enum PopupMenuColor
		{
			PMC_Special = 0,			/* 0xf1f1f1 */
			PMC_ParentBackground = 1,	/* 父菜单背景 */
			PMC_TextNormal,				/* 误操作文本 */
			PMC_TextDisabled,			/* 禁用文本 */
			PMC_TextFocused,			/* 焦点文本 */
			PMC_Background,				/* 背景色 */
			PMC_Seperator,				/* 分隔符颜色 */
			PMC_3DHightLight,	//同COLOR_3DHILIGHT 
			PMC_3DFace,			//同COLOR_3DFACE  
			PMC_Size
		};

		///
		/// @brief 选中状态
		///
		enum PopupMenuSelectedStatus 
		{
			PMSS_ReDrawAll = -2,
		};

	}
	struct CPopupMenuCtrlParameter: public CCtrlParameter
	{
		bool IsAnimatedMenus( ) const;
		void SetAnimatedMenus( bool b );
		bool IsFirstRedraw( ) const;
		void SetFirstRedraw( bool b );

		void SetHMenu( HMENU hMenu );
		HMENU GetHMenu( ) const;

		void SetSelectedIndex( int nIndex );
		int  GetSelectedIndex( ) const;

		HWND GetHwnd( ) const;
		void SetHwnd( HWND hWnd );

		void SetParent(CPopupMenuCtrlParameter* pParent );
		CPopupMenuCtrlParameter* GetParent( ) const;

		bool IsGradient( ) const;
		void SetGradient( bool b );

		bool IsFirstShow( ) const;
		void SetFirstShow( bool b );

		COLORREF GetButtonColor( ) const;
		void SetButtonColor( COLORREF color );

		bool HasRoundCorner( ) const;
		bool HasSideBar( ) const;
		bool IsFlat( ) const;

		void SetRoundCorner( bool bAdd = true );
		void SetSideBar( bool bAdd = true );
		void SetFlat( bool bAdd = true );
		void SetStyle( BYTE byStyle );
		

	private:

		// 是否处于模拟菜单中
		bool						m_bAnimatedMenus;

		// 第一次绘制
		bool						m_bFirstRedraw;
		
		///
		/// @brief 菜单
		///
		HMENU						m_hMenu;

		///
		/// @brief 选中的索引
		///
		int							m_nSelectedIndex;

		///
		/// @brief 父窗口
		///
		HWND						m_hWnd;

		///
		/// @brief 父参数
		///
		CPopupMenuCtrlParameter*	m_pParent;

		///
		/// @brief 是否是渐变
		///
		bool						m_bGradient;

		///
		/// @brief 第一次显示
		///
		bool						m_bFirstShown;

		///
		/// @brief 颜色
		///
		COLORREF					m_clrBtn;

		///
		/// @brief 风格
		///
		BYTE						m_byStyle;
	};

	///
	/// @brief 弹出菜单
	///
	class CPopupMenuCtrlSkin : public CCtrlSkinPackage<CPopupMenuCtrlParameter>
	{
	public:
		CPopupMenuCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CPopupMenuCtrlSkin( );

		/** 
		 * @override
		 */
		LPCTSTR GetHwndClassName( );
		
		/** 
		 * @override
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/** 
		 * @override
		 */
		LRESULT OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		
		/*!
		 * @brief WM_NCPAINT消息
		 * @param dc
		 * @return 
		 * @note
		 */
		void OnNcPaint(HDC hdc);
		
		/*!
		 * @brief 为菜单所在的窗口发送重绘制消息
		 * @param 
		 * @return 
		 * @note
		 */
		void SendRedrawMsg(BOOL bRedraw = TRUE) const;
		
		/*!
		 * @brief 获取绘制的矩形
		 * @param pWindow 窗口矩形
		 * @param pClient客户区矩形
		 * @return 
		 * @note
		 */
		void GetDrawRect(LPRECT pWindow, LPRECT pClient = NULL);
		
		/*!
		 * @brief 获取失效区域矩形
		 * @param 当前选中的菜单项
		 * @param 上一次选中的菜单项
		 * @param lpRect 矩形区域
		 * @return 
		 * @note
		 */
		void GetInvalidRect(int nCurSel, int nPrevSel, LPRECT lpRect); 
		
		/*!
		 * @brief 获取当前选中的菜单项
		 * @param 
		 * @return 菜单项的编号。 无选中返回-1.
		 * @note
		 */
		int GetCurSel();

		
		/*!
		 * @brief 根据颜色索引从颜色表中获取颜色值
		 * @param 颜色索引
		 * @return RGB颜色值
		 * @note
		 */
		COLORREF GetColor( CPE::PopupMenuColor nIndex );

		
		/*!
		 * @brief 从字体表中获取一个字体。
		 * @param 字体类型
		 * @return 字体句柄
		 * @note 当前字体表中仅有一种字体
		 */
		HFONT GetFont( CPE::FontType type );

		/*!
		 * @brief  替换系统的颜色
		 * @param  hdcSrc源dc
		 * @param  hdcDest 目标dc
		 * @param  pRect dc中绘制区域矩形大小
		 * @param  pClip 裁剪矩形区域
		 * @return 返回替换结果的dc
		 * @note
		 */
		HDC ReplaceSystemColors(HDC hdcSrc, HDC hdcDest, LPRECT pRect, LPRECT pClip);

		/*!
		 * @brief 获取菜单字体
		 * @param 
		 * @return 菜单字体句柄
		 * @note
		 */
		HFONT GetMenuFont();

		
		/*!
		 * @brief 绘制客户区
		 * @param hdc dc
		 * @param dwFlags 绘制参数
		 * @return 
		 * @note
		 */
		void OnPrintClient(HDC hdc, DWORD dwFlags);

		// 保留：绘制整个菜单
		void OnPaint(HDC hdc);

		/*!
		 * @brief 绘制菜单非客户区背景图
		 * @param hdc dc
		 * @param pRect 绘制区域的矩形
		 * @return 成功返回true，否则返回false
		 * @note
		 */
		bool DrawMenuNonClientBkgnd(HDC hdc, LPRECT pRect);
		
		/*!
		 * @brief 绘制菜单客户区的背景图
		 * @param hdc dc
		 * @param pRect目标区域
		 * @param pClip 裁剪区域
		 * @return 成功返回true，否则返回false
		 * @note
		 */
		bool DrawMenuClientBkgnd(HDC hdc, LPRECT pRect, LPRECT pClip);
		
		/*!
		 * @brief 绘制菜单的边栏
		 * @param hdc dc
		 * @param pRect 目标矩形
		 * @param szTitle 标题文本
		 * @return 成功返回true，否则返回false.
		 * @note
		 */
		bool DrawMenuSidebar(HDC hdc, LPRECT pRect, LPCTSTR szTitle = NULL);
		
		/*!
		 * @brief  绘制菜单边框
		 * @param  hdc dc
		 * @param  pRect 目标矩形
		 * @return  成功返回true,否则返回false
		 * @note
		 */
		bool DrawMenuBorder(HDC hdc, LPRECT pRect);

		
		/*!
		 * @brief 绘制渐变的背景
		 * @param hdc dc
		 * @param pRect 背景矩形
		 * @param pClip 裁剪矩形
		 * @return 
		 * @note
		 */
		void DrawGradientBkgnd(HDC hdc, LPRECT pRect, LPRECT pClip);
	private:
		
		/*!
		 * @brief 初始化字体
		 * @param 
		 * @return 
		 * @note
		 */
		void InitFont( );
	private:

		///
		/// @brief 颜色表。
		/// @note 由于系统颜色绘制存在渐变和3D效果，
		//        所以使用颜色替换方案并不是一种好方法。
		///
		COLORREF		m_PopupColor[CPE::PMC_Size];
		
		///
		/// @brief 字体
		///
		HFONT			m_hMenuFont;
	};
}