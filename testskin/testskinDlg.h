
// testskinDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
//#include "Layout.h"
#include "PictureStatic.h"
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
public:
	CPictureStatic m_staticGdiPlus;
	bool m_bRadio1Checked;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	float m_fTest;
	float m_fTest1;
	CToolTipCtrl	m_wndToolTips;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();
};
