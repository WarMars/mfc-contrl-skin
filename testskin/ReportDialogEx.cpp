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
END_MESSAGE_MAP()


// CReportDialogEx ��Ϣ�������


BOOL CReportDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl* pTable = (CListCtrl*)GetDlgItem(IDC_LIST_HADRWARE_REPORT );
	if( NULL != pTable )
	{ 
		CRect rectTable;
		pTable ->GetClientRect( rectTable );
		int nColWidth = rectTable.Width() / 4;
		pTable ->InsertColumn(0, _T("�����Ŀ"), LVCFMT_CENTER, nColWidth);
		pTable ->InsertColumn(1, _T("�Ƿ�ϸ�"), LVCFMT_CENTER, nColWidth);
		pTable ->InsertColumn(2, _T("��ע"), LVCFMT_CENTER, nColWidth*2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
