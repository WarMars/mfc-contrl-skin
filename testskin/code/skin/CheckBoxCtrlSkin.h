#pragma once
#include "ButtonCtrlSkin.h"

///
/// @brief ��ѡ��ؼ�
///
namespace GlobalSkin
{
	class CCheckBoxCtrlSkin: public CButtonCtrlSkin
	{
		/*!
		 * @brief ��ѡ��״̬
		 */
		enum CheckBoxState 
		{
			CBS_Normal,		/* �޲��� */
			CBS_Hover,		/* ��껬�� */
			CBS_Pressed,	/* ��갴�� */
			CBS_Focused,	/* �н��� */
			CBS_Disabled,	/* ʧЧ */
			CBS_State		
		};

		/*!
		 * @brief ״̬ͼ
		 */
		struct StatePicture 
		{
			Gdiplus::Image*	pBmpChecked;		/* ��ѡ */
			Gdiplus::Image*	pBmpUnchecked;		/* δ��ѡ */
			Gdiplus::Image*	pBmpIndeterminate;	/* �м�״̬ */
		};
	public:
		CCheckBoxCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );

		/*!
		 * @brief ����λͼ
		 * @param  pBkImg			����ͼ
		 * @param  pNormalImg				�޲���
		 * @param  pNormalCheckedImg		��ѡ
		 * @param  pMormalIndeterminateImg  �м�״̬
		 * @param  pHoverImg				��꾭��
		 * @param  pHoverCheckedImg			ѡ��ʱ��꾭��
		 * @param  pHoverIndeterminateImg	�м�״̬ʱ��꾭��
		 * @param  pPressedImg				��갴��
		 * @param  pPressedCheckedImg		ѡ��ʱ��갴��
		 * @param  pPressedIndeterminateImg	ѡ��ʱ�м�״̬
		 * @param  pFocusedImg				�н���ʱ
		 * @param  pFocusedCheckedImg		��ѡʱ�Ľ���״̬
		 * @param  pFocusedIndeterminateImg �м�״̬ʱ�н���
		 * @param  pDisabledImg				����
		 * @param  pDisabledCheckedImg		�����ҹ�ѡ
		 * @param  pDisabledIndeterminateImg �����Ҵ����м�״̬
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
		 * @brief Ҫ������ؼ���ʽ
		 * @param nStyle һ����ʽ
		 * @param nExStyle ��չ��ʽ
		 * @return ��������true�����򷵻�false.
		 */
		bool OnHandleStyleType( UINT nStype, UINT nExStyle );

		/*!
		 * @brief  ���ư�ť
		 * @param  ����
		 * @note ���а�ť��Ч������
		 */
		void OnDrawButton(CDC *pDC);

		/* ������ͼ */
		Gdiplus::Image*	m_pBmpBk;

		/* ״̬λͼ */
		StatePicture	m_pBmpState[CBS_State];
	};
}
