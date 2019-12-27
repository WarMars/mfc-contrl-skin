#include "StdAfx.h"
#include "UiDefines.h"

namespace Ui
{

HBRUSH	GetNormalEditBrush( )
{
	static CBrush brush(COLOR_EDIT_NORMAL);
	return (HBRUSH)brush.GetSafeHandle( );
}

HBRUSH  GetFocusedEditBrush( )
{
	static CBrush brush(COLOR_EDIT_FOCUSED);
	return (HBRUSH)brush.GetSafeHandle( );
}


int GetVerticalBorderSpacing( )
{
	return 9/3;
}

int GetHorizontalBorderSpacing( )
{
	return 9;
}

int GetVerticalSpacing( )
{
	return 9*3;
}

int GetHorizontalSpacing( )
{
	return 9*2;
}

CFont*  GetEditFont( CWnd* pWnd )
{
	static CFont font;
	if( NULL != font.GetSafeHandle() )
	{
		return &font;
	}
	if( NULL == pWnd )
	{
		return &font;
	}
	CFont* pWndFont = pWnd ->GetFont();
	if( NULL == pWndFont )
	{
		return &font;
	}
	LOGFONT lf = {0};
	pWndFont ->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	font.CreateFontIndirect( &lf );
	return &font;
}
#if 0
void InitFont( int nFontSize,const CString& strFamily )
{
	//设置正常字体
	LOGFONT lf;   
	afxGlobalData.fontRegular.GetLogFont(&lf);   
	afxGlobalData.fontRegular.DeleteObject();   
	lf.lfHeight = -nFontSize;   
	lstrcpy(lf.lfFaceName, strFamily);   
	afxGlobalData.fontRegular.CreateFontIndirect(&lf);  

	//设置加粗的字体 
	afxGlobalData.fontBold.GetLogFont(&lf);   
	afxGlobalData.fontBold.DeleteObject();   
	lf.lfHeight = -nFontSize;   
	lstrcpy(lf.lfFaceName, strFamily);   
	afxGlobalData.fontBold.CreateFontIndirect(&lf);

	afxGlobalData.fontTooltip.GetLogFont(&lf);   
	afxGlobalData.fontTooltip.DeleteObject();   
	lf.lfHeight = -nFontSize;   
	lstrcpy(lf.lfFaceName, strFamily );   
	afxGlobalData.fontTooltip.CreateFontIndirect(&lf);
}

#endif

CUiDefines::CUiDefines(void)
{
}


CUiDefines::~CUiDefines(void)
{
}

}
