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
			CBitmapRefPtr pBitmap = ImagePool( ).CreateBitmap(
				TEXT("ui\\skin\\CheckBox.bmp") );
			int nXOffset = 0;
			int nYOffset = 0;
			int nSize = 48;
			InitBmp( 
				Util::CreateSubBitmap( pBitmap, 
				nXOffset, nYOffset+3*nSize,nSize,nSize), //bk
				Util::CreateSubBitmap( pBitmap, 
				nXOffset, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset, nYOffset,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset, nYOffset+nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+nSize, nYOffset,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+nSize, nYOffset+nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+2*nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+2*nSize, nYOffset,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+2*nSize, nYOffset+nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+3*nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+3*nSize, nYOffset,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+3*nSize, nYOffset+nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+4*nSize, nYOffset+2*nSize,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+4*nSize, nYOffset,nSize,nSize),
				Util::CreateSubBitmap( pBitmap, 
				nXOffset+4*nSize, nYOffset+nSize,nSize,nSize) );
			return;
		}
#ifdef USING_CONFIG_FILE
		InitBmp(
			pConfig ->GetBitmap(TEXT("check/background") ),
			pConfig ->GetBitmap(TEXT("check/button/unchecked/normal") ),
			pConfig ->GetBitmap(TEXT("check/button/checked/normal") ),
			pConfig ->GetBitmap(TEXT("check/button/indetermined/normal") ),
			pConfig ->GetBitmap(TEXT("check/button/unchecked/hover") ),
			pConfig ->GetBitmap(TEXT("check/button/checked/hover") ),
			pConfig ->GetBitmap(TEXT("check/button/indetermined/hover") ),
			pConfig ->GetBitmap(TEXT("check/button/unchecked/pressed") ),
			pConfig ->GetBitmap(TEXT("check/button/checked/pressed") ),
			pConfig ->GetBitmap(TEXT("check/button/indetermined/pressed") ),
			pConfig ->GetBitmap(TEXT("check/button/unchecked/focused") ),
			pConfig ->GetBitmap(TEXT("check/button/checked/focused") ),
			pConfig ->GetBitmap(TEXT("check/button/indetermined/focused") ),
			pConfig ->GetBitmap(TEXT("check/button/unchecked/disabled") ),
			pConfig ->GetBitmap(TEXT("check/button/checked/disabled") ),
			pConfig ->GetBitmap(TEXT("check/button/indetermined/disabled") ) );
#endif
	}

	CCheckBoxCtrlSkin::~CCheckBoxCtrlSkin( )
	{

	}

	void CCheckBoxCtrlSkin::InitBmp(
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
		const CBitmapRefPtr& pDisabledIndeterminateImg   )
	{
		m_pBmpBk = pBkImg;
#define LOAD_BUTTON_STATE_BOX_BMP(variable,pChceck,pUncheck,pInde) \
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
		dcMem.SelectObject( &bmpMem );

		/* 计算图片的尺寸，作为后续绘制的依据。 
		   保证资源配置时，同一类贴图的尺寸相同。 */
		const CSize& bmpSize = GetBMPSize( 
			*m_pBmpState[CBS_Normal].pBmpUnchecked );
		int width = bmpSize.cx;
		int height = bmpSize.cy;
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
		rtRadio.left = rtWindow.left;
		rtRadio.right = rtRadio.left + width;
		rtRadio.top = (rtWindow.Height() - height)/2;
		rtRadio.bottom = rtRadio.top + height;
		/* 计算文本的位置 */
		rtText = rtWindow;
		rtText.left = rtRadio.right+2;
		
		/* 绘制背景 */
		DrawBmp( &dcMem, rtWindow, m_pBmpBk );

		if ( i2b(GetCurParam( ) ->m_nButtonState & 
			sButtonCtrlStatus::BUTTON_DISABLED ) )
		{	
			/* 禁用状态 */

			/* 禁用状态下的选择绘制 */

			if ( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_CHECKED) )
			{
				DrawBmp( &dcMem, rtRadio,
					m_pBmpState[CBS_Disabled].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Disabled].pBmpIndeterminate );
			}
			else
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Disabled].pBmpUnchecked );
			}
		}
		else if ( i2b(GetCurParam( ) ->m_nButtonState & 
			sButtonCtrlStatus::BUTTON_PRESSED) )
		{
			/* 按下状态 */

			/* 按下状态的选择绘制 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_CHECKED) )
			{
				DrawBmp( &dcMem, rtRadio,
					m_pBmpState[CBS_Pressed].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Pressed].pBmpIndeterminate );
			}
			else
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Pressed].pBmpUnchecked );
			}
		}
		else if (i2b(GetCurParam( ) ->m_nButtonState & 
			sButtonCtrlStatus::BUTTON_HOVER) )
		{
			/* 鼠标经过 */

			/* 鼠标经过时的选择绘制 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_CHECKED) )
			{
				DrawBmp( &dcMem, rtRadio,
					m_pBmpState[CBS_Hover].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Hover].pBmpIndeterminate );
			}
			else
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Hover].pBmpUnchecked );
			}
		}
		else if (i2b(GetCurParam( ) ->m_nButtonState & 
			sButtonCtrlStatus::BUTTON_FOCUS) )
		{
			/* 获得焦点状态 */

			/* 有焦点下的各种状态绘制 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_CHECKED) )
			{
				DrawBmp( &dcMem, rtRadio,
					m_pBmpState[CBS_Focused].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Focused].pBmpIndeterminate );
			}
			else
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Focused].pBmpUnchecked );
			}
		}
		else
		{
			/* 无操作状态 */

			/* 绘制在无操作状态下的各种状态背景 */
			if ( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_CHECKED) )
			{
				DrawBmp( &dcMem, rtRadio,
					m_pBmpState[CBS_Normal].pBmpChecked );
			}
			else if( i2b(GetCurParam( ) ->m_nButtonState &
				sButtonCtrlStatus::BUTTON_INDETERMINATE ) )
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Normal].pBmpIndeterminate );
			}
			else
			{
				DrawBmp( &dcMem, rtRadio, 
					m_pBmpState[CBS_Normal].pBmpUnchecked );
			}
		}
		/* 绘制文本 */
		DrawText( &dcMem,rtText );
		pDC ->BitBlt( rtWindow.left, rtWindow.top,
			rtWindow.Width(),rtWindow.Height(),
			&dcMem, 0,0, SRCCOPY );
	}
}

