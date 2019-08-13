#include "stdafx.h"
#include "RadioButtonCtrlSkin.h"
#include "ImageManager.h"
#include "utils.hpp"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
CRadioButtonCtrlSkin::CRadioButtonCtrlSkin( )
{
}

void CRadioButtonCtrlSkin::InitBmp( CBitmapRefPtr pBkImg,
                                    CBitmapRefPtr pNormalImg, CBitmapRefPtr pNormalCheckedImg,
                                    CBitmapRefPtr pHoverImg, CBitmapRefPtr pHoverCheckedImg,
                                    CBitmapRefPtr pPressedImg, CBitmapRefPtr pPressedCheckedImg,
                                    CBitmapRefPtr pFocusedImg, CBitmapRefPtr pFocusedCheckedImg,
                                    CBitmapRefPtr pDisabledImg, CBitmapRefPtr pDisabledCheckedImg )
{
    m_pBmpBk = pBkImg;
#define LOAD_BUTTON_STATE_BOX_BMP(variable,pChecked,pUnchecked) \
    variable.pBmpChecked = pChecked;\
    variable.pBmpUnchecked = pUnchecked

    LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[0],
            pNormalImg, pNormalCheckedImg );
    LOAD_BUTTON_STATE_BOX_BMP(m_pBmpState[1],
            pHoverImg, pHoverCheckedImg );
    LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[2],
            pPressedImg, pPressedCheckedImg );
    LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[3],
            pFocusedImg, pFocusedCheckedImg );
    LOAD_BUTTON_STATE_BOX_BMP( m_pBmpState[4],
            pDisabledImg, pDisabledCheckedImg );
#undef LOAD_BUTTON_STATE_BOX_BMP
}

void CRadioButtonCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
    if( NULL == pConfig )
#endif
    {
        CBitmapRefPtr pBitmap =
                ImagePool( ).CreateBitmap(
                    TEXT("ui\\skin\\RadioButton.bmp") );
        int nXOffset = 0;
        int nYOffset = 0;
        int nSize = 48;
        InitBmp(
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset,nYOffset+nSize*2,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset,nYOffset+nSize,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset,nYOffset,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize,nYOffset+nSize,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize,nYOffset,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize*2,nYOffset+nSize,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize*2,nYOffset,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize*3,nYOffset+nSize,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize*3,nYOffset,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize*4,nYOffset+nSize,nSize,nSize ),
                    Util::CreateSubBitmap(
                        pBitmap,nXOffset+nSize*4,nYOffset,nSize,nSize ) );
        return;
	}
#ifdef USING_CONFIG_FILE
    InitBmp(
                pConfig ->GetBitmap(TEXT("radio/background") ),
                pConfig ->GetBitmap(TEXT("radio/button/unchecked/background/normal") ),
                pConfig ->GetBitmap(TEXT("radio/button/checked/background/normal") ),
                pConfig ->GetBitmap(TEXT("radio/button/unchecked/background/hover") ),
                pConfig ->GetBitmap(TEXT("radio/button/checked/background/hover") ),
                pConfig ->GetBitmap(TEXT("radio/button/unchecked/background/pressed") ),
                pConfig ->GetBitmap(TEXT("radio/button/checked/background/pressed") ),
                pConfig ->GetBitmap(TEXT("radio/button/unchecked/background/focused") ),
                pConfig ->GetBitmap(TEXT("radio/button/checked/background/focused") ),
                pConfig ->GetBitmap(TEXT("radio/button/unchecked/background/disabled") ),
                pConfig ->GetBitmap(TEXT("radio/button/checked/background/disabled") )
                );
#endif
}

CRadioButtonCtrlSkin::~CRadioButtonCtrlSkin( )
{

}

bool CRadioButtonCtrlSkin::OnHandleStyleType( UINT nStype, UINT nExStyle )
{
    switch (nStype & SS_TYPEMASK)
    {
    case BS_OWNERDRAW:
        return false;
    case BS_RADIOBUTTON:
    case BS_AUTORADIOBUTTON:
        return  0== ( nStype & BS_PUSHLIKE);
    default:
        break;
    }
    return false;
}

void CRadioButtonCtrlSkin::OnDrawButton(CDC *pDC)
{
    if( IsNull() || NULL == pDC )
    {
        return;
    }

    CRect rtWindow;
    GetWindowRect( GetCurHwnd( ), &rtWindow);
    rtWindow.OffsetRect(-rtWindow.left,-rtWindow.top);

    CDC dcMem;
    dcMem.CreateCompatibleDC( pDC );
    CBitmap bmpMem;
    bmpMem.CreateCompatibleBitmap( pDC,
                                   rtWindow.Width(), rtWindow.Height() );
    dcMem.SelectObject( &bmpMem );

    /* 获取图片大小 */
    const CSize& bmpSize = GetBMPSize( *m_pBmpState[RS_Normal].pBmpUnchecked );
    int width = bmpSize.cx;
    int height = bmpSize.cy;


    /* 不失真 */
    if( width > rtWindow.Width() )
    {
        height = rtWindow.Width() * height / width;
        width = rtWindow.Width();
    }

    if( height > rtWindow.Height() )
    {
        width = rtWindow.Height() * width / height;
        height = rtWindow.Height();
    }

    CRect rtRadio,rtText;
    rtRadio.left = rtWindow.left;
    rtRadio.right = rtRadio.left + width;
    rtRadio.top = (rtWindow.Height() - height)/2;
    rtRadio.bottom = rtRadio.top + height;

    rtText = rtWindow;
    rtText.left = rtRadio.right+2;

    /* 背景 */
    DrawBmp( &dcMem, rtWindow, m_pBmpBk );

    if ( i2b(GetCurParam( ) ->m_nButtonState &
             sButtonCtrlStatus::BUTTON_DISABLED ) )
    {
        /* 禁用 */
        if ( i2b(GetCurParam( ) ->m_nButtonState &
                 sButtonCtrlStatus::BUTTON_CHECKED) )
        {
            /* 勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Disabled].pBmpChecked );
        }
        else
        {
            /* 未勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Disabled].pBmpUnchecked );
        }
    }
    else if ( i2b(GetCurParam( ) ->m_nButtonState &
                  sButtonCtrlStatus::BUTTON_PRESSED) )
    {
        /* 按下 */
        if (i2b(GetCurParam( ) ->m_nButtonState &
                sButtonCtrlStatus::BUTTON_CHECKED) )
        {
            /* 勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Pressed].pBmpChecked );
        }
        else
        {
            /* 未勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Pressed].pBmpUnchecked );
        }
    }
    else if (i2b(GetCurParam( ) ->m_nButtonState &
                 sButtonCtrlStatus::BUTTON_HOVER) )
    {
        /* 鼠标经过 */
        if (i2b(GetCurParam( ) ->m_nButtonState &
                sButtonCtrlStatus::BUTTON_CHECKED) )
        {
            /* 勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Hover].pBmpChecked );
        }
        else
        {
            /* 未勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Hover].pBmpUnchecked );
        }
    }
    else if (i2b(GetCurParam( ) ->m_nButtonState &
                 sButtonCtrlStatus::BUTTON_FOCUS) )
    {
        /* 有焦点 */
        if (i2b(GetCurParam( ) ->m_nButtonState &
                sButtonCtrlStatus::BUTTON_CHECKED) )
        {
            /* 勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Focused].pBmpChecked );
        }
        else
        {
            /* 未勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Focused].pBmpUnchecked );
        }
    }
    else
    {
        /* 无操作 */
        if (i2b(GetCurParam( ) ->m_nButtonState &
                sButtonCtrlStatus::BUTTON_CHECKED) )
        {
            /* 勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Normal].pBmpChecked );
        }
        else
        {
            /* 未勾选 */
            DrawBmp( &dcMem, rtRadio,
                     m_pBmpState[RS_Normal].pBmpUnchecked );
        }
    }

    /* 绘制文本 */
    DrawText( &dcMem,rtText );
    pDC ->BitBlt( rtWindow.left, rtWindow.top,
                  rtWindow.Width(),rtWindow.Height(),
                  &dcMem, 0,0, SRCCOPY );
}

}
