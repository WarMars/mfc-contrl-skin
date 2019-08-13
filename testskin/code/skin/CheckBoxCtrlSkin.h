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
			CBitmapRefPtr	pBmpChecked;		/* ��ѡ */
			CBitmapRefPtr	pBmpUnchecked;		/* δ��ѡ */
			CBitmapRefPtr	pBmpIndeterminate;	/* �м�״̬ */
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
			const CBitmapRefPtr& pBkImg,
			const CBitmapRefPtr& pNormalImg, 
			const CBitmapRefPtr& pNormalCheckedImg, 
			const CBitmapRefPtr& pMormalIndeterminateImg,
			const CBitmapRefPtr& pHoverImg, 
			const CBitmapRefPtr& pHoverCheckedImg, 
			const CBitmapRefPtr& pHoverIndeterminateImg,
			const CBitmapRefPtr& pPressedImg, 
			const CBitmapRefPtr& pPressedCheckedImg, 
			const CBitmapRefPtr& pPressedIndeterminateImg,
			const CBitmapRefPtr& pFocusedImg, 
			const CBitmapRefPtr& pFocusedCheckedImg, 
			const CBitmapRefPtr& pFocusedIndeterminateImg,
			const CBitmapRefPtr& pDisabledImg, 
			const CBitmapRefPtr& pDisabledCheckedImg, 
			const CBitmapRefPtr& pDisabledIndeterminateImg );

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
		CBitmapRefPtr	m_pBmpBk;

		/* ״̬λͼ */
		StatePicture	m_pBmpState[CBS_State];
	};
}
