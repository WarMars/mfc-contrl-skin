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
	 * @brief 设置所有状态的位图
	 * @param nOver（鼠标在按钮上的状态）;
	 * @param nNormal（初始状态）
	 * @param nPressed（按下状态）
	 * @param nFocus（焦点）
	 */
	void SetBitmap(
		Image*  bmpNormal,
		Image*  bmpHover, 
		Image*  bmpPressed,
		Image*  bmpDsiabled );

	/** 
	 * @breif 设置3态按钮的贴图
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
	bool	m_bOver;	//鼠标位于按钮之上时该值为true，反之为flase
	bool	m_bTracking;	//在鼠标按下没有释放时该值为true
	bool	m_bSelected;	//按钮被按下是该值为true
	bool	m_bFocus;	//按钮为当前焦点所在时该值为true
	bool	m_bChecked;
	int		m_nTextLeftSpacing;

	Image*	m_imgNormal;//加载初始状态的图片
	Image*	m_imgPressed;//按下状态的图片
	Image*	m_imgDisabled;//按钮被禁用
	Image*	m_imgHover;  //鼠标经过
	std::vector<Image*>	m_vOwnerDeleted;
	CPictureButton*	m_pPartner;
};

#endif

