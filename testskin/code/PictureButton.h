#ifndef PICTUREBUTTON_H
#define PICTUREBUTTON_H

#include <afxwin.h>
// CPictureButton
#include "gdiobj_ptr.hpp"
#include <vector>
class CPictureButton : public CButton
{
	DECLARE_DYNAMIC(CPictureButton)

public:
	CPictureButton();
	virtual ~CPictureButton();

	/** 
	 * @brief ��������״̬��λͼ
	 * @param nOver������ڰ�ť�ϵ�״̬��;
	 * @param nNormal����ʼ״̬��
	 * @param nPressed������״̬��
	 * @param nFocus�����㣩
	 */
	void SetBitmap(
		Image*  bmpNormal,
		Image*  bmpHover, 
		Image*  bmpPressed,
		Image*  bmpDsiabled );

	/** 
	 * @breif ����3̬��ť����ͼ
	 */
	void Set3StateBitmap( 
		Image*  bmpNormal,
		Image*  bmpHover, 
		Image*  bmpPressed );

	void Set2StateBitmap(  
		Image*  bmpNormal,
		Image*  bmpHover );


	void SetNormalBitmap( Image*  bmp );
	void SetHoverBitmap( Image*  bmp );
	void SetPressedBitmap( Image*  bmp );
	void SetDisabledBitmap( Image*  bmp );
	void SetFontBold( bool bBold );
	void SetFontSizeOffset( int nSize );

	void Set2StateAndDisabledBitmap( LPCTSTR lpszUiFilePath );
	void Set2StateBitmap( LPCTSTR lpszUiFilePath );
	void ShareUiWith( CPictureButton& rhs );
	bool SetHover( bool bHover );
	inline bool IsHover( ) const						{ return m_bOver; }
	inline bool IsChecked( ) const						{ return m_bChecked; }
	void SetChecked( bool bChecked ) ;
	inline bool IsSelected( )  const					{ return m_bSelected;				}
	void SetSelected( bool bSelected );
	inline int  GetTextLeftSpacing( ) const				{ return m_nTextLeftSpacing;		}
	inline void SetTextLeftSpacing( int nSpacing )		{ m_nTextLeftSpacing = nSpacing;	}
	inline void SetPartner( CPictureButton* pButton )	{ m_pPartner = pButton;				}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	int		m_nFontOffset;
	bool	m_bBoldFont;
	bool	m_bOver;	//���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
	bool	m_bTracking;	//����갴��û���ͷ�ʱ��ֵΪtrue
	bool	m_bSelected;	//��ť�������Ǹ�ֵΪtrue
	bool	m_bFocus;	//��ťΪ��ǰ��������ʱ��ֵΪtrue
	bool	m_bChecked;
	int		m_nTextLeftSpacing;

	Image*	m_imgNormal;//���س�ʼ״̬��ͼƬ
	Image*	m_imgPressed;//����״̬��ͼƬ
	Image*	m_imgDisabled;//��ť������
	Image*	m_imgHover;  //��꾭��
	std::vector<Image*>	m_vOwnerDeleted;
	CPictureButton*	m_pPartner;
};

#endif

