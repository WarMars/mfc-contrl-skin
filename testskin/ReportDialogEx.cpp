// ReportDialogEx.cpp : 实现文件
//

#include "stdafx.h"
#include "testskin.h"
#include "ReportDialogEx.h"
#include "afxdialogex.h"


// CReportDialogEx 对话框

IMPLEMENT_DYNAMIC(CReportDialogEx, CDialogEx)

CReportDialogEx::CReportDialogEx(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReportDialogEx::IDD, pParent)
{

}

CReportDialogEx::~CReportDialogEx()
{
}

void CReportDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReportDialogEx, CDialogEx)
END_MESSAGE_MAP()


// CReportDialogEx 消息处理程序


BOOL CReportDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT );
	if( NULL != pTable )
	{ 
		CRect rectTable;
		pTable ->GetClientRect( rectTable );
		int nColWidth = rectTable.Width() / 4;
		pTable ->InsertColumn(0, _T("检测项目"), LVCFMT_CENTER, nColWidth);
		pTable ->InsertColumn(1, _T("是否合格"), LVCFMT_CENTER, nColWidth);
		pTable ->InsertColumn(2, _T("备注"), LVCFMT_CENTER, nColWidth*2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
