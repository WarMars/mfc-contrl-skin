#include "ButtonCtrlSkin.h"

///
/// @brief ��ͨ��ťƤ��
///
namespace GlobalSkin
{
	class CPushButtonCtrl : public CButtonCtrlSkin
	{
	public:
		CPushButtonCtrl( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CPushButtonCtrl( );

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

		/** 
		 * @brief ���ư�ť����
		 * @param pDC dc
		 * @param r λ�þ���
		 */
		void	DrawBackground(CDC *pDC, const CRect& r);

	private:
		///
		/// @brief ������ͼ
		///
		CBitmapRefPtr	m_pBmpPressed;

		///
		/// @brief �޲�����ͼ
		///
		CBitmapRefPtr	m_pBmpNormal;

		///
		/// @brief ������ͼ
		///
		CBitmapRefPtr	m_pBmpDisabled;
	};
}