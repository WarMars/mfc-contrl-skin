#include "StdAfx.h"
#include "XmlReader.h"
#include "../../Markup.h"
#include "utils.hpp"

namespace GlobalSkin
{

CXmlReader::CXmlReader(void)
{
}

CXmlReader::CXmlReader( const XString& strPath )
{
	LoadFile(strPath);
}

CXmlReader::~CXmlReader(void)
{
}
bool Xml2XPathMap( 
	CMarkup& reader, 
	const XPath& strCurPath,
	std::map<XPath,CRefPtr<CConfigData> >& mapXml,
	const XPath& strRootPath );
bool CXmlReader::LoadFile( const XString& strPath )
{
	const CString& strFilePath = GetFilePath( strPath.c_str() );
	ASSERT( !strFilePath.IsEmpty() );
	CMarkup reader;
	if( !reader.Load( (LPCTSTR)strFilePath ) )
	{
		CString strInfo;
		strInfo.Format( _T("读取文件失败:%s,%s"),
			strPath.c_str(),
			MCD_2PCSZ( reader.GetError( ))
			);
		AfxMessageBox( strInfo );
		return false;
	}
	if( reader.FindChildElem( _T("control-skins") ) )
	{
		AfxMessageBox( _T("无法找到control-skins节点"));
		return false;
	}
	XPath strRootPath;
	if( reader.FindChildElem( _T("file") ) )
	{ 
		const MCD_STR& strValue = reader.GetAttrib(_T("rootpath") );
		strRootPath = MCD_2PCSZ( strValue );
		reader.OutOfElem();
	}
	if( strRootPath.empty() )
	{
		strRootPath = strPath.substr(0,
			strPath.find_last_of(TEXT("/\\") ) );
	}

	/* 遍历子节点 */
	if( !reader.FindChildElem( ) )
	{
		/* 错误的节点 */
		return false;
	}
	do 
	{
		Xml2XPathMap( reader,_T(""), m_mapConfig, strRootPath );
	} while ( reader.FindChildElem() );
	return !m_mapConfig.empty();
}


static bool Xml2XPathMap( 
	CMarkup& reader, 
	const XPath& strCurPath,
	std::map<XPath,CRefPtr<CConfigData> >& mapXml,
	const XPath& strRootPath )
{
	reader.IntoElem( );
	const XString& strNodeName =
		MCD_2PCSZ( reader.GetTagName( ) );
	const XPath& strLevelPath = strCurPath + _T('/') + strNodeName ;
	CRefPtr<CConfigData> configData = new CConfigData;
	configData ->SetIsColor( false );
	XPath strDiskPath = strRootPath;
	CRecti rect;
	for( int i = 0; ; ++i )
	{
		const MCD_STR& strAttribName = reader.GetAttribName( i );
		if( MCD_STRISEMPTY( strAttribName ) )
		{

			//const MCD_STR& strAttribName2 = reader.GetAttribName( ++i );
			//const MCD_STR& strAttribName3 = reader.GetAttribName( ++i );
			//const MCD_STR& strAttribName4 = reader.GetAttribName( ++i );
			/* 结束 */
			break;
		}
		if( strAttribName == _T("filename") )
		{
			const XPath& strName = MCD_2PCSZ(
				reader.GetAttrib( MCD_2PCSZ(strAttribName) ) );
			if( !strName.empty() )
			{
				strDiskPath += TEXT("\\") + strName;
			}
			continue;
		}

		int nValue = _ttoi( MCD_2PCSZ(
			reader.GetAttrib( MCD_2PCSZ(strAttribName) ) ) );

		if( strAttribName == _T("left") )
		{
			rect.m_nLeft = nValue;
		}
		else if( strAttribName == _T("top") )
		{
			rect.m_nTop = nValue;
		}
		else if( strAttribName == _T("width") )
		{
			rect.m_nWidth = nValue;
		}
		else if( strAttribName == _T("height") )
		{
			rect.m_nHeight = nValue;
		}
		else if( strAttribName == _T("red") )
		{
			configData ->SetIsColor(true);
			rect.m_nLeft = nValue;
		}
		else if( strAttribName == _T("green") )
		{
			configData ->SetIsColor(true);
			rect.m_nTop = nValue;
		}
		else if( strAttribName == _T("blue") )
		{
			configData ->SetIsColor(true);
			rect.m_nWidth = nValue;

		}

	}
	if( strLevelPath.find( TEXT("popupmenu/color/parentbk") ) != -1  )
	{
		int i = 0;
		++i;
	}
	if( configData ->IsColor( ) || rect.IsValid() )
	{
		configData ->SetRect( rect );
		configData ->SetFilePath( strDiskPath );
		mapXml[strLevelPath]  = configData;
		// 此节点遍历完成。
		reader.OutOfElem( );
		return true;
	}
	
	/* 继续遍历子节点 */
	if( !reader.FindChildElem( ) )
	{
		/* 错误的节点 */
		reader.OutOfElem( );
		return false;
	}
	bool bRet = false;
	do 
	{
		if( Xml2XPathMap( reader,strLevelPath, mapXml, strDiskPath ) )
		{
			bRet = true;
		}
	} while ( reader.FindChildElem() );

	/* 退出当前级别的节点 */
	reader.OutOfElem( );
	return bRet;
}

}
