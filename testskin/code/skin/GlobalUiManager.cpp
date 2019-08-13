#include "StdAfx.h"
#include "GlobalUiManager.h"
#include "ButtonCtrlSkin.h"
#include "EditCtrlSkin.h"
#include "ComboboxCtrlSkin.h"
#include "ListBoxCtrlSkin.h"
#include "ComboLBoxCtrlSkin.h"
#include "CheckBoxCtrlSkin.h"
#include "RadioButtonCtrlSkin.h"
#include "PushButtonCtrlSkin.h"
#include "GroupBoxCtrlSkin.h"
#include "ListCtrlSkin.h"
#include "SysHeaderSkin.h"
#include "DialogBoxSkin.h"
#include "PopupMenuCtrlSkin.h"
#include "TabCtrlSkin.h"
#include "StatusBarCtrlSkin.h"
#include "ToolBarCtrlSkin.h"
#include "TreeCtrlSkin.h"
#include "SpinCtrlSkin.h"
#include "SliderCtrlSkin.h"
#include "ProgressBarCtrlskin.h"
#include "ScrollBarCtrlSkin.h"
#include "MenuBarCtrlSkin.h"

namespace GlobalSkin
{

/** 
 * @brief ��ǰ�Ӵ������о����еİ�ť
 */
static BOOL CALLBACK ChildWndEnumProc(HWND hWnd, LPARAM lParam)
{
	CGlobalUiManager* pManager = (CGlobalUiManager*)lParam;
	if( NULL != pManager )
	{
		pManager ->Add( hWnd );
	}
	EnumChildWindows(hWnd, ChildWndEnumProc, lParam );
	return TRUE;
}

/** 
 * @brief ���ҵ�ǰ����
 */
static BOOL CALLBACK  WndEnumProc(HWND hWnd, LPARAM lParam)
{
	CGlobalUiManager* pManager = (CGlobalUiManager*)lParam;
	if( NULL != pManager )
	{
		pManager ->Add( hWnd );
	}
	EnumChildWindows(hWnd, ChildWndEnumProc, lParam );
	return TRUE;
}

/** 
 * @brief ���ڹ��̹���
 */
static LRESULT CALLBACK WndHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = CallNextHookEx( 
		CGlobalUiManager::GetPtr() ->m_pPreviosHook,
		code, wParam, lParam );
	if ((((CWPSTRUCT *) lParam)->message == WM_CREATE) && (code >= 0))
	{
		PCWPSTRUCT pMsg = PCWPSTRUCT (lParam);
		//�����´��ڴ���
		WNDPROC pOldProc = NULL;
		CGlobalUiManager::GetPtr( ) ->Add ( pMsg ->hwnd, &pOldProc );
		if( NULL != pOldProc )
		{
			//pOldProc( pMsg ->hwnd, pMsg ->message, pMsg ->wParam, pMsg ->lParam);
		}
	}
	return lResult;
}

/** 
 * @brief Ƥ���Ĵ������
 */
static LRESULT CALLBACK ControlSkinProc(
	HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	if( WM_CREATE == nMsg )
	{
		int i = 0;
		++i;
	}
	return ( NULL != CGlobalUiManager::s_pSkinManager )?
	CGlobalUiManager::s_pSkinManager ->HandleWndProc(
			hWnd, nMsg, wParam, lParam ):
	AfxWndProc( hWnd, nMsg, wParam, lParam );
	
}
CGlobalUiManager* CGlobalUiManager::s_pSkinManager = NULL;
CGlobalUiManager::CGlobalUiManager( const CSkinConfig* pConfig )
{
	if( NULL != s_pSkinManager )
	{
		AfxMessageBox(_T("Ƥ����������ʱ������ͬʱ���ڶ��ʵ��"));
		return;
	}
	s_pSkinManager = this;
	InstallSkin( pConfig );
}

CGlobalUiManager::CGlobalUiManager( const CSkinConfig& config )
{
	if( NULL != s_pSkinManager )
	{
		AfxMessageBox(_T("Ƥ����������ʱ������ͬʱ���ڶ��ʵ��"));
		return;
	}
	s_pSkinManager = this;
	InstallSkin( &config );
}

CGlobalUiManager::~CGlobalUiManager( )
{
	UninstallSkin( );
	s_pSkinManager = NULL;
}
/** 
 * @brief ��װƤ��
 */
void CGlobalUiManager::InstallSkin( const CSkinConfig* pConfig )
{
	// �����Ҫ��װ�µ�Ƥ�����������������Ƥ������

	m_vectorCtrlSkins.push_back( new CPushButtonCtrl );      // ��ťƤ��
	m_vectorCtrlSkins.push_back( new CEditCtrlSkin );        // �ı���Ƥ��
	m_vectorCtrlSkins.push_back( new CComboBoxCtrlSkin );    // ��Ͽ�Ƥ��
	m_vectorCtrlSkins.push_back( new CListBoxCtrlSkin );     // �б��Ƥ��
	m_vectorCtrlSkins.push_back( new CComboLBoxCtrlSkin );   // ��Ͽ��е��б��
	m_vectorCtrlSkins.push_back( new CCheckBoxCtrlSkin );    // ��ѡ��
	m_vectorCtrlSkins.push_back( new CRadioButtonCtrlSkin ); // ��ѡ��
	m_vectorCtrlSkins.push_back( new CGroupBoxCtrlSkin );    // groupbox
	m_vectorCtrlSkins.push_back( new CListCtrlSkin );		 // ���
	m_vectorCtrlSkins.push_back( new CSysHeaderSkin );		 // ����
	m_vectorCtrlSkins.push_back( new CDialogBoxSkin );		 // �Ի���
	m_vectorCtrlSkins.push_back( new CPopupMenuCtrlSkin );	 // �����˵�
	m_vectorCtrlSkins.push_back( new CTablCtrlSkin );		 // tab�ؼ�
	m_vectorCtrlSkins.push_back( new CTreeCtrlSkin );		 // ��״�ؼ�
	m_vectorCtrlSkins.push_back( new CStatusBarCtrlSkin );   // ״̬��
	m_vectorCtrlSkins.push_back( new CToolBarCtrlSkin );     // ������
	m_vectorCtrlSkins.push_back( new CSpinCtrlSkin );		 // Spin
	m_vectorCtrlSkins.push_back( new CSilderCtrlSkin );		 // ����
	m_vectorCtrlSkins.push_back( new CProgressBarCtrlSkin ); // ������

	m_pScrollBarCtrlSkin = new DynamicParam::CScrollBarCtrlSkin;
	m_pMenuBarCtrlSkin = new DynamicParam::CMenubarCtrlSkin;
	m_pScrollBarCtrlSkin ->LoadSkin(pConfig);
	m_pMenuBarCtrlSkin ->LoadSkin( pConfig );
	void* p1 = &m_pScrollBarCtrlSkin;
	void* p2 = &m_pMenuBarCtrlSkin;
	int nSize = sizeof(p1);
	for( std::size_t i = 0; i< m_vectorCtrlSkins.size(); ++i )
	{
		CCtrlSkin* pCtrl = m_vectorCtrlSkins.at(i);
		pCtrl ->SetUiManager( this );
		pCtrl ->LoadSkin( pConfig );
	}
	// �滻��ǰ���ڵĿؼ�
	EnumThreadWindows(GetCurrentThreadId(), WndEnumProc, (LPARAM)this ); 

	// ���������滻
	m_pPreviosHook  = SetWindowsHookEx(
		WH_CALLWNDPROC,  WndHookProc , NULL,  GetCurrentThreadId() );
}

/** 
 * @brief ж��Ƥ��
 */
void CGlobalUiManager::UninstallSkin( )
{
	if(FALSE == UnhookWindowsHookEx(m_pPreviosHook) )
	{
		TRACE(_T("UnhokkWindowsHookExʧ��:%d"),GetLastError() );
	}
	m_pPreviosHook = NULL;
	m_vectorCtrlSkins.clear();
}

bool CGlobalUiManager::Add( HWND hWnd,WNDPROC* pOldProc )
{
	switch ( GetWindowLong( hWnd, GWL_STYLE ) & SS_TYPEMASK)
	{
	case BS_OWNERDRAW:  
		//�����Ի��ư�ť
		return NULL;
	}

	for( std::vector<CCtrlSkinPtr>::iterator it = m_vectorCtrlSkins.begin();
		it != m_vectorCtrlSkins.end(); ++it )
	{
		if( (*it)->AddControl( hWnd, ControlSkinProc,pOldProc ) )
		{
			return true;
		}
	}
	return false;
}

bool CGlobalUiManager::Remove( HWND hWnd )
{

	for( std::vector<CCtrlSkinPtr>::iterator it = m_vectorCtrlSkins.begin();
		it != m_vectorCtrlSkins.end(); ++it )
	{
		if( (*it) ->RemoveControl( hWnd) )
		{
			return true;
		}
	}
	return false;
}


DynamicParam::CScrollBarCtrlSkin* CGlobalUiManager::GetScrollBarCtrlSkin( )
{
	return m_pScrollBarCtrlSkin;
}

DynamicParam::CMenubarCtrlSkin* CGlobalUiManager::GetMenuBarCtrlSkin( )
{
	return m_pMenuBarCtrlSkin;
}

LRESULT CGlobalUiManager::HandleWndProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//����
	sCtrlParameter* pParam = NULL;
	CCtrlSkin* pSkin = NULL;
	for( std::vector<CCtrlSkinPtr>::iterator it = m_vectorCtrlSkins.begin();
		it != m_vectorCtrlSkins.end(); ++it )
	{
		if( (*it) ->CheckOwner( hWnd, pParam ) )
		{
			pSkin = it->get();
			break;
		}
	}
	if( NULL == pParam || NULL == pSkin )
	{
		//������ζ����Ƴ����˴���Զ��Ӧ��ִ��
		return AfxWndProc( hWnd,
			nMsg, wParam,lParam );
	}

	switch (nMsg)
	{
	case WM_NCDESTROY: 
		{ //�ؼ�����
			WNDPROC lpProc = pParam ->m_pPreviousProc;
			Remove( hWnd );
			
			return ::CallWindowProc(
				lpProc,
				hWnd, nMsg, wParam, lParam );
		} 
		break;
	default:
		break;
	}
	//Ϊ����������ã�����
	MSG& msgLast = AfxGetThreadState()->m_lastSentMsg;
	MSG  msgCur = msgLast;  
	msgLast.hwnd = hWnd;
	msgLast.message = nMsg;
	msgLast.wParam  = wParam;
	msgLast.lParam  = lParam;

	//�ҵ���ť����
	LRESULT lResult;

	//�����¼���������
	lResult = pSkin ->OnWndProc( nMsg, wParam, lParam );

	// �ָ�״̬
	msgLast = msgCur;			
	return lResult;
}

}