#pragma once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"

///
/// @brief ����ؼ�Ƥ��
///
namespace GlobalSkin
{
	struct CSliderCtrlParameter:public CCtrlParameter
	{
	public:
		bool IsVertical( ) const;
		bool SetVertical( bool bNew );
	private:
		
		/* �Ƿ��Ǵ�ֱ�� */
		bool	m_bIsVertical;
	};
	///
	/// @brief ����ؼ���Ƥ��
	///
	class CSilderCtrlSkin:public CCtrlSkinPackage<CSliderCtrlParameter>
	{
	public:
		CSilderCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CSilderCtrlSkin( );
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
		void OnPaint( );
		
		/*!
		 * @brief ���ƻ���
		 * @param  dc
		 * @return 
		 * @note ���ƻ���ı�����
		 */
		void Draw( HDC hDC );

	private:
		
		/* ˮƽ������ͼ */
		CBitmapRefPtr	m_pBmpHBk;

		/* ��ֱ������ͼ */
		CBitmapRefPtr	m_pBmpVBk;
		
		/* ˮƽ���� */
		CBitmapRefPtr	m_pBmpHSlider;
		
		/* ��ֱ���� */
		CBitmapRefPtr	m_pBmpVSlider;
		
		/* ˮƽ������ͼ */
		CBitmapRefPtr	m_pBmpHLine;

		/* ��ֱ������ͼ */
		CBitmapRefPtr	m_pBmpVLine;
	};

}
