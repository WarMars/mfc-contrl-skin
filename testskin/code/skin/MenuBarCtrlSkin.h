#pragma once

#include "CtrlSkinPackage.hpp"
#include <vector>
#include "gdiobj_ptr.hpp"

/** 
 * �˵����ؼ�
 */
namespace GlobalSkin
{
namespace CPE
{

/** 
 * @brief �˵���״̬
 */
enum MenuItemState
{
    MIS_Hot = 0x01,		/* ���� */
    MIS_Pressed = 0x02, /* ���� */
    MIS_Horz = 0x04,	/* ˮƽ */
    MIS_Hidden = 0x08,	/* ���� */
    MIS_Wrap = 0x10,	/* ��չ�� */
    MIS_Inactive = 0x20 /* �޷����� */
};

/** 
 * @brief �˵����ı�״̬
 */
enum MenuItemTextState
{
    MITS_Normal = 0, /* ������ɫ */
    MITS_Gray,		 /* ���� */
    MITS_Pressed,	 /* ���� */
    MITS_Active,	 /* � */
    MITS_Size
};

/** 
 * @brief �˵����ͼ
 */
enum MenuItemImage
{
    MII_Activate = 0, /* ���� */
    MII_Pressed,	  /* ���� */
    MII_Size
};

/** 
 * @brief �˵���״̬׷��
 */
enum MenuBarTrackState 
{
    MBTS_None = 0, /* �޲��� */
    MBTS_Button,   /* ���Altʱ�Ĳ˵� */
    MBTS_Popup,    /* ���� */
    MBTS_Size
};
}
namespace DynamicParam
{
/**
 * @brief The CMenuItemSkinParameter class
 */
class CMenuItemSkinParameter
{
public:
    /**
     * @brief SetBkImage ���ñ���ͼ
     * @param pBmp
     */
    void SetBkImage( const CBitmapRefPtr& pBmp );
    CBitmapRefPtr GetBkImage( ) const;

    /**
     * @brief SetImage ����״̬ͼ
     * @param imgType
     * @param pBmp
     */
    void SetImage( CPE::MenuItemImage imgType,
                   const CBitmapRefPtr& pBmp );
    CBitmapRefPtr GetImage( CPE::MenuItemImage imgType ) const;

    /**
     * @brief SetTextStateColor �����ı�״̬��ɫ
     * @param textState
     * @param clrColor
     */
    void SetTextStateColor( CPE::MenuItemTextState textState,
                            COLORREF clrColor );
    COLORREF GetTextStateColor( CPE::MenuItemTextState textState );
private:
    CBitmapRefPtr						m_pBmpBk;
    CBitmapRefPtr						m_pBmpImg[CPE::MII_Size];
    COLORREF							m_clrTextState[CPE::MITS_Size];
};
DECLARE_REF_PTR_NC( CMenuItemSkinParameter );

/**
 * @brief The CMenuItemParameter class
 */
class CMenuItemParameter
{
    enum
    {
        CX_TEXT_MARGIN = 5
    };
    /**
     * @brief GetInvalidMenuId     ��ȡ ��Ч��  �˵�id
     * @return
     */
    inline UINT GetInvalidMenuId( ) const{ return (UINT)-1; }

    /**
     * @brief GetTextMarginY
     * @return
     */
    LONG GetTextMarginY( ) const ;

    /**
     * @brief GetMenuFontHeight
     * @return
     */
    LONG GetMenuFontHeight( ) const;
public:

    /**
     * @brief CMenuItemParameter
     */
    CMenuItemParameter();

    /**
     * @brief Init ��ʼ���˵���
     * @param hWnd �˵������Ĵ��ھ��
     * @param hMenu �˵�����
     * @param nIndex �˵�����
     */
    void Init( HWND hWnd, HMENU hMenu, int nIndex );

    /**
     * @brief Update ����
     * @param hdc
     * @param pParam
     */
    void Update( HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

    /**
     * @brief Layout ����
     * @param point �����
     * @param bHorz �Ƿ�Ϊˮƽ
     */
    void Layout( const CPoint& point, bool bHorz );

    /**
     * @brief TrackPopup ׷�ٵ����˵����¼�
     * @param hBar �Ӵ��ھ�������ڲ˵���˵��ͨ��ΪNULL
     * @param hWndSentCmd Ŀ�괰��
     */
    void TrackPopup( HWND hBar, HWND hWndSentCmd);

    /**
     * @brief SetText	���ò˵��ı�
     * @param hWnd	�������ھ��
     * @param lpszText �ı�
     */
    void SetText( HWND hWnd, LPCTSTR lpszText );

    /**
     * @brief GetHorizontalSize ��ȡˮƽ��С
     * @return �����Ϣ
     */
    CSize GetHorizontalSize( ) const;

    /**
     * @brief GetRect ��ȡ�˵���λ�þ���
     * @return λ�þ���
     */
    const CRect& GetRect( ) const;

    /**
     * @brief GetSubMenu ��ȡ�Ӳ˵���
     * @return �˵�����
     */
    HMENU GetSubMenu( ) const;

    /**
     * @brief ModifyState �޸Ĳ˵��ǰ��״̬������
     * @param byRemove ɾ���ķ�����
     * @param byAdd ��ӵķ�����
     * @return
     */
    bool ModifyState(BYTE byRemove, BYTE byAdd);

    /**
     * @brief DrawHot ���Ƶ�ǰ��
     * @param hdc dc
     * @param pParam �˵������
     */
    void DrawHot(
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

    /**
     * @brief DrawPressed ���ư���״̬
     * @param hdc dc
     * @param pParam �˵���µĲ���
     */
    void DrawPressed(
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

    /**
     * @brief DrawNone �����޲�����Ĭ��״̬
     * @param hdc dc
     * @param pParam �˵���Ĳ���
     */
    void DrawNormal( 
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

	COLORREF GetCurTextColor( const CMenuItemSkinParameterRefPtr& pParam  ) const;
    /**
     * @brief DrawHorzText ���ƴ�ֱ������ı�
     * @param hdc dc
     * @param pParam �˵������
     * @param ptOffset ƫ����
     */
    void DrawHorzText( 
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
        HFONT hFont, const CPoint& ptOffset = CPoint(0, 0) );

    /**
     * @brief DrawVertText ���ƴ�ֱ�ı�
     * @param hdc   dc
     * @param pParam �˵������
     * @param ptOffset �˵����ƫ��
     */
    void DrawVertText( 
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
        HFONT hFont,const CPoint& ptOffset = CPoint(0, 0) );

    /**
     * @brief DrawButton	���Ʋ˵�
     * @param hdc	dc
     * @param wState ״̬����
     * @param pParam �˵������ָ��
     */
    void DrawButton( HDC hdc, WORD wState, const CMenuItemSkinParameterRefPtr& pParam );


    /**
     * @brief InitButtonStringAndSubMenuHandle ��ʼ���˵����ı����Ӳ˵����
     * @param hMenu �˵����
     * @param nIndex �˵��������
     */
    void InitButtonStringAndSubMenuHandle(HMENU hMenu, int nIndex);

    /**
     * @brief InitHorizontalButtonSize ��ʼ��ˮƽ״̬
     * @param hWnd
     */
    void InitHorizontalButtonSize( HWND hWnd );

    /**
     * @brief InitAccessKeyAndVerticalLinePoint ��ʼ���ȼ���������2������
     * @param hWnd
     */
    void InitAccessKeyAndVerticalLinePoint( HWND hWnd );
private:
	///
	/// @brief ״̬����
	///
    BYTE		m_byState;

	///
	/// @brief λ�þ���
	///
    CRect		m_rect;

	///
	/// @brief ˮƽ��С
	///
    CSize		m_szHorz;

	///
	/// @brief �˵���id
	///
    UINT		m_nMenuId;

	///
	/// @brief �Ӳ˵��ľ��
	///
    HMENU		m_hSubMenu;

	///
	/// @brief �˵��ı�
	///
    TCHAR		m_szText[32];

	///
	/// @brief �����ȵ���ʼλ��
	///
    CPoint		m_ptMoveTo;

	///
	/// @brief �����ߵĽ���λ��
	///
    CPoint		m_ptLineTo;

	///
	/// @brief ���յ��ȼ�
	///
    TCHAR		m_chAccessKey;
};
DECLARE_REF_PTR_NC( CMenuItemParameter );

/**
 * @brief The sMenubarCtrlSkinParameter struct
 */
struct CMenubarCtrlSkinParameter:public CCtrlParameter
{
    /**
     * @brief m_pHot ��ǰ�����Ĳ˵���Ĳ���
     */
    CMenuItemParameterRef*	m_pHot;

    /**
     * @brief m_pPressed ���²˵���Ĳ���
     */
    CMenuItemParameterRef*	m_pPressed;

    /**
     * @brief m_nNewPopUp �µĵ����˵�
     */
    int						m_nNewPopUp;

    /**
     * @brief m_hTrackingMenu ���յĲ˵����
     */
    HMENU					m_hTrackingMenu;

    /**
     * @brief m_hMenu �˵����
     */
    HMENU					m_hMenu;

    /**
     * @brief m_vectorItems �˵�������
     */
    std::vector<CMenuItemParameterRefPtr> m_vectorItems;

    /**
     * @brief m_rectPos λ�þ���
     */
    CRect					m_rectPos;

    /**
     * @brief m_bEscapePressed esc���Ƿ���
     */
    bool					m_bEscapePressed;

    /**
     * @brief m_nTrackingState ׷�ٵ�״̬
     */
    CPE::MenuBarTrackState                      m_nTrackingState;

    /**
     * @brief m_bProcessLeftArrow �Ƿ�������ͷ
     */
    bool					m_bProcessLeftArrow;

    /**
     * @brief m_bProcessRightArrow �Ƿ����Ҳ��ͷ
     */
    bool					m_bProcessRightArrow;

    /**
     * @brief m_nPopupTracking ״̬׷��
     */
    int						m_nPopupTracking;

    /**
     * @brief m_ptMouse �������
     */
    CPoint					m_ptMouse;
public:
    ~CMenubarCtrlSkinParameter(){ int i=0; ++i;}
    CMenuItemParameterRef *GetHot() const;
    void SetHot(CMenuItemParameterRef *pHot);
    CMenuItemParameterRef *GetPressed() const;
    void SetPressed(CMenuItemParameterRef *pPressed);
    void SetNewPopUp( int nNew );
    int GetNewPopUp( ) const;
    HMENU GetTrackingMenu( ) const;
    void SetTrackingMenu( HMENU hMenu );
    HMENU GetHMenu( ) const;
    void SetHMenu( HMENU hMenu );
    const CRect& GetPosition( ) const;
    CRect& GetPosition( );
    void SetPosition( const CRect& rectPos );

    void AddMenuItem( const CMenuItemParameterRefPtr& pItem );
    CMenuItemParameterRefPtr GetMenuItem( int i ) const;
    int GetMenuItemCount( ) const;
    void RemoveMenuItem( int i );
    void ClearMenuItem( );

    bool GetEscapedPressed( ) const;
    void SetEscapedPressed( bool bPressed );

    CPE::MenuBarTrackState GetMenuBarTrackingState( ) const;
    void SetMenuBarTrackingState( CPE::MenuBarTrackState mbts );
    bool IsProcessLeftArrow( ) const;
    void SetProcessLeftArrow( bool b );
    bool IsProcessRightArrow( ) const;
    void SetProcessRightArrow( bool b );
    int GetPopupTracking( ) const;
    void SetPopupTracking( int nTracking );
    void SetMousePoint( const CPoint& ptMouse );
    const CPoint& GetMousePoint( ) const;
    CPoint& GetMousePoint( );
};
DECLARE_REF_PTR_NC(CMenubarCtrlSkinParameter);

/**
 * @brief CreateMenuBarSkinParameter �����˵���Ƥ������
 * @param hWnd �˵������
 * @return �˵�����ָ��
 */
CMenubarCtrlSkinParameterRefPtr CreateMenuBarSkinParameter( HWND hWnd );

/**
 * @brief CopyMenu ���Ʋ˵�
 * @param hMenuSrc Դ�˵����
 * @return ���Ƴ����Ĳ˵����
 */
HMENU CopyMenu( HMENU hMenuSrc );


/**
 * @brief The CMenubarCtrlSkin class
 */
class CMenubarCtrlSkin
{
public:

    /**
     * @brief GetInstance ��ȡһ���˵���ʵ��
     * @param hWnd �˵��������ھ��
     * @param pParam �˵�������
     * @param bInit �Ƿ�ʹ������������ʼ���˵���Ƥ��
     * @return �˵���Ƥ����������
     */
//    static CMenubarCtrlSkin& GetInstance(
//            HWND hWnd, CMenubarCtrlSkinParameterRefPtr pParam, bool bInit = true );

	void Init( HWND hWnd, const CMenubarCtrlSkinParameterRefPtr& pParam );
    CMenubarCtrlSkin( );
    ~CMenubarCtrlSkin( );
public:
	void LoadSkin( const CSkinConfig* pConfig );
    /**
     * @brief InitItems ��ʼ���˵���
     * @param rectMargins �˵������
     * @return ��ʼ���ɹ�����true�����򷵻�false
     */
    bool			InitItems( const CRect& rectMargins );

    /**
     * @brief DeleteItems ɾ�����в˵���
     */
    void			DeleteItems();

    /**
     * @brief GetItemCount ��ȡ�˵������Ŀ
     * @return �˵�����Ŀ����
     */
    int				GetItemCount() const ;

    /**
     * @brief IsValidIndex �˵���ı���Ƿ���Ч
     * @param nIndex �˵�����
     * @return ��Ч����true�����򷵻�false
     */
    bool			IsValidIndex(int nIndex) const;

    /**
     * @brief HitTestOnTrack �������
     * @param point ���Ե������
     * @return ����˵��������
     */
    int             HitTestOnTrack( const CPoint& point);

    /**
     * @brief SetMenu	���ò˵�
     * @param hMenu		�˵����
     * @param rectMargins �߿����
     */
    void			SetMenu(HMENU hMenu, const CRect& rectMargins );

    /**
     * @brief GetTrackingState ��ȡ׷��״̬
     * @param nPopup �����˵�׷�ٵı��
     * @return �˵����״̬
     */
    CPE::MenuBarTrackState	GetTrackingState(int& nPopup) ;

    /**
     * @brief CalcMenuBarPos ����˵�����λ��
     * @param rectMargin λ�þ���
     */
    void			CalcMenuBarPos( const CRect& rectMargin );

    /**
     * @brief TrackPopup ׷�ٵ����˵� 
     * @param nButton �˵��ı��
     */
    void			TrackPopup(int nButton);

    /**
     * @brief GetNextOrPrevButton ��ȡ��һ���˵�
     * @param nButton	��ǰ�˵�
     * @param bPrev		�Ƿ���ǰһ���˵�
     * @return ���������Ĳ˵���ť����
     */
    int				GetNextOrPrevButton(int nButton, bool bPrev);

    /**
     * @brief SetTrackingState ����׷�ٵ�״̬
     * @param nState ״̬
     * @param iButton ��ť���
     */
    void			SetTrackingState(CPE::MenuBarTrackState nState, int iButton=-1);

    /**
     * @brief ToggleTrackButtonMode ����׷�ٰ�ť��ģʽ
     */
    void			ToggleTrackButtonMode();

    /**
     * @brief CancelMenuAndTrackNewOne 
	 *					ȡ���¼�׷�ٲ�����ť���õ��µİ�ť��
     * @param iButton �µİ�ť����
     */
    void			CancelMenuAndTrackNewOne(int iButton);

    /**
     * @brief OnMenuInput �˵���Ϣ����
     * @param m	��Ϣ�ṹ
     * @return �ɹ�����true�����򷵻�false
     */
    virtual bool	OnMenuInput( const MSG& m);

    /**
     * @brief GetIndex	��ȡ�ƶ��˵���Ĳ�����Ϣ
     * @param nIndex	�˵��������
     * @return			�˵������Ϣ
     */
    CMenuItemParameterRef*		GetIndex(int nIndex) const;

    /**
     * @brief OnLButtonDown WM_LBUTTONDOWN��Ϣ����
     * @param nFlags
     * @param point
     */
    void            OnLButtonDown(UINT nFlags, const CPoint& point);

    /**
     * @brief OnMouseMove WM_MOUSEMOVE��Ϣ����
     * @param nFlags ��Ϣ��ʶ
     * @param point ��������
     */
    void            OnMouseMove(UINT nFlags, const CPoint& point);

    /**
     * @brief DrawMenuBar ���Ʋ˵���
     */
    void			DrawMenuBar( );

    /**
     * @brief MenuInputFilter �˵���Ϣ����
     * @param code	��Ϣ��
     * @param wp	��Ϣ��WPARAM
     * @param lp	��Ϣ��LPARAM
     * @return	��Ϣ�Ĵ�����
     */
    static LRESULT CALLBACK MenuInputFilter(int code, WPARAM wp, LPARAM lp);

private:
	///
	/// @brief ��ǰ�Ĳ˵����ڵĴ���
	///
    HWND                                        m_hWnd;

	///
	/// @brief �˵�������
	///
    CMenubarCtrlSkinParameterRefPtr            m_pParam;

    // �˵����Ƥ��
    CMenuItemSkinParameterRefPtr				m_pItem;

    // �˵��ı���
    CBitmapRefPtr                               m_pBmpBk;

	/* ���� */
	HFONT										m_hFontItem;
};
}
}
