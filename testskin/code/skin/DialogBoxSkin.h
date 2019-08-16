#pragma  once
#include "CtrlWithScrollBar.h"
#include "MenuBarCtrlSkin.h"

namespace GlobalSkin
{

namespace CPE /*control parameter enumeration */
{

/**
 * @brief The WindowButtonState enum 窗口按钮状态每局
 */
enum WindowButtonState
{
    WBS_Normal = 0, /* 无操作状态 */
    WBS_Hover,		/* 鼠标悬浮 */
    WBS_Pressed,	/* 鼠标按压 */
    WBS_Disabled,   /* 禁用 */
    WBS_Size		/* */
};

/**
 * @brief The WindowButtonType enum 窗口按钮类型
 */
enum WindowHitType
{
    WHT_None = -1,	/* 无 */
    WHT_Close = 0,  /* 关闭按钮 */
    WHT_Help,		/* 帮助按钮 */
    WHT_Max,		/* 最大化按钮 */
    WHT_Min,		/* 最小化按钮 */
    WHT_Restore,	/* 恢复按钮 */
    WHT_SysMenu,	/* 系统菜单 */
    WHT_Size		/* */
};

/**
 * @brief The WindowButton enum   窗口 按钮
 */
enum WindowButton
{
    WB_System = 0,
    WB_Help,
    WB_Min,
    WB_Max,
    WB_Restore,
    WB_Close,
    WB_Size
};

/**
 * @brief The MouseState enum    鼠标状态
 */
enum MouseState
{
    MS_Normal = 0,
    MS_Down,
    MS_Up,
    MS_Size
};

/**
 * @brief The WindowPart enum  窗口区域
 */
enum WindowPart
{
    WP_TopLeft = 0,
    WP_Top,
    WP_TopBorder,
    WP_TopRight,
    WP_Left,
    WP_Right,
    WP_BottomLeft,
    WP_Bottom,
    WP_BottomRight,
    WP_Size
};

enum WindowBackgroundImagePart
{
    WBKIP_Top = 0, /* 窗口背景图的顶部 */
    WBKIP_Bottom,  /* 窗口背景图的地部 */
    WBKIP_Left,	   /* 窗口背景图的左侧 */
    WBKIP_Right,   /* 窗口背景图的右侧 */
    WBKIP_Size	   /* */
};

}


class CWindowButtonParam
{
public:

    void SetPosRect( const CRect& rectPos );
    const CRect& GetPosRect( ) const;
    CRect& GetPosRect( );

    void SetOffsetRect( const CRect& rectOffset );
    const CRect& GetOffsetRect( ) const;
    CRect& GetOffsetRect( );

    void SetAnchorRect( const CRect& rectAnchor );
    const CRect& GetAnchorRect( ) const;
    CRect& GetAnchorRect( );

    void UpdateOffsetByRelativeRect( const CRect& rectRelative );
    CRect GetWindowButtonRect( const CRect& rectWindow ) const;

    CBitmap* GetStateBitmap( CPE::WindowButtonState state ) const;
    void SetStateBitmap( CPE::WindowButtonState state,
                         const CBitmapRefPtr& pBitmap );
private:
    CRect 			m_rectPos; 		// 位置
    CRect			m_rectOffset;	// 偏移
    CRect			m_rectAnchor;	// 锚点
    CBitmapRefPtr	m_pBmpState[CPE::WBS_Size];
};

struct CDialogBoxParameter:public CCtrlWithScrollBarParameter
{
public:


    /**
     * @brief    是否有标题
     * @return
     */
    bool HasTitle() const;
    void SetHasTitle(bool HasTitle);

    /**
     * @brief HasMaxButton 是否有最大化按钮
     * @return
     */
    bool HasMaxButton() const;
    void SetHasMaxButton(bool HasMaxButton);

    /**
     * @brief HasMinButton 是否有最小化按钮
     * @return
     */
    bool HasMinButton() const;
    void SetHasMinButton(bool HasMinButton);

    /**
     * @brief HasCloseButton
     * @return
     */
    bool HasCloseButton( ) const;
    void SetHasCloseButton( bool bHasCloseButton );

    /**
     * @brief IsActivated
     * @return
     */
    bool IsActivated( ) const;
    void SetActivated( bool bActivated );

    /**
     * @brief GetNcMouseState
     * @return
     */
    CPE::MouseState GetNcMouseState( ) const;
    void SetNcMouseState( CPE::MouseState state );

    /**
     * @brief GetMaxButtonState
     * @return
     */
    CPE::WindowButtonState GetMaxButtonState() const;
    void SetMaxButtonState(CPE::WindowButtonState nMaxButtonState);

    /**
     * @brief GetMinButtonState
     * @return
     */
    CPE::WindowButtonState GetMinButtonState() const;
    void SetMinButtonState(CPE::WindowButtonState nMinButtonState);

    /**
     * @brief GetCloseButtonState
     * @return
     */
    CPE::WindowButtonState GetCloseButtonState() const;
    void SetCloseButtonState(CPE::WindowButtonState nCloseButtonState);

    /**
     * @brief GetHelpButtonState
     * @return
     */
    CPE::WindowButtonState GetHelpButtonState() const;
    void SetHelpButtonState(CPE::WindowButtonState nHelpButtonState);

    /**
     * @brief GetSelelectedButtonType
     * @return
     */
    CPE::WindowHitType GetSelelectedButtonType() const;
    void SetSelectedButtonType(CPE::WindowHitType nSelelectedButtonType);

    /**
     * @brief IsSizable
     * @return
     */
    bool IsSizable( ) const;
    void SetSizable( bool bSizable );

    /**
     * @brief IsInMenu
     * @return
     */
    bool IsInMenu() const;
    void SetInMenu(bool IsInMenu);

    /**
     * @brief GetMenuBarParamPtr
     * @return
     */
    DynamicParam::CMenubarCtrlSkinParameterRefPtr GetMenuBarParamPtr();
    const DynamicParam::CMenubarCtrlSkinParameterRefPtr GetMenuBarParamPtr() const;
    void SetMenuBarParamPtr(
            const DynamicParam::CMenubarCtrlSkinParameterRefPtr pMenuBarParamPtr);
    
    /**
     * @brief HasMenu
     * @return
     */
    bool HasMenu() const;
    void SetHasMenu(bool IsMenu);

    /**
     * @brief GetWindowRect
     * @return
     */
    const CRect& GetWindowRect( ) const;
    CRect& GetWindowRect( );
    void SetWindowRect( const CRect& rectWindow );

    /**
     * @brief GetMargin
     * @return
     */
    const CRect& GetMargin( )const;
    CRect& GetMargin( );
    void SetMargin( const CRect& rectMargin );

    /**
     * @brief UpdatePartRect
     * @param rectWindow
     */
    void UpdatePartRect( const CRect& rectWindow );
    const CRect& GetPartRect( CPE::WindowPart wp ) const;
    CRect& GetPartRect( CPE::WindowPart wp );
    void SetPartRect( CPE::WindowPart wp, const CRect& rect );

    /**
     * @brief UpdateButtonRect
     * @param rectWindow
     */
    void UpdateButtonRect(
            const CRect& rectWindow,
            const CWindowButtonParam (&paramButtons)[CPE::WB_Size] );
    const CRect& GetButtonRect( CPE::WindowButton wb ) const;
    CRect& GetButtonRect( CPE::WindowButton wb );
    void SetButtonRect( CPE::WindowButton wb, const CRect& rect );
    UINT HitButtonTest( const CPoint& pt );
    const CRect& GetMenuRect( ) const;
    void SetMenuRect( const CRect& rect );
private:

    /**
     * @brief m_bTitle
     */
    bool				m_bTitle;

    /**
     * @brief m_bMaxBtn
     */
    bool				m_bMaxBtn;

    /**
     * @brief m_bMinBtn
     */
    bool				m_bMinBtn;

    bool				m_bCloseBtn;

    bool				m_bIsActivated;

    CPE::MouseState		m_nNcMouseState;
    /**
     * @brief m_nMaxBtnState
     */
    CPE::WindowButtonState	m_nMaxBtnState;

    /**
     * @brief m_nMinBtnState
     */
    CPE::WindowButtonState	m_nMinBtnState;

    /**
     * @brief m_nCloseBtnState
     */
    CPE::WindowButtonState	m_nCloseBtnState;

    /**
     * @brief m_nHelpBtnState
     */
    CPE::WindowButtonState	m_nHelpBtnState;

    /**
     * @brief m_nSelBtnType
     */
    CPE::WindowHitType	m_nSelBtnType;

    bool				m_bSizable;
    /**
     * @brief m_bInMenu
     */
    bool				m_bInMenu;

    /**
     * @brief m_bHasMenu
     */
    bool				m_bHasMenu;

    /**
     * @brief m_rectMenu
     */
    CRect				m_rectMenu;

    /**
     * @brief m_rectWindow
     */
    CRect				m_rectWindow;

    /**
     * @brief m_rectMargins
     */
    CRect				m_rectMargins;

    /**
     * @brief m_rectParts
     */
    CRect				m_rectParts[CPE::WP_Size];

    /**
     * @brief m_rectButtons
     */
    CRect				m_rectButtons[CPE::WB_Size];
private:
    /**
     * @brief m_pMenuBarParam
     */
    DynamicParam::CMenubarCtrlSkinParameterRefPtr	m_pMenuBarParam;

protected:

};


class CDialogBoxSkin: public CCtrlWithScrollBar<CDialogBoxParameter>
{
    enum
    {
        MenuTrackTimerId = 190719
    };
public:
	CDialogBoxSkin( );
	void LoadSkin( const CSkinConfig* pConfig );
protected:
    ~CDialogBoxSkin();


    LRESULT OnWndOtherProc( UINT nMsg, WPARAM wParam, LPARAM lParam );

    LPCTSTR GetHwndClassName( );

    /**
         * @brief 接管控件皮肤之前
         */
    bool OnInitSkinParam( HWND hWnd, CParamReference* pParam );

	void	OnCreate( LPCREATESTRUCT lpCreateStruct );

	void	OnInitDialog( );
    // 重写
    void    OnNcMouseMove( UINT nHitTest, const CPoint& point );

    // 重写
    void    OnMouseMove(UINT nFlags, const CPoint& point);

    void    OnNcLButtonUp( UINT nHitTest, const CPoint& point );

    // 重写
    void    OnNcLButtonDown( UINT nHitTest, const CPoint& point );

    void    OnNcRButtonDown(UINT nHitTest, const CPoint& point);

    // 重写
    void    OnNcLButtonDblClk( UINT nHitTest, const CPoint& point );

    // 重写
    LRESULT OnNcHitTest( const CPoint& point );
    BOOL    OnNcActivate( BOOL bActive );

    // 重写
    void    OnNcCalcSize( bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);

    // 重写
    void    OnNcPaint(HRGN rgn1);
    HRGN    CreateNcRgn( HDC hdc, const CRect& rect );
    void    DrawNcMargin( HDC hdc, const CRect& r,
                          bool bIsActive, CPE::WindowBackgroundImagePart nPart );
    void    OnSysCommand(UINT nID,LPARAM lParem);
    BOOL    OnEraseBkgnd(HDC hdc );
    void    OnSize(UINT nType,int cx,int cy);
    void    OnSetText(WPARAM wp,LPARAM lp);
    LRESULT OnSetIcon(UINT nFlag,HICON hIcon);
    void    OnEnable(BOOL bEnable);
    void    OnTimer(UINT_PTR nIDEvent);

	/*!
	 * @brief 菜单事件处理
	 * @param msg 消息id
	 * @param pt 点击的店
	 * @return 
	 * @note
	 */
    void    HandleMenuBarEvent(UINT msg,  const CPoint& pt);

	/*!
	 * @brief 菜单栏的事件追踪
	 * @param 坐标点
	 * @return 
	 * @note
	 */
    void    TrackMenuBar(const CPoint& point);

	/*!
	 * @brief 绘制边框
	 * @param hdc画笔
	 * @return 
	 * @note
	 */
    void    DrawFrame( HDC hdc );

	/*!
	 * @brief 绘制标题
	 * @param 画笔
	 * @return 
	 * @note
	 */
    void    DrawCaption( HDC hdc );

	/*!
	 * @brief 绘制关闭、最大化、最小化等窗口按钮
	 * @param 画笔
	 * @return 
	 * @note
	 */
    void    DrawWindowButton( HDC hdc );
    void    DrawWindowButton( );

    /**
         * @brief 绘制窗口的按钮
         * @param hdc-上下文句柄
         * @param rectWindow 窗口矩形
         * @param buttonType 按钮类型
         * @param buttonState 按钮的状态
         *
         */
    void    DrawWindowButton( HDC hdc, const CRect rectWindow,
                              CPE::WindowButton buttonType,
                              CPE::WindowButtonState buttonState );

	/*!
	 * @brief 绘制菜单栏
	 * @param 画笔
	 * @return 
	 * @note
	 */
    void    DrawMenuBar( HDC hdc );

protected:
	DynamicParam::CMenubarCtrlSkin& LoadMenuBarCtrlSkin( ); 
private:
	/* 窗口的按钮的贴图 */
    CWindowButtonParam	m_paramButtons[CPE::WB_Size];

	/* 窗口激活时的边框贴图 */
    CBitmapRefPtr       m_pBmpActiveNcBk[CPE::WBKIP_Size];

	/* 窗口未激活时的边框贴图 */
    CBitmapRefPtr       m_pBmpUnActiveNcBk[CPE::WBKIP_Size];
};

}
