#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief tab�ؼ�Ƥ��
///
namespace GlobalSkin
{
	namespace CPE /* control parameter enumeration �ؼ�����ö�� */
	{
		enum TabItemState /* tab�ؼ����״̬ */
		{
			TabIS_Normal = 0,	//�޲���
			TabIs_Hover,		//��껬��
			TabIS_Pressed,      //����
			TabIS_Size
		};
	}

	///
	/// @brief tab�Ĳ���
	///
	struct sTabCtrlSkinParameter:public sCtrlParameter
	{
	public:
		int	GetPressedIndex( ) const;
		void SetPressedIndex( int nIndex );

		int GetHotIndex( ) const;
		void SetHotIndex( int nIndex );
	private:
		
		// ���µ����id
		int m_nPressedIndex;
		// ѡ�е����id
		int	m_nHotIndex;
	};

	/** 
	 * @brief tab�ؼ�Ƥ��
	 */
	class CTablCtrlSkin:public CCtrlSkinPackage<sTabCtrlSkinParameter>
	{
	public:
		CTablCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CTablCtrlSkin( );
		/** 
		 * @brief override �ؼ��Ĵ���������
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief override	�ӹ�֮ǰ��������
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/** 
		 * @brief override	�ؼ���Ϣ����
		 */
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		
		/*!
		 * @brief WM_PAINT��Ϣ�Ĵ������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();

		
		/*!
		 * @brief WM_MOUSEMOVE��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseMove(UINT nKeyType, const POINT& point);

		
		/*!
		 * @brief WM_LBUTTONDOWN��Ϣ���������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonDown(UINT nKeyType, const POINT& point);

		
		/*!
		 * @brief WM_LBUTTONUP��Ϣ�Ĵ������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonUp(UINT nFlags, const POINT& point);
		
		/*!
		 * @brief WM_MOUSELEAVE��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();

		
		/*!
		 * @brief �������
		 * @param ����������
		 * @return �����tab�������
		 * @note
		 */
		int HitTest( const POINT& point);

		
		/*!
		 * @brief  ����tab
		 * @param  hdc dc
		 * @param  nIndex ���
		 * @param  rcItem �����λ�þ���
		 * @return 
		 * @note
		 */
		void DrawTab( HDC hdc );
		
		/*!
		 * @brief ��������
		 * @param hdc dc
		 * @param rcItem �����λ�þ���
		 * @param nState �����״̬
		 * @return 
		 * @note
		 */
		void DrawItemEntry( HDC hdc, int nIndex, const CRect& rcItem, CPE::TabItemState nState);

	private:

		/* ���� */
		CBitmapRefPtr		m_pBmkBk;

		/* ������ı��� */
		CBitmapRefPtr		m_pBmpItem[CPE::TabIS_Size];
	};
}

