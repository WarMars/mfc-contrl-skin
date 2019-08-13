#pragma once
#include "ButtonCtrlSkin.h"

///
/// @brief group�ؼ�
///
namespace GlobalSkin
{
	class CGroupBoxCtrlSkin : public CButtonCtrlSkin
	{

	public:
		CGroupBoxCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CGroupBoxCtrlSkin( );

		
		/*!
		 * @brief override
		 * @param 
		 * @return 
		 * @note
		 */
		bool OnHandleStyleType( UINT nStype, UINT nExStyle );

		/*!
		 * @brief ���ư�ť
		 * @param dc
		 * @return 
		 * @note
		 */
		void OnDrawButton(CDC *pDC);

	private:
		///
		/// @brief �߿���ͼ
		///
		CBitmapRefPtr	m_pBmpBorder;

		///
		/// @brief ������ɫ
		///
		CBitmapRefPtr	m_pBmpCaption;
	};
}


