
// testskin.cpp : 定义应用程序的类行为。
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


// CtestskinApp 构造

CtestskinApp::CtestskinApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CtestskinApp 对象

CtestskinApp theApp;

int test0( )
{
	using namespace apihook;

	// 启动堆栈记录

	apihook::StackWalker::Inst().Enable();



	// Hook DeleteObject，必须开

	apihook::gdi_base::EnableHook();



	// 各个对象使能，自行注释掉不需要的

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

	// 运行一段时间后，或者操作某个界面后，打印泄漏信息到执行目录下

	// 打印需要通过DeleteObject释放的泄漏地址

	apihook::gdi_base::MyStacks_base::Inst().Dump("xgdi.leak");



	// 打印需要通过ReleaseDC释放的泄漏地址，需要开启gdi_dc

	apihook::gdi_dc::MyStacks_relasedc::Inst().Dump("xreleasedc.leak");



	// 打印需要通过DeleteDC释放的泄漏地址，需要开启gdi_dc

	apihook::gdi_dc::MyStacks_deletedc::Inst().Dump("xdeletedc.leak");

	return 0;
}
// CtestskinApp 初始化
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
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	GdiplusWrapper::CGdiplusWrapper wrapper;
	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
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
	//	AfxMessageBox( _T("测试窗口") );
	}
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CtestskinApp::ExitInstance()
{
	ImagePool( ).TidyUp();
	// TODO: 在此添加专用代码和/或调用基类
	//_CrtDumpMemoryLeaks( );
	//test1( );
	return CWinApp::ExitInstance();
}
