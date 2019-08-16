#include "stdafx.h"
#include "MenuBarCtrlSkin.h"
#include "utils.hpp"
#include "GlobalSkinUtil.h"
#include "ImageManager.h"
#include "GlobalUiManager.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
namespace DynamicParam
{
namespace FileVariable
{
// ����׷�ٲ˵�����
static HHOOK g_hMenuInputHook = NULL;
}

// ���ñ���ͼ
void CMenuItemSkinParameter::SetBkImage( const CBitmapRefPtr& pBmp )
{
    m_pBmpBk = pBmp;
}

CBitmapRefPtr CMenuItemSkinParameter::GetBkImage( ) const
{
    return m_pBmpBk;
}

void CMenuItemSkinParameter::SetImage( CPE::MenuItemImage imgType,
                                       const CBitmapRefPtr& pBmp )
{
    ASSERT(imgType >= CPE::MII_Activate &&
           imgType < CPE::MII_Size );
    m_pBmpImg[imgType] = pBmp;
}

// ��ȡͼ
CBitmapRefPtr CMenuItemSkinParameter::GetImage(
        CPE::MenuItemImage imgType ) const
{
    ASSERT(imgType >= CPE::MII_Activate &&
           imgType < CPE::MII_Size );
    return m_pBmpImg[imgType];
}

void CMenuItemSkinParameter::SetTextStateColor(
        CPE::MenuItemTextState textState, COLORREF clrColor )
{
    ASSERT(textState >= CPE::MITS_Normal &&
           textState < CPE::MITS_Size );
    m_clrTextState[textState] = clrColor;
}
COLORREF CMenuItemSkinParameter::GetTextStateColor(
        CPE::MenuItemTextState textState )
{

    ASSERT(textState >= CPE::MITS_Normal &&
           textState < CPE::MITS_Size );
    return m_clrTextState[textState];
}

CMenuItemParameter::CMenuItemParameter( )
{
    m_byState = 0;
}

void CMenuItemParameter::Init( HWND hWnd, HMENU hMenu, int nIndex )
{
    //m_byStyle |= (MISTYLE_TRACKABLE | MISTYLE_WRAPPABLE);

    InitButtonStringAndSubMenuHandle(hMenu, nIndex);
    InitHorizontalButtonSize( hWnd );
    InitAccessKeyAndVerticalLinePoint( hWnd );
}

void CMenuItemParameter::Update( 
	HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
	HFONT hHorizontalFont, HFONT hVerticalFont )
{
    if ( i2b(m_byState & CPE::MIS_Hidden) )
    {/* ���� */
        return;
    }

    if ( i2b( m_byState & CPE::MIS_Hot ) )
    {/* ���� */
        DrawHot(hdc,pParam,hHorizontalFont,hVerticalFont );
    }
    else if ( i2b( m_byState & CPE::MIS_Pressed ) )
    {/* ���� */
        DrawPressed( hdc,pParam,hHorizontalFont,hVerticalFont );
    }
    else
    {/* �޲���״̬ */
        DrawNormal( hdc, pParam, hHorizontalFont, hVerticalFont );
    }
}

void CMenuItemParameter::Layout( const CPoint& point, bool bHorz )
{
    if (bHorz)
    {/* ˮƽ */
        m_byState |= CPE::MIS_Horz;
    }
    else
    {
		/* ȥ��ˮƽ��ʶ */
        m_byState &= ~CPE::MIS_Horz;
    }

    if ( i2b( m_byState & CPE::MIS_Hidden ) )
    {/* ���أ�������� */
        m_rect.SetRectEmpty();
        return;
    }

    if (bHorz)
    {/* ˮƽ */
        m_rect = CRect(point, m_szHorz );
    }
    else
    {
        m_rect = CRect(point, CSize(m_szHorz.cy, m_szHorz.cx) );
    }
}
/**
 * @brief CMenuItemParameter::TrackPopup
 * @param hBar  ׷�ٵ��˵��ĳ���Ϣ
 * @param hWndSentCmd
 */
void CMenuItemParameter::TrackPopup( HWND hBar, HWND hWndSentCmd)
{
    if (NULL != m_hSubMenu )
    {
        ASSERT(m_nMenuId != GetInvalidMenuId() );

		/* ģ��ϵͳ��������Ϣ */
        SendMessage(
                    hWndSentCmd,
                    WM_COMMAND,
                    (WPARAM)m_nMenuId,
                    (LPARAM)hBar );
        return;
    }
}

void CMenuItemParameter::SetText( HWND hWnd,LPCTSTR lpszText )
{
    // �����ı�
    _tcscpy_s( m_szText, lpszText );
	/* ���»��Ƶĳߴ���ȼ�����ǰ�ȼ�֧�ֵĲ�̫��) */
    InitHorizontalButtonSize( hWnd );
    InitAccessKeyAndVerticalLinePoint( hWnd );
}

CSize CMenuItemParameter::GetHorizontalSize( ) const
{
    //
    return ( i2b( m_byState & CPE::MIS_Hidden ) )?
                CSize(0, 0) : m_szHorz;
}

const CRect& CMenuItemParameter::GetRect( ) const
{
    return m_rect;
}

HMENU CMenuItemParameter::GetSubMenu( ) const
{
    return m_hSubMenu;
}
bool CMenuItemParameter::ModifyState(BYTE byRemove, BYTE byAdd )
{
    BYTE byOld = m_byState;
    m_byState = ( (m_byState & ~byRemove) | byAdd );
    return byOld != m_byState;
}

void CMenuItemParameter::DrawHot( 
	HDC hdc,  const CMenuItemSkinParameterRefPtr& pParam,
	HFONT hHorizontalFont, HFONT hVerticalFont )
{
	COLORREF colorBack = pParam ->GetTextStateColor(CPE::MITS_Active);

    if ( i2b( m_byState & CPE::MIS_Horz ) )
    {
		/* ˮƽ */
		/* ���Ʊ��� */
        if( !DrawBmp(hdc,m_rect,pParam ->GetImage( CPE::MII_Activate ) ) )
		{
            Util::Draw3D ( hdc, m_rect,colorBack,colorBack);
            Util::FillColor( hdc, m_rect, colorBack );
		}
		/* �����ı� */
		DrawHorzText(hdc, pParam,hVerticalFont, CPoint(-1, 1) );
    }
    else
    {
		/* ��ֱ���� */
        if(!DrawBmp(hdc,m_rect, pParam->GetImage( CPE::MII_Activate ) ) )
		{
			COLORREF colorBack = pParam ->GetTextStateColor(CPE::MITS_Active);
            Util::Draw3D( hdc, m_rect,colorBack,colorBack );
            Util::FillColor( hdc,m_rect, colorBack );
        }
        DrawVertText( hdc, pParam,hHorizontalFont );
    }
}

void CMenuItemParameter::DrawPressed(
	HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
	HFONT hHorizontalFont, HFONT hVerticalFont  )
{
    COLORREF colorBack = pParam ->GetTextStateColor( CPE::MITS_Pressed );
    if ( i2b( m_byState & CPE::MIS_Horz) )
    {
		/* ˮƽ */
        if(!DrawBmp( hdc, m_rect, pParam ->GetImage(
                         CPE::MII_Pressed ) ) )
        {
            Util::Draw3D( hdc, m_rect,colorBack,colorBack);
            Util::FillColor( hdc, m_rect, colorBack );
        }

		DrawHorzText(hdc, pParam,hVerticalFont, CPoint(1, 1) );
    }
    else
    {
		/* ��ֱ */
        if(!DrawBmp(hdc,m_rect, pParam ->GetImage(CPE::MII_Pressed) ) )
        {
            Util::Draw3D( hdc, m_rect,colorBack,colorBack);
            Util::FillColor( hdc, m_rect,colorBack);
        }
        DrawVertText(hdc, pParam,hVerticalFont, CPoint(1, 1) );
    }
}

COLORREF CMenuItemParameter::GetCurTextColor( 
	const CMenuItemSkinParameterRefPtr& pParam  ) const
{
	/* ���µ���ɫ */
	if( i2b( m_byState & CPE::MIS_Pressed ) )
	{
		return pParam ->GetTextStateColor( CPE::MITS_Pressed );
	}
	else if( i2b( m_byState & CPE::MIS_Hot ) )
	{
		/* �н���ʱ����ɫ */
		return pParam ->GetTextStateColor( CPE::MITS_Active );
	}
	// ��ʱ��֧�ֽ���
	return pParam ->GetTextStateColor( CPE::MITS_Normal );
}
void CMenuItemParameter::DrawNormal(
	HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
	HFONT hHorizontalFont, HFONT hVerticalFont )
{
	/* �����ı� */
	if( i2b( m_byState & CPE::MIS_Horz ) )
	{
		DrawHorzText( hdc, pParam, hVerticalFont, CPoint( -1, 1) );
	}
	else
	{
		DrawVertText( hdc, pParam, hVerticalFont,CPoint( 1, 1) );
	}
}

void CMenuItemParameter::DrawHorzText( 
	HDC hdc, const CMenuItemSkinParameterRefPtr& pParam, 
	HFONT hFont,const CPoint& ptOffset )
{
	/* �ı���ɫ */
    COLORREF clr = GetCurTextColor( pParam );

    COLORREF clrOldText = SetTextColor( hdc,clr );

    CRect rcBtn = m_rect;
    rcBtn.right-=1;
	HGDIOBJ hOldFont = SelectObject( hdc, hFont );
	/* �ı�����͸�� */
    int nOldBkMode = SetBkMode( hdc,TRANSPARENT );
    POINT point =
    {
        ptOffset.y-1,
        ptOffset.x+2
    };
	/* �����ı� */
    DrawText(hdc, m_szText, -1, rcBtn + ptOffset,
             DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    SetBkMode( hdc, nOldBkMode );
    SetTextColor( hdc, clrOldText );
	SelectObject( hdc, hOldFont );

}

void CMenuItemParameter::DrawVertText( 
	HDC hdc, const CMenuItemSkinParameterRefPtr& pParam, 
	HFONT hFont,const CPoint& ptOffset )
{
	/* ��ȡ�ı���ɫ */
	COLORREF clr = GetCurTextColor( pParam );
    COLORREF clrOldText = SetTextColor( hdc,clr );

    CRect rcBtn = m_rect;

	/* ��ȡ�ȼ��ַ� */
    TCHAR szTemp[sizeof(m_szText)/sizeof(TCHAR)];
    _tcscpy_s(szTemp, m_szText );
    int nLength = (int)_tcslen( szTemp);
    TCHAR* lpszFound = _tcschr( szTemp, TEXT('&') );
    if( NULL != lpszFound )
    {
        _tcscpy_s( lpszFound,
                   sizeof(m_szText)/sizeof(TCHAR)-(lpszFound-m_szText)/sizeof(TCHAR),
                   lpszFound+1 );
    }

	HGDIOBJ hOldFont = SelectObject( hdc, hFont );
    int nOldGraphicsMode = SetGraphicsMode( hdc, GM_ADVANCED);
    int nOldBkMode = SetBkMode( hdc,TRANSPARENT );

    CRect rcString = CRect(
                CPoint(rcBtn.right - GetTextMarginY(), rcBtn.top + CX_TEXT_MARGIN),
                m_szHorz );
	/* �����ı� */
    DrawText( hdc, szTemp,-1 ,
              rcString + ptOffset,
              DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);

    // ����һ������
    HPEN hPen = CreatePen(PS_SOLID, 0, clr );
    HPEN hOldPen = (HPEN)SelectObject( hdc, hPen );
    rcBtn.left-=2;
    const CPoint& ptMoveTo = rcBtn.TopLeft() + m_ptMoveTo + ptOffset;
    const CPoint& ptLineTo = rcBtn.TopLeft() + m_ptLineTo + ptOffset;
    MoveToEx( hdc, ptMoveTo.x, ptMoveTo.y, NULL );
    LineTo( hdc, ptLineTo.x, ptLineTo.y );
	/* �ָ� */
    SetGraphicsMode( hdc, nOldGraphicsMode );
    SetBkMode( hdc, nOldBkMode );
	SelectObject( hdc, hOldFont );
}

LONG CMenuItemParameter::GetTextMarginY( ) const
{

    NONCLIENTMETRICS info = {0};
    info.cbSize = sizeof(info);
    ::SystemParametersInfo(
                SPI_GETNONCLIENTMETRICS,
                sizeof(info), &info, 0 );
	/* ���㴹ֱ�ı߽�ֵ */
    long lyTextMargin = (
                max(info.iMenuHeight, ::GetSystemMetrics(SM_CYSMICON))
                - abs(info.lfMenuFont.lfHeight) ) / 2;
    return lyTextMargin;
}

LONG CMenuItemParameter::GetMenuFontHeight( ) const
{
    NONCLIENTMETRICS info = {0};
    info.cbSize = sizeof(info);
	/* ��ȡ�˵�����ĸ߶� */
    ::SystemParametersInfo(
                SPI_GETNONCLIENTMETRICS,
                sizeof(info), &info, 0 );
    return abs(info.lfMenuFont.lfHeight);
}

void CMenuItemParameter::DrawButton( HDC hdc, WORD wState,
                                     const CMenuItemSkinParameterRefPtr& pParam  )
{

}

void CMenuItemParameter::InitButtonStringAndSubMenuHandle(HMENU hMenu, int nIndex)
{
    MENUITEMINFO info = {0};
    info.cbSize		= sizeof(MENUITEMINFO);
    info.fMask		= MIIM_ID | MIIM_TYPE;
    info.dwTypeData = m_szText;
    info.cch		= sizeof(m_szText)/sizeof(TCHAR);
	/* ��ȡ�˵���Ϣ */
    ::GetMenuItemInfo(hMenu, nIndex, TRUE, &info);
	/* ��ȡ�Ӳ˵���� */
    m_hSubMenu = ::GetSubMenu(hMenu, nIndex);
	/* ��ȡ�˵���id */
    m_nMenuId = (NULL == m_hSubMenu)?
                GetMenuItemID(hMenu, nIndex):-1;
}
void CMenuItemParameter::InitHorizontalButtonSize( HWND hWnd )
{
	/* ˮƽ�ʹ�ֱ�Ĵ�С */
    m_szHorz.cx = Util::GetFontLength( hWnd, m_szText)
            + CX_TEXT_MARGIN*2 + 8;
    m_szHorz.cy = ( GetMenuFontHeight() +
                    GetTextMarginY() * 2 ) + 1;
}

void CMenuItemParameter::InitAccessKeyAndVerticalLinePoint( HWND hWnd )
{
    int nLength = (int)_tcslen( m_szText );
	/* �ȼ��ַ� */
    LPTSTR lpszFound = _tcschr( m_szText, TEXT('&') );
    if ( NULL == lpszFound ||
         lpszFound == m_szText + nLength )
    {
        m_chAccessKey = TEXT('\0');
        m_ptMoveTo = m_ptLineTo = CPoint(0, 0);
        return;
    }

    m_chAccessKey = lpszFound[1];// -1 + 1 = 0; it's ok
	/* ��ֱ����߽�ֵ */
    LONG lYTextMargin = GetTextMarginY( );
    if (lpszFound == m_szText )
    {
		/* ����ĸ���ȼ� */
        m_ptMoveTo = CPoint( lYTextMargin, CX_TEXT_MARGIN );
        TCHAR chTemp = m_szText[2];
        m_szText[2] = TEXT('\0');
		/* ���ߵĿ����һ���ַ� */
        m_ptLineTo	 = CPoint(lYTextMargin, CX_TEXT_MARGIN +
                                  Util::GetFontLength(hWnd, m_szText ) );
        m_szText[2] = chTemp;
    }
    else
    {
		/* �ȼ����м� */
        TCHAR chTemp = *lpszFound;
        lpszFound[0] = TEXT('\0');
		/* ��ʼ�ַ� */
        m_ptMoveTo = CPoint(lYTextMargin, CX_TEXT_MARGIN +
                            Util::GetFontLength(hWnd, m_szText ) );
        lpszFound[0] = chTemp;
        chTemp = m_szText[2];
        m_szText[2] = TEXT('\0');
		/* ��ֹ�ַ� */
        m_ptLineTo = CPoint(lYTextMargin, CX_TEXT_MARGIN +
                            Util::GetFontLength(hWnd, m_szText) );
        m_szText[2] = chTemp;
    }
}

CMenubarCtrlSkinParameterRefPtr CreateMenuBarSkinParameter( HWND hWnd )
{
    CMenubarCtrlSkinParameterRefPtr pParam = new CMenubarCtrlSkinParameterRef;
    pParam ->SetPressed( NULL );
    pParam ->SetHot( NULL );
    pParam ->SetNewPopUp( -1 );
    pParam ->SetTrackingMenu( NULL );
    pParam ->SetHMenu( NULL );
    pParam ->SetEscapedPressed(false);
    pParam ->SetMenuBarTrackingState(CPE::MBTS_None );
    pParam ->SetProcessLeftArrow( false );
    pParam ->SetProcessRightArrow( false );
    pParam ->SetPopupTracking( -1 );

    return pParam;
}
HMENU CopyMenu( HMENU hMenuSrc )
{
    if(hMenuSrc == NULL)
    {
        return NULL;
    }
	/* ���� */
    HMENU hMenu = ::CreatePopupMenu();
    if(hMenu == NULL)
    {
        return NULL;
    }

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(mii));
    mii.cbSize = sizeof(mii);

    mii.fMask = MIIM_STATE | MIIM_DATA | MIIM_BITMAP;

	/* ��ȡ������Ŀ */
    int nCount = ::GetMenuItemCount(hMenuSrc);


    for(int i = 0; i < nCount; ++i)
    {
        UINT nID = GetMenuItemID(hMenuSrc, i);
        TCHAR *szLabel = NULL;
        int nLen = GetMenuString(hMenuSrc, i, szLabel, 0, MF_BYPOSITION);
        szLabel = new TCHAR[nLen + 1];

        GetMenuString(hMenuSrc, i, szLabel, nLen + 1, MF_BYPOSITION);

        UINT nFlags = (nID == 0) ? MF_SEPARATOR : (nID == (UINT)-1) ? MF_POPUP : MF_STRING;


        if (nFlags == MF_POPUP)
        {
            HMENU hPopup = CopyMenu(GetSubMenu(hMenuSrc, i));
            ASSERT (hPopup);

            nID = (UINT)hPopup;
        }
		/* ����һ���˵��� */
        AppendMenu(hMenu, nFlags, nID, szLabel);

        ::GetMenuItemInfo(hMenuSrc, i, TRUE, &mii);
        ::SetMenuItemInfo(hMenu, i, TRUE, &mii);
        delete []szLabel;
    }

    return hMenu;
}

void CMenubarCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
	m_pItem = new CMenuItemSkinParameterRef;
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRefPtr pBmp = ImagePool( ).CreateBitmap(
			TEXT("ui\\skin\\MenuBar.bmp") );
		// �˵����
		m_pItem->SetBkImage( Util::CreateSubBitmap(
			pBmp,0,0,40,20) );
		// �˵������Ǽ�����ɫ
		m_pItem ->SetImage( CPE::MII_Activate,
			Util::CreateSubBitmap(pBmp,0,20,20,20 ) );
		m_pItem ->SetImage( CPE::MII_Pressed,
			Util::CreateSubBitmap(pBmp,20,20,20,20 ) );
		// �˵����ı���ɫ
		m_pItem ->SetTextStateColor( CPE::MITS_Normal,
			Util::GetBitmapPixelColor( pBmp, 5,50) );
		m_pItem ->SetTextStateColor( CPE::MITS_Gray,
			Util::GetBitmapPixelColor( pBmp, 15,50) );
		m_pItem ->SetTextStateColor( CPE::MITS_Pressed,
			Util::GetBitmapPixelColor( pBmp, 25,50) );
		m_pItem ->SetTextStateColor( CPE::MITS_Active,
			Util::GetBitmapPixelColor( pBmp, 35,50) );
		// �˵��ı���
		m_pBmpBk =
			Util::CreateSubBitmap( pBmp, 0,60,40,20);
		return;
	}

#ifdef USING_CONFIG_FILE
	// �˵����
	m_pItem->SetBkImage(
		pConfig ->GetBitmap( TEXT("menubar/item/background/normal") ) );
	// �˵������Ǽ�����ɫ
	m_pItem ->SetImage( CPE::MII_Activate,
		pConfig ->GetBitmap( TEXT("menubar/item/background/hot") ) );
	m_pItem ->SetImage( CPE::MII_Pressed,
		pConfig ->GetBitmap( TEXT("menubar/item/background/pressed") ) );
	// �˵����ı���ɫ
	m_pItem ->SetTextStateColor( CPE::MITS_Normal,
		pConfig ->GetRGBColor( TEXT("menubar/text/color/normal") ) );
	m_pItem ->SetTextStateColor( CPE::MITS_Gray,
		pConfig ->GetRGBColor( TEXT("menubar/text/color/grey") ) );
	m_pItem ->SetTextStateColor( CPE::MITS_Pressed,
		pConfig ->GetRGBColor( TEXT("menubar/text/color/pressed") ) );
	m_pItem ->SetTextStateColor( CPE::MITS_Active,
		pConfig ->GetRGBColor( TEXT("menubar/text/color/actived") ) );
	// �˵��ı���
	m_pBmpBk = pConfig ->GetBitmap( TEXT("menubar/background") ) ;
#endif

}

void CMenubarCtrlSkin::Init( HWND hWnd, const CMenubarCtrlSkinParameterRefPtr& pParam )
{
	m_hWnd = hWnd;
	m_pParam = pParam;
}
CMenubarCtrlSkin::CMenubarCtrlSkin( )
{
	NONCLIENTMETRICS info = {0}; 
	info.cbSize = sizeof(info);

	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
	m_hFontItem = CreateFontIndirect( &info.lfMenuFont );

}

CMenubarCtrlSkin::~CMenubarCtrlSkin( )
{

}

bool CMenubarCtrlSkin::InitItems( const CRect& rectMargins )
{
    DeleteItems();

    const CRect& rtWindow = Util::CTempAbsoluteWindowRect( m_hWnd);

    CRect			rtMenu;
    CRect& rectPos = m_pParam ->GetPosition();
	/* �˵��Ŀ�� */
    rectPos.SetRect(
                rtWindow.left + rectMargins.left,
                rtWindow.top + rectMargins.top,
                rtWindow.right - rectMargins.right,
                rtWindow.top + rectMargins.top + GetSystemMetrics(SM_CYMENU) );

    CRect rectLastItem (
                rectPos.left + 2,
                rectPos.top + 1,
                rectPos.right - 2,
                rectPos.bottom - 1 );

    HMENU hMenu = m_pParam ->GetHMenu();
    int nMenuCount = GetMenuItemCount( hMenu );
	/* �˵������Ŀ */
    for (int i = 0; i < GetMenuItemCount( hMenu ); ++i)
    {
        CMenuItemParameterRef *pItem = new CMenuItemParameterRef;
        pItem ->Init( m_hWnd, hMenu, i );
		/* ��Ӳ˵�����Ϣ */
        m_pParam->AddMenuItem(pItem);
        pItem->Layout(CPoint(rectLastItem.left ,rectLastItem.top),true);
        CSize size = pItem ->GetHorizontalSize();
        rectLastItem.left = rectLastItem.left + size.cx;
    }
    return true;
}
void CMenubarCtrlSkin::DeleteItems()
{
    m_pParam ->ClearMenuItem();
}
int	 CMenubarCtrlSkin::GetItemCount() const 
{
    return m_pParam ->GetMenuItemCount();
}
bool CMenubarCtrlSkin::IsValidIndex(int nIndex) const
{
    return( nIndex >= 0 && nIndex < m_pParam ->GetMenuItemCount() );
}
int CMenubarCtrlSkin::HitTestOnTrack( const CPoint& point)
{
    int nCount = m_pParam ->GetMenuItemCount( );
	/* �����������в˵����λ����Ϣ */
    for (int i = 0; i < nCount; ++i )
    {
        CMenuItemParameterRef* pItem = m_pParam ->GetMenuItem(i);
        if( TRUE == pItem->GetRect().PtInRect( point ) )
        {
			/* ��������ڵ�ǰ���δ֪������ */
            return i;
        }
    }

    return -1;
}
void CMenubarCtrlSkin::SetMenu(HMENU hMenu, const CRect& rectMargins )
{
	/* ��ʼ�� */
    m_pParam->SetHMenu( hMenu );
    InitItems( rectMargins );
}
CPE::MenuBarTrackState CMenubarCtrlSkin::GetTrackingState(int& nPopup)
{
	/* ����Ĳ˵���ı�� */
    nPopup = m_pParam ->GetPopupTracking();
    return m_pParam ->GetMenuBarTrackingState();
}
void CMenubarCtrlSkin::CalcMenuBarPos( const CRect& rectMargin )
{
    const CRect& rectWindow = Util::CTempAbsoluteWindowRect( m_hWnd );
	/* �˵���λ���ڱ߽�֮�ڣ���ϵͳ����Ĳ˵�֮�� */
    m_pParam ->GetPosition().SetRect(
                rectWindow.left + rectMargin.left,
                rectWindow.top + rectMargin.top,
                rectWindow.right - rectMargin.right,
                rectWindow.top + rectMargin.top + GetSystemMetrics(SM_CYMENU) );
}
void CMenubarCtrlSkin::TrackPopup(int nButton)
{
	/* ������׷�� */
    int nMenuItems = GetMenuItemCount( m_pParam ->GetHMenu() );

    while (nButton >= 0)
    {

        m_pParam ->SetNewPopUp( -1 );
        CMenuItemParameterRef* pMenuItem = GetIndex( nButton );
		/* ���µĲ˵���仯 */
        m_pParam ->SetPressed( pMenuItem );

        // ���²˵���
        DrawMenuBar();

        SetTrackingState(CPE::MBTS_Popup, nButton);
		/* ׷����Ϣ */
        FileVariable::g_hMenuInputHook = SetWindowsHookEx(
			WH_MSGFILTER, MenuInputFilter, NULL, ::GetCurrentThreadId() );
		/* ����׷�ٵİ�ť */
        m_pParam ->SetTrackingMenu( pMenuItem ->GetSubMenu() );
        const CRect& rtWindow = Util::CTempRelativeWindowRect( m_hWnd );
        CRect rc = pMenuItem->GetRect();
        rc.OffsetRect( rtWindow.left,rtWindow.top );
        CPoint pt ;
        pt.x = rc.left;
        pt.y = rc.bottom;
		/* �����Ӳ˵�����Ϣ׷�� */
        BOOL bRet = TrackPopupMenuEx(
                    pMenuItem ->GetSubMenu(),
                    TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
                    pt.x, pt.y, m_hWnd, NULL);
		/* �����ָ� */
        m_pParam ->SetTrackingMenu( NULL );

        // 
        ::UnhookWindowsHookEx( FileVariable::g_hMenuInputHook );

        m_pParam ->SetPressed( NULL );

		/* �ػ�˵���ˢ�� */
        DrawMenuBar();

        SetTrackingState( m_pParam ->GetEscapedPressed() ?
                              CPE::MBTS_Button: CPE::MBTS_None, nButton );

        nButton = m_pParam ->GetNewPopUp();
    }
}
int	 CMenubarCtrlSkin::GetNextOrPrevButton(int nButton, bool bPrev)
{
    if (bPrev)
    {
		/* ǰһ���˵��� */
        --nButton;
        if ( nButton <0 )
        {
            nButton = GetItemCount() - 1;
        }
    }
	else
    {
		/* ��һ���˵��� */
        ++nButton;
        if (nButton >= GetItemCount())
        {
            nButton = 0;
        }
    }
    return nButton;
}

void CMenubarCtrlSkin::SetTrackingState(CPE::MenuBarTrackState nState, int nButton )
{
    if (nState != m_pParam ->GetMenuBarTrackingState() )
    {
		//׷�ٵ�״̬�����˱仯
        if (nState == CPE::MBTS_None )
        {
			/* ״̬ȡ�� */
            nButton = -1;
        }
		/* ���� */
        m_pParam ->SetHot( GetIndex(nButton) );

        if (nState== CPE::MBTS_Popup )
        {
            m_pParam ->SetEscapedPressed( false );
            m_pParam ->SetProcessLeftArrow( true );
            m_pParam ->SetProcessRightArrow( true );
            m_pParam ->SetPopupTracking( nButton );
        }
        m_pParam ->SetMenuBarTrackingState( nState );
    }
}
void CMenubarCtrlSkin::ToggleTrackButtonMode()
{
    CPE::MenuBarTrackState nTrackingState = m_pParam ->GetMenuBarTrackingState();
    if ( nTrackingState == CPE::MBTS_None ||
         nTrackingState == CPE::MBTS_Button)
    {
        SetTrackingState(nTrackingState == CPE::MBTS_None  ?
                             CPE::MBTS_Button : CPE::MBTS_None , 0);
    }
}
void CMenubarCtrlSkin::CancelMenuAndTrackNewOne(int nButton)
{
    if (nButton !=  m_pParam ->GetPopupTracking() )
    {
		//ֹͣ�˵�����Ϣѭ��
        PostMessage(m_hWnd,WM_CANCELMODE,0,0);			
        m_pParam ->SetPopupTracking( nButton );			
    }
}
bool CMenubarCtrlSkin::OnMenuInput( const MSG& m)
{
    ASSERT( m_pParam ->GetMenuBarTrackingState() ==
            CPE::MBTS_Popup );

    int msg = m.message;

    if (msg==WM_KEYDOWN)
    {
        const char chVKCode = (char)m.wParam;
		//�û����¼�������Ҽ�ͷ
        if ((chVKCode == VK_LEFT  && m_pParam ->IsProcessLeftArrow() ) ||
                (chVKCode == VK_RIGHT && m_pParam ->IsProcessRightArrow() ) )
        {
            CancelMenuAndTrackNewOne(
                        GetNextOrPrevButton(
                            m_pParam ->GetPopupTracking(),
                            chVKCode==VK_LEFT ) );
            return true; // ����
        }
        else if (chVKCode == VK_ESCAPE)
        {
			/* ����esc�� */
            m_pParam ->SetEscapedPressed( true );
        }

    }
    else if (msg==WM_MOUSEMOVE || msg==WM_LBUTTONDOWN)
    {
		/* ����ƶ����߰��� */
        CPoint pt = m.lParam;

		/* ��������ڿͻ����е�λ�� */
        const CRect& rtWindow = Util::CTempRelativeWindowRect(m_hWnd);
        pt.Offset(-rtWindow.left,-rtWindow.top);

        if (msg == WM_MOUSEMOVE)
        {
			/* ����һ�����겻ͬ */
            if (pt != m_pParam ->GetMousePoint() )
            {
				/* ������� */
                int nButton = HitTestOnTrack(pt);

                if (IsValidIndex(nButton) && nButton != m_pParam ->GetPopupTracking() )
                {
                    // �ƶ���ǰ������˵�������
                    CancelMenuAndTrackNewOne(nButton);
                }
                m_pParam ->SetMousePoint( pt );
            }

        }
        else if (msg == WM_LBUTTONDOWN)
        {
            if ( HitTestOnTrack(pt) == m_pParam ->GetPopupTracking() )
            {
                // ��������ͬ�������ȡ��
                CancelMenuAndTrackNewOne(-1);
                return true; // ����
            }
        }
    }
    return false; // ������
}
CMenuItemParameterRef*	 CMenubarCtrlSkin::GetIndex(int nIndex) const
{
	/* ���Ϸ�����������NULL */
    return IsValidIndex(nIndex)? m_pParam ->GetMenuItem(nIndex ):NULL;
}
void CMenubarCtrlSkin::OnLButtonDown(UINT nFlags, const CPoint& point)
{
    int nButton = HitTestOnTrack(point);
	/* ����ڲ˵����� */
    if (nButton >= 0 && nButton<GetItemCount())
    {
		/* ���������Ȳ��� */
        TrackPopup( nButton );
    }
}
void CMenubarCtrlSkin::OnMouseMove(UINT nFlags, const CPoint& point)
{
	//�����˵���״̬
    if( m_pParam ->GetMenuBarTrackingState() != CPE::MBTS_Popup )
    {
        int nHot = HitTestOnTrack(point);
		/* ����˲˵��� */
        if(nHot >= 0)
        {
            m_pParam ->SetMenuBarTrackingState( CPE::MBTS_Button );
            if (IsValidIndex(nHot) && point != m_pParam ->GetMousePoint() )
            {
                m_pParam ->SetHot( GetIndex(nHot) );
            }
            else
            {
                m_pParam ->SetHot( NULL );
            }
        }
        else
        {
			/* ����������Ϊ��Ч */
            m_pParam ->SetHot( NULL );
        }
        m_pParam ->SetMousePoint( point ); // ���浱ǰ�ĵ�
        DrawMenuBar();
    }
}
void CMenubarCtrlSkin::DrawMenuBar( )
{
    const CRect& rtWindow = Util::CTempAbsoluteWindowRect(m_hWnd);

    CRect			rtMenu;

    const CRect& rectWindow = Util::CTempAbsoluteWindowRect(m_hWnd);
    CRect rectClient;
    GetClientRect( m_hWnd, &rectClient );

    const CRect& rectPosition = m_pParam ->GetPosition();

    Util::CTempWindowDC wdc(m_hWnd);

    DrawBmp( wdc, rectPosition, m_pBmpBk );

    CRect rcItem(
                rectPosition.left + 2,
                rectPosition.top + 1,
                rectPosition.right - 2,
                rectPosition.bottom - 1 );
    int nItemCount = m_pParam ->GetMenuItemCount();
    CMenuItemParameterRef* pPressed  = m_pParam ->GetPressed();
    CMenuItemParameterRef* pHot = m_pParam ->GetHot();
    for ( int i = 0 ; i < nItemCount; ++i )
    {
        CMenuItemParameterRef* pItem = m_pParam ->GetMenuItem(i);

        if( pItem == pPressed )
        {
            pItem->ModifyState( CPE::MIS_Hot, CPE::MIS_Pressed );
        }
        else if( m_pParam ->GetMenuBarTrackingState() ==
                 CPE::MBTS_Button && pItem == pHot )
        {
            pItem->ModifyState( CPE::MIS_Pressed, CPE::MIS_Hot );
        }
        else
        {
            pItem->ModifyState(CPE::MIS_Pressed|CPE::MIS_Hot, 0);
        }
        pItem->Update(wdc, m_pItem,m_hFontItem,m_hFontItem );

    }
}
LRESULT CALLBACK CMenubarCtrlSkin::MenuInputFilter(int code, WPARAM wp, LPARAM lp)
{
    if( MSGF_MENU == code )
    { // ���ǲ˵���Ϣ
        CallNextHookEx( FileVariable::g_hMenuInputHook, code, wp, lp );
    }
    if( CGlobalUiManager::GetPtr()->GetMenuBarCtrlSkin()->OnMenuInput( *((MSG*)lp) ) )
    { // ����
        return TRUE;
    }
    return CallNextHookEx(FileVariable::g_hMenuInputHook, code, wp, lp);
}


CMenuItemParameterRef *CMenubarCtrlSkinParameter::GetHot() const
{
    return m_pHot;
}

void CMenubarCtrlSkinParameter::SetHot(CMenuItemParameterRef *pHot)
{
    m_pHot = pHot;
}

CMenuItemParameterRef *CMenubarCtrlSkinParameter::GetPressed() const
{
    return m_pPressed;
}

void CMenubarCtrlSkinParameter::SetPressed(CMenuItemParameterRef *pPressed)
{
    m_pPressed = pPressed;
}

void CMenubarCtrlSkinParameter::SetNewPopUp( int nNew )
{
    m_nNewPopUp = nNew;
}

int CMenubarCtrlSkinParameter::GetNewPopUp( ) const
{
    return m_nNewPopUp;
}


HMENU CMenubarCtrlSkinParameter::GetTrackingMenu( ) const
{
    return m_hTrackingMenu;
}

void CMenubarCtrlSkinParameter::SetTrackingMenu( HMENU hMenu )
{
    m_hTrackingMenu = hMenu;
}

HMENU CMenubarCtrlSkinParameter::GetHMenu( ) const
{
    return m_hMenu;
}

void CMenubarCtrlSkinParameter::SetHMenu( HMENU hMenu )
{
    m_hMenu = hMenu;
}

const CRect& CMenubarCtrlSkinParameter::GetPosition( ) const
{
    return m_rectPos;
}

CRect& CMenubarCtrlSkinParameter::GetPosition( )
{
    return m_rectPos;
}

void CMenubarCtrlSkinParameter::SetPosition( const CRect& rectPos )
{
    m_rectPos = rectPos;
}

void CMenubarCtrlSkinParameter::AddMenuItem( const CMenuItemParameterRefPtr& pItem )
{
    m_vectorItems.push_back( pItem );
}
CMenuItemParameterRefPtr CMenubarCtrlSkinParameter::GetMenuItem( int i ) const
{
    std::size_t nIndex = (std::size_t)i;
    ASSERT( nIndex >= 0 && nIndex < m_vectorItems.size() );
    return m_vectorItems[nIndex];
}
void CMenubarCtrlSkinParameter::RemoveMenuItem( int i )
{
    std::size_t nIndex = (std::size_t)i;
    ASSERT( nIndex >= 0 && nIndex < m_vectorItems.size() );
    m_vectorItems.erase( m_vectorItems.begin() + nIndex );
}
void CMenubarCtrlSkinParameter::ClearMenuItem( )
{
    m_vectorItems.clear();
}

int CMenubarCtrlSkinParameter::GetMenuItemCount( ) const
{
    return (int) m_vectorItems.size();
}

bool CMenubarCtrlSkinParameter::GetEscapedPressed( ) const
{
    return m_bEscapePressed;
}

void CMenubarCtrlSkinParameter::SetEscapedPressed( bool bPressed )
{
    m_bEscapePressed = bPressed;
}

CPE::MenuBarTrackState CMenubarCtrlSkinParameter::GetMenuBarTrackingState( ) const
{
    return m_nTrackingState;
}

void CMenubarCtrlSkinParameter::SetMenuBarTrackingState( CPE::MenuBarTrackState mbts )
{
    m_nTrackingState = mbts;
}

bool CMenubarCtrlSkinParameter::IsProcessLeftArrow( ) const
{
    return m_bProcessLeftArrow;
}

void CMenubarCtrlSkinParameter::SetProcessLeftArrow( bool b )
{
    m_bProcessLeftArrow = b;
}

bool CMenubarCtrlSkinParameter::IsProcessRightArrow( ) const
{
    return m_bProcessRightArrow;
}

void CMenubarCtrlSkinParameter::SetProcessRightArrow( bool b )
{
    m_bProcessRightArrow = b;
}

int CMenubarCtrlSkinParameter::GetPopupTracking( ) const
{
    return m_nPopupTracking;
}
void CMenubarCtrlSkinParameter::SetPopupTracking( int nTracking )
{
    m_nPopupTracking = nTracking;
}

void CMenubarCtrlSkinParameter::SetMousePoint( const CPoint& ptMouse )
{
    m_ptMouse = ptMouse;
}

const CPoint& CMenubarCtrlSkinParameter::GetMousePoint( ) const
{
    return m_ptMouse;
}

CPoint& CMenubarCtrlSkinParameter::GetMousePoint( )
{
    return m_ptMouse;
}

}
}
