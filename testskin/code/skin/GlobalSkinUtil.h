#pragma once 
#include <Windows.h>
#include <gdiobj_ptr.hpp>

namespace GlobalSkin
{
	namespace Util
	{
		/*
		 * @brief  ��ʱʹ�õ�HDC��װ
		 */
		class CTempDC 
		{
		public:
			CTempDC( HWND hWnd, HDC hdc):m_hWnd(hWnd),m_hdc(hdc){ }
			inline ~CTempDC( ){ if( *this ){ ReleaseDC(m_hWnd, m_hdc );} }

			
			/*!
			 * @brief  ��ȡ��ǰ��dc
			 * @return dc���
			 * @note
			 */
			inline operator HDC( ){ return m_hdc; }
			
			/*!
			 * @brief  ��ǰdc�Ƿ���Ч
			 * @return ��Ч����true,���򷵻�false
			 * @note
			 */
			inline operator bool( ){ return NULL != m_hWnd && NULL != m_hdc; }
		protected:
			/*
			 * @brief  ����dc��Ӧ�Ĵ��ھ����Ϊ�����ͷ��ͷ�dcʱʹ��
			 */
			HWND m_hWnd;

			/*
			 * @brief  ��ǰ��dc
			 */
			HDC	 m_hdc;
		};

		/**
		 * @brief ��ʱ�Ĵ���dc
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
		 * @brief �ͻ���dc
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
		 * @brief WM_PAINT��Ϣ��dc
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
		 * @brief ������Դ
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
			 * @brief  ��ǰ������������������ݲ����Ļ���
			 */
			HFONT	m_hFont;
		};

		/**
		 * @brief ��ȡ�������λ�ã����û�и����ڣ����ȡ������������
		 */
		class CTempRelativeWindowRect
		{
		public:
			inline CTempRelativeWindowRect(HWND hWnd ){ GetWindowRect(hWnd, &m_rect); }
			inline operator CRect( ) { return m_rect;}
		protected:
			/*
			 * @brief  ���ڵ�����丸���ڵ�λ��
			 */
			CRect	m_rect;
		};

		/** 
		 * @brief ��ȡ�������ڵľ��Դ�С�����Ͻ�����(0,0)
		 */
		class CTempAbsoluteWindowRect:public CTempRelativeWindowRect
		{
		public:
			inline CTempAbsoluteWindowRect(HWND hWnd )
				:CTempRelativeWindowRect(hWnd)
			{
				/* ����ƽ�ƣ�ʹ���Ͻ�����Ϊ(0,0) */
				m_rect.OffsetRect( -m_rect.left, -m_rect.top );
			}
		};

		/*!
		 * @brief ����dc
		 */
		class CTempCompatibleDC
		{
		public:
			inline CTempCompatibleDC( HDC hdc, int cx, int cy,
				DWORD dwRop = SRCCOPY, int nLeft = 0, int nTop = 0 )
			{
				if( NULL == hdc || 0 == cx || 0 == cy )
				{
					/* ��Ч */
					m_hMemDC = NULL;
					return;
				}
				m_hDC = hdc;
				/* ��������dc�Լ�����Ҫ����Դ */
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
				/* ��Ч���ͷ� */
				if( *this )
				{
					BitBlt( m_hDC, m_nLeft, m_nTop, m_nCX, m_nCY,
						m_hMemDC, 0,0, m_dwRop );
					Release( );
				}
			}

			/*!
			 * @brief �ͷŴ˼���dc����Դ
			 * @note ͨ���ⲿֱ�ӶԴ˼���dc���п�Ĺ�դ����ʱ��
			 *		 Ϊ�˱����ظ��Ĺ�դ��������Ҫʹ�ô˺����ͷ���Դ��
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
			 * @brief ��ǰ��dc�Ƿ���Ч
			 * @return ��Ч����true�����򷵻�false
			 * @note 
			 */
			inline operator bool( ) { return NULL != m_hMemDC; }

			/*!
			 * @brief ��ȡ��ǰ��dc
			 * @return dc���
			 * @note ʹ�ô˺���֮ǰ��ͨ��Ҫ�жϵ�ǰdc�Ƿ���Ч
			 */
			inline operator HDC( ){ return m_hMemDC; }
		private:

			/* ԭʼ��dc */
			HDC		m_hDC;
			/* ����dc */
			HDC		m_hMemDC;
			/* ����dc��λͼ */
			HBITMAP	m_hMemBmp;
			/* ��Դ���ݣ����ͷ���Դ֮ǰ��Ҫ�ָ��ɵ���Դ���� */
			HGDIOBJ	m_hOldBmp;
			/* BitBlt�Ĳ�����ʽ */
			DWORD	m_dwRop;
			/* ����dc�Ŀ�� */
			int		m_nCX;
			/* ����dc�ĸ߶� */
			int		m_nCY;
			/* ���Ͻ�x���� */
			int		m_nLeft;
			/* ���Ͻ�Y���� */
			int		m_nTop;

		};
		/** 
		 * @brief ����λͼ����HRGN
		 * @param hBitmap λͼ���
		 * @param clrMask ������ɫ
		 * @return ִ�гɹ�������RGN�ľ�������򷵻�NULL
		 */
		HRGN   CreateRegionByBitmap( HBITMAP hBitmap, COLORREF clrMask );


		/** 
		 * @brief ���һƬ����
		 * @param hdc ����
		 * @param rect �������
		 * @param clr ��ɫ
		 */
		void FillSolid( HDC hdc, const CRect& rect, COLORREF clr );
		void FillSolid( HDC hdc, LONG lLeft, LONG lTop, LONG lWidth, LONG lHeight,
			COLORREF clr );

		/** 
		 * @brief ����3dЧ��
		 * @param hdc����
		 * @param rect Ŀ���������
		 * @param clrTopLeft ���Ͻǵ���ɫ
		 * @param clrBottomRight ���½ǵ���ɫ
		 */
		void   Draw3D( HDC hdc, const CRect& rect,
			COLORREF clrTopLeft, COLORREF clrBottomRight );

		/** 
		 * @brief ʹ����ɫ���ָ������
		 * @param hdc
		 * @param rect ������
		 * @param clr ��ɫֵ
		 */
		bool FillColor( HDC hdc, const CRect& rect, COLORREF clr );

		/** 
		 * @brief ʹ�����Խ�����ɫ����ƶ�����
		 * @param hdc
		 * @param rect ������
		 * @param crFrom ��ʼ��ɫ
		 * @param crTo ��ֹ��ɫ
		 * @param �Ƿ���ˮƽ����������
		 @ retrun ִ�гɹ�����true,���򷵻�false
		 */
		bool FillColor( HDC hdc, const RECT& rect,
			COLORREF crFrom, COLORREF crTo, bool bIsHorizontal );

		/** 
		 * @brief ��ȡָ���ı��������£�ʵ�ʵĿ��
		 * @param hWnd ���崰��
		 * @param �����ı�
		 * @return ����ռ�õ����ظ߶�ֵ
		 */
		int    GetFontLength( HWND hWnd, LPCTSTR lpszText );

		/** 
		 * @brief ����λͼ��ָ�����򴴽���λͼ
		 * @param pBitmap λͼ
		 * @param nLeft,nTop,nWidth, nHeightȷ���������
		 * @return λͼָ��
		 */
		CBitmapRefPtr CreateSubBitmap( 
			CBitmapRefPtr pBitmap, 
			int nLeft=-1, int nTop=-1, int nWidth=-1 ,int nHeight=-1 );

		/** 
		 * @brief ��ȡλͼָ�����ص����ɫֵ
		 * @param pBitmapλͼ
		 * @param nX,nYȷ�����ص��Ŀ��
		 * @return ��ɫֵ
		 */
		COLORREF GetBitmapPixelColor( 
			CBitmapRefPtr pBitmap, int nX=-1, int nY=-1 );

		/** 
		 * @brief ���2������ɫ��
		 * @param clrFrom Դ��ɫ��
		 * @param clrTo Ŀ����ɫ
		 * @param nAlpha �������,ͨ��Ϊ͸����
		 * @retrun ��Ϻ����ɫ
		 */
		COLORREF BlendColor( COLORREF clrFrom ,COLORREF clrTo, unsigned char nAlpha );
		COLORREF BlendColor( COLORREF clrFrom ,COLORREF clrTo, float fAlpha );

		/** 
		 * @brief ��ɫ�˷�
		 * @param color ��ʼ��ɫ
		 * @param fCoef ϵ��
		 * @return �����ɫ
		 */
		COLORREF ColorMultiply( COLORREF color, float fCoef );
		
		/** 
		 * @brief �Ƿ���xp���ϵ�ϵͳ
		 * @return xp���ϵ�ϵͳ����true�����򷵻�false.
		 */
		bool IsGreaterThanXP( );

		/** 
		 * @brief ��͸���ȵ�BitBlt
		 */
		bool TransparentBitBlt(
			HDC hDstDC, int nDstX, int nDstY, int nDstWidth, int nDstHeight,
			HDC hSrcDC, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight,
			COLORREF clrTransparent );
		bool TransparentBitBlt(
			HDC hDstDC, int nDstX, int nDstY, int nDstWidth, int nDstHeight,
			HDC hSrcDC, int nSrcX, int nSrcY, COLORREF clrTransparent );

		/** 
		 * @brief ȡ���ƶ�����ɫֵ
		 * @param hSrcDC Դdc,
		 * @param clrSrc Դ��ɫ,
		 * @param hDstDc Ŀ��dc,
		 * @param clrDst Ŀ����ɫ,
		 * @param rect Ŀ�����
		 * @param pRectClip �ü�����
		 */
		bool ReplaceColor( HDC hSrcDC, COLORREF clrSrc, HDC hDstDc,COLORREF crlDst,
			const RECT& rect, LPRECT pRectClip = NULL );

		
		/*!
		 * @brief ������image
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
		 * @brief �ڼ��а�����ʾλͼ��
		 * @note ����ʱʹ��
		 */
		void ShowBitmapInClipboard( HBITMAP hBitmap );
		void ShowCurBitmapInClipboard( HDC hdc );
	}
}

