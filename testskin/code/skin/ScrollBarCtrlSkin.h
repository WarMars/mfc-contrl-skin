#pragma  once
#include "GlobalUiManager.h"
#include "gdiobj_ptr.hpp"
#include <GdiPlus.h>
namespace GlobalSkin
{
namespace CPE /* Control Parameter Enumeration */
{
	
/* ��������һЩ���� */
enum ScrollBarParameter
{
    SBP_Visible = 8,			/* �Ƿ�ɼ��ı�ʶ */
    SBP_MinRect = 4,			/* ��ͷ֮��ľ�����С�ߴ� */
    SBP_MinThumb = 6,			/* ������С�ߴ� */
    SBP_ArrowThumbOverlap = 0,  /* ��ͷ�ͻ���֮�����С���� */
    SBP_FirstDelay = 100,		/* ����֮���ٴΰ��µ���ʱ */
    SBP_RepeatDelay = 50,		/* 2�λ��������ʱ���������룩 */
    SBP_TimerID = 344			/* �����Ķ�ʱ��id */
};

///
/// @brief ��������״̬
///
enum ScrollBarState
{
    SBS_Normal = 0,		/* �޲��� */
    SBS_Hover,			/* ��껬�� */
    SBS_Pressed,		/* ��갴�� */
    SBS_Disabled,		/* ���� */
    SBS_Size
};

///
/// @brief ���������λ��
///
enum ScrollBarHitTest
{
    SBHT_Nowhere,      /* �����������֮�� */
    SBHT_TopArrow,     /* ���������򶥲��ļ�ͷ */
    SBHT_TopRect,      /* ������ͷ�뻬��֮��ľ��� */
    SBHT_Thumb,        /* ���������� */
    SBHT_BottomRect,   /* ������ǵײ���ͷ�뻬��֮��ľ��� */
    SBHT_BottomArrow   /* ����ײ����Ҳ�ļ�ͷ */
};
}
namespace DynamicParam
{

bool GetScrollRect( HWND hWnd, UINT nBar, LPRECT lpRect,int *nArrowSize,int *nThumbSize,int *nThumbPos);
struct CScrollBarBasic
{
	///
	/// @brief ��־��Ϊ�˴洢�����״̬
	///
    UINT		nFlags;

	///
	/// @brief �Ƿ�ɼ�
	///
    bool		bVisible;

	///
	/// @brief ϵͳ��Ϣ (range, position, page size ��)
	///
    SCROLLINFO	sysInfo; 


    union
    {
        struct
        {
			///
			/// @brief top/left״̬
			///
            CPE::ScrollBarState			nArrowState1;	

			///
			/// @brief bot/right״̬
			///
            CPE::ScrollBarState			nArrowState2;		
        };

        struct
        {
			///
			/// @brief top״̬
			///
            CPE::ScrollBarState			nTopArrowState;	

			///
			/// @brief bot״̬
			///
            CPE::ScrollBarState			nBotArrowState;		
        };

        struct
        {
			///
			/// @brief left״̬
			///
            CPE::ScrollBarState			nLeftArrowState;	
			
			///
			/// @brief right״̬
			///
            CPE::ScrollBarState			nRightArrowState;		
        };
    };

	///
	/// @brief ����״̬
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
	/// @brief ˮƽ����������
	///
    CScrollBarBasic m_hBar; 

	///
	/// @brief ��ֱ����������
	///
    CScrollBarBasic m_vBar;
	
	///
	/// @brief ��������׷��
	///
    bool	m_bEnableThumbTracking;

	///
	/// @brief �Ƿ�֧��WS_EX_LEFTSCROLLBAR���
	///
    bool	m_bLeftScrollbar;


    ///
    /// @brief ��ʹ��oldproc��
	///        �˲�����ʱδʹ��
    ///
    bool m_bPreventStyleChange;

	///
	/// @brief ˮƽ������λ�þ���
	///
    CRect			m_rectHScroll;

	///
	/// @brief ��ֱ������λ�þ���
	///
    CRect			m_rectVScroll;

	///
	/// @brief �������
	///
    CPE::ScrollBarHitTest	m_hitTest;

	///
	/// @brief ����׷�ٻ���
	///
    bool			m_bDrawTrackingBar;

	///
	/// @brief ׷��λ��
	///
    int				m_nTrackingPos;

	///
	/// @brief ׷�ٵ�ֵ
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
	 * @brief ��ȡ����������
	 * @param 
	 * @return ���������������
	 * @note 
	 */
    //static CScrollBarCtrlSkin&  GetInstance( );

	void LoadSkin( const CSkinConfig* pConfig );
	/*!
	 * @brief ����ˮƽ������
	 * @param hWnd ����
	 * @param pParam ����������
	 * @return 
	 * @note 
	 */
    void DrawHScrollBar( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam, bool bIsControl = false  );

	/*!
	 * @brief ���ƴ�ֱ������
	 * @param hWnd ����
	 * @param pParam ����������
	 * @return 
	 * @note
	 */
    void DrawVScrollBar( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam, bool bIsControl = false );

	/*!
	 * @brief ����sizing��
	 * @param hWnd ����
	 * @param r ����
	 * @return 
	 * @note
	 */
    void DrawSizing( HWND hWnd, const CRect& r );

	/*!
	 * @brief ���������¼�׷��
	 * @param hWnd ����
	 * @param pParam ����������
	 * @param nType
	 * @param ptCur �������
	 * @return 
	 * @note
	 */
    void TrackScrollBar(
            HWND hWnd,
            CScrollBarCtrlParameterRefPtr pParam,
            UINT nType, const CPoint& ptCur );
	
	/*!
	 * @brief �����λ�ü��
	 * @param hWnd ����
	 * @param nType ����ľ���
	 * @param ptCur���λ��
	 * @param bDragging �Ƿ������϶�
	 * @return ���λ�ô��ڹ�������λ��
	 * @note
	 */
    CPE::ScrollBarHitTest ScrollHitTest(
		HWND hWnd, UINT nType, const CPoint& ptCur, BOOL bDragging );

	CScrollBarCtrlSkin( );

	
	/*!
	 * @brief ����ˮƽ����
	 * @param hdc hdc
	 * @param r ��������
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
	 * @brief ���ƴ�ֱ����
	 * @param hdc dc
	 * @param r ����ͼ�ľ���
	 * @return 
	 * @note
	 */
    void DrawVBackground( HDC hdc, const CRect& r );
	
	/*!
	 * @brief ���ƴ�ֱ���ϵļ�ͷ
	 * @param hdc dc
	 * @param r λ�þ���
	 * @param nState ״̬
	 * @return 
	 * @note
	 */
    void DrawVTopArrow( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief ���Ƶײ��ļ�ͷ
	 * @param hdc dc
	 * @param r λ�þ���
	 * @param nState ״̬
	 * @return 
	 * @note
	 */
    void DrawVBotArrow( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief ���ƴ�ֱ����
	 * @param hdc dc
	 * @param r λ�þ���
	 * @param nState ״̬
	 * @return 
	 * @note
	 */
    void DrawVThumb( HDC hdc, const CRect& r, int nState );
	
	/*!
	 * @brief ���ƴ�ֱ������
	 * @param hdc dc
	 * @param rtDest λ�þ���
	 * @return 
	 * @note
	 */
    void DrawHScroll( HDC hdc, const CRect& rtDest,int nState );
    void DrawVScroll( HDC hdc, const CRect& rtDest,int nState );

    /**
	 * @brief ����������¼�
	 * @param ptPrevious ��һ�ε����λ��
	 * @param nThumbPos �����λ��
	 * @param nLastClickPos ��һ����갴�µ�λ��
	 * @param nLastMousePos ��һ������¼���λ��
	 */
    void HandleScrollEvent(
            HWND hWnd,
            CScrollBarCtrlParameterRefPtr pParam,
            UINT nType, UINT nEventType, const CPoint& ptCur,
            POINT& ptPrevious,UINT& nThumbPos, INT& nLastClickPos,
            INT& nLastMousePos,
			bool& bIsTrackingVertical );

	
	/*!
	 * @brief ���ƻ���
	 * @param hWnd ����
	 * @param pParam ����������
	 * @param bVertical �Ƿ��Ǵ�ֱ
	 * @param rtPos λ��
	 * @param nArrowSize ��ͷ��С
	 * @param nThumbSize �����С
	 * @return 
	 * @note
	 */
    void DrawMovingThumb(
            HWND hWnd, CScrollBarCtrlParameterRefPtr pParam,
            bool bVertical, const CRect& rtPos,int nArrowSize,int nThumbSize);
private:
	
	/* ��ǰ�������Ĳ��� */
    CScrollBarCtrlParameterRefPtr	m_pParam;
	
	/* ��ǰ���������� */
    HWND							m_hWnd;
	
	/* ˮƽ�����������ͷ��ͼ */
    Gdiplus::Image*					m_bmpHLeftArrow[CPE::SBS_Size];
	
	/* ˮƽ�����������ͷ��ͼ */
    Gdiplus::Image*					m_bmpHRightArrow[CPE::SBS_Size];
	
	/* ˮƽ������������ͼ */
    Gdiplus::Image*					m_bmpHThumb[CPE::SBS_Size];
	
	/*  ˮƽ����������ͼ */
    Gdiplus::Image*					m_bmpHBk;

	/* ��ֱ���������ϼ�ͷ����ͼ */
	Gdiplus::Image*					m_bmpVTopArrow[CPE::SBS_Size];

	/* ��ֱ���������¼�ͷ����ͼ */
	Gdiplus::Image*					m_bmpVBotArrow[CPE::SBS_Size];

	/* ��ֱ���������鱳��ͼ */
	Gdiplus::Image*					m_bmpVThumb[CPE::SBS_Size];

	/* ��ֱ����������ͼ */
	Gdiplus::Image*					m_bmpVBk;

	/* ��ֱ������sizing��ͷ����ͼ */
    Gdiplus::Image*					m_bmpSizing;

};


/*!
 * @brief �������ڹ�����
 * @param hWnd ����
 * @return ����������ָ��
 * @note
 */
CScrollBarCtrlParameterRefPtr CreateHwndScrollBarParam( HWND hWnd );


/*!
 * @brief ����������
 * @param hWnd ��������
 * @param pParam ����������
 * @param point ����ĵ�
 * @return �����ڹ����������λ��
 * @note
 */
UINT OnScrollBarHitTest(
        HWND  hWnd,
        CScrollBarCtrlParameterRefPtr pParam,
        const CPoint& point );


/*!
 * @brief ���ù���������
 * @param hWnd ��������
 * @param pParam ����
 * @return 
 * @note
 */
void SetScrollBarParamVisible(
	HWND hWnd, 
	CScrollBarCtrlParameterRefPtr pParam );


/*!
 * @brief �������ǿͻ�������Ϣ׷��
 * @param hWnd ��������������
 * @param pParam ����������
 * @param bBorder �Ƿ��б߿�
 * @param bCalcValidRects �Ƿ�����Ч�ļ����rect
 * @param lpncsp ����ǿͻ����ߴ���Ϣ�Ĳ���
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
