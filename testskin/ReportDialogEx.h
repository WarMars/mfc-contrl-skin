#pragma once


// CReportDialogEx �Ի���

class CReportDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CReportDialogEx)

public:
	CReportDialogEx(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportDialogEx();

// �Ի�������
	enum { IDD = IDD_DIALOG_HADRDWARE_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
