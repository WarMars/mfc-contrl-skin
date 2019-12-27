// TooltipsDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testskin.h"
#include "TooltipsDialog.h"
#include "afxdialogex.h"


// CTooltipsDialog �Ի���

IMPLEMENT_DYNAMIC(CTooltipsDialog, CDialogEx)


CTooltipsDialog::CTooltipsDialog() // ��׼���캯��
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


// CTooltipsDialog ��Ϣ�������


BOOL CTooltipsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ʼ��
	m_wndTooltips.Create( this );
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool CTooltipsDialog::AddTooltips(UINT nCtrlID, LPCTSTR lpszTipsText )
{
	//��ȡ
	CWnd* pWnd = GetDlgItem(nCtrlID);
	ASSERT( NULL != pWnd );
	if( NULL == pWnd )
	{
		return false;
	}
	//���
	return TRUE == m_wndTooltips.AddTool( pWnd, lpszTipsText );
}

BOOL CTooltipsDialog::PreTranslateMessage(MSG* pMsg)
{
	//if( TRUE == IsWindow( m_wndTooltips.GetSafeHwnd() )
	{
		//��Ϣ���˴���
		m_wndTooltips.RelayEvent( pMsg );
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTooltipsDialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CTooltipsDialog::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}
