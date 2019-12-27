#pragma once
#include <GdiPlus.h>

// CPictureStatus

class CPictureStatic : public CStatic
{
	DECLARE_DYNAMIC(CPictureStatic)

public:
	CPictureStatic( Gdiplus::Image* pImgBk );
	virtual ~CPictureStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

public:
	Gdiplus::Image*	m_pImgBk;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


