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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_HADRWARE_REPORT, &CReportDialogEx::OnNMCustomdrawListHadrwareReport)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CReportDialogEx 消息处理程序


BOOL CReportDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT);
	SetWindowText(CTime::GetCurrentTime().Format(
		_T("%Y-%M-%d %H:%M:%S 报告")));
	if (NULL != pTable)
	{
		m_tableImgList.Create(1, 48, TRUE | ILC_COLOR32, 1, 0);
		pTable ->SetImageList(&m_tableImgList, LVSIL_SMALL);
		pTable->SetExtendedStyle(
			pTable ->GetExtendedStyle()| LVS_EX_GRIDLINES );
		CRect rectTable;
		pTable->GetClientRect(rectTable);
		
		int nColWidth = rectTable.Width() / 4;
		pTable->InsertColumn(0, _T("检测项目"), LVCFMT_CENTER, nColWidth);
		pTable->InsertColumn(1, _T("是否合格"), LVCFMT_CENTER, nColWidth);
		pTable->InsertColumn(2, _T("备注"), LVCFMT_CENTER, nColWidth * 2);

	}
	ClearItem();
	AddItem(_T("CPU"), true, _T("状态良好"));
	AddItem(_T("GPU"), true, _T("未使用"));
	AddItem(_T("内存"), !true, _T("已经耗尽"));
	AddItem(_T("磁盘"), !true, _T("即将到达红线"));
	AddItem(_T("网卡数目"), !true, _T("当前仅开启了2个网卡"));
	AddItem(_T("USB设备"), !true, _T("当前使用USB设备数目为3"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReportDialogEx::ClearItem()
{
	CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT);
	ASSERT(NULL != pTable);
	if (NULL == pTable)
	{
		return;
	}
	pTable->SetItemCount(0);
}

void CReportDialogEx::AddItem(const CString& strName, bool bIsPassed, const CString& strDetialed)
{
	CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT);
	ASSERT(NULL != pTable);
	if (NULL == pTable)
	{
		return;
	}
	int nRowCount = pTable->GetItemCount();
	//nRowCount += 1;
	pTable->InsertItem(nRowCount,/* 0,*/ strName);
	pTable->SetItemText(nRowCount, 1, bIsPassed ? _T("是") : _T("否"));
	pTable->SetItemText(nRowCount, 2, strDetialed);
}

void CReportDialogEx::SetResultComment(const CString& strName)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_REPORTRESULT);
	ASSERT(NULL != pEdit);
	if (NULL == pEdit)
	{
		return;
	}
	pEdit->SetWindowText(strName);
}


void CReportDialogEx::OnNMCustomdrawListHadrwareReport(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	switch (pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	break;
	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	break;
	case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
	{
		CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT);
		ASSERT(NULL != pTable);
		if (NULL == pTable)
		{
			*pResult = 0;
			break;
		}

		int nRowIndex = INT(pNMCD->nmcd.dwItemSpec);//行
		if (-1 != pTable->GetItemText(nRowIndex, 1).Find(_T("是")))
		{
			pNMCD->clrTextBk = RGB(255, 150, 150);
		}
		else
		{
			pNMCD->clrTextBk = RGB(150, 255, 150);
		}

	}
	*pResult = 0;
	break;
	default:
	{
		*pResult = 0;
	}
		break;

	}

}


HBRUSH CReportDialogEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_REPORTRESULT:
		break;
	default:
		break;
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
