#pragma once
#include "CtrlSkinPackage.hpp"
namespace GlobalSkin
{
	namespace CPE /* control parameter enumeration */
	{
		enum
		{
			CONST_SiderBarWidth = 5, /*��������*/
			CONST_OTHER				 /* �������� */
		};
		enum FontType
		{
			FT_MarLeft,		/* ���߽� */
			FT_Tip,			/* ��ʾ */
			FT_Menu,		/* �˵� */
			FT_Message,		/* ��Ϣ */
			FT_Caption,		/* ���� */
		};

		///
		/// @brief �˵����
		///
		enum PopupMenuStyle
		{
			PMS_RoundCorner = 0x0001,	/* Բ�� */
			PMS_SiderBar = 0x0002,		/* ���� */
			PMS_Flat = 0x0004,			/* ƽ */

		};

		///
		/// @brief �˵���ɫ
		///
		enum PopupMenuColor
		{
			PMC_Special = 0,			/* 0xf1f1f1 */
			PMC_ParentBackground = 1,	/* ���˵����� */
			PMC_TextNormal,				/* ������ı� */
			PMC_TextDisabled,			/* �����ı� */
			PMC_TextFocused,			/* �����ı� */
			PMC_Background,				/* ����ɫ */
			PMC_Seperator,				/* �ָ�����ɫ */
			PMC_3DHightLight,	//ͬCOLOR_3DHILIGHT 
			PMC_3DFace,			//ͬCOLOR_3DFACE  
			PMC_Size
		};

		///
		/// @brief ѡ��״̬
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

		// �Ƿ���ģ��˵���
		bool						m_bAnimatedMenus;

		// ��һ�λ���
		bool						m_bFirstRedraw;
		
		///
		/// @brief �˵�
		///
		HMENU						m_hMenu;

		///
		/// @brief ѡ�е�����
		///
		int							m_nSelectedIndex;

		///
		/// @brief ������
		///
		HWND						m_hWnd;

		///
		/// @brief ������
		///
		CPopupMenuCtrlParameter*	m_pParent;

		///
		/// @brief �Ƿ��ǽ���
		///
		bool						m_bGradient;

		///
		/// @brief ��һ����ʾ
		///
		bool						m_bFirstShown;

		///
		/// @brief ��ɫ
		///
		COLORREF					m_clrBtn;

		///
		/// @brief ���
		///
		BYTE						m_byStyle;
	};

	///
	/// @brief �����˵�
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
		 * @brief WM_NCPAINT��Ϣ
		 * @param dc
		 * @return 
		 * @note
		 */
		void OnNcPaint(HDC hdc);
		
		/*!
		 * @brief Ϊ�˵����ڵĴ��ڷ����ػ�����Ϣ
		 * @param 
		 * @return 
		 * @note
		 */
		void SendRedrawMsg(BOOL bRedraw = TRUE) const;
		
		/*!
		 * @brief ��ȡ���Ƶľ���
		 * @param pWindow ���ھ���
		 * @param pClient�ͻ�������
		 * @return 
		 * @note
		 */
		void GetDrawRect(LPRECT pWindow, LPRECT pClient = NULL);
		
		/*!
		 * @brief ��ȡʧЧ�������
		 * @param ��ǰѡ�еĲ˵���
		 * @param ��һ��ѡ�еĲ˵���
		 * @param lpRect ��������
		 * @return 
		 * @note
		 */
		void GetInvalidRect(int nCurSel, int nPrevSel, LPRECT lpRect); 
		
		/*!
		 * @brief ��ȡ��ǰѡ�еĲ˵���
		 * @param 
		 * @return �˵���ı�š� ��ѡ�з���-1.
		 * @note
		 */
		int GetCurSel();

		
		/*!
		 * @brief ������ɫ��������ɫ���л�ȡ��ɫֵ
		 * @param ��ɫ����
		 * @return RGB��ɫֵ
		 * @note
		 */
		COLORREF GetColor( CPE::PopupMenuColor nIndex );

		
		/*!
		 * @brief ��������л�ȡһ�����塣
		 * @param ��������
		 * @return ������
		 * @note ��ǰ������н���һ������
		 */
		HFONT GetFont( CPE::FontType type );

		/*!
		 * @brief  �滻ϵͳ����ɫ
		 * @param  hdcSrcԴdc
		 * @param  hdcDest Ŀ��dc
		 * @param  pRect dc�л���������δ�С
		 * @param  pClip �ü���������
		 * @return �����滻�����dc
		 * @note
		 */
		HDC ReplaceSystemColors(HDC hdcSrc, HDC hdcDest, LPRECT pRect, LPRECT pClip);

		/*!
		 * @brief ��ȡ�˵�����
		 * @param 
		 * @return �˵�������
		 * @note
		 */
		HFONT GetMenuFont();

		
		/*!
		 * @brief ���ƿͻ���
		 * @param hdc dc
		 * @param dwFlags ���Ʋ���
		 * @return 
		 * @note
		 */
		void OnPrintClient(HDC hdc, DWORD dwFlags);

		// ���������������˵�
		void OnPaint(HDC hdc);

		/*!
		 * @brief ���Ʋ˵��ǿͻ�������ͼ
		 * @param hdc dc
		 * @param pRect ��������ľ���
		 * @return �ɹ�����true�����򷵻�false
		 * @note
		 */
		bool DrawMenuNonClientBkgnd(HDC hdc, LPRECT pRect);
		
		/*!
		 * @brief ���Ʋ˵��ͻ����ı���ͼ
		 * @param hdc dc
		 * @param pRectĿ������
		 * @param pClip �ü�����
		 * @return �ɹ�����true�����򷵻�false
		 * @note
		 */
		bool DrawMenuClientBkgnd(HDC hdc, LPRECT pRect, LPRECT pClip);
		
		/*!
		 * @brief ���Ʋ˵��ı���
		 * @param hdc dc
		 * @param pRect Ŀ�����
		 * @param szTitle �����ı�
		 * @return �ɹ�����true�����򷵻�false.
		 * @note
		 */
		bool DrawMenuSidebar(HDC hdc, LPRECT pRect, LPCTSTR szTitle = NULL);
		
		/*!
		 * @brief  ���Ʋ˵��߿�
		 * @param  hdc dc
		 * @param  pRect Ŀ�����
		 * @return  �ɹ�����true,���򷵻�false
		 * @note
		 */
		bool DrawMenuBorder(HDC hdc, LPRECT pRect);

		
		/*!
		 * @brief ���ƽ���ı���
		 * @param hdc dc
		 * @param pRect ��������
		 * @param pClip �ü�����
		 * @return 
		 * @note
		 */
		void DrawGradientBkgnd(HDC hdc, LPRECT pRect, LPRECT pClip);
	private:
		
		/*!
		 * @brief ��ʼ������
		 * @param 
		 * @return 
		 * @note
		 */
		void InitFont( );
	private:

		///
		/// @brief ��ɫ��
		/// @note ����ϵͳ��ɫ���ƴ��ڽ����3DЧ����
		//        ����ʹ����ɫ�滻����������һ�ֺ÷�����
		///
		COLORREF		m_PopupColor[CPE::PMC_Size];
		
		///
		/// @brief ����
		///
		HFONT			m_hMenuFont;
	};
}