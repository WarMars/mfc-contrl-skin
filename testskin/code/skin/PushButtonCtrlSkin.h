#include "ButtonCtrlSkin.h"

///
/// @brief 普通按钮皮肤
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
		 * @brief 绘制按钮
		 * @param dc
		 * @return 
		 * @note
		 */
		void OnDrawButton(CDC *pDC);

		/** 
		 * @brief 绘制按钮背景
		 * @param pDC dc
		 * @param r 位置矩形
		 */
		void	DrawBackground(CDC *pDC, const CRect& r);

	private:
		///
		/// @brief 按下贴图
		///
		CBitmapRefPtr	m_pBmpPressed;

		///
		/// @brief 无操作贴图
		///
		CBitmapRefPtr	m_pBmpNormal;

		///
		/// @brief 禁用贴图
		///
		CBitmapRefPtr	m_pBmpDisabled;
	};
}