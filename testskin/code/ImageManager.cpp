#include "StdAfx.h"
#include "ImageManager.h"
#include "utils.hpp"

CImageManager::CImageManager(void)
{
}
CImageManager& CImageManager::GetInst( )
{
	static CImageManager mamager;
	return mamager;
}
CBitmapRefPtr	CImageManager::CreateBitmap( UINT nBmpResourceId )
{
	std::map<UINT,CBitmapRefPtr>::const_iterator it = 
		m_mapRcBmpPtr.find( nBmpResourceId);
	if( it != m_mapRcBmpPtr.end() )
	{
		if( !IsCGDIObjectValid( it ->second.get() ) )
		{
			it ->second->LoadBitmap( nBmpResourceId );
		}
		return it ->second;
	}
	CBitmapRef* pBmpObj = new CBitmapRef;
	pBmpObj->LoadBitmap( nBmpResourceId );
	m_mapRcBmpPtr.insert( std::pair<UINT, CBitmapRefPtr>(
		nBmpResourceId, pBmpObj ) );
	return pBmpObj;
}

CBitmapRefPtr	CImageManager::GetBitmap( UINT nBmpResourceId )
{
	return CreateBitmap( nBmpResourceId );
}


CBitmapRefPtr CImageManager::CreateBitmap( LPCTSTR lpszBmpFilePath )
{
	const CString& strFilePath = GetFilePath( lpszBmpFilePath );
	ASSERT( !strFilePath.IsEmpty() );
	for( std::map<Xstring,CBitmapRefPtr>::const_iterator it = 
		m_mapFileBmpPtr.begin(); it != m_mapFileBmpPtr.end(); ++it )
	{
		if( 0 == _tcsicmp( it ->first.c_str(), lpszBmpFilePath ) )
		{
			if( !IsCGDIObjectValid( it ->second) )
			{ 
				CImage img;
				img.Load(strFilePath);
				it ->second ->Attach( img.Detach() );
			}
			return it ->second;
		}
	}

	CBitmapRef* pBmpObj = new CBitmapRef;
	CImage img;
	img.Load(strFilePath);
	pBmpObj->Attach( img.Detach() );
	m_mapFileBmpPtr.insert( 
		std::pair<Xstring, CBitmapRefPtr>( lpszBmpFilePath, pBmpObj ) );
	return pBmpObj;
}

CBitmapRefPtr CImageManager::GetBitmap( LPCTSTR lpszBmpFilePath )
{
	return CreateBitmap( lpszBmpFilePath );
}

Gdiplus::Image* CImageManager::GetImage( LPCTSTR lpszImgFilePath )
{
	const CString& strFilePath = GetFilePath( lpszImgFilePath );
	ASSERT( !strFilePath.IsEmpty() );
	for( std::map<Xstring,Gdiplus::Image*>::iterator it = 
		m_mapImage.begin(); it != m_mapImage.end(); ++it )
	{
		if( 0 == _tcsicmp( it ->first.c_str(), lpszImgFilePath ) )
		{
			if( NULL == it ->second )
			{ 

				it ->second = Gdiplus::Image::FromFile( lpszImgFilePath );
			}
			return it ->second;
		}
	}
	Gdiplus::Image* pImage = Gdiplus::Image::FromFile( strFilePath );
	m_mapImage.insert( 
		std::pair<Xstring, Gdiplus::Image*>( lpszImgFilePath, 
		pImage
		) );
	return pImage;

}

void CImageManager::AddImage( LPCTSTR lpszImgFilePath, Gdiplus::Image* pImage )
{
	ASSERT( m_mapImage.find( lpszImgFilePath ) == m_mapImage.end() );
	m_mapImage[lpszImgFilePath] = pImage;
}

void CImageManager::TidyUp( )
{
	for(std::map<UINT,CBitmapRefPtr>::iterator it = m_mapRcBmpPtr.begin();
		it != m_mapRcBmpPtr.end();)
	{
		if( 1 == it ->second->refCount() )
		{
			/* 释放位图 */
			CBitmapRef* pBitmap =  it->second.release( );
			delete pBitmap;
			it = m_mapRcBmpPtr.erase( it );
		}
		else
		{
			++it;
		}
	}

	for(std::map<Xstring,CBitmapRefPtr>::iterator it = 
		m_mapFileBmpPtr.begin(); it != m_mapFileBmpPtr.end();)
	{
		if( 1 == it ->second->refCount() )
		{
			/* 释放位图 */
			CBitmapRef* pBitmap =  it->second.release( );
			delete pBitmap;
			it = m_mapFileBmpPtr.erase( it );
		}
		else
		{
			++it;
		}
	}

}

void CImageManager::Reset( )
{
	TidyUp( );
	m_mapRcBmpPtr.clear();
	m_mapFileBmpPtr.clear();
	for( auto it = m_mapImage.begin(); it != m_mapImage.end();++it )
	{
		delete it ->second;
	}
	m_mapImage.clear();
}
