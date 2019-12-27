#ifndef MFCCONTROLS_UTIL_HPP
#define MFCCONTROLS_UTIL_HPP
#include <afxwin.h>
#include <string>

// �ж�GDI�����Ƿ���Ч
inline bool IsCGDIObjectValid( const CGdiObject& obj )
{
	HGDIOBJ hGdiObj = obj.GetSafeHandle();
	return  hGdiObj != NULL || ::GetObjectType(hGdiObj) != 0;
}

// �ж�GDI�����Ƿ���Ч
inline bool IsCGDIObjectValid( const CGdiObject* pObj )
{
	if( NULL == pObj )
	{
		return false;
	}
	return IsCGDIObjectValid( *pObj );
}

// ��ȡλͼ��С
inline CSize GetBMPSize( CBitmap& bmp )
{
	//��ȡλͼ��BITMAP����
	BITMAP aBmp;
	bmp.GetBitmap(&aBmp);
	return CSize( aBmp.bmWidth, aBmp.bmHeight);
}

// ת��Ϊ���ֽ��ַ���
inline CStringW  toWideCharString( LPCSTR pMultiByteChar, int nCodePange )
{
	if( NULL == pMultiByteChar )
	{
		return CStringW( );
	}
	int nNum = MultiByteToWideChar(nCodePange, 0, 
		pMultiByteChar, -1, NULL, 0 );
	LPWSTR pUniCode = new WCHAR[sizeof(wchar_t) * nNum];
	MultiByteToWideChar( nCodePange, 0, pMultiByteChar, -1, 
		pUniCode, sizeof(wchar_t) * nNum );
	CStringW strResult(pUniCode );
	delete []pUniCode;
	return strResult;
}


// ת��Ϊ���ֽ��ַ���
inline CStringW  toWideCharString( const std::string& strMultiByteChar )
{
	if( strMultiByteChar.empty() )
	{
		return CStringW( );
	}
	int nNum = (int)strMultiByteChar.size();
	LPWSTR pUniCode = new WCHAR[sizeof(wchar_t) * nNum];
	MultiByteToWideChar( CP_ACP, 0, strMultiByteChar.c_str(), -1, 
		pUniCode, sizeof(wchar_t) * nNum );
	CStringW strResult(pUniCode );
	delete []pUniCode;
	return strResult;
}
// ת��Ϊ���ֽ��ַ���
inline CStringW toWideCharString( LPCWSTR pWideChar, int nCodePange=CP_ACP )
{
	UNUSED( nCodePange );
	return  CStringW( NULL == pWideChar?L"":pWideChar );
}


// ת��Ϊ����ַ���
inline CStringA toMultiCharString( LPCSTR pMultiByteChar, int nCodePange=CP_ACP )
{	
	UNUSED( nCodePange );
	return CStringA( pMultiByteChar );
}
inline CStringA toMultiCharString( LPCWSTR pMultiByteChar, int nCodePange=CP_ACP )
{
	if( NULL == pMultiByteChar )
	{
		return CStringA( );
	}
	int nNum = WideCharToMultiByte(CP_ACP,NULL,pMultiByteChar,
		-1,NULL,0,NULL,FALSE );
	char *pszText = new char[nNum];
	WideCharToMultiByte (CP_ACP, NULL, pMultiByteChar,
		-1, pszText,nNum,NULL,FALSE);
	CStringA strResult( pszText );
	delete []pszText;
	return strResult;
}

// תtchar
inline CString toTCharString( const std::string& strText, int nCodePage = CP_ACP )
{
	CString strResult;
#ifdef _UNICODE
	strResult = toWideCharString( strText.c_str() );
#else
	strResult = toMultiCharString( strText.c_str() );
#endif
	return strResult;
}

// תtchar
inline CString toTCharString( const std::wstring& strText, int nCodePage = CP_ACP )
{
	CString strResult;
#ifdef _UNICODE
	strResult = toWideCharString( strText.c_str() );
#else
	strResult = toMultiCharString( strText.c_str() );
#endif
	return strResult;
}

// gbkתutf-8
inline std::string ANSI2UTF8(const std::string& strGBK)
{
	wchar_t* str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, nullptr, 0);
	str1 = new wchar_t[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, nullptr, 0, nullptr, nullptr);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, nullptr, nullptr);
	std::string strUTF8(str2);
	delete[]str1;
	delete[]str2;

	return strUTF8;
}

// utf-8תwindows��׼�ַ�
inline std::string UTF82ANSI(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, nullptr, 0);
	unsigned short * str1 = new unsigned short[len + 1];
	memset(str1, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (const char*)strUTF8.c_str(), -1, (LPWSTR)str1, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str1, -1, nullptr, 0, nullptr, nullptr);
	char *str2 = new char[len + 1];
	memset(str2, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str1, -1, str2, len, nullptr, nullptr);
	std::string strGBK(str2);
	delete[]str1;
	delete[]str2;

	return strGBK;
}
// ���ֽڸ�ʽ��
inline CStringW WideCharFormat( const wchar_t* fmt,...)
{
	if( NULL == fmt )
	{
		return L"";
	}
	wchar_t szBuf[4096] = {0};
	va_list vp;
	va_start( vp,fmt );
	vswprintf_s( szBuf, sizeof(szBuf), fmt, vp );
	va_end( vp );
	return szBuf;
}

// c�ַ�����ʽ��
inline CStringA MultiByteFormat( const char* fmt,... )
{
	if( NULL == fmt )
	{
		return "";
	}
	char szBuf[4096] = {0};
	va_list vp;
	va_start( vp,fmt );
	vsprintf_s( szBuf, sizeof(szBuf), fmt, vp );
	va_end( vp );
	return szBuf;
}


/*!
 * @brief ��ȡ��ǰexe�ļ���(������չ��)
 * @param 
 * @return 
 * @note 
 */
inline CString GetExeFileName( )
{
	TCHAR szModuleFileName[MAX_PATH] = {0};
	GetModuleFileName( NULL, szModuleFileName ,sizeof(szModuleFileName) );
	return _tcsrchr( szModuleFileName,_T('\\') )+1;
}

/*!
 * @brief ��ȡ��ǰexe��Ŀ¼��
 * @param 
 * @return 
 * @note ��Ŀ¼��\��β��
 */
inline CString GetExeFileDir( )
{
	TCHAR szModuleFileName[MAX_PATH] = {0};
	GetModuleFileName( NULL, szModuleFileName ,sizeof(szModuleFileName) );
	TCHAR* lpszFound = _tcsrchr( szModuleFileName, _T('\\') );
	if( NULL != lpszFound )
	{
		lpszFound[1] = _T('\0');
	}
	return szModuleFileName;
}

/*!
 * @brief time_tת��ΪCTime
 * @param 
 * @return 
 * @note
 */
inline CTime Time_t2CTime( time_t nSecondsFrom1970 )
{
	time_t nTime = (time_t)nSecondsFrom1970;
	struct tm tmSturct;
	localtime_s( &tmSturct, &nTime );
	return CTime(
		tmSturct.tm_year + 1900,
		tmSturct.tm_mon + 1,
		tmSturct.tm_mday,
		tmSturct.tm_hour,
		tmSturct.tm_min,
		tmSturct.tm_sec );
}


/*!
 * @brief CTimeת��Ϊtime_t
 * @param 
 * @return 
 * @note
 */
inline time_t CTime2Time_t( const CTime& srcTime )
{
	struct tm tmStruct;
	srcTime.GetLocalTm( &tmStruct );
	return mktime( &tmStruct );
}


/*!
 * @brief ����λͼ
 * @param hdc ����
 * @param r λͼ����
 * @param pBmp λͼ
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool DrawBmp( HDC hdc, const CRect& r, const CBitmap* pBmp )
{
	if( NULL == pBmp )
	{
		AfxMessageBox(_T("λͼΪ��,����ʧ��") );
		return false;
	}
	HDC hMemDC = CreateCompatibleDC( hdc );
	HGDIOBJ hOldBmp = SelectObject( hMemDC, pBmp ->GetSafeHandle() );
	const CSize& szBmp = GetBMPSize( *(CBitmap*)pBmp );
	int nOldMode = SetStretchBltMode(hdc,STRETCH_HALFTONE);
	if( FALSE == StretchBlt( hdc, r.left,r.top, r.Width(),r.Height(),
		hMemDC, 0,0, szBmp.cx, szBmp.cy, SRCCOPY ) )
	{
		DWORD dwErrorCode = GetLastError( );
		CString strMsg;
		strMsg.Format( _T("StretchBlt ʧ��:%d"), dwErrorCode );
		AfxMessageBox( strMsg );
	}
	SelectObject( hMemDC,hOldBmp );
	DeleteDC( hMemDC );
	SetStretchBltMode( hdc, nOldMode );
	return true;
}


/*!
 * @brief ����λͼ
 * @param pDC ����
 * @param r ���Ƶ�λͼ��λ��
 * @param pBmp λͼ
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool DrawBmp( CDC* pDC, const CRect& r, const CBitmap* pBmp )
{
	if( NULL == pDC )
	{
		return false;
	}
	return DrawBmp( pDC ->GetSafeHdc(), r, pBmp );
}


/*!
 * @brief ��Ļ����ת��Ϊָ�����ڿͻ���������
 * @param hWnd ָ���Ĵ���
 * @param lpRect ��Ļ�������
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool ScreenToClient( HWND hWnd, LPRECT lpRect )
{
	if( NULL == lpRect )
	{
		return false;
	}
	BOOL bRet1 = ScreenToClient( hWnd, (LPPOINT)&(lpRect ->left) );
	BOOL bRet2 = ScreenToClient( hWnd, (LPPOINT)&(lpRect ->right) );
	if( TRUE == bRet1 && TRUE == bRet2 )
	{
		return true;
	}
	return false;
}


/*!
 * @brief �ͻ����ľ�������ת��Ϊ��Ļ�ľ�������
 * @param hWnd ���ζ�Ӧ�Ĵ���
 * @param lpRect ��������
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool ClientToScreen( HWND hWnd, LPRECT lpRect )
{
	if( NULL == lpRect )
	{
		return false;
	}

	BOOL bRet1 = ::ClientToScreen(hWnd, (LPPOINT)lpRect);
	BOOL bRet2 = ::ClientToScreen(hWnd, ((LPPOINT)lpRect)+1);
	if ( GetWindowLong( hWnd, GWL_EXSTYLE) & WS_EX_LAYOUTRTL)
	{
		CRect::SwapLeftRight(lpRect);
	}
	if( TRUE == bRet1 && TRUE == bRet2 )
	{
		return true;
	}
	return false;
}


/*!
 * @brief ��ȡ�ļ���·��
 * @param �ļ���
 * @return �����򷵻س��ȴ���0���ַ���,���򷵻س���Ϊ0���ַ���
 * @note
 */
inline CString GetFilePath( LPCTSTR lpszFileName )
{
	ASSERT(NULL != lpszFileName );
	if( TRUE == PathFileExists( lpszFileName) )
	{
		return lpszFileName;
	}
	CString strPath = GetExeFileDir( );
	strPath += lpszFileName;
	if( TRUE == PathFileExists( (LPCTSTR)strPath ) )
	{
		return strPath;
	}
	return CString();
}


/*!
 * @brief ��Ϣ��LPARAMת��ΪPOINT
 * @param ��Ϣ��LPARAM����
 * @return POINT����
 * @note
 */
inline POINT Lparam2Point( LPARAM lParam )
{
	POINT pt = {GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	return pt;
}


/*!
 * @brief ���ô��ڵĳߴ���Ϣ
 * @param pWnd ����
 * @param rectGeometry �ߴ�λ��
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool SetWindowGeometry( CWnd* pWnd, const CRect& rectGeometry )
{
	ASSERT(NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	pWnd ->MoveWindow( rectGeometry, FALSE );
	return true;
}


/*!
 * @brief  ���ô�������
 * @param  pWnd ����
 * @param  pFont �������
 * @return ִ�гɹ�����true,���򷵻�false.
 * @note
 */
inline bool SetWindowFont( CWnd* pWnd, CFont* pFont )
{
	ASSERT( NULL != pWnd );
	ASSERT( NULL != pFont );
	if( NULL == pWnd || NULL == pFont )
	{
		return false;
	}
	pWnd ->SetFont( pFont );
	return true;
}

/*!
 * @brief  ���ô�����ָ��������ж���
 * @param pWnd ����
 * @param rectPos λ������
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool SetWindowCenter( CWnd* pWnd, const CRect& rectPos )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	CRect wndRect;
	pWnd ->GetWindowRect( &wndRect );
	int nXOffset = (rectPos.Width() - wndRect.Width())/2;
	int nYOffset = (rectPos.Height() - wndRect.Height())/2;
	pWnd ->MoveWindow( rectPos.left+nXOffset, rectPos.top + nYOffset,
		wndRect.Width(), wndRect.Height() );
	return true;
}

/*!
 * @brief ���ô�����ָ���������϶���
 * @param pWnd����
 * @param rectPos λ������
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool SetWindowTopLeft( CWnd* pWnd, const CRect& rectPos )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	CRect wndRect;
	pWnd ->GetWindowRect( &wndRect );
	int nXOffset = 0;
	int nYOffset = 0;
	pWnd ->MoveWindow( rectPos.left+nXOffset, rectPos.top + nYOffset,
		wndRect.Width(), wndRect.Height() );
	return true;
}

/*!
 * @brief ���ô�����ָ�������������
 * @param ����
 * @return ִ�гɹ�����true�����򷵻�false
 * @note
 */
inline bool SetWindowLeft( CWnd* pWnd, const CRect& rectPos )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	CRect wndRect;
	pWnd ->GetWindowRect( &wndRect );
	int nXOffset = 0;
	int nYOffset = (rectPos.Height() - wndRect.Height())/2;
	pWnd ->MoveWindow( rectPos.left+nXOffset, rectPos.top + nYOffset,
		wndRect.Width(), wndRect.Height() );
	return true;
}


/*!
 * @brief ���ô������ƶ��������Ҷ���
 * @param pWnd����
 * @param rectPos ����λ������
 * @return ִ�в����ĳɹ�����true�����򷵻�false.
 * @note
 */
inline bool SetWindowRight( CWnd* pWnd, const CRect& rectPos )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	CRect wndRect;
	pWnd ->GetWindowRect( &wndRect );
	int nXOffset = (rectPos.Width() - wndRect.Width());
	int nYOffset = (rectPos.Height() - wndRect.Height())/2;
	pWnd ->MoveWindow( rectPos.left+nXOffset, rectPos.top + nYOffset,
		wndRect.Width(), wndRect.Height() );
	return true;
}


/*!
 * @brief  ��ȡ���ڱ���
 * @param  ����
 * @return  ���ڱ����ַ���
 * @note
 */
inline CString GetWindowTitle( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return CString( );
	}
	CString strText;
	pWnd ->GetWindowText( strText );
	return strText;
}


/*!
 * @brief  ���ô��ڱ���
 * @param pWnd		 ����
 * @param strTitle	 ����
 * @return ִ�гɹ�����true,���򷵻�false
 * @note
 */
inline bool SetWindowTitle( CWnd* pWnd,const CString& strTitle )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	pWnd ->SetWindowText( strTitle );
	return true;
}


/*!
 * @brief  ���ô���
 * @param  ����
 * @return  �ɹ�����true�����򷵻�false.
 * @note
 */
inline bool EnableWindow( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	return TRUE == pWnd ->EnableWindow(TRUE);
}

/*!
 * @brief ���ô���
 * @param ����
 * @return ִ�гɹ�����true,���򷵻�true.
 * @note
 */
inline bool DisableWindow( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	return TRUE == pWnd ->EnableWindow( FALSE );
}


/*!
 * @brief ���ش���
 * @param ����
 * @return  ����֮ǰ������ʾ�򷵻�true�����򷵻�false.
 * @note
 */
inline bool HideWindow( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if(NULL == pWnd )
	{
		return false;
	}
	return TRUE == pWnd ->ShowWindow( SW_HIDE );
}


/*!
 * @brief ��ʾ����
 * @param pWnd���ڶ���
 * @return ����֮ǰ��ʾ������Ϊtrue������Ϊfalse
 * @note
 */
inline bool ShowWindow( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	return  TRUE == pWnd ->ShowWindow( SW_SHOW );
}


/*!
 * @brief ���ô����Ƿ���ʾ
 * @param pWnd ����
 * @param bIsVisible trueΪ��ʾ,falseΪ����
 * @return ����֮ǰ��ʾ�򷵻�true�����򷵻�false.
 * @note
 */
inline bool SetWindowVisible( CWnd* pWnd, bool bIsVisble )
{
	return bIsVisble?ShowWindow(pWnd):HideWindow(pWnd);
}

/*!
 * @brief �ڵ�ǰ�����ϻ���ָ����ͼ��
 * @param hdc ����
 * @param pImage ͼ��
 * @param rectDraw ���Ƶ�Ŀ������
 * @return ִ�гɹ�����true,���򷵻�false.
 * @note
 */
inline bool DrawImage( HDC hdc, Gdiplus::Image* pImage, const CRect& rectDraw )
{
	ASSERT( NULL != hdc && NULL != pImage );
	if( NULL == hdc || NULL == pImage )
	{
		return false;
	}
	Gdiplus::Graphics graph( hdc );
	graph.SetPageUnit(Gdiplus::UnitPixel);

	graph.DrawImage( pImage, 
		rectDraw.left, 
		rectDraw.top,
		rectDraw.Width(),
		rectDraw.Height() );
	graph.ReleaseHDC( hdc );
	return true;
}


/*!
 * @brief �ڻ�����ָ��λ�ã�ʹ��ָ����ͼ���ļ����ơ�
 * @param hdc ����
 * @param lpszImageFilePath ͼ���ļ�·��
 * @param rectDraw��������
 * @return ִ�гɹ�����true�����򷵻�false.
 * @note
 */
inline bool DrawImage( HDC hdc, LPCTSTR lpszImageFilePath, const CRect& rectDraw )
{
	ASSERT( NULL != hdc && NULL != lpszImageFilePath );
	if( NULL == hdc || NULL == lpszImageFilePath )
	{
		return false;
	}
	const CString& strFilePath = GetFilePath( lpszImageFilePath );
	ASSERT( !strFilePath.IsEmpty() );
	if( strFilePath.IsEmpty() )
	{
		return false;
	}
	Gdiplus::Image* pImage = Gdiplus::Image::FromFile(strFilePath);
	if( NULL == pImage )
	{
		return false;
	}
	Gdiplus::Graphics graph( hdc );
	graph.SetPageUnit(Gdiplus::UnitPixel);

	graph.DrawImage( pImage, 
		rectDraw.left, 
		rectDraw.top,
		rectDraw.Width(),
		rectDraw.Height() );
	graph.ReleaseHDC( hdc );
	delete pImage;
	return true;
}

/*!
 * @brief ���ÿؼ����ڴ�С
 * @param pWnd �ؼ�
 * @param cx ���
 * @param cy �߶�
 * @return ִ�гɹ�����true,���򷵻�false.
 * @note
 */
inline bool SetWindowSize( CWnd* pWnd, int cx, int cy )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	CRect r;
	pWnd ->GetWindowRect( r );
	pWnd ->MoveWindow( r.left,r.top, cx,cy,FALSE );
	return true;
}


/*!
 * @brief ��ȡ�ؼ�/���ڵ�λ����Ϣ
 * @param pWnd �ؼ�/����
 * @paran rect ����λ�úͳߴ���Ϣ
 * @return �ɹ�����true�����򷵻�false
 * @note
 */
inline bool GetWindowGeometry( CWnd* pWnd, CRect& rect)
{
	ASSERT(NULL != pWnd);
	if(NULL == pWnd )
	{
		return false;
	}
	pWnd ->GetWindowRect( rect );
	CWnd* pParent = pWnd ->GetParent();
	if( NULL != pParent )
	{
		pParent ->ScreenToClient( rect );
	}
	return true;
}


/*!
 * @brief �ü�ͼ��
 * @param pSrcImg ԭʼͼ��
 * @param nLeft	  ���ü������ ���Ͻ�x����
 * @param nTop    ���ü������ ���Ͻ�y����
 * @param nWidth  ���ü������ ���
 * @param nHeight ���ü������ �߶�
 * @return �ü��õ���ͼ��
 * @note
 */
inline Gdiplus::Image* CreateSubBitmap(Gdiplus::Image *pSrcImg,int nLeft, int nTop, int Width, int Height)
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

/* ����תbool */
#define i2b(IntV) (0 != (IntV) )
#define b2i(BoolV) (BoolV?1:0 )

/* ��ȡ���ڱ��� */
inline bool GetWindowTitle( CWnd* pWnd, CString& strTitle )
{
	if( NULL == pWnd )
	{
		return false;
	}
	pWnd ->GetWindowText( strTitle );
	return true;
}

/* intת�ַ��� */
inline CString ToCString( int n )
{
	CString str;
	str.Format(_T("%d"),n );
	return str;
}


/*!
 * @brief ������ת��Ϊ�ַ���
 * @param ��������ֵ
 * @return �ַ���
 * @note 
 */
inline CString ToCString( float f )
{
	CString str;
	str.Format(_T("%.02f"), f );
	return str;
}


/*!
 * @brief �ַ���תint
 * @param �ַ���
 * @return intֵ
 * @note 
 */
inline int ToInt( const CString& strText )
{
	return (int)_ttoi( strText );
}

/*!
 * @brief �ַ���תfloat
 * @param �ַ���
 * @return float��ֵ
 * @note
 */
inline float ToFloat( const CString& strText )
{
	return (float)_ttof( strText );
}

/*!
 * @brief  ������GetDlgItemInt
 * @param 
 * @return int����
 * @note 
 */
inline int GetWindowTextInt( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return 0;
	}
	CString strText;
	pWnd ->GetWindowText( strText );
	return ToInt( strText );
}


/*!
 * @brief  ������GetDlgItemFloat
 * @param 
 * @return float����
 * @note 
 */
inline float GetWindowTextFloat( CWnd* pWnd )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return 0;
	}
	CString strText;
	pWnd ->GetWindowText( strText );
	return ToFloat( strText );
}


/*!
 * @brief ���ð�ť�ؼ�����ʾ״̬Ϊѡ�л��߷�ѡ��
 * @param  nCtrlId �ؼ���id
 * @param  bValue  �ؼ�״̬�Ƿ�Ϊѡ��
 * @return 
 * @note �˺���һ������checkbox����radio button
 */
#define SetCtrlBool( nCtrlId, bValue ) \
{ \
	CButton* pButton = ( (CButton*)GetDlgItem(nCtrlId) ); \
	if( pButton != GetFocus() )\
	{\
		pButton ->SetCheck(bValue?BST_CHECKED:BST_UNCHECKED );\
	}\
}

/*!
 * @brief ��ȡ�ؼ���ѡ��״̬
 * @param �ؼ���id
 * @return ѡ�з���true�����򷵻�false
 * @note
 */
#define GetCtrlBool( nCtrlId ) \
	( (BST_CHECKED == ( (CButton*)GetDlgItem(nCtrlId) ) ->GetCheck( ))?1:0 )


/*!
 * @brief ������ֵ���ÿؼ���
 * @param nCtrlId�ؼ���id
 * @param nValue�ؼ���ֵ
 * @return ��
 * @note 
 */
#define SetCtrlInt( nCtrlId, nValue ) \
{ \
	CWnd* pWnd = GetDlgItem(nCtrlId); \
	if( pWnd != GetFocus() ) \
	pWnd ->SetWindowText(  ToCString( nValue) );\
}


/*!
 * @brief ��ȡ�ؼ�����ʾ�ı�����ת��Ϊintֵ
 * @param �ؼ�id
 * @return ������ֵ
 * @note
 */
#define GetCtrlInt( nCtrlId ) \
	GetWindowTextInt( GetDlgItem(nCtrlId) )


/*!
 * @brief ʹ��float�������ÿؼ�����ʾ�ı�
 * @param nCtrlId �ؼ�id
 * @param fValue  �ؼ�ֵ
 * @return ��
 * @note 
 */
#define SetCtrlFloat( nCtrlId, fValue )\
{ \
	CWnd* pWnd = GetDlgItem(nCtrlId); \
	if( pWnd != GetFocus() ) \
	pWnd  ->SetWindowText(  ToCString( fValue) ); \
}


/*!
 * @brief ��ȡ�ؼ�����ʾ�ı�����ת��Ϊfloat����
 * @param �ؼ���ID
 * @return float����
 * @note �˺���һ�����ڽ������븡������edit�ؼ�
 */
#define GetCtrlFloat( nCtrlId ) \
	GetWindowTextFloat( GetDlgItem(nCtrlId) )


/*!
 * @brief �ļ��Ƿ����
 * @param �ļ� ·��
 * @return ���ڷ���true�����򷵻�false
 * @note
 */
inline bool DoesModuleExist( const CString& strFilePathName )
{
	return FALSE == GetFilePath(strFilePathName ).IsEmpty();
}



/*!
 * @brief ��ʼ��CImage����
 * @param imgֵCImage����
 * @param lpszImgFilePathָͼ���ļ���·��
 * @return ִ�гɹ�����true�����򷵻�false.
 * @note
 */
inline bool InitCImage( CImage& img, LPCTSTR lpszImgFilePath )
{
	const CString& strFilePath = GetFilePath( lpszImgFilePath );
	ASSERT( !strFilePath.IsEmpty() );
	if( strFilePath.IsEmpty() )
	{
		return false;
	}

	return SUCCEEDED(img.Load(strFilePath));

}


/*!
 * @brief ��ʼ��ͼ�껯��static�ؼ�����λ������Ϊ��ǰλ��ָ�����
 * @param pWnd �ؼ�
 * @param nWidth ���
 * @param nHeight �߶�
 * @return ��
 * @note ͨ���ڳ�ʼ������ʱ����ͼ��static�ؼ��Ĵ�С
 */
inline void InitBmpStatic( CWnd* pWnd, int nWidth, int nHeight )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return;
	}
	/* �����ʽ��֧��ͼ�� */
	if( FALSE == pWnd ->ModifyStyle(0,SS_BITMAP|SS_CENTERIMAGE) )
	{
		ASSERT( TRUE ==  pWnd ->ModifyStyle(0,SS_BITMAP|SS_CENTERIMAGE) );
		//return false;
	}
	/* ��ȡ������λ��, */
	CRect rectGeometry;
	GetWindowGeometry( pWnd, rectGeometry );
	pWnd ->MoveWindow( rectGeometry.left,rectGeometry.top,
		nWidth,nHeight,FALSE );
}
#define InitBmpStaticId( nCtrlId,w,h ) InitBmpStatic(GetDlgItem(nCtrlId),w,h) 

/*!
 * @brief ����static�ؼ���ͼ��,������ͼ��ߴ����static�Ĵ�С.
 * @param pWndStatic �ؼ�.
 * @param imgIcon ͼ��.
 * @return ִ�гɹ�����true,���򷵻�true.
 * @note
 */
inline bool SetStaticIcon( CWnd* pWndStatic, const CImage& imgIcon )
{
	ASSERT(NULL != pWndStatic && !imgIcon.IsNull() );
	if( NULL == pWndStatic )
	{
		return false;
	}
	if( imgIcon.IsNull() )
	{
		return false;
	}
	if( FALSE == pWndStatic ->ModifyStyle(0,SS_BITMAP|SS_CENTERIMAGE) )
	{
		//ASSERT( TRUE ==  pWndStatic ->ModifyStyle(0,SS_BITMAP|SS_CENTERIMAGE) );
		//return false;
	}
	CRect rectGeometry;
	GetWindowGeometry( pWndStatic, rectGeometry );
	pWndStatic ->MoveWindow( 
		rectGeometry.left, rectGeometry.right,
		imgIcon.GetWidth(),imgIcon.GetHeight(),FALSE );
	HBITMAP hOldBitmap =  ( (CStatic*)pWndStatic) ->SetBitmap( imgIcon );
	if( NULL != hOldBitmap )
	{
		DeleteObject( hOldBitmap );
	}
	ASSERT( ( (CStatic*)pWndStatic) ->GetBitmap( ) != NULL );

	return true;
}


/*!
 * @brief ����static�ؼ���ͼ��
 * @param 
 * @return 
 * @note �˺����������ͼ��ߴ����static�Ĵ�С�������Ҫ���ô�С����ʹ�ô˺���֮ǰ,
 *      ����ʹ��InitBmpStatic����Ƶ���ĳߴ��趨��
 */
inline bool SetStaticIcon2( CWnd* pWndStatic, HBITMAP hBmpIcon )
{
	ASSERT(NULL != pWndStatic && NULL != hBmpIcon );
	if( NULL == pWndStatic )
	{
		return false;
	}
	if( NULL == hBmpIcon )
	{
		return false;
	}
	HBITMAP hOldBmp = ( (CStatic*)pWndStatic) ->SetBitmap( hBmpIcon );
	if( NULL != hOldBmp )
	{
		DeleteObject( hOldBmp );
	}
	ASSERT( ( (CStatic*)pWndStatic) ->GetBitmap( ) != NULL );

	return true;
}

#endif //MFCCONTROLS_UTIL_HPP
