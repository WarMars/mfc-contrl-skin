#include "stdafx.h"
#include "SysHeaderSkin.h"
#include "utils.hpp"
#include "ImageManager.h"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif //USING_CONFIG_FILE

namespace GlobalSkin
{

CSysHeaderSkin::CSysHeaderSkin( )
{

}

void CSysHeaderSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
    if( NULL == pConfig )
#endif
    {
        CBitmapRefPtr pBitmap = ImagePool( ).CreateBitmap(
                    TEXT("ui\\skin\\Header.bmp") );
        int nXOffset = 0;
        int nYOffset = 0;
        int nSize = 0;
        m_pBmpBk = Util::CreateSubBitmap(pBitmap,
                                         nXOffset, nYOffset + nSize, nSize, nSize );
        m_pBmpItem[CSysHeaderParameter::HIS_Normal]=
                Util::CreateSubBitmap(pBitmap,
                                      nXOffset, nYOffset, nSize, nSize );
        m_pBmpItem[CSysHeaderParameter::HIS_Hover] =
                Util::CreateSubBitmap(pBitmap,
                                      nXOffset + nSize, nYOffset, nSize, nSize );
        m_pBmpItem[CSysHeaderParameter::HIS_Press] =
                Util::CreateSubBitmap(pBitmap,
                                      nXOffset + nSize*2, nYOffset, nSize, nSize );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBmpBk = pConfig ->GetBitmap(TEXT("header/background") );
	
	m_pBmpItem[CSysHeaderParameter::HIS_Normal]=
		 pConfig ->GetBitmap(TEXT("header/item/background/normal") );
	
	m_pBmpItem[CSysHeaderParameter::HIS_Hover] =
		 pConfig ->GetBitmap(TEXT("header/item/background/hover") );

	m_pBmpItem[CSysHeaderParameter::HIS_Press] =
		 pConfig ->GetBitmap(TEXT("header/item/background/pressed") );
#endif

}

CSysHeaderSkin::~CSysHeaderSkin( )
{

}
/**
         * @brief ��ȡ��ǰ�Ĵ�������
         */
LPCTSTR CSysHeaderSkin::GetHwndClassName( )
{
    return TEXT("SysHeader32");
}

/**
         * @brief �ӹܿؼ�Ƥ��֮ǰ
         */
CSysHeaderSkin::CParamReference*
CSysHeaderSkin::OnPreTakeOverSkin( HWND hWnd )
{
    CParamReference* pParam = new CParamReference;

    /* ��ʼ��״̬ */
    pParam ->m_nHotItem = -1;
    pParam ->m_nPressedItem = -1;
    return pParam;
}

LRESULT CSysHeaderSkin::OnWndProc(
        UINT nMsg, WPARAM wParam, LPARAM lParam )
{
    switch( nMsg )
    {
    case WM_PAINT:
        OnPaint();
        return 0;
        break;
    case WM_ERASEBKGND:
        return (LRESULT)OnEraseBkgnd( (HDC)wParam );
        break;
    case WM_MOUSEMOVE:
        OnMouseMove(UINT(wParam),
                    CPoint(
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam) ) );
        return 0;
        break;
    case WM_LBUTTONDOWN:
        OnLButtonDown(UINT(wParam),
                      CPoint(
                          GET_X_LPARAM(lParam),
                          GET_Y_LPARAM(lParam) ) );
        return 0;
        break;
    case WM_LBUTTONUP:
        OnLButtonUp(UINT(wParam),
                    CPoint(
                        GET_X_LPARAM(lParam),
                        GET_Y_LPARAM(lParam) ) );
        return 0;
        break;
    case WM_MOUSELEAVE:
        OnMouseLeave();
        return 0;
        break;
    default:
        break;
    }
    return OnAutoDefaultWndProc();
}

void CSysHeaderSkin::OnPaint()
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint( GetCurHwnd( ), &ps );

    /* ���� */
    DrawHeader( hdc );
    EndPaint( GetCurHwnd( ), &ps );
}

BOOL CSysHeaderSkin::OnEraseBkgnd( HDC hdc )
{
    /* �������� */
    return TRUE;
}

void CSysHeaderSkin::OnMouseMove(UINT nFlags, const CPoint& point)
{
    OnAutoDefaultWndProc( );
    if( IsNull() )
    {
        return;
    }

    int	nHotItem = GetCurParam( ) ->m_nHotItem;
    int nPressedItem = GetCurParam( ) ->m_nPressedItem;

    /* ������� */
    if( i2b(nFlags & MK_LBUTTON) )
    {
        /* ���¼��仯 */
        GetCurParam( ) ->m_nPressedItem = HitTest(point);
        GetCurParam( ) ->m_nHotItem = -1;
    }
    else
    {
        /* �ȵ�仯 */
        GetCurParam( ) ->m_nHotItem = HitTest(point);
        GetCurParam( ) ->m_nPressedItem = -1;
    }


    /* ������Ϣ׷�� */
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = GetCurHwnd( );
    TrackMouseEvent(&tme);

    if( nPressedItem != GetCurParam( ) ->m_nPressedItem ||
            nHotItem != GetCurParam( ) ->m_nHotItem )
    {
        Redraw( );
    }
}

void CSysHeaderSkin::OnLButtonDown(UINT nFlags, const CPoint& point)
{
    OnAutoDefaultWndProc( );
    if( IsNull() )
    {
        return;
    }

    int nRes = HitTest(point);
    bool bRedraw = false;
    if( nRes != GetCurParam( ) ->m_nPressedItem )
    {
        /* ��������仯 */
        GetCurParam( ) ->m_nPressedItem = nRes;
        bRedraw = true;
    }
    if( -1 != GetCurParam( ) ->m_nHotItem )
    {
        /* �ȵ㷢���仯 */
        GetCurParam( ) ->m_nHotItem = -1;
        bRedraw = true;
    }

    /* �ػ� */
    if( bRedraw )
    {
        Redraw( );
    }
}

void CSysHeaderSkin::OnLButtonUp(UINT nFlags, const CPoint& point)
{
    OnAutoDefaultWndProc( );
    bool bRedraw = false;
    int nRes = HitTest(point);

    /* �ȵ��� */
    if( nRes != GetCurParam( ) ->m_nHotItem )
    {
        GetCurParam( ) ->m_nHotItem = nRes;
        bRedraw = true;
    }

    /* ������ */
    if( -1 != GetCurParam( ) ->m_nPressedItem )
    {
        GetCurParam( ) ->m_nPressedItem = -1;
        bRedraw = true;
    }

    /* �ػ� */
    if( bRedraw )
    {
        Redraw( );
    }

}

void CSysHeaderSkin::OnMouseLeave( )
{
    bool bRedraw = false;

    /* ״̬��λ */
    if( -1 != GetCurParam( ) ->m_nHotItem )
    {
        GetCurParam( ) ->m_nHotItem = -1;
        bRedraw = true;
    }
    if( -1 != GetCurParam( ) ->m_nPressedItem )
    {
        GetCurParam( ) ->m_nPressedItem = -1;
        bRedraw = true;
    }

    /* �ػ� */
    if( bRedraw )
    {
        Redraw( );
    }
}

int CSysHeaderSkin::HitTest( const CPoint& point)
{
    /* ��ȡ������ */
    LRESULT lCount = SendMessage(GetCurHwnd( ), HDM_GETITEMCOUNT, 0, 0L);
    CRect rectItem;
    for(LRESULT i = 0 ; i < lCount ; ++i )
    {

        /* ��ȡ��ǰ����� */
        SendMessage(GetCurHwnd( ), HDM_GETITEMRECT, i, (LPARAM)&rectItem );
        if(TRUE== rectItem.PtInRect(point))
        {
            //λ�ھ�����
            return (int)i;
        }
    }

    /* �����κ������� */
    return -1;
}

void CSysHeaderSkin::DrawHeader(HDC hdc )
{
    if( IsNull() )
    {
        return;
    }
    CRect rectClient;
    GetClientRect( GetCurHwnd( ), &rectClient);

    /* �������屳�� */
    DrawBmp( hdc,rectClient, m_pBmpBk );

    /* ��ȡ�������� */
    LRESULT lCount = SendMessage(GetCurHwnd( ), HDM_GETITEMCOUNT, 0, 0L);
    CRect rectItem;
    for( LRESULT i = 0 ; i < lCount ; ++i )
    {
        /* ��ȡ����λ�� */
        ::SendMessage(GetCurHwnd( ), HDM_GETITEMRECT, i, (LPARAM)&rectItem );

        if( GetCurParam( ) ->m_nPressedItem == i )
        {
            /* ��ǰ���µ� */
            DrawItemEntry(hdc,i,rectItem,
                          CSysHeaderParameter::HIS_Press );
        }
        else if( GetCurParam( ) ->m_nHotItem == i )
        {
            /* ������ */
            DrawItemEntry(hdc,i,rectItem,
                          CSysHeaderParameter::HIS_Hover );
        }
        else
        {
            /* һ���� */
            DrawItemEntry(hdc,i,rectItem,
                          CSysHeaderParameter::HIS_Normal );
        }
    }
}

void CSysHeaderSkin::DrawItemEntry(HDC hdc, LRESULT nIndex,
                                   const CRect& rectItem,  CSysHeaderParameter::HeaderItemState state )
{
    if( state >= CSysHeaderParameter::HIS_Normal &&
            state < CSysHeaderParameter::HIS_State )
    {

        /* ��������ı��� */
        DrawBmp( hdc, rectItem, m_pBmpItem[state] );
    }
    else
    {
        ASSERT(state >= CSysHeaderParameter::HIS_Normal &&
               state < CSysHeaderParameter::HIS_State );
    }

    /* ��ȡ�ı����� */
    TCHAR szBuf[256] = {0};
    HD_ITEM hItem;
    hItem.mask = (HDI_WIDTH | HDI_TEXT | HDI_FORMAT |
                  HDI_LPARAM | HDI_BITMAP | HDI_IMAGE | HDI_ORDER );
    hItem.pszText = szBuf;
    hItem.cchTextMax = sizeof(szBuf) / sizeof(TCHAR );
    SendMessage(GetCurHwnd( ), HDM_GETITEM, nIndex, (LPARAM)&hItem );

    //HIMAGELIST hImgList = (HIMAGELIST)SendMessage(m_hWnd,
    //	HDM_GETIMAGELIST, HDSIL_NORMAL, 0L);

    UINT rw, rh, *x = NULL, *w = NULL;
    UINT cw, tw, iw, bw;

    cw = tw = iw = bw = 0;
    rw = rectItem.Width();
    rh = rectItem.Height();


    /* �������ֶ��䷽ʽ */
    if ( i2b( hItem.fmt & HDF_STRING ) )
    {
        RECT textRect;

        SetRectEmpty(&textRect);
        DrawText ( hdc, szBuf, -1,
                   &textRect, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_CALCRECT );
        cw = textRect.right - textRect.left +
                2 * 3*GetSystemMetrics(SM_CXEDGE);
    }
    UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS ;

    CRect rtText = rectItem;
    if( i2b( (hItem.fmt & HDF_RIGHT) == HDF_RIGHT) )
    {
        rtText.right -= 6;
        uFormat |= DT_RIGHT;
    }
    else if( i2b( (hItem.fmt & HDF_CENTER) == HDF_CENTER) )
    {
        uFormat |= DT_CENTER;
    }
    else
    {
        rtText.left += 6;
        uFormat |= DT_LEFT;
    }

    int nOldMode = SetBkMode(hdc, TRANSPARENT);

    /* �����ı� */
    DrawText(hdc, szBuf, -1, &rtText, uFormat);
    SetBkMode( hdc, nOldMode );

}

void CSysHeaderSkin::Redraw( )
{
    if( IsNull() )
    {
        return;
    }
    HDC hdc = GetWindowDC( GetCurHwnd( ) );
    CRect rectClient;
    GetClientRect( GetCurHwnd( ), &rectClient );

    /* ���� */
    DrawHeader( hdc );

    ReleaseDC( GetCurHwnd( ), hdc );
}
}


