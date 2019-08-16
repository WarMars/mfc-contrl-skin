#pragma once

#include "CtrlSkinPackage.hpp"
#include <vector>
#include "gdiobj_ptr.hpp"

/** 
 * 菜单栏控件
 */
namespace GlobalSkin
{
namespace CPE
{

/** 
 * @brief 菜单项状态
 */
enum MenuItemState
{
    MIS_Hot = 0x01,		/* 焦点 */
    MIS_Pressed = 0x02, /* 按下 */
    MIS_Horz = 0x04,	/* 水平 */
    MIS_Hidden = 0x08,	/* 隐藏 */
    MIS_Wrap = 0x10,	/* 不展开 */
    MIS_Inactive = 0x20 /* 无法交互 */
};

/** 
 * @brief 菜单项文本状态
 */
enum MenuItemTextState
{
    MITS_Normal = 0, /* 操作颜色 */
    MITS_Gray,		 /* 禁用 */
    MITS_Pressed,	 /* 按下 */
    MITS_Active,	 /* 活动 */
    MITS_Size
};

/** 
 * @brief 菜单项背景图
 */
enum MenuItemImage
{
    MII_Activate = 0, /* 激活 */
    MII_Pressed,	  /* 按下 */
    MII_Size
};

/** 
 * @brief 菜单栏状态追踪
 */
enum MenuBarTrackState 
{
    MBTS_None = 0, /* 无操作 */
    MBTS_Button,   /* 点击Alt时的菜单 */
    MBTS_Popup,    /* 弹出 */
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
     * @brief SetBkImage 设置背景图
     * @param pBmp
     */
    void SetBkImage( const CBitmapRefPtr& pBmp );
    CBitmapRefPtr GetBkImage( ) const;

    /**
     * @brief SetImage 设置状态图
     * @param imgType
     * @param pBmp
     */
    void SetImage( CPE::MenuItemImage imgType,
                   const CBitmapRefPtr& pBmp );
    CBitmapRefPtr GetImage( CPE::MenuItemImage imgType ) const;

    /**
     * @brief SetTextStateColor 设置文本状态颜色
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
     * @brief GetInvalidMenuId     获取 无效的  菜单id
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
     * @brief Init 初始化菜单项
     * @param hWnd 菜单所属的窗口句柄
     * @param hMenu 菜单项句柄
     * @param nIndex 菜单索引
     */
    void Init( HWND hWnd, HMENU hMenu, int nIndex );

    /**
     * @brief Update 更新
     * @param hdc
     * @param pParam
     */
    void Update( HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

    /**
     * @brief Layout 布局
     * @param point 坐标点
     * @param bHorz 是否为水平
     */
    void Layout( const CPoint& point, bool bHorz );

    /**
     * @brief TrackPopup 追踪弹出菜单的事件
     * @param hBar 子窗口句柄，对于菜单来说，通常为NULL
     * @param hWndSentCmd 目标窗口
     */
    void TrackPopup( HWND hBar, HWND hWndSentCmd);

    /**
     * @brief SetText	设置菜单文本
     * @param hWnd	所属窗口句柄
     * @param lpszText 文本
     */
    void SetText( HWND hWnd, LPCTSTR lpszText );

    /**
     * @brief GetHorizontalSize 获取水平大小
     * @return 款高信息
     */
    CSize GetHorizontalSize( ) const;

    /**
     * @brief GetRect 获取菜单的位置矩形
     * @return 位置矩形
     */
    const CRect& GetRect( ) const;

    /**
     * @brief GetSubMenu 获取子菜单项
     * @return 菜单项句柄
     */
    HMENU GetSubMenu( ) const;

    /**
     * @brief ModifyState 修改菜单项当前的状态风格参数
     * @param byRemove 删除的风格参数
     * @param byAdd 添加的风格参数
     * @return
     */
    bool ModifyState(BYTE byRemove, BYTE byAdd);

    /**
     * @brief DrawHot 绘制当前项
     * @param hdc dc
     * @param pParam 菜单项参数
     */
    void DrawHot(
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

    /**
     * @brief DrawPressed 绘制按下状态
     * @param hdc dc
     * @param pParam 菜单项按下的参数
     */
    void DrawPressed(
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

    /**
     * @brief DrawNone 绘制无操作的默认状态
     * @param hdc dc
     * @param pParam 菜单项的参数
     */
    void DrawNormal( 
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
		HFONT hHorizontalFont, HFONT hVerticalFont );

	COLORREF GetCurTextColor( const CMenuItemSkinParameterRefPtr& pParam  ) const;
    /**
     * @brief DrawHorzText 绘制垂直方向的文本
     * @param hdc dc
     * @param pParam 菜单项参数
     * @param ptOffset 偏移量
     */
    void DrawHorzText( 
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
        HFONT hFont, const CPoint& ptOffset = CPoint(0, 0) );

    /**
     * @brief DrawVertText 绘制垂直文本
     * @param hdc   dc
     * @param pParam 菜单项参数
     * @param ptOffset 菜单项的偏移
     */
    void DrawVertText( 
		HDC hdc, const CMenuItemSkinParameterRefPtr& pParam,
        HFONT hFont,const CPoint& ptOffset = CPoint(0, 0) );

    /**
     * @brief DrawButton	绘制菜单
     * @param hdc	dc
     * @param wState 状态参数
     * @param pParam 菜单项参数指针
     */
    void DrawButton( HDC hdc, WORD wState, const CMenuItemSkinParameterRefPtr& pParam );


    /**
     * @brief InitButtonStringAndSubMenuHandle 初始化菜单的文本和子菜单句柄
     * @param hMenu 菜单句柄
     * @param nIndex 菜单项的索引
     */
    void InitButtonStringAndSubMenuHandle(HMENU hMenu, int nIndex);

    /**
     * @brief InitHorizontalButtonSize 初始化水平状态
     * @param hWnd
     */
    void InitHorizontalButtonSize( HWND hWnd );

    /**
     * @brief InitAccessKeyAndVerticalLinePoint 初始化热键和线条的2点坐标
     * @param hWnd
     */
    void InitAccessKeyAndVerticalLinePoint( HWND hWnd );
private:
	///
	/// @brief 状态参数
	///
    BYTE		m_byState;

	///
	/// @brief 位置矩形
	///
    CRect		m_rect;

	///
	/// @brief 水平大小
	///
    CSize		m_szHorz;

	///
	/// @brief 菜单的id
	///
    UINT		m_nMenuId;

	///
	/// @brief 子菜单的句柄
	///
    HMENU		m_hSubMenu;

	///
	/// @brief 菜单文本
	///
    TCHAR		m_szText[32];

	///
	/// @brief 绘制先的起始位置
	///
    CPoint		m_ptMoveTo;

	///
	/// @brief 绘制线的结束位置
	///
    CPoint		m_ptLineTo;

	///
	/// @brief 接收的热键
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
     * @brief m_pHot 当前操作的菜单项的参数
     */
    CMenuItemParameterRef*	m_pHot;

    /**
     * @brief m_pPressed 按下菜单项的参数
     */
    CMenuItemParameterRef*	m_pPressed;

    /**
     * @brief m_nNewPopUp 新的弹出菜单
     */
    int						m_nNewPopUp;

    /**
     * @brief m_hTrackingMenu 最终的菜单句柄
     */
    HMENU					m_hTrackingMenu;

    /**
     * @brief m_hMenu 菜单句柄
     */
    HMENU					m_hMenu;

    /**
     * @brief m_vectorItems 菜单项数组
     */
    std::vector<CMenuItemParameterRefPtr> m_vectorItems;

    /**
     * @brief m_rectPos 位置矩形
     */
    CRect					m_rectPos;

    /**
     * @brief m_bEscapePressed esc键是否按下
     */
    bool					m_bEscapePressed;

    /**
     * @brief m_nTrackingState 追踪的状态
     */
    CPE::MenuBarTrackState                      m_nTrackingState;

    /**
     * @brief m_bProcessLeftArrow 是否处理左侧箭头
     */
    bool					m_bProcessLeftArrow;

    /**
     * @brief m_bProcessRightArrow 是否处理右侧箭头
     */
    bool					m_bProcessRightArrow;

    /**
     * @brief m_nPopupTracking 状态追踪
     */
    int						m_nPopupTracking;

    /**
     * @brief m_ptMouse 鼠标坐标
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
 * @brief CreateMenuBarSkinParameter 创建菜单栏皮肤参数
 * @param hWnd 菜单栏句柄
 * @return 菜单参数指针
 */
CMenubarCtrlSkinParameterRefPtr CreateMenuBarSkinParameter( HWND hWnd );

/**
 * @brief CopyMenu 复制菜单
 * @param hMenuSrc 源菜单句柄
 * @return 复制出来的菜单句柄
 */
HMENU CopyMenu( HMENU hMenuSrc );


/**
 * @brief The CMenubarCtrlSkin class
 */
class CMenubarCtrlSkin
{
public:

    /**
     * @brief GetInstance 获取一个菜单栏实例
     * @param hWnd 菜单所属窗口句柄
     * @param pParam 菜单栏参数
     * @param bInit 是否使用其它参数初始化菜单栏皮肤
     * @return 菜单栏皮肤对象引用
     */
//    static CMenubarCtrlSkin& GetInstance(
//            HWND hWnd, CMenubarCtrlSkinParameterRefPtr pParam, bool bInit = true );

	void Init( HWND hWnd, const CMenubarCtrlSkinParameterRefPtr& pParam );
    CMenubarCtrlSkin( );
    ~CMenubarCtrlSkin( );
public:
	void LoadSkin( const CSkinConfig* pConfig );
    /**
     * @brief InitItems 初始化菜单项
     * @param rectMargins 菜单项矩形
     * @return 初始化成功返回true，否则返回false
     */
    bool			InitItems( const CRect& rectMargins );

    /**
     * @brief DeleteItems 删除所有菜单项
     */
    void			DeleteItems();

    /**
     * @brief GetItemCount 获取菜单项的数目
     * @return 菜单项数目索引
     */
    int				GetItemCount() const ;

    /**
     * @brief IsValidIndex 菜单项的编号是否有效
     * @param nIndex 菜单项编号
     * @return 有效返回true，否则返回false
     */
    bool			IsValidIndex(int nIndex) const;

    /**
     * @brief HitTestOnTrack 点击测试
     * @param point 测试的坐标点
     * @return 点击菜单项的索引
     */
    int             HitTestOnTrack( const CPoint& point);

    /**
     * @brief SetMenu	设置菜单
     * @param hMenu		菜单句柄
     * @param rectMargins 边框矩形
     */
    void			SetMenu(HMENU hMenu, const CRect& rectMargins );

    /**
     * @brief GetTrackingState 获取追踪状态
     * @param nPopup 弹出菜单追踪的编号
     * @return 菜单项的状态
     */
    CPE::MenuBarTrackState	GetTrackingState(int& nPopup) ;

    /**
     * @brief CalcMenuBarPos 计算菜单栏的位置
     * @param rectMargin 位置矩形
     */
    void			CalcMenuBarPos( const CRect& rectMargin );

    /**
     * @brief TrackPopup 追踪弹出菜单 
     * @param nButton 菜单的编号
     */
    void			TrackPopup(int nButton);

    /**
     * @brief GetNextOrPrevButton 获取下一个菜单
     * @param nButton	当前菜单
     * @param bPrev		是否是前一个菜单
     * @return 符合条件的菜单按钮索引
     */
    int				GetNextOrPrevButton(int nButton, bool bPrev);

    /**
     * @brief SetTrackingState 设置追踪的状态
     * @param nState 状态
     * @param iButton 按钮编号
     */
    void			SetTrackingState(CPE::MenuBarTrackState nState, int iButton=-1);

    /**
     * @brief ToggleTrackButtonMode 设置追踪按钮的模式
     */
    void			ToggleTrackButtonMode();

    /**
     * @brief CancelMenuAndTrackNewOne 
	 *					取消事件追踪并将按钮设置到新的按钮上
     * @param iButton 新的按钮索引
     */
    void			CancelMenuAndTrackNewOne(int iButton);

    /**
     * @brief OnMenuInput 菜单消息处理
     * @param m	消息结构
     * @return 成功返回true，否则返回false
     */
    virtual bool	OnMenuInput( const MSG& m);

    /**
     * @brief GetIndex	获取制定菜单项的参数信息
     * @param nIndex	菜单项的索引
     * @return			菜单项的信息
     */
    CMenuItemParameterRef*		GetIndex(int nIndex) const;

    /**
     * @brief OnLButtonDown WM_LBUTTONDOWN消息处理
     * @param nFlags
     * @param point
     */
    void            OnLButtonDown(UINT nFlags, const CPoint& point);

    /**
     * @brief OnMouseMove WM_MOUSEMOVE消息处理
     * @param nFlags 消息标识
     * @param point 鼠标的坐标
     */
    void            OnMouseMove(UINT nFlags, const CPoint& point);

    /**
     * @brief DrawMenuBar 绘制菜单栏
     */
    void			DrawMenuBar( );

    /**
     * @brief MenuInputFilter 菜单消息拦截
     * @param code	消息码
     * @param wp	消息的WPARAM
     * @param lp	消息的LPARAM
     * @return	消息的处理结果
     */
    static LRESULT CALLBACK MenuInputFilter(int code, WPARAM wp, LPARAM lp);

private:
	///
	/// @brief 当前的菜单所在的窗口
	///
    HWND                                        m_hWnd;

	///
	/// @brief 菜单栏参数
	///
    CMenubarCtrlSkinParameterRefPtr            m_pParam;

    // 菜单项的皮肤
    CMenuItemSkinParameterRefPtr				m_pItem;

    // 菜单的背景
    CBitmapRefPtr                               m_pBmpBk;

	/* 字体 */
	HFONT										m_hFontItem;
};
}
}
