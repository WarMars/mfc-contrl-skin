#include "StdAfx.h"
#include "CtrlSkinConfig.h"
#include "ImageManager.h"
#include "GlobalSkinUtil.h"

namespace GlobalSkin
{
	bool CConfigData::IsColor( ) const
	{
		return m_bColor;
	}

	void    CConfigData::SetIsColor(  bool bIsColor  )
	{
		m_bColor = bIsColor;
	}

	XPath	CConfigData::GetFilePath( ) const
	{
		return m_filePath;
	}

	void	CConfigData::SetFilePath( const XPath& strPath )
	{
		m_filePath = strPath;
	}

	CRecti	CConfigData::GetRect( ) const
	{
		return m_imgRect;
	}

	void	CConfigData::SetRect(
		int nLeft, int nTop, int nWidth, int nHeight )
	{
		m_imgRect.m_nLeft = nLeft;
		m_imgRect.m_nTop = nTop;
		m_imgRect.m_nWidth = nWidth;
		m_imgRect.m_nHeight = nHeight;
	}


	CBitmapRefPtr CConfigData::GetImagePtr( ) const
	{
		CBitmapRefPtr pBitmap = ImagePool().GetBitmap(
			m_filePath.c_str() );
		return Util::CreateSubBitmap( pBitmap, 
			m_imgRect.Left(),
			m_imgRect.Top(),
			m_imgRect.Width(),
			m_imgRect.Height() );
	}

	Gdiplus::Image* CConfigData::GetGdiplusImagePtr( ) const
	{

		Gdiplus::Image* pBitmap = ImagePool().GetImage(
			m_filePath.c_str() );
		return Util::CreateSubImage( pBitmap, 
			m_imgRect.Left(),
			m_imgRect.Top(),
			m_imgRect.Width(),
			m_imgRect.Height() );
	}

	void	CConfigData::SetRect( const CRecti& rect )
	{
		m_imgRect = rect;
	}
#if defined(_WINDEF_) || defined( __wtypes_h__)
	void	CConfigData::SetColor( COLORREF color )
	{
		m_imgRect.m_nLeft = GetRValue(color);
		m_imgRect.m_nTop = GetRValue(color);
		m_imgRect.m_nWidth = GetRValue(color);
	}

	COLORREF CConfigData::GetColor( ) const
	{
		return RGB(m_imgRect.Left(),m_imgRect.Top(), m_imgRect.Width() );
	}

#endif
	bool CSkinConfig::GetConfigData(
		const XPath& strPath,CRefPtr<CConfigData>& configData ) const
	{
		for( std::map<XString,CRefPtr<CConfigData> >::const_iterator 
			it = m_mapConfig.begin(); it != m_mapConfig.end(); ++it )
		{
			if( NULL != _tcsstr( it ->first.c_str( ), strPath.c_str() ) )
			{
				configData = it ->second;
				return true;
			}
		}
		return false;
	}

#if defined(_WINDEF_) || defined( __wtypes_h__)
	COLORREF CSkinConfig::GetRGBColor( const XPath& strPath ) const
	{
		const CRecti& colorRect =  GetColor( strPath );
		return RGB(colorRect.Left(),colorRect.Top(),  colorRect.Width() );
	}
#endif
	CRecti CSkinConfig::GetColor( const XPath& strPath ) const
	{
		CRefPtr<CConfigData> configData;
		if( !GetConfigData( strPath,configData) )
		{
			AfxMessageBox( (_T("无法找到:") + strPath ).c_str() );
			return CRecti( );
		}
		return configData ->GetRect();
	}

	CBitmapRefPtr CSkinConfig::GetBitmap( const XPath& strPath ) const
	{
		CRefPtr<CConfigData> configData;
		if( !GetConfigData( strPath,configData) )
		{
			AfxMessageBox( (_T("无法找到:") + strPath ).c_str() );
			return NULL;
		}
		return configData ->GetImagePtr( );
	}

	Gdiplus::Image*	CSkinConfig::GetImage( const XPath& strPath ) const
	{
		CRefPtr<CConfigData> configData;
		if( !GetConfigData( strPath,configData) )
		{
			AfxMessageBox( (_T("无法找到:") + strPath ).c_str() );
			return NULL;
		}
		Gdiplus::Image* pImage = configData ->GetGdiplusImagePtr( );
		CImagePool( ).AddImage( strPath.c_str(), pImage );
		return pImage;
	}
}

