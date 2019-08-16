#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

namespace GlobalSkin
{
	struct CSysHeaderParameter: public CCtrlParameter
	{
		/* ����ͷ����״̬ */
		enum HeaderItemState
		{
			HIS_Normal=0,	/* ���κβ��� */
			HIS_Hover,		/* ��꾭�� */
			HIS_Press,		/* ��갴�� */
			HIS_State		/*  */
		};
		
		/* ��ǰ�������� */
		UINT m_nHotItem;
		
		/* ���µ���ı�� */
		UINT m_nPressedItem;
	};

	
	/* ����ͷ��Ƥ�� */
	class CSysHeaderSkin: public CCtrlSkinPackage<CSysHeaderParameter>
	{
	public:
		CSysHeaderSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CSysHeaderSkin( );
		
		/** 
		 * @brief ��ȡ��ǰ�Ĵ�������
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief �ӹܿؼ�Ƥ��֮ǰ
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		
		/*!
		 * @brief ���ڹ���
		 * @param 
		 * @return 
		 * @note
		 */
		LRESULT OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		
		/*!
		 * @brief	WM_PAINT��Ϣ����
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();

		
		/*!
		 * @brief WM_ERASEBKGND ��Ϣ�Ĵ���
		 * @param 
		 * @return 
		 * @note
		 */
		BOOL OnEraseBkgnd( HDC hdc );
		
		/*!
		 * @brief WM_MOUSEMOVE��Ϣ
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseMove(UINT nFlags, const CPoint& point);

		
		/*!
		 * @brief WM_LBUTTONDOWN��Ϣ
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonDown(UINT nFlags, const CPoint& point);

		
		/*!
		 * @brief WM_LBUTTONUP��Ϣ
		 * @param 
		 * @return 
		 * @note
		 */
		void OnLButtonUp(UINT nFlags, const CPoint& point);

		
		/*!
		 * @brief	WM_MOUSEMOVE��Ϣ
		 * @param 
		 * @return 
		 * @note
		 */
		void OnMouseLeave();

		
		/*!
		 * @brief  �������
		 * @param  �����
		 * @return ������������ı��
		 * @note
		 */
		int HitTest( const CPoint& point);

		
		/*!
		 * @brief ���Ʊ���ͷ.���ݵ�ǰ��������͵�ǰ�������Ŀ��
		 *		  Ϊ����ͷ��ͬ��λ�û��Ʋ�ͬ�ı�������ɫ��
		 * @param dc
		 * @return 
		 * @note
		 */
		void DrawHeader(HDC hdc );
		
		/*!
		 * @brief ��������
		 * @param dc
		 * @param nIndex ����ı��
		 * @param rectItem ����ľ���
		 * @param state Ҫ���Ƶ�״̬
		 * @return 
		 * @note
		 */
		void DrawItemEntry( HDC hdc, LRESULT nIndex, 
			const CRect& rectItem,
			CSysHeaderParameter::HeaderItemState state);

		
		/*!
		 * @brief  �ػ�
		 * @param 
		 * @return 
		 * @note
		 */
		void Redraw( );
	private:
		
		/* ����ͼ */
		CBitmapRefPtr		m_pBmpBk;
		
		/* ����ı���ͼ */
		CBitmapRefPtr		m_pBmpItem[CSysHeaderParameter::HIS_State];
	};
}


