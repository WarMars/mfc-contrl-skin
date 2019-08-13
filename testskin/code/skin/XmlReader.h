#pragma once
#include <skin/CtrlSkinConfig.h>

namespace GlobalSkin
{

class CXmlReader : public CSkinConfig
{
public:
	CXmlReader(void);
	CXmlReader( const XString& strPath );
	~CXmlReader(void);
	bool LoadFile( const XString& strPath );
};


}
