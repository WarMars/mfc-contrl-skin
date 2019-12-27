
// testskin.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "testskin.h"
#include "testskinDlg.h"
#include "skin/GlobalUiManager.h"
#include <skin/XmlReader.h>
#include "code/ImageManager.h"
#include <cmath>
#include "ReportDialogEx.h"
//#include <vld.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "gdi_leak/source/apihook/gdi/Gdi.hpp"
#include "GDIPlusWrapper.h"
//#include "gdi_leak/source/apihook/APIHook.hpp"
#include "GdiplusWrapper.h"
// CtestskinApp

BEGIN_MESSAGE_MAP(CtestskinApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtestskinApp ����

CtestskinApp::CtestskinApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CtestskinApp ����

CtestskinApp theApp;

int test0( )
{
	using namespace apihook;

	// ������ջ��¼

	apihook::StackWalker::Inst().Enable();



	// Hook DeleteObject�����뿪

	apihook::gdi_base::EnableHook();



	// ��������ʹ�ܣ�����ע�͵�����Ҫ��

	apihook::gdi_pen::EnableHook();

	apihook::gdi_font::EnableHook();

	apihook::gdi_dc::EnableHook();

	apihook::gdi_bitmap::EnableHook();

	apihook::gdi_brush::EnableHook();

	apihook::gdi_extpen::EnableHook();

	apihook::gdi_palette::EnableHook();

	apihook::gdi_region::EnableHook();

	return 0;
}

int test1( )
{

	// ����һ��ʱ��󣬻��߲���ĳ������󣬴�ӡй©��Ϣ��ִ��Ŀ¼��

	// ��ӡ��Ҫͨ��DeleteObject�ͷŵ�й©��ַ

	apihook::gdi_base::MyStacks_base::Inst().Dump("xgdi.leak");



	// ��ӡ��Ҫͨ��ReleaseDC�ͷŵ�й©��ַ����Ҫ����gdi_dc

	apihook::gdi_dc::MyStacks_relasedc::Inst().Dump("xreleasedc.leak");



	// ��ӡ��Ҫͨ��DeleteDC�ͷŵ�й©��ַ����Ҫ����gdi_dc

	apihook::gdi_dc::MyStacks_deletedc::Inst().Dump("xdeletedc.leak");

	return 0;
}
// CtestskinApp ��ʼ��
namespace MYTEST
{
	float xKey2Longitude( int nXKey, float fZ )
	{
		return nXKey / std::pow(2.0f, fZ) * 360.0f - 180.0f;
	}


	float yKey2Latitude( int nYKey, float fZ )
	{
		double dTemp =  M_PI - 2.0f * M_PI * nYKey / std::pow(2.0f, fZ);

		return float( 180.0f / M_PI * std::atan(0.5f * 
			( std::exp(dTemp) - std::exp(-dTemp) ) ));

	}
}
BOOL CtestskinApp::InitInstance()
{
	//float floatArray[] = 
	//{
	//	MYTEST::xKey2Longitude( 123);
	//};
	//test0( );
	DWORD dwTime = GetDoubleClickTime( );
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	GdiplusWrapper::CGdiplusWrapper wrapper;
	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	//AfxEnableMemoryTracking( TRUE );
	//AfxEnableMemoryLeakDump( TRUE );
	GlobalSkin::CXmlReader* pReader = new GlobalSkin::CXmlReader;
	pReader ->LoadFile(_T("ui\\skin\\skin-config.xml") );
	//GlobalSkin::CGlobalUiManager uiManager( pReader );
	delete pReader;
	CReportDialogEx dlg;
	//CtestskinDlg dlg;
	{
		//ASSERT(false);
	//	AfxMessageBox( _T("���Դ���") );
	}
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CtestskinApp::ExitInstance()
{
	ImagePool( ).TidyUp();
	// TODO: �ڴ����ר�ô����/����û���
	//_CrtDumpMemoryLeaks( );
	//test1( );
	return CWinApp::ExitInstance();
}
