#ifndef MFCCONTROLS_UTIL_HPP
#define MFCCONTROLS_UTIL_HPP
#include <afxwin.h>

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
	return  CStringW( NULL == pWideChar?pWideChar:L"" );
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

// 转utf-8
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

// 获取当前exe文件名(包含拓展名)
inline CString GetExeFileName( )
{
	TCHAR szModuleFileName[MAX_PATH] = {0};
	GetModuleFileName( NULL, szModuleFileName ,sizeof(szModuleFileName) );
	return _tcsrchr( szModuleFileName,_T('\\') )+1;
}
// 获取当前exe的目录名
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

inline time_t CTime2Time_t( const CTime& srcTime )
{
	struct tm tmStruct;
	srcTime.GetLocalTm( &tmStruct );
	return mktime( &tmStruct );
}

inline bool DrawBmp( HDC hdc, const CRect& r, const CBitmap* pBmp )
{
	if( NULL == pBmp )
	{
		return false;
	}
	HDC hMemDC = CreateCompatibleDC( hdc );
	HGDIOBJ hOldBmp = SelectObject( hMemDC, pBmp ->GetSafeHandle() );
	const CSize& szBmp = GetBMPSize( *(CBitmap*)pBmp );
	StretchBlt( hdc, r.left,r.top, r.Width(),r.Height(),
		hMemDC, 0,0, szBmp.cx, szBmp.cy, SRCCOPY );
	SelectObject( hMemDC,hOldBmp );
	DeleteDC( hMemDC );
	return true;
}
inline bool DrawBmp( CDC* pDC, const CRect& r, const CBitmap* pBmp )
{
	if( NULL == pDC )
	{
		return false;
	}
	return DrawBmp( pDC ->GetSafeHdc(), r, pBmp );
}
inline BOOL ScreenToClient( HWND hWnd, LPRECT lpRect )
{
	if( NULL == lpRect )
	{
		return false;
	}
	BOOL bRet1 = ScreenToClient( hWnd, (LPPOINT)&(lpRect ->left) );
	BOOL bRet2 = ScreenToClient( hWnd, (LPPOINT)&(lpRect ->right) );
	if( TRUE == bRet1 && TRUE == bRet2 )
	{
		return TRUE;
	}
	return FALSE;
}
inline BOOL ClientToScreen( HWND hWnd, LPRECT lpRect )
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
		return TRUE;
	}
	return FALSE;
}

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
inline POINT Lparam2Point( LPARAM lParam )
{
	POINT pt = {GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
	return pt;
}

#define i2b( IntV) (0 != (IntV) )

#endif //MFCCONTROLS_UTIL_HPP
