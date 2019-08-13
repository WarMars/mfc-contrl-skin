#pragma once
#include "gdiobj_ptr.hpp"
#include <map>
#include <string>

class CImageManager
{
public:
	static CImageManager& GetInst( );
public:
	CBitmapRefPtr	CreateBitmap( UINT nBmpResourceId );
	CBitmapRefPtr	GetBitmap( UINT nBmpResourceId );
	CBitmapRefPtr	CreateBitmap( LPCTSTR lpszBmpFilePath );
	CBitmapRefPtr	GetBitmap( LPCTSTR lpszBmpFilePath );

	
	/*!
	 * @brief 整理：会将使用的资源删除。
	 * @param 
	 * @return 
	 * @note
	 */
	void TidyUp( );
	void Reset( );
private:
	CImageManager( );

#if defined(_UNICODE)
	typedef std::wstring Xstring;
#else
	typedef std::string Xstring;
#endif
private:
	/** 
	 * @brief 资源位图
	 */
	std::map<UINT,CBitmapRefPtr>			m_mapRcBmpPtr;

	/** 
	 * @brief 文件位图
	 */
	std::map<Xstring,CBitmapRefPtr>			m_mapFileBmpPtr;

};

#define ImagePool( ) CImageManager::GetInst( )
