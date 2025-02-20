#pragma once
#include "ButtonCtrlSkin.h"

///
/// @brief 复选框控件
///
namespace GlobalSkin
{
	class CCheckBoxCtrlSkin: public CButtonCtrlSkin
	{
		/*!
		 * @brief 单选框状态
		 */
		enum CheckBoxState 
		{
			CBS_Normal,		/* 无操作 */
			CBS_Hover,		/* 鼠标滑过 */
			CBS_Pressed,	/* 鼠标按下 */
			CBS_Focused,	/* 有焦点 */
			CBS_Disabled,	/* 失效 */
			CBS_State		
		};

		/*!
		 * @brief 状态图
		 */
		struct StatePicture 
		{
			Gdiplus::Image*	pBmpChecked;		/* 勾选 */
			Gdiplus::Image*	pBmpUnchecked;		/* 未勾选 */
			Gdiplus::Image*	pBmpIndeterminate;	/* 中间状态 */
		};
	public:
		CCheckBoxCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );

		/*!
		 * @brief 设置位图
		 * @param  pBkImg			背景图
		 * @param  pNormalImg				无操作
		 * @param  pNormalCheckedImg		勾选
		 * @param  pMormalIndeterminateImg  中间状态
		 * @param  pHoverImg				鼠标经过
		 * @param  pHoverCheckedImg			选中时鼠标经过
		 * @param  pHoverIndeterminateImg	中间状态时鼠标经过
		 * @param  pPressedImg				鼠标按下
		 * @param  pPressedCheckedImg		选中时鼠标按下
		 * @param  pPressedIndeterminateImg	选中时中间状态
		 * @param  pFocusedImg				有焦点时
		 * @param  pFocusedCheckedImg		勾选时的焦点状态
		 * @param  pFocusedIndeterminateImg 中间状态时有焦点
		 * @param  pDisabledImg				禁用
		 * @param  pDisabledCheckedImg		禁用且勾选
		 * @param  pDisabledIndeterminateImg 禁用且处于中间状态
		 * @note
		 */
		void InitBmp(
			Gdiplus::Image* pBkImg,
			Gdiplus::Image* pNormalImg, 
			Gdiplus::Image* pNormalCheckedImg, 
			Gdiplus::Image* pMormalIndeterminateImg,
			Gdiplus::Image* pHoverImg, 
			Gdiplus::Image* pHoverCheckedImg, 
			Gdiplus::Image* pHoverIndeterminateImg,
			Gdiplus::Image* pPressedImg, 
			Gdiplus::Image* pPressedCheckedImg, 
			Gdiplus::Image* pPressedIndeterminateImg,
			Gdiplus::Image* pFocusedImg, 
			Gdiplus::Image* pFocusedCheckedImg, 
			Gdiplus::Image* pFocusedIndeterminateImg,
			Gdiplus::Image* pDisabledImg, 
			Gdiplus::Image* pDisabledCheckedImg, 
			Gdiplus::Image* pDisabledIndeterminateImg );

	protected:
		~CCheckBoxCtrlSkin( );

		/** 
		 * @brief 要处理处理控件样式
		 * @param nStyle 一般样式
		 * @param nExStyle 扩展样式
		 * @return 处理，返回true；否则返回false.
		 */
		bool OnHandleStyleType( UINT nStype, UINT nExStyle );

		/*!
		 * @brief  绘制按钮
		 * @param  画布
		 * @note 进行按钮的效果绘制
		 */
		void OnDrawButton(CDC *pDC);

		/* 背景贴图 */
		Gdiplus::Image*	m_pBmpBk;

		/* 状态位图 */
		StatePicture	m_pBmpState[CBS_State];
	};
}
