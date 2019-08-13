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
		/* ���ڳߴ� */
		CRect rtWindow;
		GetWindowRect( GetCurHwnd( ), &rtWindow);
		rtWindow.OffsetRect(-rtWindow.left,-rtWindow.top);

		CDC dcMem;
		dcMem.CreateCompatibleDC( pDC );
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap( pDC, 
			rtWindow.Width(), rtWindow.Height() );
		dcMem.SelectObject( &bmpMem );

		/* ����ͼƬ�ĳߴ磬��Ϊ�������Ƶ����ݡ� 
		   ��֤��Դ����ʱ��ͬһ����ͼ�ĳߴ���ͬ�� */
		const CSize& bmpSize = GetBMPSize( 
			*m_pBmpState[CBS_Normal].pBmpUnchecked );
		int width = bmpSize.cx;
		int height = bmpSize.cy;
		/* ��� */
		if( width > rtWindow.Width() )
		{
			height = rtWindow.Width() * height / width;
			width = rtWindow.Width();
		}
		/* �߶� */
		if( height > rtWindow.Height() )
		{
			width = rtWindow.Height() * width / height;
			height = rtWindow.Height();
		}

		CRect rtRadio,rtText;
		/* ����radio��λ�� */
		rtRadio.left = rtWindow.left;
		rtRadio.right = rtRadio.left + width;
		rtRadio.top = (rtWindow.Height() - height)/2;
		rtRadio.bottom = rtRadio.top + height;
		/* �����ı���λ�� */
		rtText = rtWindow;
		rtText.left = rtRadio.right+2;
		
		/* ���Ʊ��� */
		DrawBmp( &dcMem, rtWindow, m_pBmpBk );

		if ( i2b(GetCurParam( ) ->m_nButtonState & 
			sButtonCtrlStatus::BUTTON_DISABLED ) )
		{	
			/* ����״̬ */

			/* ����״̬�µ�ѡ����� */

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
			/* ����״̬ */

			/* ����״̬��ѡ����� */
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
			/* ��꾭�� */

			/* ��꾭��ʱ��ѡ����� */
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
			/* ��ý���״̬ */

			/* �н����µĸ���״̬���� */
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
			/* �޲���״̬ */

			/* �������޲���״̬�µĸ���״̬���� */
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
		/* �����ı� */
		DrawText( &dcMem,rtText );
		pDC ->BitBlt( rtWindow.left, rtWindow.top,
			rtWindow.Width(),rtWindow.Height(),
			&dcMem, 0,0, SRCCOPY );
	}
}

