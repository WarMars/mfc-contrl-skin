#pragma  once

#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief spin�ؼ���Ƥ������
///
namespace GlobalSkin
{
	namespace CPE
	{
		
		/* spin�İ�ť���� */
		enum SpinCtrlButton	
		{
			SCB_Up = 0,				/* ���ϼ�ͷ */
			SCB_Down,				/* ���¼�ͷ */
			SCB_Left = SCB_Up,		/* �����ͷ */
			SCB_Right = SCB_Down,	/* ���Ҽ�ͷ */
			SCB_None,				/* �޼�ͷ */
			SCB_Size
		};
		
		/* ��ť״̬ */
		enum SpinCtrlButtonState
		{
			SCBS_Normal = 0,	/* �޲��� */
			SCBS_Hot,			/* ��ǰ�������ȵ��� */
			SCBS_Pressed,		/* ���µ��� */
			SCBS_Disabled,		/* ���õ��� */
			SCBS_Size
		};
	}

	///
	/// @brief spin�ؼ��Ĳ���
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
		
		/* ���µİ�ť */
		CPE::SpinCtrlButton		m_nPressedButton; 
		
		/* �ȵ㰴ť */
		CPE::SpinCtrlButton		m_nHotButton;

		/* �Ƿ��Ǵ�ֱ�� */
		bool					m_bVertical;

	};

	///
	/// @brief spin��Ƥ��
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
		 * @brief WM_PAINT ��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();
		
		/*!
		 * @brief WM_ERASEBKGND��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		BOOL OnEraseBkgnd(HDC hDC);
		
		/*!
		 * @brief WM_MOUSEMOVE��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseMove(WPARAM wKeyType, const POINT& point);
		
		/*!
		 * @brief WM_LBUTTONDOWN��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonDown(WPARAM wKeyType, const POINT& point);
		
		/*!
		 * @brief WM_LBUTTONUP��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonUp(WPARAM wKeyType, const POINT& point);
		
		/*!
		 * @brief WM_MOUSELEAVE��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();

		
		/*!
		 * @brief  �����Ϣ�������
		 * @param  ����������
		 * @return ����İ�ť
		 * @note
		 */
		CPE::SpinCtrlButton HitTest( const POINT& point);

		
		/*!
		 * @brief ����spin��ť
		 * @param 
		 * @return 
		 * @note
		 */
		void DrawSpin(HDC hDC);

	private:
		
		/* ���ϼ�ͷ����ͼ */
		CBitmapRefPtr	m_pBmpUpArrow[CPE::SCBS_Size];
		
		/* ���¼�ͷ����ͼ */
		CBitmapRefPtr	m_pBmpDownArrow[CPE::SCBS_Size];
		
		/* �����ͷ����ͼ */
		CBitmapRefPtr	m_pBmpLeftArrow[CPE::SCBS_Size];
		
		/* ���Ҽ�ͷ����ͼ */
		CBitmapRefPtr	m_pBmpRightArrow[CPE::SCBS_Size];
	
	};

}
