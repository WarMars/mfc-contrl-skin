// ReportDialogEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testskin.h"
#include "ReportDialogEx.h"
#include "afxdialogex.h"


// CReportDialogEx �Ի���

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


// CReportDialogEx ��Ϣ�������


BOOL CReportDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT);
	SetWindowText(CTime::GetCurrentTime().Format(
		_T("%Y-%M-%d %H:%M:%S ����")));
	if (NULL != pTable)
	{
		m_tableImgList.Create(1, 48, TRUE | ILC_COLOR32, 1, 0);
		pTable ->SetImageList(&m_tableImgList, LVSIL_SMALL);
		pTable->SetExtendedStyle(
			pTable ->GetExtendedStyle()| LVS_EX_GRIDLINES );
		CRect rectTable;
		pTable->GetClientRect(rectTable);
		
		int nColWidth = rectTable.Width() / 4;
		pTable->InsertColumn(0, _T("�����Ŀ"), LVCFMT_CENTER, nColWidth);
		pTable->InsertColumn(1, _T("�Ƿ�ϸ�"), LVCFMT_CENTER, nColWidth);
		pTable->InsertColumn(2, _T("��ע"), LVCFMT_CENTER, nColWidth * 2);

	}
	ClearItem();
	AddItem(_T("CPU"), true, _T("״̬����"));
	AddItem(_T("GPU"), true, _T("δʹ��"));
	AddItem(_T("�ڴ�"), !true, _T("�Ѿ��ľ�"));
	AddItem(_T("����"), !true, _T("�����������"));
	AddItem(_T("������Ŀ"), !true, _T("��ǰ��������2������"));
	AddItem(_T("USB�豸"), !true, _T("��ǰʹ��USB�豸��ĿΪ3"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	pTable->SetItemText(nRowCount, 1, bIsPassed ? _T("��") : _T("��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

		int nRowIndex = INT(pNMCD->nmcd.dwItemSpec);//��
		if (-1 != pTable->GetItemText(nRowIndex, 1).Find(_T("��")))
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

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_REPORTRESULT:
		break;
	default:
		break;
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
