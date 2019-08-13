#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief ��������ͼ
///
namespace GlobalSkin
{
	struct sProgressBarCtrlParameter:public sCtrlParameter
	{
	public:
		bool IsVertical( ) const;
		bool SetVertical( bool bNew );
	private:
		///
		/// @brief �Ƿ��Ǵ�ֱ������
		///
		bool	m_bIsVertical;
	};

	class CProgressBarCtrlSkin:public CCtrlSkinPackage<sProgressBarCtrlParameter>
	{
	public:
		CProgressBarCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CProgressBarCtrlSkin( );
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
		 * @brief ����
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint();
		
		/*!
		 * @brief WM_ERASEBKGND ���Ʊ���
		 * @param hdc dc
		 * @return 
		 * @note
		 */
		BOOL OnEraseBkgnd( HDC hdc );

		
		/*!
		 * @brief ��ȡ����λ��
		 * @param �����λ��
		 * @return �ɹ�����true,���򷵻�false.
		 * @note
		 */
		BOOL GetPosRect( RECT &rtPos );
	private:
		///
		/// @brief ����ͼ
		///
		CBitmapRefPtr	m_pBmpHBk;
		CBitmapRefPtr	m_pBmpVBk;

		///
		/// @brief ��������ͼ
		///
		CBitmapRefPtr	m_pBmpHProgress;
		CBitmapRefPtr	m_pBmpVProgress;
	};

}
