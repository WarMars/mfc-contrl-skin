#include "stdafx.h"
#include "ScrollBarCtrlSkin.h"
#include "utils.hpp"
#include "ImageManager.h"
#include "GlobalSkinUtil.h"

#ifdef USING_CONFIG_FILE
#include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE

namespace GlobalSkin
{
namespace DynamicParam
{
static const TCHAR szBarDynamicParamter[] = TEXT("szBarDynamicParamter");
bool GetScrollRect( HWND hWnd, UINT nBar, LPRECT lpRect,int *nArrowSize,int *nThumbSize,int *nThumbPos);


CScrollBarCtrlParameterRefPtr CreateHwndScrollBarParam( HWND hWnd )
{
    CScrollBarCtrlParameterRefPtr pParam = new CScrollBarCtrlParameterRef;
	
	/* 获取水平滚动条信息 */
    pParam ->m_hBar.nArrowState1 = CPE::SBS_Normal;
    pParam ->m_hBar.nArrowState2 = CPE::SBS_Normal;
    pParam ->m_hBar.nThumbState = CPE::SBS_Normal;

    SCROLLINFO * pScrollInfo = &pParam ->m_hBar.sysInfo;
    pScrollInfo ->cbSize = sizeof(SCROLLINFO);
    pScrollInfo ->fMask  = SIF_ALL;
    GetScrollInfo( hWnd, SB_HORZ,  pScrollInfo );

	
	/* 垂直滚动条信息 */
    pParam ->m_vBar.nArrowState1 = CPE::SBS_Normal;
    pParam ->m_vBar.nArrowState2 = CPE::SBS_Normal;
    pParam ->m_vBar.nThumbState = CPE::SBS_Normal;
    pScrollInfo = &pParam ->m_vBar.sysInfo;
    pScrollInfo ->cbSize = sizeof(SCROLLINFO);
    pScrollInfo ->fMask  = SIF_ALL;
    GetScrollInfo( hWnd, SB_VERT,  pScrollInfo );

	
	/* 设置是否可见 */
    SetScrollBarParamVisible( hWnd, pParam );

    //pParam ->hBar.nArrowLength	 = 0;
    //pParam ->hBar.nArrowWidth	 = 0;
    //pParam ->vBar.nArrowLength	 = 0;
    //pParam ->vBar.nArrowWidth	 = 0;

    pParam ->m_bPreventStyleChange = false;
    return pParam;

}

UINT OnScrollBarHitTest(
        HWND  hWnd,  
		CScrollBarCtrlParameterRefPtr pParam,
		const CPoint& point )
{
    if( !pParam )
    {
        return HTNOWHERE;
    }
    //CRect rectWindow;
    CRect rectClient;
	
	/* 水平滚动条的高度 */
    int nHHeight = GetSystemMetrics(SM_CYHSCROLL);
	
	/* 垂直滚动条的宽度 */
    int nVWidth = GetSystemMetrics(SM_CXVSCROLL);
    //GetWindowRect(&rectWindow);
	
	/* 转换为屏幕坐标 */
    GetClientRect( hWnd, &rectClient);
    ClientToScreen( hWnd, &rectClient);

	
    if(rectClient.PtInRect(point))
    {
		/* 点击了窗口内部 */
        return HTCLIENT;
    }
    if( pParam ->m_vBar.bVisible )
	{
		/* 设置垂直滚动条的位置和大小 */


        if( pParam ->m_bLeftScrollbar )
        {
			
			/* 特殊地：滚动条位于窗口左侧 */
            pParam ->m_rectVScroll.SetRect(
                        rectClient.left - nVWidth,
                        rectClient.top,
                        rectClient.left,rectClient.bottom );
        }
        else
        {
			/* 滚动条位于窗口右侧的一般情况 */
            pParam ->m_rectVScroll.SetRect(
                        rectClient.right,
                        rectClient.top,
                        rectClient.right + nVWidth,
                        rectClient.bottom );
        }

        if( TRUE == pParam ->m_rectVScroll.PtInRect(point))
        {
			/* 点击了滚动条 */
            return HTVSCROLL;
        }
    }
    else if( pParam ->m_hBar.bVisible )
    {
		/* 垂直滚动条可见 */

		/* 设置水平滚动条位于窗口底部 */
        pParam ->m_rectHScroll.SetRect(
                    rectClient.left,
                    rectClient.bottom,
                    rectClient.right,
                    rectClient.bottom + nHHeight);

        if( TRUE == pParam ->m_rectHScroll.PtInRect(point) )
        {
			/* 点击了水平滚动条 */
            return HTHSCROLL;
        }
    }

	
	/* 窗口内部与滚动条都没有被点击 */
    return HTNOWHERE;
}

/**
 * @brief 获取滚动条滑块当前的位置
 * @param infoPtr 滑块信息
 * @param rect 滑块矩形
 * @param vertical 是否是垂直的
 * @param 位置信息
 * @return 返回滑块的位置
 */
static UINT GetScrollThumbValue(
        SCROLLINFO *infoPtr,
        RECT *rect,
        bool vertical,
        INT pos )
{
    INT thumbSize;
	
	/* 滑块的最大滑动范围：垂直滚动条为高度，水平滚动条为宽度 */
    INT pixels = vertical ? rect->bottom-rect->top : rect->right-rect->left;

    if ((pixels -= 2*(
             GetSystemMetrics(SM_CXVSCROLL) -
             CPE::SBP_ArrowThumbOverlap) ) <= 0)
	{
		/* 超出最小范围，则设置为下线 */
        return infoPtr->nMin;
	}

    if ( 0 != infoPtr->nPage )
    {
		/* 当前的位置 */
        thumbSize = MulDiv(pixels,infoPtr->nPage,(infoPtr->nMax-infoPtr->nMin+1));

        if (thumbSize < CPE::SBP_MinThumb)
		{
			/* 不小于最小尺寸 */
            thumbSize = CPE::SBP_MinThumb;
		}
    }
    else
    {
		/* 无page限制，使用默认的尺寸 */
        thumbSize = GetSystemMetrics(SM_CXVSCROLL);
    }
	
    if ((pixels -= thumbSize) <= 0)
    {
		/* 滚动条无法装下滑块 */
        return infoPtr->nMin;
    }

	
	/* 位置信息必须大于0 */
    pos = max( 0, pos - (GetSystemMetrics(SM_CXVSCROLL) -
                         CPE::SBP_ArrowThumbOverlap) );
    if (pos > pixels)
    {
		/* 最大为滚动条最大范围处 */		
        pos = pixels;
    }

	
    if ( 0 == infoPtr->nPage)
    {
		/* 无页信息 */
        pos *= infoPtr->nMax - infoPtr->nMin;
    }
    else
    {
		/* 包含页信息 */
        pos *= infoPtr->nMax - infoPtr->nMin - infoPtr->nPage + 1;
    }
	/* 最小值加上偏移量 */
    return infoPtr->nMin + ((pos + pixels / 2) / pixels);
}
CPE::ScrollBarHitTest CScrollBarCtrlSkin::ScrollHitTest(
        HWND hWnd, UINT nType, const CPoint& ptCur, BOOL bDragging )
{
    m_hWnd = hWnd;
    CPoint ptTemp = ptCur;
    int arrowSize, thumbSize, thumbPos;
    CRect rect;

	/* 获取滚动条位置、2端箭头大小、滑块大小、滑块位置 */
    bool bVertical = GetScrollRect(
                hWnd, nType, &rect,
                &arrowSize, &thumbSize, &thumbPos );

    if ( FALSE == rect.PtInRect( ptTemp ) )
    {
		/* 不在滚动条中 */
        return CPE::SBHT_Nowhere;
    }

    if (bVertical)
    {
        if (ptTemp.y < rect.top + arrowSize)
        {
			/* 在顶部箭头上 */
            return CPE::SBHT_TopArrow;
        }
        if (ptTemp.y >= rect.bottom - arrowSize)
        {
			/* 在底部箭头上 */
            return CPE::SBHT_BottomArrow;
        }
        if ( 0 == thumbPos)
        {
			/* 在顶部滑块上 */
            return CPE::SBHT_TopRect;
        }
        ptTemp.y -= rect.top;
        if (ptTemp.y < thumbPos)
        {
            return CPE::SBHT_TopRect;
        }
        if (ptTemp.y >= thumbPos + thumbSize)
        {
			/* 在底部滑块上 */
            return CPE::SBHT_BottomRect;
        }
    }
    else  // 水平
    {
        if (ptTemp.x < rect.left + arrowSize)
        {
			/* 左侧箭头上 */
            return CPE::SBHT_TopArrow;
        }
        if (ptTemp.x >= rect.right - arrowSize)
        {
			/* 右侧箭头上 */
            return CPE::SBHT_BottomArrow;
        }
        if ( 0 == thumbPos)
        {
			/* 直接左侧的矩形小区域上 */
            return CPE::SBHT_TopRect;
        }
        ptTemp.x -= rect.left;
        if (ptTemp.x < thumbPos)
        {
            return CPE::SBHT_TopRect;
        }
        if (ptTemp.x >= thumbPos + thumbSize)
        {
			/* 右侧小区域上 */
            return CPE::SBHT_BottomRect;
        }
    }
    return CPE::SBHT_Thumb;
}
void SetScrollBarParamVisible( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam )
{
    if( !pParam )
    {
        return;
    }
    long lStyle	= GetWindowLong( hWnd, GWL_STYLE );
    long lExStyle	= GetWindowLong( hWnd,GWL_EXSTYLE);
	
	/* 滚动条是否可见 */
    pParam ->m_hBar.bVisible = (0 !=(lStyle & WS_HSCROLL));

    pParam ->m_vBar.bVisible = ( 0 != (lStyle & WS_VSCROLL) );

    // 检查滚动条是否有WS_EX_LEFTSCROLLBAR风格
    pParam ->m_bLeftScrollbar = (
                0 != (GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_LEFTSCROLLBAR) );

    pParam->m_hBar.nFlags =
            (0!=(lStyle & WS_HSCROLL) )?
                CPE::SBP_Visible:0;

    pParam->m_vBar.nFlags =
            (0!=(lStyle & WS_VSCROLL) )?
                CPE::SBP_Visible:0;
}

void OnNcScrollBar( HWND hWnd,
                    CScrollBarCtrlParameterRefPtr pParam,
                    bool bBorder, bool bCalcValidRects, NCCALCSIZE_PARAMS *lpncsp)
{
    if( !pParam )
    {
        return;
    }
	
	/* 刷新滚动条参数 */
    SetScrollBarParamVisible( hWnd, pParam );

    LPRECT lpRect = &(lpncsp->rgrc[0]);

	
    if( bBorder )
    {//有边框，则去掉边框的细微尺寸
        lpncsp->rgrc[0].left += 1;
        lpncsp->rgrc[0].top += 1;
        lpncsp->rgrc[0].right -= 1;
        lpncsp->rgrc[0].bottom -= 1;

        lpncsp->rgrc[1] = lpncsp->rgrc[0];
    }

    if(pParam ->m_hBar.bVisible )
    {
        if(pParam ->m_hBar.nFlags &
                CPE::SBP_Visible )
        {
			/* 水平滚动条的高度出现偏移 */
            if( lpRect->bottom - lpRect->top > GetSystemMetrics(SM_CYHSCROLL))
			{
				//重置到合适位置
                lpRect->bottom -= GetSystemMetrics(SM_CYHSCROLL);
			}
            pParam ->m_hBar.bVisible = true;
        }
        else
        {
			//TRACE("水平滚动条隐藏(%d).\n",__LINE__ );
            pParam ->m_hBar.bVisible = false;
        }
    }

	/* 垂直滚动条同理操作 */
    if(pParam ->m_vBar.bVisible )
    {
        if(pParam ->m_vBar.nFlags &
                CPE::SBP_Visible)
        {
            if( lpRect->right - lpRect->left >= GetSystemMetrics(SM_CXVSCROLL)){
                if(pParam ->m_bLeftScrollbar )
                {
                    lpRect->left  += GetSystemMetrics(SM_CXVSCROLL);
                }
                else
                {
                    lpRect->right -= GetSystemMetrics(SM_CXVSCROLL);
                }
            }
            pParam ->m_vBar.bVisible = true;
        }
        else
		{
			//TRACE("垂直滚动条隐藏(%d).\n",__LINE__ );
            pParam ->m_vBar.bVisible = false;
        }

    }

}

CScrollBarCtrlSkin::CScrollBarCtrlSkin( )
{

}

void CScrollBarCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		CBitmapRefPtr pBitmap = ImagePool( ).CreateBitmap( 
			TEXT("ui\\skin\\ScrollBar.bmp") );
		const int nXOffsetBase = 0;
		const int nYOffsetBase = 0;

		int nXOffset = 0;
		int nYOffset = 0;
		int nSize = 48;
		int nBkLarge = 240;
		int nBkSmall = 14;
		// <- 箭头
		nXOffset = nXOffsetBase;
		nYOffset = nYOffsetBase + nSize * 3;
		m_bmpHLeftArrow[CPE::SBS_Normal] =
			Util::CreateSubBitmap( pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_bmpHLeftArrow[CPE::SBS_Hover] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpHLeftArrow[CPE::SBS_Pressed] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpHLeftArrow[CPE::SBS_Disabled] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );

		// -> 箭头
		nXOffset = nXOffsetBase;
		nYOffset = nYOffsetBase + nSize * 2;
		m_bmpHRightArrow[CPE::SBS_Normal] =
			Util::CreateSubBitmap( pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_bmpHRightArrow[CPE::SBS_Hover] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpHRightArrow[CPE::SBS_Pressed] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpHRightArrow[CPE::SBS_Disabled] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );

		//  水平滑块
		nXOffset = nXOffsetBase;
		nYOffset = nYOffsetBase + nSize * 4;
		m_bmpHThumb[CPE::SBS_Normal] =
			Util::CreateSubBitmap( pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_bmpHThumb[CPE::SBS_Hover] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpHThumb[CPE::SBS_Pressed] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpHThumb[CPE::SBS_Disabled] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		// 水平背景
		m_bmpHBk = Util::CreateSubBitmap( 
			pBitmap, nXOffsetBase,
			nYOffsetBase + nSize * 6,
			nBkLarge, nBkSmall );

		// Up箭头
		nXOffset = nXOffsetBase;
		nYOffset = nYOffsetBase ;
		m_bmpVTopArrow[CPE::SBS_Normal] =
			Util::CreateSubBitmap( pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_bmpVTopArrow[CPE::SBS_Hover] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpVTopArrow[CPE::SBS_Pressed] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpVTopArrow[CPE::SBS_Disabled] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );

		// down 箭头
		nXOffset = nXOffsetBase;
		nYOffset = nYOffsetBase + nSize;
		m_bmpVBotArrow[CPE::SBS_Normal] =
			Util::CreateSubBitmap( pBitmap, nXOffset,nYOffset,nSize,nSize );
		m_bmpVBotArrow[CPE::SBS_Hover] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpVBotArrow[CPE::SBS_Pressed] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );
		m_bmpVBotArrow[CPE::SBS_Disabled] =
			Util::CreateSubBitmap( pBitmap, nXOffset+=nSize,nYOffset,nSize,nSize );

		//  垂直滑块
		m_bmpVThumb[CPE::SBS_Normal] = m_bmpHThumb[CPE::SBS_Normal] ;
		m_bmpVThumb[CPE::SBS_Hover] = m_bmpHThumb[CPE::SBS_Hover] ;
		m_bmpVThumb[CPE::SBS_Pressed] = m_bmpHThumb[CPE::SBS_Pressed] ;
		m_bmpVThumb[CPE::SBS_Disabled] = m_bmpHThumb[CPE::SBS_Disabled] ;
		// 水平背景
		m_bmpVBk = Util::CreateSubBitmap( 
			pBitmap, nXOffsetBase+nSize*4,nYOffsetBase/* + nSize*5*/,
			nBkSmall, nBkLarge );
		m_bmpSizing =  Util::CreateSubBitmap( 
			pBitmap, nXOffsetBase,nYOffsetBase + nSize*5,nSize,nSize );
		return;
	}

#ifdef USING_CONFIG_FILE
	// <- 箭头
	m_bmpHLeftArrow[CPE::SBS_Normal] = 
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/left/normal"));
	m_bmpHLeftArrow[CPE::SBS_Hover] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/left/hover"));
	m_bmpHLeftArrow[CPE::SBS_Pressed] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/left/pressed"));
	m_bmpHLeftArrow[CPE::SBS_Disabled] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/left/disabled"));

	// -> 箭头
	m_bmpHRightArrow[CPE::SBS_Normal] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/right/normal"));
	m_bmpHRightArrow[CPE::SBS_Hover] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/right/normal"));
	m_bmpHRightArrow[CPE::SBS_Pressed] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/right/normal"));
	m_bmpHRightArrow[CPE::SBS_Disabled] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/arrow/right/normal"));

	//  水平滑块
	m_bmpHThumb[CPE::SBS_Normal] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/thumb/normal") );
	m_bmpHThumb[CPE::SBS_Hover] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/thumb/hover") );
	m_bmpHThumb[CPE::SBS_Pressed] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/thumb/pressed") );
	m_bmpHThumb[CPE::SBS_Disabled] =
		pConfig ->GetBitmap(TEXT("scrollbar/horizontal/thumb/disabled") );
	// 水平背景
	m_bmpHBk = pConfig ->GetBitmap(TEXT("scrollbar/horizontal/background") );

	// Up箭头
	m_bmpVTopArrow[CPE::SBS_Normal] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/top/normal"));
	m_bmpVTopArrow[CPE::SBS_Hover] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/top/hover"));
	m_bmpVTopArrow[CPE::SBS_Pressed] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/top/pressed"));
	m_bmpVTopArrow[CPE::SBS_Disabled] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/top/disabled"));

	// down 箭头
	m_bmpVBotArrow[CPE::SBS_Normal] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/bottom/normal"));
	m_bmpVBotArrow[CPE::SBS_Hover] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/bottom/hover"));
	m_bmpVBotArrow[CPE::SBS_Pressed] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/bottom/pressed"));
	m_bmpVBotArrow[CPE::SBS_Disabled] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/arrow/bottom/disabled"));

	//  垂直滑块
	m_bmpVThumb[CPE::SBS_Normal] = 
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/thumb/normal"));
	m_bmpVThumb[CPE::SBS_Hover] = 
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/thumb/hover"));
	m_bmpVThumb[CPE::SBS_Pressed] = 
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/thumb/pressed"));
	m_bmpVThumb[CPE::SBS_Disabled] =
		pConfig ->GetBitmap(TEXT("scrollbar/vertical/thumb/disabled"));
	// 水平背景
	m_bmpVBk = pConfig ->GetBitmap(TEXT("scrollbar/vertical/background") );
	m_bmpSizing =  pConfig ->GetBitmap(TEXT("scrollbar/sizing") );
#endif

}

bool GetScrollRect( HWND hWnd, UINT nBar, LPRECT lpRect,int *nArrowSize,int *nThumbSize,int *nThumbPos)
{
    CRect rtClient,rtWindow;
    int pixels;
    BOOL vertical;
	
	/* 相对屏幕的坐标信息 */
    GetClientRect( hWnd, &rtClient);
    ClientToScreen( hWnd, &rtClient);
    GetWindowRect( hWnd, &rtWindow);

    switch(nBar)
    {
    case SB_HORZ:
		
		/* 水平滚动条 */
        lpRect->left   = rtClient.left - rtWindow.left;
        lpRect->top    = rtClient.bottom - rtWindow.top;
        lpRect->right  = rtClient.right - rtWindow.left;
        lpRect->bottom = lpRect->top + GetSystemMetrics(SM_CYHSCROLL);

        vertical = FALSE;
        break;

    case SB_VERT:
		
		/* 垂直滚动条 */
        if(( GetWindowLong(hWnd, GWL_EXSTYLE ) & WS_EX_LEFTSCROLLBAR) != 0)
        {
            lpRect->left   = rtClient.left - rtWindow.left - GetSystemMetrics(SM_CXVSCROLL);
        }
        else
        {
            lpRect->left   = rtClient.right - rtWindow.left;
        }
        lpRect->top    = rtClient.top - rtWindow.top;
        lpRect->right  = lpRect->left + GetSystemMetrics(SM_CXVSCROLL);
        lpRect->bottom = rtClient.bottom - rtWindow.top;
        vertical = TRUE;
        break;

    case SB_CTL:
		/* 其它情况 */
        GetClientRect( hWnd, lpRect );
		
		/* 是否是垂直 */
        vertical = (( GetWindowLong( hWnd, GWL_EXSTYLE ) & SBS_VERT) != 0);
        break;

    default:
        return false;
    }


	
	/* 垂直像素数是高，水平是款宽 */
    if (vertical)
    {
        pixels = lpRect->bottom - lpRect->top;
    }
    else
    {
        pixels = lpRect->right - lpRect->left;
    }

	
	/* 比最小值还小 */
    if (pixels <= 2*GetSystemMetrics(SM_CXVSCROLL) +
            CPE::SBP_MinRect )
    {
        if (pixels > CPE::SBP_MinRect )
        {
			//2端的箭头
            *nArrowSize = ( pixels - CPE::SBP_MinRect ) / 2;
        }
        else
        {
			/* 太小就不绘制 */
            *nArrowSize = 0;
        }
        *nThumbPos = *nThumbSize = 0;
    }
    else
    {
        SCROLLINFO info = {0} ;
        info.cbSize = sizeof(SCROLLINFO);
        info.fMask = SIF_ALL;
        GetScrollInfo( hWnd, nBar, &info );

		/* 校准当前位置 */
        if(info.nPos < info.nMin)
            info.nPos = info.nMin;
        if(info.nPos > info.nMax)
            info.nPos = info.nMax;

		/* 计算箭头大小 */
        *nArrowSize = GetSystemMetrics(SM_CXVSCROLL);

		/* 去掉2端箭头 */
        pixels -= (2 * (*nArrowSize -
                        CPE::SBP_ArrowThumbOverlap ) );


        if ( 0 != info.nPage )
        {
			/* 去掉滑块尺寸 */
            *nThumbSize = MulDiv(pixels,info.nPage,(info.nMax - info.nMin+1));
            if (*nThumbSize < CPE:: SBP_MinThumb)
                *nThumbSize = CPE::SBP_MinThumb;
        }
        else
		{
            *nThumbSize = GetSystemMetrics(SM_CXVSCROLL);
		}

		/* 页为超过范围 */
        if( (int) info.nPage >= (info.nMax -info.nMin + 1))
        {
			/* 取消滑块绘制 */
            *nThumbPos = 0;
            *nThumbSize = 0;
            return 0 != vertical;
        }
        if ((pixels -= *nThumbSize ) < 0 )
        {
            /* 矩形太小或者滚动被禁用 */
            *nThumbPos = *nThumbSize = 0;
        }
        else
        {
            INT max = info.nMax - max( info.nPage-1, 0 );
			//计算滑块位置
            if (info.nMin >= max)
			{
                *nThumbPos = *nArrowSize -
                    CPE::SBP_ArrowThumbOverlap;
			}
            else
			{
                *nThumbPos = *nArrowSize -
                    CPE::SBP_ArrowThumbOverlap
                    + MulDiv(pixels, (info.nPos-info.nMin),(max - info.nMin));
			}

        }
    }
    return 0 != vertical;
}
void CScrollBarCtrlSkin::DrawHScrollBar( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam )
{
    if( !pParam )
    {
        return;
    }
    m_hWnd = hWnd;
    m_pParam = pParam;
    HDC hdc = GetWindowDC( hWnd );
    CRect rtWindow;
    GetWindowRect( hWnd, &rtWindow);
    CRect rtPos;
    int nArrowSize;
    int nThumbSize;
    int nThumbPos;
	//获取滚动条的位置、箭头、滑块等信息

    GetScrollRect(hWnd,SB_HORZ,&rtPos,&nArrowSize,&nThumbSize,&nThumbPos);
    HDC hMemDc = hdc;//CreateCompatibleDC( hdc );
    DrawHBackground( hMemDc, rtPos );

	/* 绘制左侧箭头 */
    DrawHLeftArrow(
                hMemDc,
                CRect(rtPos.left,rtPos.top,rtPos.left + nArrowSize,rtPos.bottom),
                pParam ->m_hBar.nArrowState1 );
	/* 绘制右侧箭头 */
    DrawHRightArrow(
                hMemDc,
                CRect(rtPos.right - nArrowSize,rtPos.top,rtPos.right,rtPos.bottom),
                pParam ->m_hBar.nArrowState2 );

	/* 绘制滑块 */
    if( 0 != nThumbSize )
    {
        DrawHThumb(hMemDc,CRect(
                       rtPos.left + nThumbPos,rtPos.top+1,
                       rtPos.left +nThumbPos + nThumbSize,rtPos.bottom-1),
                   pParam ->m_hBar.nThumbState );
    }

    ReleaseDC( hWnd, hdc );
}

void CScrollBarCtrlSkin::DrawVScrollBar( HWND hWnd, CScrollBarCtrlParameterRefPtr pParam )
{
    if( !pParam )
    {
        return;
    }
    m_hWnd = hWnd;
    m_pParam = pParam;
    CRect rtWindow;
    GetWindowRect( hWnd, &rtWindow);
    CRect rtPos;
    int nArrowSize;
    int nThumbSize;
    int nThumbPos;

	/* 获取滚动条位置、尺寸等相关参数 */
    GetScrollRect( hWnd, SB_VERT,&rtPos,&nArrowSize,&nThumbSize,&nThumbPos);

    HDC hdc = GetWindowDC( hWnd );
    HDC hMemDc = hdc;//CreateCompatibleDC( hdc );

	/* 绘制背景 */
    DrawVBackground( hMemDc,rtPos);

	/* 绘制顶部箭头 */
    DrawVTopArrow(
                hMemDc,
                CRect(rtPos.left,rtPos.top,rtPos.right ,rtPos.top + nArrowSize),
                pParam ->m_vBar.nArrowState1 );
	/* 绘制底部箭头 */
    DrawVBotArrow(
                hMemDc,
                CRect(rtPos.left,rtPos.bottom - nArrowSize,rtPos.right,rtPos.bottom),
                pParam ->m_vBar.nArrowState2 );

	/* 绘制滑块 */
    if( 0 != nThumbSize)
    {
        DrawVThumb(
                    hMemDc,
                    CRect(rtPos.left+1,rtPos.top +nThumbPos,rtPos.right -1,rtPos.top + +nThumbPos + nThumbSize),
                    pParam ->m_vBar.nThumbState );
    }

    ReleaseDC( hWnd, hdc );

}

void CScrollBarCtrlSkin::DrawSizing( HWND hWnd, const CRect& r )
{
    HDC hdc = GetWindowDC( hWnd );
	/* 绘制bmp */
    if( m_bmpSizing.valid() )
    {
        HDC hMemDC = CreateCompatibleDC( hdc );
        SelectObject( hMemDC, m_bmpSizing );
        const CSize& szBmp = GetBMPSize( *m_bmpSizing );
        StretchBlt( hdc, r.left, r.top, r.Width(), r.Height(),
                    hMemDC, 0,0, szBmp.cx, szBmp.cy, SRCCOPY );
        DeleteDC( hMemDC );

    }
    else
    {
        HBRUSH hBrush = CreateSolidBrush(
                    GetSysColor( COLOR_BTNFACE ) );
        FillRect( hdc, &r, hBrush );
        DeleteObject( hBrush );
    }


    ReleaseDC( hWnd, hdc );
}
void CScrollBarCtrlSkin::HandleScrollEvent(
        HWND hWnd,
        CScrollBarCtrlParameterRefPtr pParam,
        UINT nType,UINT msg, const CPoint& pt1,
        POINT& ptPrevious,
        UINT& nThumbPos,
        INT& nLastClickPos,
        INT& nLastMousePos,
		bool& bIsTrackingVertical )
{
    CPoint pt = pt1;

    CPE::ScrollBarHitTest hitTest;
    HWND hwndOwner, hwndCtl;
    bool vertical;
    INT arrowSize, thumbSize, thumbPos;
    RECT rect;
//    HDC hdc;

    SCROLLINFO info;
    info.cbSize = sizeof(info);
    info.fMask = SIF_ALL;
	/* 获取滚动条信息 */
    GetScrollInfo( m_hWnd, nType, &info);

	/* 不是左键按下或者没有点击到滚动条，跳过 */
    if (( pParam ->m_hitTest == CPE::SBHT_Nowhere) &&
            ( msg != WM_LBUTTONDOWN) )
    {
        return;
    }

    if ( nType == SB_CTL && 0 !=
         (GetWindowLong( m_hWnd, GWL_STYLE ) & (SBS_SIZEGRIP | SBS_SIZEBOX) ) )
    {
		/* 滚动条上有size-grip和size框 */
        switch(msg)
        {
        case WM_LBUTTONDOWN:
        {
			/* 捕获和记录坐标信息 */
            SetCapture( m_hWnd );
            ptPrevious = pt;
            pParam ->m_hitTest = hitTest =
                    CPE::SBHT_Thumb;
        }
            break;
        case WM_MOUSEMOVE:
        {
			/* 捕获鼠标移动 */
            ::GetClientRect(::GetParent(::GetParent(m_hWnd)),&rect);
            ptPrevious = pt;
        }
            break;
        case WM_LBUTTONUP:
        {
			/* 按键弹起 */
            ReleaseCapture();
            pParam ->m_hitTest = hitTest =
                    CPE::SBHT_Nowhere;
        }
            break;
        case WM_TIMER:
        {
            pt = ptPrevious;
        }
            break;
        }
        return;
    }

	
    //hdc = GetDCEx( m_hWnd, 0, DCX_CACHE |
    //               ( (nType == SB_CTL) ? 0 : DCX_WINDOW));
    //HDC hDC = GetWindowDC( hWnd );

    vertical = GetScrollRect( hWnd, nType, &rect,&arrowSize, &thumbSize, &thumbPos );
    hwndOwner = (nType == SB_CTL) ? GetParent(m_hWnd) : m_hWnd;
    hwndCtl   = (nType == SB_CTL) ? m_hWnd : 0;

    switch(msg)
    {
    case WM_LBUTTONDOWN:  /* Initialise mouse tracking */
        bIsTrackingVertical = vertical;
        pParam ->m_hitTest  = hitTest =
                ScrollHitTest(hWnd, nType, pt, FALSE );
        nLastClickPos  = vertical ? (pt.y - rect.top) : (pt.x - rect.left);
        nLastMousePos  = nLastClickPos;
        nThumbPos = thumbPos;
        ptPrevious = pt;
        if ( nType == SB_CTL &&
             (GetWindowLong(m_hWnd, GWL_STYLE) & WS_TABSTOP) )
        {
            SetFocus( m_hWnd );
        }
        SetCapture( m_hWnd );
        break;

    case WM_MOUSEMOVE:
        hitTest = ScrollHitTest( hWnd, nType, pt, TRUE );
        ptPrevious = pt;
        break;

    case WM_LBUTTONUP:
        hitTest = CPE::SBHT_Nowhere;
        ReleaseCapture();
        break;

    case WM_TIMER:
        pt = ptPrevious;
        hitTest = ScrollHitTest( hWnd, nType, pt, FALSE );
        break;

    default:
        return;  // 不应该发生的情况
    }

    switch( pParam ->m_hitTest)
    {
    case CPE::SBHT_Nowhere: // 没有点击到任何地方
        break;

    case CPE::SBHT_TopArrow:
        if ( bIsTrackingVertical )
        {
            if( pParam ->m_vBar.bVisible )
            {
                pParam ->m_vBar.nArrowState1 =
                        CPE::SBS_Pressed;
                pParam ->m_vBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam ->m_vBar.nThumbState =
                        CPE::SBS_Normal;
                //	DrawVScrollBar(pDC);
                HDC hDC = GetWindowDC( hWnd );
                DrawVTopArrow(
                            hDC,
                            CRect(rect.left,rect.top,rect.right,rect.top + arrowSize),
                            pParam ->m_vBar.nArrowState1 );
                ReleaseDC( hWnd, hDC );
            }
            else
            { // 水平滚动条
                pParam ->m_hBar.nArrowState1 =
                        CPE::SBS_Pressed;
                pParam ->m_hBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam ->m_hBar.nThumbState =
                        CPE::SBS_Normal;
                //	DrawHScrollBar(pDC);
                HDC hDC = GetWindowDC( hWnd );
                DrawHLeftArrow(
                            hDC,
                            CRect(rect.left,rect.top,rect.left + arrowSize,rect.bottom),
                            pParam ->m_hBar.nArrowState1 );
                ReleaseDC( hWnd, hDC );
            }
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_TIMER))
            {
                ::SendMessage( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                               SB_LINEUP, (LPARAM)hwndCtl );
                //TRACE(_T("SendMessage:%d\n"),__LINE__ );
            }

            SetTimer(
                        m_hWnd,
                        CPE::SBP_TimerID,
                        (msg == WM_LBUTTONDOWN) ?
                            CPE::SBP_FirstDelay :
                            CPE::SBP_RepeatDelay,
                        (TIMERPROC)0 );
        }
        else
        {
            if( bIsTrackingVertical )
            {
                pParam ->m_vBar.nArrowState1 =
                        CPE::SBS_Normal;
                pParam ->m_vBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam ->m_vBar.nThumbState =
                        CPE::SBS_Normal;
                DrawVScrollBar( hWnd ,pParam);
            }
            else
            {
                pParam ->m_hBar.nArrowState1 =
                        CPE::SBS_Normal;
                pParam ->m_hBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam ->m_hBar.nThumbState =
                        CPE::SBS_Normal;
                DrawHScrollBar( hWnd, pParam );
            }
            // 关闭监视
            KillTimer( m_hWnd, CPE::SBP_TimerID );
        }
        break;

    case CPE::SBHT_TopRect:
        if( bIsTrackingVertical )
            DrawVScrollBar( hWnd, pParam );
        else
            DrawHScrollBar( hWnd, pParam );
        if ( hitTest == pParam ->m_hitTest )
        {
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_TIMER))
            {
                // 左键按滑块上长按，模拟一次滚动
                SendMessage( hwndOwner,
                             vertical ? WM_VSCROLL : WM_HSCROLL,
                             SB_PAGEUP,
                             (LPARAM)hwndCtl );
               // TRACE(_T("SendMessage:%d\n"),__LINE__ );
            }
            SetTimer( m_hWnd, CPE::SBP_TimerID,
                      (msg == WM_LBUTTONDOWN) ?
                          CPE::SBP_FirstDelay :
                          CPE::SBP_RepeatDelay,
                      (TIMERPROC)0 );
        }
        else
            KillTimer( m_hWnd, CPE::SBP_TimerID );
        break;

    case CPE::SBHT_Thumb:
        if (msg == WM_LBUTTONDOWN)
        {
            if( pParam.valid() )
            {
                pParam ->m_bEnableThumbTracking = true;
                if(vertical)
                {
                    pParam->m_vBar.sysInfo.nTrackPos = pParam->m_vBar.sysInfo.nPos;
                }
                else
                {
                    pParam->m_vBar.sysInfo.nTrackPos = pParam->m_vBar.sysInfo.nPos;
                }
            }
            pParam ->m_bDrawTrackingBar = (0!=nType);
            pParam ->m_nTrackingPos = nThumbPos + nLastMousePos - nLastClickPos;


            pParam ->m_nTrackingValue =
                    GetScrollThumbValue(
                        &info, &rect,vertical,pParam ->m_nTrackingPos );


            if( pParam.valid() )
            {
                if(vertical)
                {
                    pParam->m_vBar.sysInfo.nTrackPos = pParam ->m_nTrackingValue;
                }
                else
                {
                    pParam->m_hBar.sysInfo.nTrackPos = pParam ->m_nTrackingValue;
                }
            }

            if(bIsTrackingVertical)
            {
                pParam->m_vBar.nArrowState1 =
                        CPE::SBS_Normal;
                pParam->m_vBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam->m_vBar.nThumbState =
                        CPE::SBS_Pressed;
                DrawVScrollBar( hWnd, pParam );
            }
            else
            {
                pParam->m_hBar.nArrowState1 =
                        CPE::SBS_Normal;
                pParam->m_hBar.nArrowState2 =
                        CPE::SBS_Normal;
                CPE::SBS_Pressed;
                DrawHScrollBar( hWnd, pParam );
            }

            if ( 0 == pParam ->m_bDrawTrackingBar )
            {
                DrawMovingThumb( hWnd, pParam, vertical, rect,  arrowSize, thumbSize);
            }
        }
        else if (msg == WM_LBUTTONUP)
        {
            if(pParam.valid() )
            {
                pParam->m_bEnableThumbTracking = false;
            }
            if (pParam->m_bDrawTrackingBar)
            {
                DrawMovingThumb(hWnd, pParam, vertical,rect,  arrowSize, thumbSize);
            }
        }
        else // 鼠标移动
        {
            UINT pos;

            //if (!PtInRect( &rect, pt ))
            //{
            ////	pos = lastClickPos;
            //}
            //else
            {
                pos = vertical ? (pt.y - rect.top) : (pt.x - rect.left);
            }
            if ( (pos != nLastMousePos) || (!pParam ->m_bDrawTrackingBar) )
            {
                if (pParam ->m_bDrawTrackingBar)
                {
                    DrawMovingThumb(
                                hWnd, pParam,
                                vertical, rect, arrowSize, thumbSize );
                }
                nLastMousePos = pos;
                pParam ->m_nTrackingPos = nThumbPos + pos - nLastClickPos;

                pParam ->m_nTrackingValue = GetScrollThumbValue(
                            &info, &rect,
                            vertical,
                            pParam ->m_nTrackingPos );
                if( pParam.valid() )
                {
                    if(vertical)
                    {
                        pParam->m_vBar.sysInfo.nTrackPos = pParam ->m_nTrackingValue;
                    }
                    else
                    {
                        pParam->m_hBar.sysInfo.nTrackPos = pParam ->m_nTrackingValue;
                    }
                }
                int nBarType = (vertical ? WM_VSCROLL : WM_HSCROLL );
                {
                    SetScrollPos(hwndOwner,nType,pParam ->m_nTrackingPos, FALSE );
                }
                LRESULT lResult = SendMessage( hwndOwner, nBarType,
                                               MAKEWPARAM( SB_THUMBTRACK, pParam ->m_nTrackingValue ),
                                               (LPARAM)hwndCtl );
                //DWORD dwError = GetLastError( );
                //{

                //    SCROLLINFO info = {0} ;
                //    info.cbSize = sizeof(SCROLLINFO);
                //    info.fMask = SIF_ALL;
                //    GetScrollInfo( hWnd, nType, &info );
                //    TRACE("value:%d|%d,%d,%d,pos:%d(error:%d:%d),hwnd:%s\n",
                //          pParam ->m_nTrackingValue,pParam ->m_nTrackingPos,
                //          info.nPos,info.nTrackPos,pParam ->m_nTrackingPos,dwError,GetLastError(),
                //          NULL != hwndCtl?"true":"false" );
                //}
                if (!pParam ->m_bDrawTrackingBar )
                {
                    DrawMovingThumb( hWnd, pParam, vertical, rect, arrowSize, thumbSize );
                }
            }

        }
        break;

    case CPE::SBHT_BottomRect:
        if( bIsTrackingVertical )
        {
            DrawVScrollBar(hWnd, pParam );
        }
        else
        {
            DrawHScrollBar(hWnd, pParam );
        }
        if ( hitTest == pParam ->m_hitTest )
        {
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_TIMER))
            {
                SendMessage( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                             SB_PAGEDOWN, (LPARAM)hwndCtl );
                //TRACE(_T("SendMessage:%d\n"),__LINE__ );
            }
            SetTimer( m_hWnd, CPE::SBP_TimerID,
                      (msg == WM_LBUTTONDOWN) ? CPE::SBP_FirstDelay :
                                                CPE::SBP_RepeatDelay,
                      (TIMERPROC)0 );
        }
        else
            KillTimer( m_hWnd, CPE::SBP_TimerID );
        break;

    case CPE::SBHT_BottomArrow:
        if ( hitTest == pParam ->m_hitTest )
        {
            if( bIsTrackingVertical )
            {
                pParam ->m_vBar.nArrowState1 =
                        CPE::SBS_Pressed;
                pParam ->m_vBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam ->m_vBar.nThumbState =
                        CPE::SBS_Normal;
                HDC hdc = GetWindowDC( hWnd );
                DrawVBotArrow( hdc,
                               CRect(rect.left,rect.bottom - arrowSize,rect.right,rect.bottom),
                               pParam ->m_vBar.nArrowState1 );
                ReleaseDC( hWnd,hdc );
            }
            else
            {
                pParam ->m_hBar.nArrowState1 =
                        CPE::SBS_Normal;
                pParam ->m_hBar.nArrowState2 =
                        CPE::SBS_Pressed;
                pParam ->m_hBar.nThumbState =
                        CPE::SBS_Normal;
                HDC hdc = GetWindowDC( hWnd );
                DrawHRightArrow(hdc,
                                CRect(rect.right - arrowSize,rect.top,rect.right,rect.bottom),
                                pParam ->m_hBar.nArrowState1 );
                ReleaseDC( hWnd,hdc );
            }

            if ((msg == WM_LBUTTONDOWN) || (msg == WM_TIMER))
            {
                SendMessage( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                             SB_LINEDOWN, (LPARAM)hwndCtl );
                //TRACE(_T("SendMessage:%d\n"),__LINE__ );
            }

            SetTimer( m_hWnd, CPE::SBP_TimerID,
                      (msg == WM_LBUTTONDOWN) ?
                          CPE::SBP_FirstDelay :
                          CPE::SBP_RepeatDelay,
                      (TIMERPROC)0 );
        }
        else
        {
            if( bIsTrackingVertical )
            {
                pParam ->m_vBar.nArrowState1 = CPE::SBS_Normal;
                pParam ->m_vBar.nArrowState2 = CPE::SBS_Normal;
                pParam ->m_vBar.nThumbState = CPE::SBS_Normal;
                DrawVScrollBar(hWnd,pParam);
            }
            else
            {
                pParam ->m_hBar.nArrowState1 = CPE::SBS_Normal;
                pParam ->m_hBar.nArrowState2 = CPE::SBS_Normal;
                pParam ->m_hBar.nThumbState = CPE::SBS_Normal;
                DrawHScrollBar(hWnd,pParam);
            }
            KillTimer( m_hWnd, CPE::SBP_TimerID );
        }
        break;
    }

    if (msg == WM_LBUTTONDOWN)
    {

        if ( hitTest == CPE::SBHT_Thumb )
        {
            int nCurPos = nThumbPos + nLastMousePos - nLastClickPos;
            UINT val = GetScrollThumbValue(
                        &info, &rect, vertical,
                        nCurPos );
            int nBarType = (vertical ? WM_VSCROLL : WM_HSCROLL );
            {
                SetScrollPos(hwndOwner,nType,val, FALSE );
            }
            SendMessage( hwndOwner, nBarType,
                         MAKEWPARAM( SB_THUMBTRACK, val ), (LPARAM)hwndCtl );
            //TRACE(_T("SendMessage:%d\n"),__LINE__ );

            if( bIsTrackingVertical )
            {
                pParam ->m_vBar.nArrowState1 =
                        CPE::SBS_Normal;
                pParam ->m_vBar.nArrowState2 =
                        CPE::SBS_Normal;
                pParam ->m_vBar.nThumbState =
                        CPE::SBS_Pressed;
                DrawVScrollBar(hWnd, pParam );
            }
            else
            {
                pParam ->m_hBar.nArrowState1 = CPE::SBS_Normal;
                pParam ->m_hBar.nArrowState2 = CPE::SBS_Normal;
                pParam ->m_hBar.nThumbState = CPE::SBS_Pressed;
                DrawHScrollBar(hWnd, pParam);
            }

        }
    }

    if (msg == WM_LBUTTONUP)
    {
        hitTest = pParam ->m_hitTest;
        pParam ->m_hitTest = CPE::SBHT_Nowhere; //结束追踪

        if ( CPE::SBHT_Thumb == hitTest )
        {
            int nCurPos = nThumbPos + nLastMousePos - nLastClickPos;
            UINT val = GetScrollThumbValue( &info, &rect, vertical,
                                            nCurPos );
            int nBarType = (vertical ? WM_VSCROLL : WM_HSCROLL);
            {
                SetScrollPos( hwndOwner, nType, val, FALSE );
            }
            SendMessage( hwndOwner, nBarType,
                         MAKEWPARAM( SB_THUMBPOSITION, val ), (LPARAM)hwndCtl );
            {
                DWORD dwError = GetLastError( );
                SCROLLINFO info = {0} ;
                info.cbSize = sizeof(SCROLLINFO);
                info.fMask = SIF_ALL;
                GetScrollInfo( hwndOwner, nType, &info );
                //TRACE("****** value:%d,%d,%d,pos:%d(error:%d,%d)hwnd:%s\n", val,
                //      info.nPos,info.nTrackPos,nCurPos,dwError,GetLastError(),
                //      NULL != hwndCtl?"true":"false" );
            }
        }
        int nLastPos = -1;
        {
            SCROLLINFO info = {0} ;
            info.cbSize = sizeof(SCROLLINFO);
            info.fMask = SIF_ALL;
            GetScrollInfo( hwndOwner, nType, &info );
            //TRACE(_T("SendMessage:%d,%d,%d\n"),
            //      __LINE__,info.nPos,info.nTrackPos );
            nLastPos = info.nPos;
        }
        SendMessage( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                     SB_ENDSCROLL, (LPARAM)hwndCtl );
        {
            SCROLLINFO info = {0} ;
            info.cbSize = sizeof(SCROLLINFO);
            info.fMask = SIF_ALL;
            GetScrollInfo( hwndOwner, nType, &info );
            //TRACE(_T("SendMessage:%d,%d,%d\n"),
            //      __LINE__,info.nPos,info.nTrackPos );
            if( nLastPos != info.nPos )
            {
                SetScrollPos( hwndOwner,nType,nLastPos,FALSE);
            }
        }
    }

    //ReleaseDC( m_hWnd, hdc );
}
void CScrollBarCtrlSkin::TrackScrollBar(
        HWND hWnd,
        CScrollBarCtrlParameterRefPtr pParam,
        UINT nType, const CPoint& ptCur )
{
    if( !pParam )
    {
        return;
    }
    m_hWnd = hWnd;
    m_pParam = pParam;
    MSG msg;
    INT xoffset = 0, yoffset = 0;
    CRect rtClient,rtWindow;
    GetClientRect( hWnd, &rtClient );
    ClientToScreen( hWnd, &rtClient );
    GetWindowRect( hWnd, &rtWindow );
    POINT pt = ptCur;
    if ( nType != SB_CTL)
    {
        xoffset = rtClient.left - rtWindow.left;
        yoffset = rtClient.top - rtWindow.top;

        ::ScreenToClient(m_hWnd, &pt );
        pt.x += xoffset;
        pt.y += yoffset;
    }
    POINT ptPrevious = {0L,0L};
    UINT nThumbPos = 0;
    INT nLastClickPos = 0;
    INT nLastMousePos = 0;
	
	/* tacking中会初始化此值 */
	bool bIsVertical = false;
    HandleScrollEvent( 
		hWnd, pParam, nType,
		WM_LBUTTONDOWN, pt,
		ptPrevious,nThumbPos,
		nLastClickPos,nLastMousePos,
		bIsVertical );

    do
    {
        if (!GetMessage( &msg, 0, 0, 0 )) break;
        if (CallMsgFilter( &msg, MSGF_SCROLLBAR )) continue;
        if (msg.message == WM_LBUTTONUP ||
                msg.message == WM_MOUSEMOVE ||
                (msg.message == WM_TIMER &&
                 msg.wParam ==  CPE::SBP_TimerID))
        {
            pt.x = (short)LOWORD(msg.lParam) + xoffset;
            pt.y = (short)HIWORD(msg.lParam) + yoffset;
            HandleScrollEvent( 
				hWnd,pParam,nType, msg.message, pt,
				ptPrevious, nThumbPos, nLastClickPos, nLastMousePos,
				bIsVertical );
        }
        else
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        if (!IsWindow( m_hWnd ))
        {
            ReleaseCapture();
            break;
        }
    } while (msg.message != WM_LBUTTONUP);
}

void CScrollBarCtrlSkin::DrawHBackground( HDC hdc, const CRect& rtDest )
{
    DrawBmp(hdc,rtDest, m_bmpHBk );
}

void CScrollBarCtrlSkin::DrawHLeftArrow( HDC hdc, const CRect& rtDest,int nState )
{
    if( !DrawBmp(hdc,rtDest,m_bmpHLeftArrow[nState] ) )
    {
        DrawBmp(hdc,rtDest,m_bmpHLeftArrow[0]);
    }

}
void CScrollBarCtrlSkin::DrawHRightArrow( HDC hdc, const CRect& rtDest,int nState )
{
    if(!DrawBmp(hdc,rtDest,m_bmpHRightArrow[nState]))
    {
        DrawBmp(hdc,rtDest,m_bmpHRightArrow[0]);
    }
}
void CScrollBarCtrlSkin::DrawHThumb( HDC hdc, const CRect& rtDest,int nState )
{
    if(!DrawBmp(hdc,rtDest,m_bmpHThumb[nState]))
    {
        DrawBmp(hdc,rtDest,m_bmpHThumb[0]);
    }
}

void CScrollBarCtrlSkin::DrawVTopArrow( HDC hdc, const CRect& rtDest,int nState )
{
    if(!DrawBmp(hdc,rtDest,m_bmpVTopArrow[nState]))
    {
        DrawBmp(hdc,rtDest,m_bmpVTopArrow[0]);
    }
}
void CScrollBarCtrlSkin::DrawVBotArrow( HDC hdc, const CRect& rtDest,int nState )
{
    if(!DrawBmp(hdc,rtDest,m_bmpVBotArrow[nState]))
    {
        DrawBmp(hdc,rtDest,m_bmpVBotArrow[0]);
    }
}
void CScrollBarCtrlSkin::DrawVThumb( HDC hdc, const CRect& rtDest,int nState )
{
    if(!DrawBmp(hdc,rtDest,m_bmpVThumb[nState]))
    {
        DrawBmp(hdc,rtDest,m_bmpVThumb[0]);
    }
}
void CScrollBarCtrlSkin::DrawVBackground( HDC hdc, const CRect& rtDest )
{
    DrawBmp(hdc,rtDest, m_bmpVBk );
}
void CScrollBarCtrlSkin::DrawHScroll( HDC hdc, const CRect& rtDest,int nState )
{
    int nHeight = rtDest.Height();

    CRect rtArrowLeft = CRect(rtDest.left,rtDest.top,rtDest.left + nHeight,rtDest.bottom);
    CRect rtArrowRight = CRect(rtDest.right - nHeight,rtDest.top,rtDest.right,rtDest.bottom);
    DrawHBackground(hdc,rtDest);
    DrawHLeftArrow(hdc,rtArrowLeft,nState);
    DrawHRightArrow(hdc,rtArrowRight,nState);

}
void CScrollBarCtrlSkin::DrawVScroll( HDC hdc, const CRect& rtDest,int nState )
{
    int nWidth = rtDest.Width();

    CRect rtArrowTop = CRect(rtDest.left, rtDest.top,rtDest.right,rtDest.top + nWidth);
    CRect rtArrowBottom = CRect(rtDest.left,rtDest.bottom - nWidth,rtDest.right,rtDest.bottom);
    DrawVBackground(hdc,rtDest);
    DrawVTopArrow(hdc,rtArrowTop,nState);
    DrawVBotArrow(hdc,rtArrowBottom,nState);
}

void CScrollBarCtrlSkin::DrawMovingThumb(
        HWND hWnd, CScrollBarCtrlParameterRefPtr pParam,
        bool bVertical, const CRect& rtPos,int nArrowSize,int nThumbSize)
{
    int pos = pParam ->m_nTrackingPos;
    int max_size;

    if( bVertical )
    {
        max_size = rtPos.bottom - rtPos.top;
    }
    else
    {
        max_size = rtPos.right - rtPos.left;
    }

    max_size -= (nArrowSize- CPE::SBP_ArrowThumbOverlap) + nThumbSize;

    if( pos < (nArrowSize-CPE::SBP_ArrowThumbOverlap) )
    {
        pos = (nArrowSize-CPE::SBP_ArrowThumbOverlap);
    }
    else if( pos > max_size )
    {
        pos = max_size;
    }
    HDC hdc = GetWindowDC( hWnd );
    HDC hMemDC = hdc;// CreateCompatibleDC( hdc );
    // HBITMAP hBmp = CreateCompatibleBitmap( hdc, rtPos.Width(), rtPos.Height() );
    // SelectObject( hMemDC, hBmp );
    if(!bVertical)
    {
        DrawHBackground(hMemDC,rtPos);
        DrawHLeftArrow(hMemDC,
                       CRect(rtPos.left,rtPos.top,rtPos.left + nArrowSize,rtPos.bottom),
                       pParam ->m_hBar.nArrowState1 );
        DrawHRightArrow(hMemDC,CRect(rtPos.right - nArrowSize,rtPos.top,rtPos.right,rtPos.bottom),
                        pParam ->m_hBar.nArrowState2 );
        DrawHThumb(hMemDC,CRect(rtPos.left + pos,rtPos.top+1,rtPos.left +pos + nThumbSize,rtPos.bottom-1),
                   pParam ->m_hBar.nThumbState );
    }
    else
    {
        DrawVBackground(hMemDC,rtPos);
        DrawVTopArrow(hMemDC,CRect(rtPos.left,rtPos.top,rtPos.right,rtPos.top + nArrowSize),
                      pParam ->m_vBar.nArrowState1 );
        DrawVBotArrow(hMemDC,CRect(rtPos.left,rtPos.bottom  - nArrowSize,rtPos.right,rtPos.bottom),
                      pParam ->m_vBar.nArrowState2 );
        DrawVThumb(hMemDC,CRect(rtPos.left+1,rtPos.top + pos,rtPos.right-1 ,rtPos.top +pos + nThumbSize),
                   pParam ->m_vBar.nThumbState );
    }
    // BitBlt( hdc, rtPos.left, rtPos.right, rtPos.Width(),rtPos.Height(),
    // hMemDC, rtPos.Width(),rtPos.Height(), SRCCOPY );
    // DeleteObject( hBmp );
    // DeleteDC( hMemDC );
    ReleaseDC( hWnd, hdc );

    pParam ->m_bDrawTrackingBar = !pParam ->m_bDrawTrackingBar;
}


bool CScrollBarCtrlParameter::IsEnableThumbTracking( ) const
{
	return m_bEnableThumbTracking;
}

void CScrollBarCtrlParameter::SetEnableThumbTracking( bool bEnable )
{
	m_bEnableThumbTracking = bEnable;
}

bool CScrollBarCtrlParameter::IsLeftScrollBar( ) const
{
	return m_bLeftScrollbar;
}

void CScrollBarCtrlParameter::SetLeftScrollBar( bool b )
{
	m_bLeftScrollbar = b;
}

const CScrollBarBasic& CScrollBarCtrlParameter::GetVBar() const
{
    return m_vBar;
}

const CScrollBarBasic& CScrollBarCtrlParameter::GetHBar() const
{
    return m_hBar;
}

const CRect& CScrollBarCtrlParameter::GetHScrollRect() const
{
    return m_rectHScroll;
}

void CScrollBarCtrlParameter::SetHScrollRect(const CRect &rtHScroll)
{
    m_rectHScroll = rtHScroll;
}

const CRect& CScrollBarCtrlParameter::GetVScrollRect() const
{
    return m_rectVScroll;
}

void CScrollBarCtrlParameter::SetVScrollRect(const CRect &rtVScroll)
{
    m_rectVScroll = rtVScroll;
}

CPE::ScrollBarHitTest CScrollBarCtrlParameter::GetHitTest() const
{
    return m_hitTest;
}

void CScrollBarCtrlParameter::setHitTest(const CPE::ScrollBarHitTest &hitTest)
{
    m_hitTest = hitTest;
}

bool CScrollBarCtrlParameter::NeedDrawTrackingBar() const
{
    return m_bDrawTrackingBar;
}

void CScrollBarCtrlParameter::SetNeedDrawTrackingBar(bool bDrawTrackingBar)
{
    m_bDrawTrackingBar = bDrawTrackingBar;
}

int CScrollBarCtrlParameter::GetTrackingPos() const
{
    return m_nTrackingPos;
}

void CScrollBarCtrlParameter::SetTrackingPos(int nTrackingPos)
{
    m_nTrackingPos = nTrackingPos;
}

int CScrollBarCtrlParameter::GetTrackingValue() const
{
    return m_nTrackingValue;
}

void CScrollBarCtrlParameter::SetTrackingValue(int nTrackingValue)
{
    m_nTrackingValue = nTrackingValue;
}

CScrollBarBasic &CScrollBarCtrlParameter::GetHBar()
{
    return m_hBar;
}

CScrollBarBasic &CScrollBarCtrlParameter::GetVBar()
{
    return m_vBar;
}
bool CScrollBarCtrlParameter::IsPreventStyleChange() const
{
    return m_bPreventStyleChange;
}

void CScrollBarCtrlParameter::SetPreventStyleChange(bool value)
{
    m_bPreventStyleChange = value;
}

bool CScrollBarBasic::IsVisible() const
{
    return bVisible;
}

void CScrollBarBasic::SetVisible(bool value)
{
    bVisible = value;
}

const SCROLLINFO &CScrollBarBasic::GetSysInfo() const
{
    return sysInfo;
}

SCROLLINFO &CScrollBarBasic::GetSysInfo()
{
    return sysInfo;
}

CPE::ScrollBarState CScrollBarBasic::GetArrowState1( ) const
{
    return nArrowState1;
}

void CScrollBarBasic::SetArrowState1(CPE::ScrollBarState state )
{
    nArrowState1 = state;
}

CPE::ScrollBarState CScrollBarBasic::GetArrowState2( ) const
{
    return  nArrowState2;
}

void CScrollBarBasic::SetArrowState2(CPE::ScrollBarState state )
{
    nArrowState2 = state;
}

CPE::ScrollBarState CScrollBarBasic::GetTopArrowState( ) const
{
    return nTopArrowState;
}

void CScrollBarBasic::SetTopArrowState(CPE::ScrollBarState state )
{
    nTopArrowState = state;
}

CPE::ScrollBarState CScrollBarBasic::GetBotArrowState( ) const
{
    return nBotArrowState;
}

void CScrollBarBasic::SetBotArrowState(CPE::ScrollBarState state )
{
    nBotArrowState = state;
}

CPE::ScrollBarState CScrollBarBasic::GetLeftArrowState( ) const
{
    return nLeftArrowState;
}

void CScrollBarBasic::SetLeftArrowState(CPE::ScrollBarState state )
{
    nLeftArrowState = state;
}

CPE::ScrollBarState CScrollBarBasic::GetRightArrowState( ) const
{
    return nRightArrowState;
}

void CScrollBarBasic::SetRightArrowState(CPE::ScrollBarState state )
{
    nRightArrowState = state;
}

CPE::ScrollBarState CScrollBarBasic::GetThumbState() const
{
    return nThumbState;
}

void CScrollBarBasic::SetThumbState(CPE::ScrollBarState value)
{
    nThumbState = value;
}

UINT CScrollBarBasic::GetFlags() const
{
    return nFlags;
}

void CScrollBarBasic::SetFlags(const UINT &value)
{
    nFlags = value;
}


}
}


