#pragma once


// tooltips提示 对话框

class CTooltipsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTooltipsDialog)

public:
	CTooltipsDialog(); // 标准构造函数
	CTooltipsDialog(UINT nIDTemplate, CWnd *pParent = NULL);
	CTooltipsDialog(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);

	virtual ~CTooltipsDialog();
public:
	
	/*!
	 * @brief 添加一个tooltips
	 * @param nCtrlId 控件的id
	 * @param lpszTipsText tooltips的文本
	 * @return 成功返回true,否则返回false
	 * @note 
	 */
	bool AddTooltips(UINT nCtrlID, LPCTSTR lpszTipsText );
// 对话框数据

protected:

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CToolTipCtrl	m_wndTooltips;

	virtual void OnOK();
	virtual void OnCancel();
};
