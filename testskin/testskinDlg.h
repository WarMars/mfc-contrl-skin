
// testskinDlg.h : ͷ�ļ�
//

#pragma once
//#include "Layout.h"

// CtestskinDlg �Ի���
class CtestskinDlg : public CDialogEx
{
// ����
public:
	CtestskinDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTSKIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	CStatusBar   m_wndStatusBar; 
	CToolBar	 m_wndToolBar;
	//CVBoxLayout	 m_layout;
};
