#include "stdafx.h"
#include "EditCtrlSkin.h"
#include <Windows.h>
#include "ImageManager.h"

#ifdef USING_CONFIG_FILE
# include "CtrlSkinConfig.h"
#endif // USING_CONFIG_FILE


namespace GlobalSkin
{

CEditCtrlSkin::CEditCtrlSkin()
{

}

void CEditCtrlSkin::LoadSkin( const CSkinConfig* pConfig )
{
#ifdef USING_CONFIG_FILE
	if( NULL == pConfig )
#endif
	{
		m_pBorderBmp = ImagePool( ).GetBitmap( 
			TEXT("ui\\skin\\edit.bmp") );
		return;
	}
#ifdef USING_CONFIG_FILE
	m_pBorderBmp = pConfig ->GetBitmap(TEXT("edit/border/background") );
#endif
}

void CEditCtrlSkin::SetBorderBmp( CBitmapRefPtr pBitmap )
{
	m_pBorderBmp = pBitmap;
}
/** 
	* @brief ���ڹ��̴���
	*/
LRESULT	CEditCtrlSkin::OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_PAINT:
		OnPaint();
		return 0;
		break;
	default:
		break;
	}
	return OnPreviousWndProc( GetCurHwnd( ), nMsg, wParam, lParam );
}
		

void CEditCtrlSkin::OnPaint( )
{
	OnAutoDefaultWndProc();
	if( IsNull() )
	{
		return;
	}
	/* ���û�б߿�ֱ�ӷ��� */
	if( !GetCurParam() ->HasBorder() )
	{
		return;
	}
	if( NULL == GetCurHwnd( ) )
	{
		return;
	}
	HDC hDC=::GetWindowDC(GetCurHwnd( ));
	if( NULL == hDC )
	{
		return;
	}
	//TRACE("CALLING ME\n");
	//if( m_pCurParam ->m_bBorder )
	{
		CRect rectWindow;
		::GetWindowRect(GetCurHwnd( ),&rectWindow );
		rectWindow.OffsetRect( 
			-rectWindow.left, 
			-rectWindow.top );
		
		HBRUSH hBrush = ::CreatePatternBrush(
			(HBITMAP)m_pBorderBmp->GetSafeHandle() );
		/* ���Ʊ߿� */
		::FrameRect(hDC,&rectWindow, hBrush);
		rectWindow.InflateRect(-1,-1);
		/* �߿�̫ϸ���ڲ��ٻ���һ�㣺
		   ���ַ������ӱ�������������ʣ�ȥ����
		 */
		::FrameRect(hDC, &rectWindow, hBrush );
		DeleteObject( hBrush );
		::ReleaseDC(GetCurHwnd( ),hDC);
	}
	OnNcPaint( NULL );

}

/** 
	* @brief ��ȡ��ǰ�Ĵ�������
	*/
LPCTSTR CEditCtrlSkin::GetHwndClassName( )
{
	return TEXT("Edit");
}

/** 
	* @brief �ӹܿؼ�Ƥ��֮ǰ
	*/
bool CEditCtrlSkin::OnInitSkinParam( HWND hWnd, CParamReference* pParam )
{
	//LONG lStyle = GetWindowLong( hWnd, GWL_STYLE );
	//pParam ->SetHasBorder(
	//	0 != ( lStyle & (WS_THICKFRAME | 
	//	WS_DLGFRAME | WS_BORDER) ) );
	UNUSED(hWnd);
	UNUSED(pParam);
	return true;
}

CEditCtrlSkin::~CEditCtrlSkin()
{

}


}


