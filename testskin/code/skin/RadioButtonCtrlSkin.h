#pragma once
#include "ButtonCtrlSkin.h"

///
/// @brief radio控件
///
namespace GlobalSkin
{
class CRadioButtonCtrlSkin : public CButtonCtrlSkin
{
	///
	/// @brief radio状态
	///
	enum RadioState
	{
		RS_Normal,		/* 无操作 */
		RS_Hover,		/* 鼠标经过 */
		RS_Pressed,		/* 鼠标按下 */
		RS_Focused,		/* 有鼠标焦点 */
		RS_Disabled,	/* 禁用 */
		RS_State		
	};

	///
	/// @brief 状态贴图
	///
	struct StatePicture 
	{
		///
		/// @brief 勾选的图片
		///
		CBitmapRefPtr	pBmpChecked;

		///
		/// @brief 未勾选的图片
		///
		CBitmapRefPtr	pBmpUnchecked;
	};
public:
	CRadioButtonCtrlSkin( );
	void LoadSkin( const CSkinConfig* pConfig );
protected:
	~CRadioButtonCtrlSkin( );

	/*!
	 * @brief  override
	 * @param  
	 * @return  
	 * @note
	 */
	bool OnHandleStyleType( UINT nStype, UINT nExStyle );

	/*!
	 * @brief  绘制按钮
	 * @param  dc
	 * @return 
	 * @note
	 */
	void OnDrawButton(CDC *pDC);

	/*!
	 * @brief  初始化贴图位图
	 * @return 
	 * @note
	 */
	void InitBmp( CBitmapRefPtr pBkImg, 
		CBitmapRefPtr pNormalImg, CBitmapRefPtr pNormalCheckedImg,
		CBitmapRefPtr pHoverImg, CBitmapRefPtr pHoverCheckedImg,
		CBitmapRefPtr pPressedImg, CBitmapRefPtr pPressedCheckedImg,
		CBitmapRefPtr pFocusedImg, CBitmapRefPtr pFocusedCheckedImg,
		CBitmapRefPtr pDisabledImg, CBitmapRefPtr pDisabledCheckedImg );
private:

	///
	/// @brief 背景图
	///
	CBitmapRefPtr	m_pBmpBk;
	
	///
	/// @brief 状态图0-正常,1-鼠标悬浮,2-按下，3-获取焦点，4-禁用
	///
	StatePicture	m_pBmpState[RS_State];

};

}