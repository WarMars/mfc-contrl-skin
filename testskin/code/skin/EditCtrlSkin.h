#pragma once
#include "CtrlWithScrollBar.h"
#include "gdiobj_ptr.hpp"

///
/// @brief Edit �ؼ�
///
namespace GlobalSkin
{
	struct sEditParameter:public sCtrlWithScrollBar
	{

	};

	class CEditCtrlSkin:public CCtrlWithScrollBar<sEditParameter>
	{
	public:
		CEditCtrlSkin();

		void LoadSkin( const CSkinConfig* pConfig );
		/** 
		 * @brief ���ڹ��̴���
		 */
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

		/*!
		 * @brief ���ñ߿����ͼ
		 * @param λͼָ��
		 * @return 
		 * @note
		 */
		void SetBorderBmp( CBitmapRefPtr pBitmap );
	protected:

		/** 
		 * @brief ��ȡ��ǰ�Ĵ�������
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief �ӹܿؼ�Ƥ��֮ǰ
		 */
		bool OnInitSkinParam( HWND hWnd, CParamReference* pParam );

		
		/*!
		 * @brief WM_PAINT��Ϣ�������
		 * @param 
		 * @return 
		 * @note
		 */
		void OnPaint( );

		~CEditCtrlSkin();
	private:
		/* �߿���ͼ */
		CBitmapRefPtr	m_pBorderBmp;
	};
}


