#include "stdafx.h"
#include "CheckBoxCtrlSkin.h"
#include "ImageManager.h"
#include "utils.hpp"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE


namespace GlobalSkin
{

	CCheckBoxCtrlSkin::CCheckBoxCtrlSkin( )
	{

	}

	void CCheckBoxCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
	{
#ifdef USING_CONFIG_FILE
		if( NULL == pConfig )
#endif
		{
			ASSERT(false);
			//*如果一定要用，请将下面的SubImage图片添加到CImagePool中进行管理
			Gdiplus::Image* pBitmap = ImagePool( ).GetImage(
				TEXT("ui\\skin\\CheckBox.bmp") );
			int nXOffset = 0;
			int nYOffset = 0;
			int nSize = 48;
			InitBmp( 
				Util::CreateSubImage( pBitmap, 
				nXOffset, nYOffset+3*nSize,nSize,nSize), //bk
				Util::CreateSubImage( pBitmap, 
				nXOffset, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset, nYOffset,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset, nYOffset+nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+nSize, nYOffset,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+nSize, nYOffset+nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+2*nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+2*nSize, nYOffset,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+2*nSize, nYOffset+nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+3*nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+3*nSize, nYOffset,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+3*nSize, nYOffset+nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+4*nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+4*nSize, nYOffset,nSize,nSize),
				Util::CreateSubImage( pBitmap, 
				nXOffset+4*nSize, nYOffset+nSize,nSize,nSize) );
			return;
		}
#ifdef USING_CONFIG_FILE
		InitBmp(
			pConfig ->GetImage(TEXT("check/background") ),
			pConfig ->GetImage(TEXT("check/button/unchecked/normal") ),
			pConfig ->GetImage(TEXT("check/button/checked/normal") ),
			pConfig ->GetImage(TEXT("check/button/indetermined/normal") ),
			pConfig ->GetImage(TEXT("check/button/unchecked/hover") ),
			pConfig ->GetImage(TEXT("check/button/checked/hover") ),
			pConfig ->GetImage(TEXT("check/button/indetermined/hover") ),
			pConfig ->GetImage(TEXT("check/button/unchecked/pressed") ),
			pConfig ->GetImage(TEXT("check/button/checked/pressed") ),
			pConfig ->GetImage(TEXT("check/button/indetermined/pressed") ),
			pConfig ->GetImage(TEXT("check/button/unchecked/focused") ),
			pConfig ->GetImage(TEXT("check/button/checked/focused") ),
			pConfig ->GetImage(TEXT("check/button/indetermined/focused") ),
			pConfig ->GetImage(TEXT("check/button/unchecked/disabled") ),
			pConfig ->GetImage(TEXT("check/button/checked/disabled") ),
			pConfig ->GetImage(TEXT("check/button/indetermined/disabled") ) );
#endif
	}

	CCheckBoxCtrlSkin::~CCheckBoxCtrlSkin( )
	{

	}

	void CCheckBoxCtrlSkin::InitBmp(
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
		Gdiplus::Image* pDisabledIndeterminateImg   )
	{
		m_pBmpBk = pBkImg;
#define LOAD_BUTTON_STATE_BOX_BMP(variable,pUncheck,pChceck,pInde) \
	variable.pBmpChecked = pChceck;\
	variable.pBmpUnchecked = pUncheck;\
	variable.pBmpIndeterminate = pInde

		LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[0],
			pNormalImg, pNormalCheckedImg, 
			pMormalIndeterminateImg );
		LOAD_BUTTON_STATE_BOX_BMP(m_pBmpState[1],
			pHoverImg, pHoverCheckedImg,
			pHoverIndeterminateImg );
		LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[2],
			pPressedImg, pPressedCheckedImg,
			pPressedIndeterminateImg );
		LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[3],
			pFocusedImg, pFocusedCheckedImg,
			pFocusedIndeterminateImg );
		LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[4],
			pDisabledImg, pDisabledCheckedImg,
			pDisabledIndeterminateImg );
#undef LOAD_BUTTON_STATE_BOX_BMP


	}
	bool CCheckBoxCtrlSkin::OnHandleStyleType( UINT nStype, UINT nExStyle )
	{
		switch (nStype & SS_TYPEMASK)
		{
		case BS_OWNERDRAW:
			return false;
		case BS_CHECKBOX:			
		case BS_AUTOCHECKBOX:		
		case BS_3STATE:				
		case BS_AUTO3STATE:			
			return  ( 0 == (nStype & BS_PUSHLIKE) );
			break;
		default:	
			break;
		}
		return false;
	}

	void CCheckBoxCtrlSkin::OnDrawButton(CDC *pDC)
	{
		if( IsNull() || NULL == pDC )
		{
			return;
		}
		/* 窗口尺寸 */
		CRect rtWindow;
		GetWindowRect( GetCurHwnd( ), &rtWindow);
		rtWindow.OffsetRect(-rtWindow.left,-rtWindow.top);

		CDC dcMem;
		dcMem.CreateCompatibleDC( pDC );
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap( pDC, 
			rtWindow.Width(), rtWindow.Height() );
		CBitmap* pOldBitmap = dcMem.SelectObject( &bmpMem );
		dcMem.BitBlt( 0,0, rtWindow.Width(),rtWindow.Height(), pDC, 0,0 ,SRCCOPY );
		/* 计算图片的尺寸，作为后续绘制的依据。 
		   保证资源配置时，同一类贴图的尺寸相同。 */
		int width = m_pBmpState[CBS_Normal].pBmpUnchecked ->GetWidth();
		int height = m_pBmpState[CBS_Normal].pBmpUnchecked ->GetHeight();
		/* 宽度 */
		if( width > rtWindow.Width() )
		{
			height = rtWindow.Width() * height / width;
			width = rtWindow.Width();
		}
		/* 高度 */
		if( height > rtWindow.Height() )
		{
			width = rtWindow.Height() * width / height;
			height = rtWindow.Height();
		}

		CRect rtRadio,rtText;
		/* 计算radio的位置 */
		rtRadio.right = rtWindow.right;
		rtRadio.left = rtRadio.right - width;
		rtRadio.top = (rtWindow.Height() - height)/2;
		rtRadio.bottom = rtRadio.top + height;
		/* 计算文本的位置 */
		rtText = rtWindow;
		rtText.right = rtRadio.left-2;
		
		/* 绘制背景 */
		Util::DrawImage( dcMem.GetSafeHdc(), m_pBmpBk, rtWindow );

		if ( i2b(GetCurParam( ) ->m_nButtonState & 
			CButtonCtrlStatus::BUTTON_DISABLED ) )
		{	
			/* 禁用状态 */

			/* 禁用状态下的选择绘制 */

			if ( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_CHECKED) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio,
					m_pBmpState[CBS_Disabled].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Disabled].pBmpIndeterminate );
			}
			else
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Disabled].pBmpUnchecked );
			}
		}
		else if ( i2b(GetCurParam( ) ->m_nButtonState & 
			CButtonCtrlStatus::BUTTON_PRESSED) )
		{
			/* 按下状态 */

			/* 按下状态的选择绘制 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_CHECKED) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio,
					m_pBmpState[CBS_Pressed].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Pressed].pBmpIndeterminate );
			}
			else
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Pressed].pBmpUnchecked );
			}
		}
		else if (i2b(GetCurParam( ) ->m_nButtonState & 
			CButtonCtrlStatus::BUTTON_HOVER) )
		{
			/* 鼠标经过 */

			/* 鼠标经过时的选择绘制 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_CHECKED) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio,
					m_pBmpState[CBS_Hover].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Hover].pBmpIndeterminate );
			}
			else
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Hover].pBmpUnchecked );
			}
		}
		else if (i2b(GetCurParam( ) ->m_nButtonState & 
			CButtonCtrlStatus::BUTTON_FOCUS) )
		{
			/* 获得焦点状态 */

			/* 有焦点下的各种状态绘制 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_CHECKED) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio,
					m_pBmpState[CBS_Focused].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Focused].pBmpIndeterminate );
			}
			else
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Focused].pBmpUnchecked );
			}
		}
		else
		{
			/* 无操作状态 */

			/* 绘制在无操作状态下的各种状态背景 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_CHECKED) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio,
					m_pBmpState[CBS_Normal].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				CButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Normal].pBmpIndeterminate );
			}
			else
			{
				Util::DrawImage( dcMem.GetSafeHdc(), rtRadio, 
					m_pBmpState[CBS_Normal].pBmpUnchecked );
			}
		}
		/* 绘制文本 */
		DrawText( &dcMem,rtText );
		pDC ->BitBlt( rtWindow.left, rtWindow.top,
			rtWindow.Width(),rtWindow.Height(),
			&dcMem, 0,0, SRCCOPY );
		dcMem.SelectObject( pOldBitmap );
	}
}

