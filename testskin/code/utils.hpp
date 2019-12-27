#ifndef MFCCONTROLS_UTIL_HPP
#define MFCCONTROLS_UTIL_HPP
#include <afxwin.h>
#include <string>

// 判断GDI对象是否有效
inline bool IsCGDIObjectValid( const CGdiObject& obj )
{
	HGDIOBJ hGdiObj = obj.GetSafeHandle();
	return  hGdiObj != NULL || ::GetObjectType(hGdiObj) != 0;
}

// 判断GDI对象是否有效
inline bool IsCGDIObjectValid( const CGdiObject* pObj )
{
	if( NULL == pObj )
	{
		return false;
	}
	return IsCGDIObjectValid( *pObj );
}

// 获取位图大小
inline CSize GetBMPSize( CBitmap& bmp )
{
	//获取位图的BITMAP数据
	BITMAP aBmp;
	bmp.GetBitmap(&aBmp);
	return CSize( aBmp.bmWidth, aBmp.bmHeight);
}

// 转换为宽字节字符集
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


// 转换为宽字节字符集
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
// 转换为宽字节字符集
inline CStringW toWideCharString( LPCWSTR pWideChar, int nCodePange=CP_ACP )
{
	UNUSED( nCodePange );
	return  CStringW( NULL == pWideChar?L"":pWideChar );
}


// 转换为多节字符集
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

// 转tchar
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

// 转tchar
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

// gbk转utf-8
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

// utf-8转windows标准字符
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
// 宽字节格式化
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

// c字符串格式化
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
 * @brief 获取当前exe文件名(包含拓展名)
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
 * @brief 获取当前exe的目录名
 * @param 
 * @return 
 * @note 此目录以\结尾。
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
 * @brief time_t转换为CTime
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
 * @brief CTime转换为time_t
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
 * @brief 绘制位图
 * @param hdc 画布
 * @param r 位图矩形
 * @param pBmp 位图
 * @return 执行成功返回true，否则返回false
 * @note
 */
inline bool DrawBmp( HDC hdc, const CRect& r, const CBitmap* pBmp )
{
	if( NULL == pBmp )
	{
		AfxMessageBox(_T("位图为空,绘制失败") );
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
		strMsg.Format( _T("StretchBlt 失败:%d"), dwErrorCode );
		AfxMessageBox( strMsg );
	}
	SelectObject( hMemDC,hOldBmp );
	DeleteDC( hMemDC );
	SetStretchBltMode( hdc, nOldMode );
	return true;
}


/*!
 * @brief 绘制位图
 * @param pDC 画布
 * @param r 绘制的位图的位置
 * @param pBmp 位图
 * @return 执行成功返回true，否则返回false
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
 * @brief 屏幕坐标转换为指定窗口客户区的坐标
 * @param hWnd 指定的窗口
 * @param lpRect 屏幕坐标矩形
 * @return 执行成功返回true，否则返回false
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
 * @brief 客户区的矩形坐标转换为屏幕的矩形坐标
 * @param hWnd 矩形对应的窗口
 * @param lpRect 矩形区域
 * @return 执行成功返回true，否则返回false
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
 * @brief 获取文件的路径
 * @param 文件名
 * @return 存在则返回长度大于0的字符串,否则返回长度为0的字符串
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
 * @brief 消息的LPARAM转换为POINT
 * @param 消息的LPARAM参数
 * @return POINT对象
 * @note
 */
inline POINT Lparam2Point( LPARAM lParam )
{
	POINT pt = {GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	return pt;
}


/*!
 * @brief 设置窗口的尺寸信息
 * @param pWnd 窗口
 * @param rectGeometry 尺寸位置
 * @return 执行成功返回true，否则返回false
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
 * @brief  设置窗口字体
 * @param  pWnd 窗口
 * @param  pFont 字体对象
 * @return 执行成功返回true,否则返回false.
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
 * @brief  设置窗口与指定区域居中对齐
 * @param pWnd 窗口
 * @param rectPos 位置区域
 * @return 执行成功返回true，否则返回false
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
 * @brief 设置窗口与指定区域左上对齐
 * @param pWnd窗口
 * @param rectPos 位置区域
 * @return 执行成功返回true，否则返回false
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
 * @brief 设置窗口与指定的区域左对齐
 * @param 窗口
 * @return 执行成功返回true，否则返回false
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
 * @brief 设置窗口在制定的区域右对齐
 * @param pWnd窗口
 * @param rectPos 窗口位置坐标
 * @return 执行不到的成功返回true，否则返回false.
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
 * @brief  获取窗口标题
 * @param  窗口
 * @return  窗口标题字符串
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
 * @brief  设置窗口标题
 * @param pWnd		 窗口
 * @param strTitle	 标题
 * @return 执行成功返回true,否则返回false
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
 * @brief  启用窗口
 * @param  窗口
 * @return  成功返回true，否则返回false.
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
 * @brief 禁用窗口
 * @param 窗口
 * @return 执行成功返回true,否则返回true.
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
 * @brief 隐藏窗口
 * @param 窗口
 * @return  设置之前窗口显示则返回true，否则返回false.
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
 * @brief 显示窗口
 * @param pWnd窗口对象
 * @return 设置之前显示窗口则为true，否则为false
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
 * @brief 设置窗口是否显示
 * @param pWnd 窗口
 * @param bIsVisible true为显示,false为隐藏
 * @return 设置之前显示则返回true，否则返回false.
 * @note
 */
inline bool SetWindowVisible( CWnd* pWnd, bool bIsVisble )
{
	return bIsVisble?ShowWindow(pWnd):HideWindow(pWnd);
}

/*!
 * @brief 在当前画布上绘制指定的图像。
 * @param hdc 画布
 * @param pImage 图像
 * @param rectDraw 绘制的目标区域
 * @return 执行成功返回true,否则返回false.
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
 * @brief 在画布的指定位置，使用指定的图像文件绘制。
 * @param hdc 画布
 * @param lpszImageFilePath 图像文件路径
 * @param rectDraw绘制区域
 * @return 执行成功返回true，否则返回false.
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
 * @brief 设置控件窗口大小
 * @param pWnd 控件
 * @param cx 宽度
 * @param cy 高度
 * @return 执行成功返回true,否则返回false.
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
 * @brief 获取控件/窗口的位置信息
 * @param pWnd 控件/窗口
 * @paran rect 窗口位置和尺寸信息
 * @return 成功返回true，否则返回false
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
 * @brief 裁剪图像
 * @param pSrcImg 原始图像
 * @param nLeft	  欲裁剪区域的 左上角x坐标
 * @param nTop    欲裁剪区域的 左上角y坐标
 * @param nWidth  欲裁剪区域的 宽度
 * @param nHeight 欲裁剪区域的 高度
 * @return 裁剪得到的图像
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
		 nLeft, nTop, Width,Height, Gdiplus::UnitPixel,NULL);//实现裁剪
	return pDstImg;

}

/* 整数转bool */
#define i2b(IntV) (0 != (IntV) )
#define b2i(BoolV) (BoolV?1:0 )

/* 获取窗口标题 */
inline bool GetWindowTitle( CWnd* pWnd, CString& strTitle )
{
	if( NULL == pWnd )
	{
		return false;
	}
	pWnd ->GetWindowText( strTitle );
	return true;
}

/* int转字符串 */
inline CString ToCString( int n )
{
	CString str;
	str.Format(_T("%d"),n );
	return str;
}


/*!
 * @brief 浮点数转换为字符串
 * @param 浮点数数值
 * @return 字符串
 * @note 
 */
inline CString ToCString( float f )
{
	CString str;
	str.Format(_T("%.02f"), f );
	return str;
}


/*!
 * @brief 字符串转int
 * @param 字符串
 * @return int值
 * @note 
 */
inline int ToInt( const CString& strText )
{
	return (int)_ttoi( strText );
}

/*!
 * @brief 字符串转float
 * @param 字符串
 * @return float数值
 * @note
 */
inline float ToFloat( const CString& strText )
{
	return (float)_ttof( strText );
}

/*!
 * @brief  类似于GetDlgItemInt
 * @param 
 * @return int数据
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
 * @brief  类似于GetDlgItemFloat
 * @param 
 * @return float数据
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
 * @brief 设置按钮控件的显示状态为选中或者非选中
 * @param  nCtrlId 控件的id
 * @param  bValue  控件状态是否为选中
 * @return 
 * @note 此函数一般用于checkbox或者radio button
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
 * @brief 获取控件的选中状态
 * @param 控件的id
 * @return 选中返回true，否则返回false
 * @note
 */
#define GetCtrlBool( nCtrlId ) \
	( (BST_CHECKED == ( (CButton*)GetDlgItem(nCtrlId) ) ->GetCheck( ))?1:0 )


/*!
 * @brief 用整数值设置控件的
 * @param nCtrlId控件的id
 * @param nValue控件的值
 * @return 无
 * @note 
 */
#define SetCtrlInt( nCtrlId, nValue ) \
{ \
	CWnd* pWnd = GetDlgItem(nCtrlId); \
	if( pWnd != GetFocus() ) \
	pWnd ->SetWindowText(  ToCString( nValue) );\
}


/*!
 * @brief 获取控件的显示文本，并转换为int值
 * @param 控件id
 * @return 整数数值
 * @note
 */
#define GetCtrlInt( nCtrlId ) \
	GetWindowTextInt( GetDlgItem(nCtrlId) )


/*!
 * @brief 使用float数据设置控件的显示文本
 * @param nCtrlId 控件id
 * @param fValue  控件值
 * @return 无
 * @note 
 */
#define SetCtrlFloat( nCtrlId, fValue )\
{ \
	CWnd* pWnd = GetDlgItem(nCtrlId); \
	if( pWnd != GetFocus() ) \
	pWnd  ->SetWindowText(  ToCString( fValue) ); \
}


/*!
 * @brief 获取控件的显示文本，并转换为float类型
 * @param 控件的ID
 * @return float数据
 * @note 此函数一般用于仅可输入浮点数的edit控件
 */
#define GetCtrlFloat( nCtrlId ) \
	GetWindowTextFloat( GetDlgItem(nCtrlId) )


/*!
 * @brief 文件是否存在
 * @param 文件 路径
 * @return 存在返回true，否则返回false
 * @note
 */
inline bool DoesModuleExist( const CString& strFilePathName )
{
	return FALSE == GetFilePath(strFilePathName ).IsEmpty();
}



/*!
 * @brief 初始化CImage对象
 * @param img值CImage对象
 * @param lpszImgFilePath指图像文件的路径
 * @return 执行成功返回true，否则返回false.
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
 * @brief 初始化图标化的static控件，将位置设置为当前位置指定宽高
 * @param pWnd 控件
 * @param nWidth 宽度
 * @param nHeight 高度
 * @return 无
 * @note 通常在初始化界面时设置图标static控件的大小
 */
inline void InitBmpStatic( CWnd* pWnd, int nWidth, int nHeight )
{
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return;
	}
	/* 添加样式以支持图标 */
	if( FALSE == pWnd ->ModifyStyle(0,SS_BITMAP|SS_CENTERIMAGE) )
	{
		ASSERT( TRUE ==  pWnd ->ModifyStyle(0,SS_BITMAP|SS_CENTERIMAGE) );
		//return false;
	}
	/* 获取并设置位置, */
	CRect rectGeometry;
	GetWindowGeometry( pWnd, rectGeometry );
	pWnd ->MoveWindow( rectGeometry.left,rectGeometry.top,
		nWidth,nHeight,FALSE );
}
#define InitBmpStaticId( nCtrlId,w,h ) InitBmpStatic(GetDlgItem(nCtrlId),w,h) 

/*!
 * @brief 设置static控件的图标,并按照图标尺寸更新static的大小.
 * @param pWndStatic 控件.
 * @param imgIcon 图标.
 * @return 执行成功返回true,否则返回true.
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
 * @brief 设置static控件的图标
 * @param 
 * @return 
 * @note 此函数不会根据图标尺寸更新static的大小，如果需要设置大小，在使用此函数之前,
 *      请先使用InitBmpStatic避免频繁的尺寸设定。
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
