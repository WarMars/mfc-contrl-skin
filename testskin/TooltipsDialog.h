#pragma once


// tooltips��ʾ �Ի���

class CTooltipsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTooltipsDialog)

public:
	CTooltipsDialog(); // ��׼���캯��
	CTooltipsDialog(UINT nIDTemplate, CWnd *pParent = NULL);
	CTooltipsDialog(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);

	virtual ~CTooltipsDialog();
public:
	
	/*!
	 * @brief ���һ��tooltips
	 * @param nCtrlId �ؼ���id
	 * @param lpszTipsText tooltips���ı�
	 * @return �ɹ�����true,���򷵻�false
	 * @note 
	 */
	bool AddTooltips(UINT nCtrlID, LPCTSTR lpszTipsText );
// �Ի�������

protected:

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CToolTipCtrl	m_wndTooltips;

	virtual void OnOK();
	virtual void OnCancel();
};
