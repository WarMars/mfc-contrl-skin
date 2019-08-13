#pragma once
#include "ButtonCtrlSkin.h"

///
/// @brief radio�ؼ�
///
namespace GlobalSkin
{
class CRadioButtonCtrlSkin : public CButtonCtrlSkin
{
	///
	/// @brief radio״̬
	///
	enum RadioState
	{
		RS_Normal,		/* �޲��� */
		RS_Hover,		/* ��꾭�� */
		RS_Pressed,		/* ��갴�� */
		RS_Focused,		/* ����꽹�� */
		RS_Disabled,	/* ���� */
		RS_State		
	};

	///
	/// @brief ״̬��ͼ
	///
	struct StatePicture 
	{
		///
		/// @brief ��ѡ��ͼƬ
		///
		CBitmapRefPtr	pBmpChecked;

		///
		/// @brief δ��ѡ��ͼƬ
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
	 * @brief  ���ư�ť
	 * @param  dc
	 * @return 
	 * @note
	 */
	void OnDrawButton(CDC *pDC);

	/*!
	 * @brief  ��ʼ����ͼλͼ
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
	/// @brief ����ͼ
	///
	CBitmapRefPtr	m_pBmpBk;
	
	///
	/// @brief ״̬ͼ0-����,1-�������,2-���£�3-��ȡ���㣬4-����
	///
	StatePicture	m_pBmpState[RS_State];

};

}