#pragma once
#include <Windows.h>
#include <GdiPlus.h>
#include <string>
namespace GdiplusWrapper
{

#ifdef _UNICODE
	typedef std::wstring XString;
#	define _X( quote ) L##quote
#else
	typedef std::string XString;
#	define _X( quote ) quote
#define 
#endif
//XString GetErrorMsg( );
XString GetErrorMsg( Gdiplus::Status status );
void MsgBox( const XString& strContent, const XString& strTitle );
XString toXString( const TCHAR* pszFmt,...);
#define SHOW_ERROR( status ) MsgBox(GetErrorMsg(status), _X("gdi+ error") );
class CGdiplusWrapper
{
public:
	CGdiplusWrapper(void);
	~CGdiplusWrapper(void);
	bool StartUp( );
	bool Quit( );
private:

	Gdiplus::GdiplusStartupInput m_gdiPlusStartupInput;
	ULONG_PTR			m_gdiPlusToken;
};


}
