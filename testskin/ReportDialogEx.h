#pragma once


// CReportDialogEx 对话框

class CReportDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CReportDialogEx)

public:
	CReportDialogEx(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportDialogEx();

// 对话框数据
	enum { IDD = IDD_DIALOG_HADRDWARE_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
