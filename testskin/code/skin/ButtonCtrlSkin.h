#pragma once
#include <gdiobj_ptr.hpp>
#include <map>
#include "CtrlSkinPackage.hpp"

/** 
 * @brief 全局的皮肤
 *	按钮的全局皮肤实现
 */
namespace GlobalSkin
{ 

/** 
 * @brief 按钮控件状态
 */
struct CButtonCtrlStatus:public CCtrlParameter
{
	enum
	{ 
		BUTTON_NORMAL = 0x00000080L,
		BUTTON_DISABLED = 0x00000001L,		// 禁用状态
		BUTTON_PRESSED = 0x00000002L,		// 按下状态
		BUTTON_HOVER = 0x00000004L,			// 高亮状态 (鼠标在该窗口上)
		BUTTON_FOCUS = 0x00000008L,			// 具有键盘输入焦点
		BUTTON_DEFAULT = 0x00000010L,		// 默认状态
		BUTTON_CHECKED = 0x00000020L,		// 选中状态
		BUTTON_INDETERMINATE = 0x00000040L	// 未确定状态
	};
	// 鼠标行为捕捉状态 类型定义
	enum TCAPTURESTATE
	{
		NO_CAPTURE_OR_UP_RELEASE,	// 无状态
		CAPTURE_IN_DOWN,			// 鼠标按下
		RELEASE_IN_LEAVE			// 鼠标抬起
	};
	int				m_nID;		  // 按钮的id
	int				m_nButtonState; // 按钮当前的状态
	BOOL			m_bIcon;	  // 按钮是否有图标
	
	TCAPTURESTATE m_CaptureState; // 鼠标行为捕捉状态
};

DECLARE_REF_PTR( CButtonCtrlStatus );

/** 
 * @brief 按钮控件皮肤
 */
class CButtonCtrlSkin:public CCtrlSkinPackage<CButtonCtrlStatus>
{
public:

	CButtonCtrlSkin(void);
	
	
	/** 
	 * @brief 获取当前的窗口类名
	 */
	LPCTSTR GetHwndClassName( );

	/** 
	 * @brief 接管控件皮肤之前
	 */
	CParamReference* OnPreTakeOverSkin( HWND hWnd );

	/** 
	 * @brief 消息处理过程
	 */
	virtual LRESULT OnWndProc(UINT msg,WPARAM wp,LPARAM lp);
protected:
	/** 
	 * @brief 在创建窗口之前对风格的预处理
	 */
	virtual bool OnHandleStyleType( UINT nStype, UINT nExStyle ) = 0;
	/** 
	 * @brief 按钮风格格式化
	 */
	UINT ButtonStyle2Format(DWORD style);

	/** 
	 * @brief 鼠标移动
	 */
    void OnMouseMove(UINT nFlags, CPoint point);

	/** 
	 * @brief 鼠标左键按下
	 */
    void OnLButtonDown(UINT nFlags, const CPoint& point);

	/** 
	 * @brief 鼠标左键抬起
	 */
    void OnLButtonUp(UINT nFlags, const CPoint& point);

	/** 
	 * @brief 鼠标离开
	 */
	void OnMouseLeave();

	/** 
	 * @brief 绘制
	 */
	void OnPaint();

	bool UpdateCheckStatus( );

	/** 
	 * @brief 获取焦点
	 */
	void OnSetFocus( );

	/** 
	 * @brief 失去焦点
	 */
	void OnKillFocus( );

	/** 
	 * @brief 激活状态变化
	 */
	void OnEnable(BOOL bEnable);

	/** 
	 * @brief 设置状态
	 */
	void OnSetState(WPARAM wp,LPARAM lp);

	void OnSetCheck(WPARAM wp, LPARAM lp );

	/** 
	 * @brief 设置风格
	 */
	void OnSetStyle(WPARAM wp,LPARAM lp);

	/** 
	 * @brief 绘制按钮
	 */
	virtual void	OnDrawButton(CDC *pDC) = 0;

	bool GetPreviousWndProc( WNDPROC& pProc ) const;

	/** 
	 * @brief 设置状态
	 * @param nState 状态参数
	 * @param nSet   新增参数
	 * @param bIsSet 增加参数还是去掉参数
	 * @return 执行成功返回true，否则返回false
	 */
	bool SetState(int &nState, int nSet, bool bIsSet = true);
protected:
	~CButtonCtrlSkin(void);	
	void	Redraw( );
	
	/** 
		* @brief 绘制按钮的文本
		*/
	void	DrawText(CDC *pDC, const CRect& rectDest);
protected:
	// 保存按钮按下时的参数
	WPARAM m_wParamOnDown;
	LPARAM m_lParamOnDown;
};

}
