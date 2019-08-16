#pragma once
#include <map>
#include <string>
#include <reference_ptr.hpp>
#include "gdiobj_ptr.hpp"
namespace GlobalSkin
{
#ifdef _UNICODE
	typedef std::wstring XString;
#else
	typedef std::string XString;
#endif
	/* XPath支持的分隔符-linux文件的/分隔符 */
	typedef XString XPath;

	template <typename T>
	class CRectTemplate
	{
	public:
		typedef T value_type;
	public:
		CRectTemplate( 
			value_type nLeft = 0, value_type nTop = 0,
			value_type nWidth = 0, value_type nBottom = 0 )
			:m_nLeft( nLeft )
			,m_nTop( nTop )
			,m_nWidth( nWidth )
			,m_nHeight( nWidth )
		{ }
		value_type Left( ) const{ return m_nLeft; }
		value_type Top( ) const{ return m_nTop; }
		value_type Width( ) const{ return m_nWidth; }
		value_type Height( ) const{ return m_nHeight; }
		value_type Right( ) const{ return m_nLeft + m_nWidth; }
		value_type Bottom( ) const{ return m_nTop + m_nHeight; }
		bool IsValid( ) const { return  0!= m_nWidth&& 0 != m_nHeight;}
#if defined(_WINDEF_) || defined( __wtypes_h__)
		operator RECT( )
		{ 
			RECT r = 
			{
				m_nLeft,
				m_nTop,
				m_nLeft + m_nWidth,
				m_nTop + m_nHeight
			}; 
			return r; 
		}
#endif
	public:

		value_type	m_nLeft;
		value_type	m_nTop;
		value_type	m_nWidth;
		value_type	m_nHeight;
	};
	typedef CRectTemplate<int> CRecti;

	class CConfigData : public CReferenceObject
	{
		friend class CRefPtr<CConfigData>;
	public:
		bool	IsColor( ) const;
		void    SetIsColor( bool bIsColor );
		XPath	GetFilePath( ) const;
		void	SetFilePath( const XPath& strPath );
		CRecti	GetRect( ) const;
		void	SetRect( int nLeft, int nTop, int nWidth, int nHeight );
		void	SetRect( const CRecti& rect );
		CBitmapRefPtr	GetImagePtr( ) const;
#if defined(_WINDEF_) || defined( __wtypes_h__)
		void	SetColor( COLORREF color );
		COLORREF GetColor( ) const;
#endif
	private:
		XString		m_filePath;
		bool		m_bColor;
		CRecti		m_imgRect;
	};
	class CSkinConfig
	{
	public:
		virtual bool LoadFile( const XString& strPath ) = 0; 
		bool GetConfigData(
			const XPath& strPath,CRefPtr<CConfigData>& configData ) const;
#if defined(_WINDEF_) || defined( __wtypes_h__)
		COLORREF GetRGBColor( const XPath& strPath ) const;
#endif
		CRecti GetColor( const XPath& strPath ) const;
		CBitmapRefPtr	GetBitmap( const XPath& strPath ) const;

	protected:
		
		/* 配置数据 */
		std::map<XString,CRefPtr<CConfigData> >	m_mapConfig;;
	};
}


