
// testskinDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
//#include "Layout.h"
#include "PictureStatic.h"
// CtestskinDlg 对话框
class CtestskinDlg : public CDialogEx
{
// 构造
public:
	CtestskinDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTSKIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
