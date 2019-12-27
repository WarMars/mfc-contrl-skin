#include "stdafx.h"
#include "GlobalSkinUtil.h"
#include <vector>
#include <map>
namespace GlobalSkin
{
	namespace Util
	{
		/** 
		 * @license Դ��΢�����MSDN��ʾ������ copyright@microsoft
		 */
		HRGN   CreateRegionByBitmap( HBITMAP hBitmap, COLORREF color )
		{
			if( NULL == hBitmap )
			{
				return NULL;
			}
			BITMAP bmp = { 0 };
			::GetObject( hBitmap, sizeof(BITMAP), &bmp );
			LPBITMAPINFO bi = (LPBITMAPINFO) new BYTE[ sizeof(BITMAPINFO) + 8 ];

			memset( bi, 0, sizeof(BITMAPINFO) + 8 );
			bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			int m_dwWidth	= bmp.bmWidth;
			int m_dwHeight	= bmp.bmHeight;
			
			HDC dc = CreateIC( _TEXT("DISPLAY"),NULL,NULL,NULL );
			// ��ȡbitmap����ϸ��Ϣ
			DWORD res = GetDIBits( dc, hBitmap, 0, bmp.bmHeight, 0, bi, DIB_RGB_COLORS );
			LPBYTE pBits = new BYTE[ bi->bmiHeader.biSizeImage + 4 ];
			if ( bi->bmiHeader.biBitCount == 8 )
			{
				// ����ɫ��������Ӧ����β��������ɫ��
				LPBITMAPINFO old_bi = bi;
				
				bi = (LPBITMAPINFO)new char[ sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD) ];
				memcpy( bi, old_bi, sizeof(BITMAPINFO) );
				// �ͷžɵ�
				delete []old_bi;
			}
			// ��ȡλͼ��ͷ��
			BITMAPINFOHEADER& bih = bi->bmiHeader;
			// ��ȡ��ɫ��
			LPDWORD clr_tbl = (LPDWORD)&bi->bmiColors;
			res = GetDIBits( dc, hBitmap, 0, bih.biHeight, pBits, bi, DIB_RGB_COLORS );
			DeleteDC( dc );

			// ��ȡ��ɫ��Ϣ
			BITMAP bm;
			::GetObject( hBitmap, sizeof(BITMAP), &bm );
			LPBYTE pClr = (LPBYTE)&color;
			BYTE tmp = pClr[0]; pClr[0] = pClr[2]; pClr[2] = tmp;
			// 16λ(5-6-5)ת��
			if ( bih.biBitCount == 16 )
			{
				color = ((DWORD)(pClr[0] & 0xf8) >> 3) |
					((DWORD)(pClr[1] & 0xfc) << 3) |
					((DWORD)(pClr[2] & 0xf8) << 8);
			}

			const DWORD RGNDATAHEADER_SIZE	= sizeof(RGNDATAHEADER);

			// ���ӵľ���
			const DWORD ADD_RECTS_COUNT		= 40;
			// ���ص�bit��Ŀ
			BYTE	Bpp = bih.biBitCount >> 3;

			// ��pBits����DOWRD�����,��bmp�ṹ����bmWidthBytes��word�����
			DWORD m_dwAlignedWidthBytes = (bmp.bmWidthBytes & ~0x3) + 
				(!!(bmp.bmWidthBytes & 0x3) << 2);
			// ���һ��
			LPBYTE	pColor = pBits + (bih.biHeight - 1) * m_dwAlignedWidthBytes;
			// ����ǰһ�е�ƫ����
			DWORD	dwLineBackLen = m_dwAlignedWidthBytes + bih.biWidth * Bpp;
			// �����еľ�����Ŀ
			DWORD	dwRectsCount = bih.biHeight;
			// maskͼ�еĵ�ǰλ��
			INT		i, j;
			// ��ǰɨ����е����λ��
			INT		first = 0;
			// mask���ҵ���λ��
			bool	wasfirst = false;
			// ��ǰ��ͼ��mask��ɫ�ĳ�ʼλ��
			bool	ismask;	

			// allocate memory for region data
			// region data here is set of regions that are rectangles with height 1 pixel (scan line)
			// that's why first allocation is <bm.biHeight> RECTs - number of scan lines in image
			RGNDATAHEADER* pRgnData = 
				(RGNDATAHEADER*)new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
			// get pointer to RECT table
			LPRECT pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
			// zero region data header memory (header  part only)
			memset( pRgnData, 0, RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) );
			// fill it by default
			pRgnData->dwSize	= RGNDATAHEADER_SIZE;
			pRgnData->iType		= RDH_RECTANGLES;

			for ( i = 0; i < bih.biHeight; i++ )
			{
				for ( j = 0; j < bih.biWidth; j++ )
				{
					// get color
					switch ( bih.biBitCount )
					{
					case 8:
						ismask = (clr_tbl[ *pColor ] != color);
						break;
					case 16:
						ismask = (*(LPWORD)pColor != (WORD)color);
						break;
					case 24:
						ismask = ((*(LPDWORD)pColor & 0x00ffffff) != color);
						break;
					case 32:
						ismask = (*(LPDWORD)pColor != color);
					}
					// shift pointer to next color
					pColor += Bpp;
					// place part of scan line as RECT region if transparent color found after mask color or
					// mask color found at the end of mask image
					if ( wasfirst )
					{
						if ( !ismask )
						{
							// save current RECT
							pRects[ pRgnData->nCount++ ] = CRect( first, i, j, i + 1 );
							// if buffer full reallocate it with more room
							if ( pRgnData->nCount >= dwRectsCount )
							{
								dwRectsCount += ADD_RECTS_COUNT;
								// allocate new buffer
								LPBYTE pRgnDataNew = new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
								// copy current region data to it
								memcpy( pRgnDataNew, pRgnData, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT) );
								// delte old region data buffer
								delete pRgnData;
								// set pointer to new regiondata buffer to current
								pRgnData = (RGNDATAHEADER*)pRgnDataNew;
								// correct pointer to RECT table
								pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
							}
							wasfirst = false;
						}
					}
					else if ( ismask )		// set wasfirst when mask is found
					{
						first = j;
						wasfirst = true;
					}
				}

				if ( wasfirst && ismask )
				{
					// save current RECT
					pRects[ pRgnData->nCount++ ] = CRect( first, i, j, i + 1 );
					// if buffer full reallocate it with more room
					if ( pRgnData->nCount >= dwRectsCount )
					{
						dwRectsCount += ADD_RECTS_COUNT;
						// allocate new buffer
						LPBYTE pRgnDataNew = new BYTE[ RGNDATAHEADER_SIZE + dwRectsCount * sizeof(RECT) ];
						// copy current region data to it
						memcpy( pRgnDataNew, pRgnData, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT) );
						// delte old region data buffer
						delete [] pRgnData;
						// set pointer to new regiondata buffer to current
						pRgnData = (RGNDATAHEADER*)pRgnDataNew;
						// correct pointer to RECT table
						pRects = (LPRECT)((LPBYTE)pRgnData + RGNDATAHEADER_SIZE);
					}
					wasfirst = false;
				}

				pColor -= dwLineBackLen;
			}
			// release image data
			delete [] pBits;
			delete [] bi;

			// create region
			HRGN hRgn = ExtCreateRegion( NULL, RGNDATAHEADER_SIZE + pRgnData->nCount * sizeof(RECT), (LPRGNDATA)pRgnData );
			// release region data
			delete [] pRgnData;

			return hRgn;
		}

		void FillSolid( HDC hdc, const CRect& rect, COLORREF clr )
		{
			::SetBkColor(hdc, clr);
			::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
		}

		void FillSolid( HDC hdc, LONG lLeft, LONG lTop, LONG lWidth, LONG lHeight,
			COLORREF clr )
		{
			FillSolid( hdc,
				CRect( lLeft, lTop, 
					   lLeft + lWidth,
					   lTop + lHeight), clr );
		}

		void   Draw3D( HDC hdc, const CRect& rect,
			COLORREF clrTopLeft, COLORREF clrBottomRight )
		{
			LONG x = rect.left;
			LONG y = rect.top;
			LONG cx = rect.Width();
			LONG cy = rect.Height();

			FillSolid(hdc,x, y, cx - 1, 1, clrTopLeft);
			FillSolid(hdc,x, y, 1, cy - 1, clrTopLeft);
			FillSolid(hdc,x + cx, y, -1, cy, clrBottomRight);
			FillSolid(hdc,x, y + cy, cx, -1, clrBottomRight);
		}

		bool   FillColor( HDC hdc, const CRect& rect, COLORREF clr )
		{
			HBRUSH hBrush = CreateSolidBrush( clr );
			FillRect( hdc, &rect, hBrush );
			DeleteObject( hBrush );
			return true;
		}
		
		bool FillColor( HDC hdc, const RECT& rect, 
			COLORREF crFrom, COLORREF crTo, bool bIsHorizontal )
		{

			if ( TRUE ==  IsRectEmpty(&rect) )
			{
				return false;
			}

			if (crFrom == crTo)
			{
				FillSolid( hdc, rect, crFrom);
				return TRUE;
			}
			TRIVERTEX vert[2];
			vert[0].x      = rect.left;
			vert[0].y      = rect.top;
			vert[0].Red    = GetRValue(crFrom) << 8;
			vert[0].Green  = GetGValue(crFrom) << 8;
			vert[0].Blue   = GetBValue(crFrom) << 8;
			vert[0].Alpha  = 0x0000;

			vert[1].x      = rect.right;
			vert[1].y      = rect.bottom; 
			vert[1].Red    = GetRValue(crTo) << 8;
			vert[1].Green  = GetGValue(crTo) << 8;
			vert[1].Blue   = GetBValue(crTo) << 8;
			vert[1].Alpha  = 0x0000;

			GRADIENT_RECT gRect = { 0, 1 };

			//ʹ��ϵͳgdi��������
			if( TRUE == GradientFill(
				hdc, vert,
				2, &gRect, 1,
				bIsHorizontal ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V ) )
			{
				return true;
			}

			int nWidth = rect.right - rect.left;
			int nHeight = rect.bottom - rect.top;

			if ( bIsHorizontal )
			{
				for (int nX = rect.left; nX < rect.right; ++nX )
				{
					FillSolid(hdc, nX, rect.top, 1, nHeight, 
						BlendColor(crFrom, crTo, (rect.right - nX) / (float)nWidth ));
				}
			}
			else
			{
				for (int nY = rect.top; nY < rect.bottom; ++nY )
				{
					FillSolid( hdc, rect.left, nY, nWidth, 1, 
						BlendColor(crFrom, crTo, (rect.bottom - nY) / (float)nHeight) );
				}
			}

			return true;

		}

		/** 
		 * @brief ��ȡָ���ı��������£�ʵ�ʵĿ��
		 */
		int    GetFontLength( HWND hWnd, LPCTSTR lpszText )
		{
			if( NULL == hWnd || NULL == lpszText )
			{
				return 0;
			}
			CTempWindowDC wdc( hWnd );
			HFONT hFont=(HFONT)(SendMessage(hWnd, WM_GETFONT, 0, 0));
			HGDIOBJ hOldFont = SelectObject( wdc, hFont );
			RECT rect = {0};
			DrawText( wdc, lpszText,-1, &rect, DT_SINGLELINE | DT_CALCRECT );
			
			SelectObject( wdc, hOldFont);

			return rect.right-rect.left;
		}

				/** 
		 * @brief ����λͼ����ͼƬ
		 */
		CBitmapRefPtr CreateSubBitmap( 
			CBitmapRefPtr pBitmap, 
			int nLeft, int nTop, int nWidth ,int nHeight )
		{
			if( !pBitmap )
			{
				ASSERT(false);
				return NULL;
			}
			HBITMAP hBmp = (HBITMAP)(pBitmap ->GetSafeHandle());
			HDC hdc = GetDC(NULL);
			HDC hMemDC = CreateCompatibleDC(hdc);

			BITMAP bitmap = {0};
			GetObject( hBmp, sizeof(bitmap), &bitmap );
			if( nLeft < 0 )
			{
				nLeft = 0;
			}
			if( nTop < 0 )
			{
				nTop = 0;
			}
			if( nWidth < 0 || nWidth > bitmap.bmWidth )
			{
				nWidth = bitmap.bmWidth;
			}
			if( nHeight < 0 || nHeight > bitmap.bmHeight )
			{
				nHeight = bitmap.bmHeight;
			}

			// ��ȡ��λͼ
			HBITMAP hBmp1 = CreateCompatibleBitmap(
				hdc, nWidth, nHeight );
			HGDIOBJ hOldBmp1 =  SelectObject(hMemDC, hBmp1);
			HDC hMemDC1 = CreateCompatibleDC(hdc);
			HGDIOBJ hOldBmp2 = SelectObject(hMemDC1, hBmp);
			BitBlt(hMemDC, 0,0, nWidth, nHeight,
				hMemDC1, nLeft, nTop, SRCCOPY );

			// ����
			CBitmapRef* pSubBmp = new CBitmapRef;
			pSubBmp->Attach( hBmp1 );

			//����
			SelectObject(hMemDC, hOldBmp1);
			SelectObject(hMemDC1, hOldBmp2 );
			ReleaseDC(NULL, hdc);
			DeleteDC(hMemDC);
			DeleteDC(hMemDC1);
			return pSubBmp;
		}

		/** 
		 * @brief ��ȡλͼָ�����ص����ɫֵ
		 */
		COLORREF GetBitmapPixelColor( 
			CBitmapRefPtr pBitmap, int nX, int nY )
		{			
			if( !pBitmap )
			{
				return RGB(0,0,0);
			}
			if( -1 == nX )
			{
				nX = 0;
			}
			if( -1 == nY )
			{
				nY = 0;
			}

			HDC hDC = CreateCompatibleDC(NULL);
			HBITMAP hBMP = (HBITMAP)( pBitmap ->GetSafeHandle());
			HGDIOBJ hOldBmp = SelectObject( hDC, hBMP );
			COLORREF clrRes = GetPixel( hDC, nX, nY );
			SelectObject( hDC, hOldBmp );
			DeleteDC( hDC );
			return clrRes;
		}

		COLORREF BlendColor( COLORREF clrFrom ,COLORREF clrTo, float fAlpha )
		{
			int nRed =  (int)(GetRValue(clrFrom) * fAlpha
				+ GetRValue(clrTo) * (1.0f - fAlpha));
			int nGreen =  (int)(GetGValue(clrFrom) * fAlpha 
				+ GetGValue(clrTo) * (1.0f - fAlpha));
			int nBlue = (int)(GetBValue(clrFrom) * fAlpha
				+ GetBValue(clrTo) * (1.0f - fAlpha));

#define CHECK_COLOR_VALUE(c) if(c < 0) c = 0; else if( c>255 ) c=255
			CHECK_COLOR_VALUE( nRed );
			CHECK_COLOR_VALUE( nGreen );
			CHECK_COLOR_VALUE( nBlue );
#undef CHECK_COLOR_VALUE
			return RGB( nRed, nGreen, nBlue );
		}
		COLORREF BlendColor( COLORREF clrFrom ,COLORREF clrTo, unsigned char nAlpha )
		{
			return BlendColor( clrFrom, clrTo, nAlpha/255.0f );
		}


		COLORREF ColorMultiply( COLORREF color, float fCoef )
		{
			int nRed =	 (int)(GetRValue(color) * fCoef);
			int nGreen = (int)(GetGValue(color) * fCoef);
			int nBlue =  (int)(GetBValue(color) * fCoef);

#define CHECK_COLOR_VALUE(c) if(c < 0) c = 0; else if( c>255 ) c=255
			CHECK_COLOR_VALUE( nRed );
			CHECK_COLOR_VALUE( nGreen );
			CHECK_COLOR_VALUE( nBlue );
#undef CHECK_COLOR_VALUE
			return RGB( nRed, nGreen, nBlue );
		}

		bool IsGreaterThanXP( )
		{
			OSVERSIONINFO ovi = { sizeof(OSVERSIONINFO) };
			BOOL bRet = ::GetVersionEx(&ovi);
			return ((bRet != FALSE) && (ovi.dwMajorVersion >= 6));

		}


		bool TransparentBitBlt(
			HDC hDstDC, int nDstX, int nDstY, int nDstWidth, int nDstHeight,
			HDC hSrcDC, int nSrcX, int nSrcY, COLORREF clrTransparent )
		{
			return TransparentBitBlt( hDstDC, nDstX, nDstY, nDstWidth, nDstHeight,
				hSrcDC, nSrcX, nSrcY, nDstWidth, nDstHeight, clrTransparent );
		}

		/** 
		 * @brief ��͸���ȵ�BitBlt
		 */
		bool TransparentBitBlt(
			HDC hDstDC, int nDstX, int nDstY, int nDstWidth, int nDstHeight,
			HDC hSrcDC, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight,
			COLORREF clrTransparent )
		{
			if ( nDstWidth < 1 || nDstHeight < 1 || 
				nSrcWidth < 1 || nSrcHeight < 1 ) 
			{
				return false;
			}
	
			// ʹ��ϵͳ�ķ�ʽ
			if( TRUE == TransparentBlt( hDstDC, 
				nDstX, nDstY, 
				nDstWidth, nDstHeight,
				hSrcDC, 
				nSrcX, nSrcY, 
				nSrcWidth,nSrcHeight,   
				clrTransparent ) )
			{
				return true;
			}
			HDC hMemDC = CreateCompatibleDC( hDstDC );
			HDC hMaskDC = CreateCompatibleDC( hDstDC );
			// ��������ͼ
			HBITMAP hMaskBmp = CreateBitmap( nSrcWidth, nSrcHeight, 1, 1, NULL) ;
			HBITMAP hMemBmp = CreateCompatibleBitmap( hDstDC, nSrcWidth, nSrcHeight );


			HGDIOBJ hOldMeMDcBmp = SelectObject(hMemDC,hMemBmp);
			// ����
			BitBlt(hMemDC,0, 0, nSrcWidth, nSrcHeight, hSrcDC, nSrcX, nSrcY, SRCCOPY );

			HGDIOBJ pOldMaskDcBmp = SelectObject(hMaskDC,hMaskBmp);
			SetBkColor(hMemDC,clrTransparent );

			// ��������ͼ
			BitBlt(hMaskDC,0, 0, nSrcWidth, nSrcHeight, hMemDC, 0, 0, SRCCOPY);

			SetBkColor(hMemDC,RGB(0,0,0));
			SetTextColor(hMemDC,RGB(255,255,255));
			// ԭͼ������ͼ�������������������ͼ��Ϊ1�����ر�������͸��),Ϊ0�Ļᱻ���
			BitBlt(hMemDC,0, 0, nSrcWidth, nSrcHeight, hMaskDC, 0, 0, SRCAND);

			SetStretchBltMode( hDstDC, HALFTONE );
			SetBkColor( hDstDC, RGB(255,255,255) );
			SetTextColor( hDstDC, RGB(0,0,0) );

			if ( nDstWidth == nSrcWidth && nDstHeight == nSrcHeight)
			{
				BitBlt( hDstDC, nDstX, nDstY,
					nDstWidth, nDstHeight, hMaskDC, 0, 0, SRCAND );

				// ��ԭʼͼ���ؽ��л������hMemDC���Ѿ��Ǿ���������˵���ɫ�ˡ�
				// �˲������ὫĿ����ɫ��Ϊ��ɫ�������Ѿ���������ɫ����Ϊ0�ˣ���
				BitBlt( hDstDC,nDstX, nDstY, nDstWidth, nDstHeight, 
					hMemDC, 0, 0, SRCPAINT );

			}
			else
			{
				StretchBlt( hDstDC, nDstX, nDstY,
					nDstWidth, nDstHeight, hMaskDC, 
					0, 0, nSrcWidth, nSrcHeight,SRCAND );
				StretchBlt( hDstDC, nDstX, nDstY,
					nDstWidth, nDstHeight, hMemDC, 
					0, 0, nSrcWidth, nSrcHeight,SRCPAINT );
			}

			SelectObject( hMaskDC,pOldMaskDcBmp);
			SelectObject(hMemDC, hOldMeMDcBmp );
			DeleteObject( hMemBmp );
			DeleteObject( hMaskBmp );
			DeleteDC( hMemDC );
			DeleteDC( hMaskDC );
			return TRUE;
		}

		bool ReplaceColor( 
			HDC hSrcDC, COLORREF clrSrc, 
			HDC hDstDc,COLORREF crlDst,
			const RECT& rect, LPRECT pRectClip )
		{
			if (clrSrc == crlDst )
			{
				return false;
			}
			if( NULL ==  pRectClip )
			{
				FillSolid( hDstDc, rect, crlDst );
				return TransparentBitBlt( 
					hDstDc, rect.left, rect.top,
					rect.right - rect.left,
					rect.bottom - rect.top,
					hSrcDC, rect.left, rect.top, clrSrc );
			}
			FillSolid( hDstDc, *pRectClip, crlDst );
			return TransparentBitBlt( hDstDc, 
				pRectClip->left, pRectClip->top,
				pRectClip->right - pRectClip->left, 
				pRectClip->bottom - pRectClip->top, 
				hSrcDC, pRectClip->left, pRectClip->top, clrSrc );
		}
		Gdiplus::Image* CreateSubImage(Gdiplus::Image *pSrcImg,int nLeft, int nTop, int Width, int Height)
		{
			if( NULL == pSrcImg )
			{
				return NULL;
			}
			int w, h;
			w = pSrcImg->GetWidth();
			h = pSrcImg->GetHeight();

			Gdiplus::Bitmap *pDstImg = new Gdiplus::Bitmap(Width, Height);
			pDstImg->SetResolution(pSrcImg->GetHorizontalResolution(), 
				pSrcImg->GetVerticalResolution());
			Gdiplus::Graphics grPhoto(pDstImg);
			grPhoto.Clear((Gdiplus::ARGB)Gdiplus::Color::Transparent );
			grPhoto.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
			grPhoto.DrawImage(pSrcImg, Gdiplus::RectF(0,0,Width,Height),
				nLeft, nTop, Width,Height, Gdiplus::UnitPixel,NULL);//ʵ�ֲü�
			return pDstImg;

		}

		bool DrawImage( HDC hdc, Gdiplus::Image* pImage, const RECT& rect )
		{

			ASSERT( NULL != hdc && NULL != pImage );
			if( NULL == hdc || NULL == pImage )
			{
				return false;
			}
			int nWidth = rect.right - rect.left;
			if( nWidth < (int)pImage ->GetWidth() )
			{
				nWidth = (int)pImage ->GetWidth( );
			}
			int nHeight = rect.bottom - rect.top;
			if( nHeight < (int)pImage ->GetHeight() )
			{
				nHeight = (int)pImage ->GetHeight();
			}
			Gdiplus::Graphics graph( hdc );
#if !0
			graph.SetPageUnit(Gdiplus::UnitPixel);
			Gdiplus::Bitmap bmpScale(nWidth, nHeight);
			{
				Gdiplus::Graphics graphicsScale(&bmpScale);
				graphicsScale.Clear(Gdiplus::Color::Transparent ); //����͸��
				Gdiplus::TextureBrush brush( pImage );

				Gdiplus::REAL fHScale =(Gdiplus::REAL)nWidth /pImage->GetWidth() ;
				Gdiplus::REAL fVScale = (Gdiplus::REAL)nHeight / pImage->GetHeight();
				graphicsScale.ScaleTransform(fHScale, fVScale);
				graphicsScale.FillRectangle(&brush,
					Gdiplus::RectF(0,0,nWidth,nHeight));
			}
			graph.DrawImage(
				&bmpScale, 
				rect.left, rect.top,
				rect.right - rect.left, 
				rect.bottom - rect.top );
#else
			graph.DrawImage(
				pImage,
				rect.left,rect.top,nWidth,nHeight );
#endif
			graph.ReleaseHDC( hdc );
			return true;
		}

		bool DrawImage( HDC hdc, const RECT& rect, Gdiplus::Image* pImage )
		{
			return DrawImage( hdc, pImage, rect );
		}

		bool FillColor( HDC hdc, const Gdiplus::Color& color)
		{

			Gdiplus::Graphics graphics(hdc);
			graphics.Clear(color); //����͸��

			graphics.ReleaseHDC( hdc );
			return true;
		}

/** 
 * @brief ��ǰ�Ӵ������о����еİ�ť
 */
static BOOL CALLBACK ChildWndEnumProc(HWND hWnd, LPARAM lParam)
{
	std::pair<LPCTSTR, std::vector<HWND> >* paramPair = 
		(std::pair<LPCTSTR, std::vector<HWND> >*)lParam;
	if( NULL != paramPair  )
	{
		TCHAR szClassName[MAX_CLASS_NAME];
		GetClassName( hWnd, szClassName, MAX_CLASS_NAME );
		if( 0 == _tcsicmp( szClassName, paramPair ->first) )
		{
			paramPair ->second.push_back( hWnd );
		}
	}
	EnumChildWindows(hWnd, ChildWndEnumProc, lParam );
	return TRUE;
}

/** 
 * @brief ���ҵ�ǰ����
 */
static BOOL CALLBACK  WndEnumProc(HWND hWnd, LPARAM lParam)
{
	std::pair<LPCTSTR, std::vector<HWND> >* paramPair = 
		(std::pair<LPCTSTR, std::vector<HWND> >*)lParam;
	if( NULL != paramPair  )
	{
		TCHAR szClassName[MAX_CLASS_NAME];
		GetClassName( hWnd, szClassName, MAX_CLASS_NAME );
		if( 0 == _tcsicmp( szClassName, paramPair ->first) )
		{
			paramPair ->second.push_back( hWnd );
		}
	}
	EnumChildWindows(hWnd, ChildWndEnumProc, lParam );
	return TRUE;
}



		HWND GetChildWindow( HWND hParent, LPCTSTR lpszChildWindowClassName )
		{
			std::pair<LPCTSTR, std::vector<HWND> > paramPair;
			paramPair.first = lpszChildWindowClassName;
			EnumChildWindows( hParent,WndEnumProc, (LPARAM)&paramPair );
			if( paramPair.second.empty() )
			{
				return NULL;
			}
			return paramPair.second.front();
		}

		void ShowBitmapInClipboard( HBITMAP hBitmap )
		{
			OpenClipboard( NULL );
			EmptyClipboard( );
			SetClipboardData( CF_BITMAP, hBitmap );
			CloseClipboard( );
		}

		void ShowCurBitmapInClipboard( HDC hdc )
		{
			ShowBitmapInClipboard( 
				(HBITMAP)GetCurrentObject( hdc, OBJ_BITMAP) );
		}

	}

}