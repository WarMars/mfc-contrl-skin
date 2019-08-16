#pragma once
#include <gdiobj_ptr.hpp>
#include <map>
#include "CtrlSkinPackage.hpp"

/** 
 * @brief ȫ�ֵ�Ƥ��
 *	��ť��ȫ��Ƥ��ʵ��
 */
namespace GlobalSkin
{ 

/** 
 * @brief ��ť�ؼ�״̬
 */
struct CButtonCtrlStatus:public CCtrlParameter
{
	enum
	{ 
		BUTTON_NORMAL = 0x00000080L,
		BUTTON_DISABLED = 0x00000001L,		// ����״̬
		BUTTON_PRESSED = 0x00000002L,		// ����״̬
		BUTTON_HOVER = 0x00000004L,			// ����״̬ (����ڸô�����)
		BUTTON_FOCUS = 0x00000008L,			// ���м������뽹��
		BUTTON_DEFAULT = 0x00000010L,		// Ĭ��״̬
		BUTTON_CHECKED = 0x00000020L,		// ѡ��״̬
		BUTTON_INDETERMINATE = 0x00000040L	// δȷ��״̬
	};
	// �����Ϊ��׽״̬ ���Ͷ���
	enum TCAPTURESTATE
	{
		NO_CAPTURE_OR_UP_RELEASE,	// ��״̬
		CAPTURE_IN_DOWN,			// ��갴��
		RELEASE_IN_LEAVE			// ���̧��
	};
	int				m_nID;		  // ��ť��id
	int				m_nButtonState; // ��ť��ǰ��״̬
	BOOL			m_bIcon;	  // ��ť�Ƿ���ͼ��
	
	TCAPTURESTATE m_CaptureState; // �����Ϊ��׽״̬
};

DECLARE_REF_PTR( CButtonCtrlStatus );

/** 
 * @brief ��ť�ؼ�Ƥ��
 */
class CButtonCtrlSkin:public CCtrlSkinPackage<CButtonCtrlStatus>
{
public:

	CButtonCtrlSkin(void);
	
	
	/** 
	 * @brief ��ȡ��ǰ�Ĵ�������
	 */
	LPCTSTR GetHwndClassName( );

	/** 
	 * @brief �ӹܿؼ�Ƥ��֮ǰ
	 */
	CParamReference* OnPreTakeOverSkin( HWND hWnd );

	/** 
	 * @brief ��Ϣ�������
	 */
	virtual LRESULT OnWndProc(UINT msg,WPARAM wp,LPARAM lp);
protected:
	/** 
	 * @brief �ڴ�������֮ǰ�Է���Ԥ����
	 */
	virtual bool OnHandleStyleType( UINT nStype, UINT nExStyle ) = 0;
	/** 
	 * @brief ��ť����ʽ��
	 */
	UINT ButtonStyle2Format(DWORD style);

	/** 
	 * @brief ����ƶ�
	 */
    void OnMouseMove(UINT nFlags, CPoint point);

	/** 
	 * @brief ����������
	 */
    void OnLButtonDown(UINT nFlags, const CPoint& point);

	/** 
	 * @brief ������̧��
	 */
    void OnLButtonUp(UINT nFlags, const CPoint& point);

	/** 
	 * @brief ����뿪
	 */
	void OnMouseLeave();

	/** 
	 * @brief ����
	 */
	void OnPaint();

	bool UpdateCheckStatus( );

	/** 
	 * @brief ��ȡ����
	 */
	void OnSetFocus( );

	/** 
	 * @brief ʧȥ����
	 */
	void OnKillFocus( );

	/** 
	 * @brief ����״̬�仯
	 */
	void OnEnable(BOOL bEnable);

	/** 
	 * @brief ����״̬
	 */
	void OnSetState(WPARAM wp,LPARAM lp);

	void OnSetCheck(WPARAM wp, LPARAM lp );

	/** 
	 * @brief ���÷��
	 */
	void OnSetStyle(WPARAM wp,LPARAM lp);

	/** 
	 * @brief ���ư�ť
	 */
	virtual void	OnDrawButton(CDC *pDC) = 0;

	bool GetPreviousWndProc( WNDPROC& pProc ) const;

	/** 
	 * @brief ����״̬
	 * @param nState ״̬����
	 * @param nSet   ��������
	 * @param bIsSet ���Ӳ�������ȥ������
	 * @return ִ�гɹ�����true�����򷵻�false
	 */
	bool SetState(int &nState, int nSet, bool bIsSet = true);
protected:
	~CButtonCtrlSkin(void);	
	void	Redraw( );
	
	/** 
		* @brief ���ư�ť���ı�
		*/
	void	DrawText(CDC *pDC, const CRect& rectDest);
protected:
	// ���水ť����ʱ�Ĳ���
	WPARAM m_wParamOnDown;
	LPARAM m_lParamOnDown;
};

}
