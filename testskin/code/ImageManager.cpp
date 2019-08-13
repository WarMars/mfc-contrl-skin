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
}
