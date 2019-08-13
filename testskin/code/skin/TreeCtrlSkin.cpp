#include "stdafx.h"
#include "TreeCtrlSkin.h"
#include "utils.hpp"

namespace GlobalSkin
{

void CTreeCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
	return;
}
/** 
 * @brief overide
 */
LPCTSTR CTreeCtrlSkin::GetHwndClassName( )
{
	return TEXT("SysTreeView32");
}
		
/** 
 * @brief overide
 */
bool CTreeCtrlSkin::OnInitSkinParam( HWND hWnd, CParamReference* pParam ) 
{
	return true;
}

}

