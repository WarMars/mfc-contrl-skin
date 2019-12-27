// TooltipsDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "testskin.h"
#include "TooltipsDialog.h"
#include "afxdialogex.h"


// CTooltipsDialog 对话框

IMPLEMENT_DYNAMIC(CTooltipsDialog, CDialogEx)


CTooltipsDialog::CTooltipsDialog() // 标准构造函数
	:CDialogEx()
{

}

CTooltipsDialog::CTooltipsDialog(UINT nIDTemplate, CWnd *pParent )
	:CDialogEx( nIDTemplate, pParent )
{

}
CTooltipsDialog::CTooltipsDialog(LPCTSTR lpszTemplateName, CWnd *pParentWnd )
	:CDialogEx(lpszTemplateName, pParentWnd)
{
}

CTooltipsDialog::~CTooltipsDialog()
{
}

void CTooltipsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTooltipsDialog, CDialogEx)
END_MESSAGE_MAP()


// CTooltipsDialog 消息处理程序


BOOL CTooltipsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始胡
	m_wndTooltips.Create( this );
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

bool CTooltipsDialog::AddTooltips(UINT nCtrlID, LPCTSTR lpszTipsText )
{
	//获取
	CWnd* pWnd = GetDlgItem(nCtrlID);
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	//添加
	return TRUE == m_wndTooltips.AddTool( pWnd, lpszTipsText );
}

BOOL CTooltipsDialog::PreTranslateMessage(MSG* pMsg)
{
	//if( TRUE == IsWindow( m_wndTooltips.GetSafeHwnd() )
	{
		//消息过滤处理
		m_wndTooltips.RelayEvent( pMsg );
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTooltipsDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CTooltipsDialog::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}
