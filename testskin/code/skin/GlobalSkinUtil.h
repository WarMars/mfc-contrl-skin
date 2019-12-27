#pragma once 
#include <Windows.h>
#include <gdiobj_ptr.hpp>

namespace GlobalSkin
{
	namespace Util
	{
		/*
		 * @brief  临时使用的HDC封装
		 */
		class CTempDC 
		{
		public:
			CTempDC( HWND hWnd, HDC hdc):m_hWnd(hWnd),m_hdc(hdc){ }
			inline ~CTempDC( ){ if( *this ){ ReleaseDC(m_hWnd, m_hdc );} }

			
			/*!
			 * @brief  获取当前的dc
			 * @return dc句柄
			 * @note
			 */
			inline operator HDC( ){ return m_hdc; }
			
			/*!
			 * @brief  当前dc是否有效
			 * @return 有效返回true,否则返回false
			 * @note
			 */
			inline operator bool( ){ return NULL != m_hWnd && NULL != m_hdc; }
		protected:
			/*
			 * @brief  保存dc对应的窗口句柄，为了在释放释放dc时使用
			 */
			HWND m_hWnd;

			/*
			 * @brief  当前的dc
			 */
			HDC	 m_hdc;
		};

		/**
		 * @brief 临时的窗口dc
		 */
		class CTempWindowDC:public CTempDC
		{
		public:
			inline CTempWindowDC(HWND hWnd )
				:CTempDC(hWnd,( (NULL != hWnd)?GetWindowDC(hWnd):NULL) )
			{
			}

		};

		/*!
		 * @brief 客户区dc
		 */
		class CTempClientDC: public CTempDC
		{
		public:
			inline CTempClientDC(HWND hWnd )
				:CTempDC(hWnd,( (NULL != hWnd)?GetDC(hWnd):NULL) )
			{
			}
		};

		/** 
		 * @brief WM_PAINT消息的dc
		 */
		class CTempPaintDC
		{
		public:
			inline CTempPaintDC(HWND hWnd )
			{
				m_hWnd = hWnd;
				m_hdc = ( (NULL != m_hWnd)?BeginPaint(m_hWnd,&m_ps):NULL);
			}
			inline ~CTempPaintDC( ){ if( *this ){ EndPaint(m_hWnd, &m_ps );} }
			inline operator HDC( ){ return m_hdc; }
			inline operator bool( ){ return NULL != m_hWnd && NULL != m_hdc; }
		private:
			HWND	m_hWnd;
			HDC		m_hdc;
			PAINTSTRUCT	m_ps;
		};

		/*!
		 * @brief 字体资源
		 */
		class CHFontWraper
		{
		public:
			inline CHFontWraper( ) { m_hFont = NULL; }
			inline ~CHFontWraper( ) { if( *this ){ DeleteObject( m_hFont); } }
			inline HFONT Release( ){ HFONT tmp = m_hFont; m_hFont = NULL; return tmp; }
			inline HFONT& HFontRef( ) { return m_hFont; }
			inline operator HFONT&( ) {return m_hFont;}
			inline operator bool( ) { return NULL != m_hFont; }
		private:
			/*
			 * @brief  当前的字体对象，整个类数据操作的基础
			 */
			HFONT	m_hFont;
		};

		/**
		 * @brief 获取窗口相对位置，如果没有父窗口，则获取相对桌面的坐标
		 */
		class CTempRelativeWindowRect
		{
		public:
			inline CTempRelativeWindowRect(HWND hWnd ){ GetWindowRect(hWnd, &m_rect); }
			inline operator CRect( ) { return m_rect;}
		protected:
			/*
			 * @brief  窗口的相对其父窗口的位置
			 */
			CRect	m_rect;
		};

		/** 
		 * @brief 获取整个窗口的绝对大小，左上角总是(0,0)
		 */
		class CTempAbsoluteWindowRect:public CTempRelativeWindowRect
		{
		public:
			inline CTempAbsoluteWindowRect(HWND hWnd )
				:CTempRelativeWindowRect(hWnd)
			{
				/* 矩形平移，使左上角坐标为(0,0) */
				m_rect.OffsetRect( -m_rect.left, -m_rect.top );
			}
		};

		/*!
		 * @brief 兼容dc
		 */
		class CTempCompatibleDC
		{
		public:
			inline CTempCompatibleDC( HDC hdc, int cx, int cy,
				DWORD dwRop = SRCCOPY, int nLeft = 0, int nTop = 0 )
			{
				if( NULL == hdc || 0 == cx || 0 == cy )
				{
					/* 无效 */
					m_hMemDC = NULL;
					return;
				}
				m_hDC = hdc;
				/* 创建兼容dc以及它需要的资源 */
				m_hMemDC = CreateCompatibleDC(hdc);
				m_hMemBmp = CreateCompatibleBitmap( hdc, cx, cy );
				m_hOldBmp = SelectObject( m_hMemDC, m_hMemBmp );
				m_dwRop = dwRop;
				m_nCX = cx;
				m_nCY = cy;
				m_nLeft = nLeft;
				m_nTop = nTop;
			}
			~CTempCompatibleDC( )
			{
				/* 有效则释放 */
				if( *this )
				{
					BitBlt( m_hDC, m_nLeft, m_nTop, m_nCX, m_nCY,
						m_hMemDC, 0,0, m_dwRop );
					Release( );
				}
			}

			/*!
			 * @brief 释放此兼容dc的资源
			 * @note 通常外部直接对此兼容dc进行块的光栅操作时，
			 *		 为了避免重复的光栅操作，需要使用此函数释放资源。
			 */
			inline void Release( )
			{ 
				if(*this)
				{
					SelectObject(m_hMemDC,m_hOldBmp);
					DeleteDC( m_hMemDC );
					DeleteObject( m_hMemBmp );
					m_hMemDC = NULL;
					m_hMemBmp = NULL;
					m_hOldBmp = NULL;
				}
			}

			/*!
			 * @brief 当前的dc是否有效
			 * @return 有效返回true，否则返回false
			 * @note 
			 */
			inline operator bool( ) { return NULL != m_hMemDC; }

			/*!
			 * @brief 获取当前的dc
			 * @return dc句柄
			 * @note 使用此函数之前，通常要判断当前dc是否有效
			 */
			inline operator HDC( ){ return m_hMemDC; }
		private:

			/* 原始的dc */
			HDC		m_hDC;
			/* 兼容dc */
			HDC		m_hMemDC;
			/* 兼容dc的位图 */
			HBITMAP	m_hMemBmp;
			/* 资源备份，在释放资源之前需要恢复旧的资源设置 */
			HGDIOBJ	m_hOldBmp;
			/* BitBlt的操作方式 */
			DWORD	m_dwRop;
			/* 兼容dc的宽度 */
			int		m_nCX;
			/* 兼容dc的高度 */
			int		m_nCY;
			/* 左上角x坐标 */
			int		m_nLeft;
			/* 左上角Y坐标 */
			int		m_nTop;

		};
		/** 
		 * @brief 根据位图创建HRGN
		 * @param hBitmap 位图句柄
		 * @param clrMask 掩码颜色
		 * @return 执行成功，返回RGN的句柄，否则返回NULL
		 */
		HRGN   CreateRegionByBitmap( HBITMAP hBitmap, COLORREF clrMask );


		/** 
		 * @brief 填充一片区域
		 * @param hdc 画笔
		 * @param rect 区域矩形
		 * @param clr 颜色
		 */
		void FillSolid( HDC hdc, const CRect& rect, COLORREF clr );
		void FillSolid( HDC hdc, LONG lLeft, LONG lTop, LONG lWidth, LONG lHeight,
			COLORREF clr );

		/** 
		 * @brief 绘制3d效果
		 * @param hdc画布
		 * @param rect 目标矩形区域
		 * @param clrTopLeft 左上角的颜色
		 * @param clrBottomRight 右下角的颜色
		 */
		void   Draw3D( HDC hdc, const CRect& rect,
			COLORREF clrTopLeft, COLORREF clrBottomRight );

		/** 
		 * @brief 使用颜色填充指定区域
		 * @param hdc
		 * @param rect 填充矩形
		 * @param clr 颜色值
		 */
		bool FillColor( HDC hdc, const CRect& rect, COLORREF clr );

		/** 
		 * @brief 使用线性渐变颜色填充制定区域
		 * @param hdc
		 * @param rect 填充矩形
		 * @param crFrom 起始颜色
		 * @param crTo 终止颜色
		 * @param 是否是水平方向填充矩形
		 @ retrun 执行成功返回true,否则返回false
		 */
		bool FillColor( HDC hdc, const RECT& rect,
			COLORREF crFrom, COLORREF crTo, bool bIsHorizontal );

		/** 
		 * @brief 获取指定文本在字体下，实际的宽度
		 * @param hWnd 字体窗口
		 * @param 字体文本
		 * @return 字体占用的像素高度值
		 */
		int    GetFontLength( HWND hWnd, LPCTSTR lpszText );

		/** 
		 * @brief 创建位图的指定区域创建子位图
		 * @param pBitmap 位图
		 * @param nLeft,nTop,nWidth, nHeight确定区域矩形
		 * @return 位图指针
		 */
		CBitmapRefPtr CreateSubBitmap( 
			CBitmapRefPtr pBitmap, 
			int nLeft=-1, int nTop=-1, int nWidth=-1 ,int nHeight=-1 );

		/** 
		 * @brief 获取位图指定像素点的颜色值
		 * @param pBitmap位图
		 * @param nX,nY确定像素点的目标
		 * @return 颜色值
		 */
		COLORREF GetBitmapPixelColor( 
			CBitmapRefPtr pBitmap, int nX=-1, int nY=-1 );

		/** 
		 * @brief 混合2种类颜色，
		 * @param clrFrom 源颜色，
		 * @param clrTo 目标颜色
		 * @param nAlpha 混合因子,通常为透明度
		 * @retrun 混合后的颜色
		 */
		COLORREF BlendColor( COLORREF clrFrom ,COLORREF clrTo, unsigned char nAlpha );
		COLORREF BlendColor( COLORREF clrFrom ,COLORREF clrTo, float fAlpha );

		/** 
		 * @brief 颜色乘法
		 * @param color 初始颜色
		 * @param fCoef 系数
		 * @return 结果颜色
		 */
		COLORREF ColorMultiply( COLORREF color, float fCoef );
		
		/** 
		 * @brief 是否是xp以上的系统
		 * @return xp以上的系统返回true，否则返回false.
		 */
		bool IsGreaterThanXP( );

		/** 
		 * @brief 带透明度的BitBlt
		 */
		bool TransparentBitBlt(
			HDC hDstDC, int nDstX, int nDstY, int nDstWidth, int nDstHeight,
			HDC hSrcDC, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight,
			COLORREF clrTransparent );
		bool TransparentBitBlt(
			HDC hDstDC, int nDstX, int nDstY, int nDstWidth, int nDstHeight,
			HDC hSrcDC, int nSrcX, int nSrcY, COLORREF clrTransparent );

		/** 
		 * @brief 取代制定的颜色值
		 * @param hSrcDC 源dc,
		 * @param clrSrc 源颜色,
		 * @param hDstDc 目标dc,
		 * @param clrDst 目标颜色,
		 * @param rect 目标矩形
		 * @param pRectClip 裁剪矩形
		 */
		bool ReplaceColor( HDC hSrcDC, COLORREF clrSrc, HDC hDstDc,COLORREF crlDst,
			const RECT& rect, LPRECT pRectClip = NULL );

		
		/*!
		 * @brief 创建子image
		 * @param 
		 * @return 
		 * @note
		 */
		Gdiplus::Image* CreateSubImage(
			Gdiplus::Image *pSrcImg,int nLeft, int nTop, int Width, int Height);

		bool DrawImage( HDC hdc, Gdiplus::Image* pImage, const RECT& rect );
		bool DrawImage( HDC hdc, const RECT& rect, Gdiplus::Image* pImage );
		bool FillColor( HDC hdc, const Gdiplus::Color& color = Gdiplus::Color::Transparent );

		HWND GetChildWindow( HWND hParent, LPCTSTR lpszChildWindowClassName );

		/** 
		 * @brief 在剪切板上显示位图。
		 * @note 调试时使用
		 */
		void ShowBitmapInClipboard( HBITMAP hBitmap );
		void ShowCurBitmapInClipboard( HDC hdc );
	}
}

