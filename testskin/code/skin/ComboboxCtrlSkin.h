#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief ��Ͽ�ؼ�
///
namespace GlobalSkin
{
	/*!
	 * @brief ��Ͽ�Ŀؼ�����
	 */
	struct CComboboxCtrlParameter:public CCtrlParameter
	{
		enum
		{
			COMBOX_NORMAL	= 0x00000080L, // ����״̬
			COMBOX_DISABLED = 0x00000001L, // ����״̬
			COMBOX_PRESSED	= 0x00000002L, // ����״̬
			COMBOX_HOVER	= 0x00000004L, // ����״̬ (����ڸô�����)
			COMBOX_FOCUS	= 0x00000008L  // ���м������뽹��
		};

		/*!
		 * @brief �����ļ�ͷ��״̬
		 */
		enum ThumbBoxState
		{
			CheckNormal = 0,	/* �޲���״̬ */
			CheckHover,			/* ��꾭�� */
			CheckPressed,		/* ��갴�� */
			CheckFocused,		/* �н��� */
			CheckDisabled,		/* ���� */
			CheckBoxStateSize,	/*  */
		};

		INT		m_nState;		// ��ǰ״̬
		LONG	m_nHScrollBar;  // ˮƽ������
		LONG	m_nVScrollBar;	// ��ֱ������
		bool	m_bHitThumb;	// �Ƿ����������ļ�ͷ
		bool	m_bTouchedListBox; // �Ƿ��Ѿ������������б�
	};

	/*!
	 * @brief ��Ͽ�Ŀؼ�Ƥ��
	 */
	class CComboBoxCtrlSkin: public CCtrlSkinPackage<CComboboxCtrlParameter>
	{
	public:
		CComboBoxCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CComboBoxCtrlSkin( );

		/**
		 * @brief override
		 */
		LRESULT OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		/** 
		 * @brief ��ȡ��ǰ�Ĵ�������
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief �ӹܿؼ�Ƥ��֮ǰ
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );

		/*!
		 * @brief  WM_CTLCOLOR ��Ϣ�Ĵ�����̡�
		 *		   ��û�й��������б�ؼ�������½��й�����
		 * @param wParam HDC
		 * @param lParam HWND
		 * @return ������HBRUSH
		 * @note �μ�ϵͳ����Ϣ˵��
		 */
		LRESULT OnCtrlColor( WPARAM wParam, LPARAM lParam );

		/*!
		 * @brief  WM_MOUSEMOVE��Ϣ�Ĵ�����̡�
		 *		   ��¼����״̬��Ϊ������׼����
		 * @param  nFlags ����
		 * @param  point ��������
		 * @note �μ�ϵͳ����Ϣ˵��
		 */
		void OnMouseMove(UINT nFlags, const CPoint& point);

		/*!
		 * @brief  WM_LBUTTONDOWN��Ϣ�Ĵ������
		 * @param  nFlags ����ʱ������ϵͳ������־
		 * @param  point ����ʱ����С
		 * @return 
		 * @note ׷�ٿؼ���״̬��Ϊ������׼��
		 */
		void OnLButtonDown(UINT nFlags , const CPoint& point); //
		void OnLButtonUp(UINT nFlags, const CPoint& point); //
		void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp); //
		void OnNcPaint(HRGN rgn1); //
		void OnPaint();//
		void OnSetFocus(HWND hWnd); //
		void OnKillFocus(HWND hWnd); //
		/*!
		 * @brief 
		 * @param 
		 * @return 
		 * @note
		 */
		void OnSetText(WPARAM wp,LPARAM lp); //
		void OnMouseLeave(); //
		
		/*!
		 * @brief ����
		 * @param ����
		 * @return 
		 * @note
		 */
		void DrawComboBox(CDC *pDC);

		/*!
		 * @brief ���������ͷ�ļ��
		 * @param �����
		 * @return ���������ͷ����true,���򷵻�false
		 * @note
		 */
		bool HitTestThumb( const CPoint& point );
		void OnSize( int cx, int cy );
	private:
		void Redraw( bool bDrawBorder = false );

	private:
		/* �߿�ͼ */
		CBitmapRefPtr	m_pBmpBorder;
		/* ������ͷ��״̬��ͼ */
		CBitmapRefPtr	m_pBmpThumb[CComboboxCtrlParameter::CheckBoxStateSize];
	};

}