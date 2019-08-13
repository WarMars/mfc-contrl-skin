#pragma once
#include "ButtonCtrlSkin.h"

///
/// @brief group控件
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
		 * @brief 绘制按钮
		 * @param dc
		 * @return 
		 * @note
		 */
		void OnDrawButton(CDC *pDC);

	private:
		///
		/// @brief 边框贴图
		///
		CBitmapRefPtr	m_pBmpBorder;

		///
		/// @brief 标题颜色
		///
		CBitmapRefPtr	m_pBmpCaption;
	};
}


