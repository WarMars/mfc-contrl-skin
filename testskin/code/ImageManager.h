#pragma once
#include "gdiobj_ptr.hpp"
#include <map>
#include <string>
#include <GdiPlus.h>

class CImageManager
{
public:
	static CImageManager& GetInst( );
public:
	CBitmapRefPtr	CreateBitmap( UINT nBmpResourceId );
	CBitmapRefPtr	GetBitmap( UINT nBmpResourceId );
	CBitmapRefPtr	CreateBitmap( LPCTSTR lpszBmpFilePath );
	CBitmapRefPtr	GetBitmap( LPCTSTR lpszBmpFilePath );

	Gdiplus::Image* GetImage( LPCTSTR lpszImgFilePath );
	void			AddImage( LPCTSTR lpszImgFilePath, Gdiplus::Image* pImage );
	/*!
	 * @brief �����Ὣʹ�õ���Դɾ����
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
	 * @brief ��Դλͼ
	 */
	std::map<UINT,CBitmapRefPtr>			m_mapRcBmpPtr;

	/** 
	 * @brief �ļ�λͼ
	 */
	std::map<Xstring,CBitmapRefPtr>			m_mapFileBmpPtr;

	/** 
	 * @brief ��͸���ȵ�ͼƬ
	 */
	std::map<Xstring,Gdiplus::Image*>		m_mapImage;

};

#define ImagePool( ) CImageManager::GetInst( )
#define CImagePool ImagePool