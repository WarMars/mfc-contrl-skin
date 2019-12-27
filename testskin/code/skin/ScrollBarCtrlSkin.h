#pragma  once
#include "GlobalUiManager.h"
#include "gdiobj_ptr.hpp"
#include <GdiPlus.h>
namespace GlobalSkin
{
namespace CPE /* Control Parameter Enumeration */
{
	
/* 滚动条的一些参数 */
enum ScrollBarParameter
{
    SBP_Visible = 8,			/* 是否可见的标识 */
    SBP_MinRect = 4,			/* 箭头之外的举行最小尺寸 */
    SBP_MinThumb = 6,			/* 滑块最小尺寸 */
    SBP_ArrowThumbOverlap = 0,  /* 箭头和滑块之间的最小距离 */
    SBP_FirstDelay = 100,		/* 按下之后再次按下的延时 */
    SBP_RepeatDelay = 50,		/* 2次滑动滑块的时间间隔（毫秒） */
    SBP_TimerID = 344			/* 滑动的定时器id */
};

///
/// @brief 滚动条的状态
///
enum ScrollBarState
{
    SBS_Normal = 0,		/* 无操作 */
    SBS_Hover,			/* 鼠标滑过 */
    SBS_Pressed,		/* 鼠标按下 */
    SBS_Disabled,		/* 禁用 */
    SBS_Size
};

///
/// @brief 滚动条鼠标位置
///
enum ScrollBarHitTest
{
    SBHT_Nowhere,      /* 点击到滚动条之外 */
    SBHT_TopArrow,     /* 滚动条左侧或顶部的箭头 */
    SBHT_TopRect,      /* 顶部箭头与滑块之间的距离 */
    SBHT_Thumb,        /* 点击滑块矩形 */
    SBHT_BottomRect,   /* 点击的是底部箭头与滑块之间的举行 */
    SBHT_BottomArrow   /* 点击底部或右侧的箭头 */
};
}
namespace DynamicParam
{

bool GetScrollRect( HWND hWnd, UINT nBar, LPRECT lpRect,int *nArrowSize,int *nThumbSize,int *nThumbPos);
struct CScrollBarBasic
{
	///
	/// @brief 标志。为了存储更多的状态
	///
    UINT		nFlags;

	///
	/// @brief 是否可见
	///
    bool		bVisible;

	///
	/// @brief 系统信息 (range, position, page size 等)
	///
    SCROLLINFO	sysInfo; 


    union
    {
        struct
        {
			///
			/// @brief top/left状态
			///
            CPE::ScrollBarState			nArrowState1;	

			///
			/// @brief bot/right状态
			///
            CPE::ScrollBarState			nArrowState2;		
        };

        struct
        {
			///
			/// @brief top状态
			///
            CPE::ScrollBarState			nTopArrowState;	

			///
			/// @brief bot状态
			///
            CPE::ScrollBarState			nBotArrowState;		
        };

        struct
        {
			///
			/// @brief left状态
			///
            CPE::ScrollBarState			nLeftArrowState;	
			
			///
			/// @brief right状态
			///
            CPE::ScrollBarState			nRightArrowState;		
        };
    };

	///
	/// @brief 滑块状态
	///
    CPE::ScrollBarState			nThumbState;		


public:
    UINT GetFlags() const;
    void SetFlags(const UINT &value);
    bool IsVisible() const;
    void SetVisible(bool value);
    const SCROLLINFO& GetSysInfo() const;
    SCROLLINFO& GetSysInfo();
    CPE::ScrollBarState GetArrowState1( ) const;
    void SetArrowState1(CPE::ScrollBarState state );
    CPE::ScrollBarState GetArrowState2( ) const;
    void SetArrowState2(CPE::ScrollBarState state );
    CPE::ScrollBarState GetTopArrowState( ) const;
    void SetTopArrowState(CPE::ScrollBarState state );
    CPE::ScrollBarState GetBotArrowState( ) const;
    void SetBotArrowState(CPE::ScrollBarState state );
    CPE::ScrollBarState GetLeftArrowState( ) const;
    void SetLeftArrowState(CPE::ScrollBarState state );
    CPE::ScrollBarState GetRightArrowState( ) const;
    void SetRightArrowState(CPE::ScrollBarState state );
    CPE::ScrollBarState GetThumbState() const;
    void SetThumbState(CPE::ScrollBarState value);
};

struct CScrollBarCtrlParameter : public CCtrlParameter
{
	///
	/// @brief 水平滚动条参数
	///
    CScrollBarBasic m_hBar; 

	///
	/// @brief 垂直滚动条参数
	///
    CScrollBarBasic m_vBar;
	
	///
	/// @brief 启动滑块追踪
	///
    bool	m_bEnableThumbTracking;

	///
	/// @brief 是否支持WS_EX_LEFTSCROLLBAR风格
	///
    bool	m_bLeftScrollbar;


    ///
    /// @brief 能使用oldproc吗
	///        此参数暂时未使用
    ///
    bool m_bPreventStyleChange;

	///
	/// @brief 水平滚动条位置矩形
	///
    CRect			m_rectHScroll;

	///
	/// @brief 垂直滚动条位置矩形
	///
    CRect			m_rectVScroll;

	///
	/// @brief 点击测试
	///
    CPE::ScrollBarHitTest	m_hitTest;

	///
	/// @brief 绘制追踪滑块
	///
    bool			m_bDrawTrackingBar;

	///
	/// @brief 追踪位置
	///
    int				m_nTrackingPos;

	///
	/// @brief 追踪的值
	///
    int				m_nTrackingValue;	

public:
	bool IsEnableThumbTracking( ) const;
	void SetEnableThumbTracking( bool bEnable );
	bool IsLeftScrollBar( ) const;
	void SetLeftScrollBar( bool b );

    bool IsPreventStyleChange() const;
    void SetPreventStyleChange(bool value);
    const CRect& GetHScrollRect() const;
    void SetHScrollRect(const CRect &rtHScroll);
    const CRect& GetVScrollRect() const;
    void SetVScrollRect(const CRect &rtVScroll);
    CPE::ScrollBarHitTest GetHitTest() const;
    void setHitTest(const CPE::ScrollBarHitTest &hitTest);
    bool NeedDrawTrackingBar() const;
    void SetNeedDrawTrackingBar(bool bDrawTrackingBar);
    int GetTrackingPos() const;
    void SetTrackingPos(int nTrackingPos);
    int GetTrackingValue() const;
    void SetTrackingValue(int nTrackingValue);
    const CScrollBarBasic& GetHBar() const;
    const CScrollBarBasic& GetVBar() const;

    CScrollBarBasic& GetHBar();
    CScrollBarBasic& GetVBar();
};

DECLARE_REF_PTR_NC( CScrollBarCtrlParameter );

class CScrollBarCtrlSkin
{
public:
	
	/*!
	 * @brief 获取滚动条对象
	 * @param 
	 * @return 滚动条对象的引用
	 * @note 
	 */
    //static CScrollBarCtrlSkin&  GetInstance( );

	void LoadSkin( const CSkinConfig* pConfig );
	/*!
	 * @brief 绘制水平滚动条
	 * @param hWnd 窗口
	 * @param pParam 滚动条参数
	 * @return 
	 * @note 
	 */
    void DrawHScrollBar( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam, bool bIsControl = false  );

	/*!
	 * @brief 绘制垂直滚动条
	 * @param hWnd 窗口
	 * @param pParam 滚动条参数
	 * @return 
	 * @note
	 */
    void DrawVScrollBar( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam, bool bIsControl = false );

	/*!
	 * @brief 绘制sizing块
	 * @param hWnd 窗口
	 * @param r 矩形
	 * @return 
	 * @note
	 */
    void DrawSizing( HWND hWnd, const CRect& r );

	/*!
	 * @brief 滚动条的事件追踪
	 * @param hWnd 窗口
	 * @param pParam 滚动条参数
	 * @param nType
	 * @param ptCur 鼠标坐标
	 * @return 
	 * @note
	 */
    void TrackScrollBar(
            HWND hWnd,
            CScrollBarCtrlParameterRefPtr pParam,
            UINT nType, const CPoint& ptCur );
	
	/*!
	 * @brief 鼠标点击位置检测
	 * @param hWnd 窗口
	 * @param nType 点击的矩形
	 * @param ptCur鼠标位置
	 * @param bDragging 是否正在拖动
	 * @return 鼠标位置处于滚动条的位置
	 * @note
	 */
    CPE::ScrollBarHitTest ScrollHitTest(
		HWND hWnd, UINT nType, const CPoint& ptCur, BOOL bDragging );

	CScrollBarCtrlSkin( );

	
	/*!
	 * @brief 绘制水平背景
	 * @param hdc hdc
	 * @param r 背景矩形
	 * @return 
	 * @note
	 */
    void DrawHBackground( HDC hdc, const CRect& r );

	/*!
	 * @brief 
	 * @param 
	 * @return 
	 * @note
	 */
    void DrawHLeftArrow( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief 
	 * @param 
	 * @return 
	 * @note
	 */
    void DrawHRightArrow( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief 
	 * @param 
	 * @return 
	 * @note
	 */
    void DrawHThumb( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief 绘制垂直背景
	 * @param hdc dc
	 * @param r 背景图的矩形
	 * @return 
	 * @note
	 */
    void DrawVBackground( HDC hdc, const CRect& r );
	
	/*!
	 * @brief 绘制垂直向上的箭头
	 * @param hdc dc
	 * @param r 位置矩形
	 * @param nState 状态
	 * @return 
	 * @note
	 */
    void DrawVTopArrow( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief 绘制底部的箭头
	 * @param hdc dc
	 * @param r 位置矩形
	 * @param nState 状态
	 * @return 
	 * @note
	 */
    void DrawVBotArrow( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief 绘制垂直滑块
	 * @param hdc dc
	 * @param r 位置矩形
	 * @param nState 状态
	 * @return 
	 * @note
	 */
    void DrawVThumb( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief 绘制垂直滚动条
	 * @param hdc dc
	 * @param rtDest 位置矩形
	 * @return 
	 * @note
	 */
    void DrawHScroll( HDC hdc, const CRect& rtDest,int nState );
    void DrawVScroll( HDC hdc, const CRect& rtDest,int nState );

    /**
	 * @brief 处理滚动条事件
	 * @param ptPrevious 上一次点击的位置
	 * @param nThumbPos 滑块的位置
	 * @param nLastClickPos 上一次鼠标按下的位置
	 * @param nLastMousePos 上一次鼠标事件的位置
	 */
    void HandleScrollEvent(
            HWND hWnd,
            CScrollBarCtrlParameterRefPtr pParam,
            UINT nType, UINT nEventType, const CPoint& ptCur,
            POINT& ptPrevious,UINT& nThumbPos, INT& nLastClickPos,
            INT& nLastMousePos,
			bool& bIsTrackingVertical );

	
	/*!
	 * @brief 绘制滑块
	 * @param hWnd 窗口
	 * @param pParam 滚动条参数
	 * @param bVertical 是否是垂直
	 * @param rtPos 位置
	 * @param nArrowSize 箭头大小
	 * @param nThumbSize 滑块大小
	 * @return 
	 * @note
	 */
    void DrawMovingThumb(
            HWND hWnd, CScrollBarCtrlParameterRefPtr pParam,
            bool bVertical, const CRect& rtPos,int nArrowSize,int nThumbSize);
private:
	
	/* 当前滚动条的参数 */
    CScrollBarCtrlParameterRefPtr	m_pParam;
	
	/* 当前滚动条窗口 */
    HWND							m_hWnd;
	
	/* 水平滚动条左向箭头贴图 */
    Gdiplus::Image*					m_bmpHLeftArrow[CPE::SBS_Size];
	
	/* 水平滚动条右向箭头贴图 */
    Gdiplus::Image*					m_bmpHRightArrow[CPE::SBS_Size];
	
	/* 水平滚动条滑块贴图 */
    Gdiplus::Image*					m_bmpHThumb[CPE::SBS_Size];
	
	/*  水平滚动条背景图 */
    Gdiplus::Image*					m_bmpHBk;

	/* 垂直滚动条向上箭头背景图 */
	Gdiplus::Image*					m_bmpVTopArrow[CPE::SBS_Size];

	/* 垂直滚动条向下箭头背景图 */
	Gdiplus::Image*					m_bmpVBotArrow[CPE::SBS_Size];

	/* 垂直滚动条滑块背景图 */
	Gdiplus::Image*					m_bmpVThumb[CPE::SBS_Size];

	/* 垂直滚动条背景图 */
	Gdiplus::Image*					m_bmpVBk;

	/* 垂直滚动条sizing箭头背景图 */
    Gdiplus::Image*					m_bmpSizing;

};


/*!
 * @brief 创建窗口滚动条
 * @param hWnd 窗口
 * @return 滚动条参数指针
 * @note
 */
CScrollBarCtrlParameterRefPtr CreateHwndScrollBarParam( HWND hWnd );


/*!
 * @brief 滚动条测试
 * @param hWnd 所属窗口
 * @param pParam 滚动条参数
 * @param point 点击的点
 * @return 点所在滚动条的相对位置
 * @note
 */
UINT OnScrollBarHitTest(
        HWND  hWnd,
        CScrollBarCtrlParameterRefPtr pParam,
        const CPoint& point );


/*!
 * @brief 设置滚动条参数
 * @param hWnd 所属窗口
 * @param pParam 参数
 * @return 
 * @note
 */
void SetScrollBarParamVisible(
	HWND hWnd, 
	CScrollBarCtrlParameterRefPtr pParam );


/*!
 * @brief 滚动条非客户区的消息追踪
 * @param hWnd 滚动条所属窗口
 * @param pParam 滚动条参数
 * @param bBorder 是否有边框
 * @param bCalcValidRects 是否是有效的计算的rect
 * @param lpncsp 计算非客户区尺寸信息的参数
 * @return 
 * @note
 */
void OnNcScrollBar( 
	HWND hWnd,
	CScrollBarCtrlParameterRefPtr pParam,
	bool bBorder, 
	bool bCalcValidRects, 
	NCCALCSIZE_PARAMS *lpncsp);

}

}
