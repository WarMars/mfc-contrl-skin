#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

namespace GlobalSkin
{
	namespace CPE /* Control Parameter Enumeration �ؼ�����ö����*/
	{
		/*!
		 * @brief ����������״̬
		 */
		enum ToolBarItemState
		{
			TBIS_Normal = 0,	/* �޲��� */
			TBIS_Hover,			/* ��꾭�� */
			TBIS_Pressed,		/* ��갴�� */
			TBIS_Disabled,		/* ������ */
			TBIS_Size
		};
	}

	/*!
	 * @brief �������ؼ�����
	 */
	struct CToolBarCtrlParameter:public CCtrlParameter
	{
	public:

		int GetPressedItem( ) const;
		void SetPressedItem( int nIndex );

		int GetHotItem( ) const;
		void SetHotItem( int nIndex );
	private:
		/* ��ǰ���µ����� */
		int m_nPressedItem;
		/* ��ǰ�������� */
		int	m_nHotItem;
	};

	/* �������ؼ�Ƥ�� */
	class CToolBarCtrlSkin:public CCtrlSkinPackage<CToolBarCtrlParameter>
	{
	public:
		CToolBarCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CToolBarCtrlSkin( );
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
		 * @brief WM_PAINT��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();

		/*!
		 * @brief WM_NCPAINT��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnNcPaint(HRGN rgn1);

		
		/*!
		 * @brief WM_MOUSEMOVE��Ϣ�������
		 * @param  
		 * @return 
		 * @note
		 */
		void OnMouseMove(WPARAM wKeyType, const POINT& point);
		
		/*!
		 * @brief  WM_LBUTTONDOWN��Ϣ�������
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
		 * @brief WM_MOUSELEAVE��Ϣ����
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();
		
		/*!
		 * @brief ���toolbar������Ŀ�ļ��
		 * @param �����
		 * @return ���������
		 * @note ����ȷ����ǰ������ĸ���ť
		 */
		int HitTest(const POINT& point);

		
		/*!
		 * @brief ���ƹ�����
		 * @param 
		 * @return 
		 * @note
		 */
		void DrawToolBar(HDC hDC);

		
		/*!
		 * @brief ���ƹ���������
		 * @param hdc dc
		 * @param rcItem �����λ�þ���
		 * @param nState �����״̬
		 * @return 
		 * @note
		 */
		void DrawItemEntry(HDC hDC, const CRect& rcItem, CPE::ToolBarItemState nState );

	private:
		
		/* ����ͼ */
		CBitmapRefPtr	m_pBmpBk;

		/* ��������ť��ı��� */
		CBitmapRefPtr	m_pBmpItemBk[CPE::TBIS_Size];
	};

}
