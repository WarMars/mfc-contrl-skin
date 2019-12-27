#include "StdAfx.h"
#include "GDIPlusWrapper.h"

/**
 * Windows对gdi+的支持
 * 客户端版本	Windows XP, Windows 2000 Professional [desktop apps only]
 * 服务端版本	Windows 2000 Server [desktop apps only]
 */
#pragma comment(lib,"Gdiplus.lib")

namespace GdiplusWrapper
{

	XString GetErrorMsg( )
	{
		ASSERT(false);
		return XString();
		//return GetErrorMsg( Gdiplus::GetLastStatus() );
	}

	XString GetErrorMsg( Gdiplus::Status status )
	{
		switch(status)
		{ 
		case Gdiplus::Ok:	
			return _X("successful");
		case Gdiplus::GenericError:	
			return _X("Indicates that there was an error on the method call,\
					  which is identified as something other than \
					  those defined by the other elements of this enumeration.");
		case Gdiplus::InvalidParameter:	
			return _X("Indicates that one of the arguments passed to the method was not valid.");
		case Gdiplus::OutOfMemory:	
			return _X("Indicates that the operating system is out of \
					  memory and could not allocate memory to process \
					  the method call. For an explanation of how \
					  constructors use the OutOfMemory status, \
					  see the Remarks section at the end of this topic.");
		case Gdiplus::ObjectBusy:	
			return _X("Indicates that one of the arguments specified in\
					  the API call is already in use in another thread.");
		case Gdiplus::InsufficientBuffer:	
			return _X("Indicates that a buffer specified as an argument \
					  in the API call is not large enough to\
					  hold the data to be received.");
		case Gdiplus::NotImplemented:	
			return _X("Indicates that the method is not implemented.");
		case Gdiplus::Win32Error:	
			return toXString(_X("win32 error:%d"),GetLastError() );
			return _X("Indicates that the method generated a Win32 error.");
		case Gdiplus::WrongState:	
			return _X("Indicates that the object is in an invalid state \
					  to satisfy the API call. For example, \
					  calling Pen::GetColor from a pen that is\
					  not a single, solid color results in a WrongState status.");
		case Gdiplus::Aborted:	
			return _X("Indicates that the method was aborted.");
		case Gdiplus::FileNotFound:	
			return _X("Indicates that the specified image file or metafile cannot be found.");
		case Gdiplus::ValueOverflow:	
			return _X("Indicates that the method performed an arithmetic\
					  operation that produced a numeric overflow.");
		case Gdiplus::AccessDenied:	
			return _X("Indicates that a write operation is\
					  not allowed on the specified file.");
		case Gdiplus::UnknownImageFormat:	
			return _X("Indicates that the specified image file format is not known.");
		case Gdiplus::FontFamilyNotFound:	
			return _X("Indicates that the specified font family cannot be found.\
					  Either the font family name is incorrect or \
					  the font family is not installed.");
		case Gdiplus::FontStyleNotFound:	
			return _X("Indicates that the specified style is\
					  not available for the specified font family.");
		case Gdiplus::NotTrueTypeFont:	
			return _X("Indicates that the font retrieved from an \
					  HDC or LOGFONT is not a TrueType font and cannot be used with GDI+.");
		case Gdiplus::UnsupportedGdiplusVersion:	
			return _X("Indicates that the version of GDI+ that\
					  is installed on the system is incompatible with\
					  the version with which the application was compiled.");
		case Gdiplus::GdiplusNotInitialized:	
			return _X("Indicates that the GDI+API is not\
					  in an initialized state. To function, \
					  all GDI+ objects require that GDI+ be in an initialized state. \
					  Initialize GDI+ by calling GdiplusStartup.");
		case Gdiplus::PropertyNotFound:	
			return _X("Indicates that the specified property does not exist in the image.");
		case Gdiplus::PropertyNotSupported:	
			return _X("Indicates that the specified property is not \
					  supported by the format of the image and, therefore, cannot be set.");
#if (GDIPVER >= 0x0110)
		case Gdiplus::ProfileNotFound:	
			return _X("Indicates that the color profile required\
					  to save an image in CMYK format was not found.");
#endif //(GDIPVER >= 0x0110)
		default:
			break;
		}
		return toXString(_X("Unknown error:%d"), status );
	}
	void MsgBox( const XString& strContent, const XString& strTitle )
	{
		MessageBox(NULL, strContent.c_str(), strTitle.c_str(), MB_OK );
	}

	XString toXString( const TCHAR* pszFmt,...)
	{
		va_list argList;
		va_start(argList,pszFmt);
		TCHAR szBuf[4096] = {0};
		_vstprintf_s(szBuf, pszFmt, argList );
		va_end(argList);
		return szBuf;
	}

bool CGdiplusWrapper::StartUp( )
{
	Gdiplus::Status status=
	Gdiplus::GdiplusStartup(&m_gdiPlusToken, &m_gdiPlusStartupInput, NULL);

	if(Gdiplus::Ok != status )
	{
		SHOW_ERROR( status );
		return false;
	}

	return true;

}

bool CGdiplusWrapper::Quit( )
{
	Gdiplus::GdiplusShutdown(m_gdiPlusToken);
	return true;
}

CGdiplusWrapper::CGdiplusWrapper(void)
{
	StartUp( );
}


CGdiplusWrapper::~CGdiplusWrapper(void)
{
	Quit();
}

}
