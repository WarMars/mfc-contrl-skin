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
	void ClearItem();
	void AddItem(const CString& strName, bool bIsPassed, const CString& strDetialed);
	void SetResultComment(const CString& strName);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawListHadrwareReport(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	CImageList			m_tableImgList;
};
