#pragma  once
#include <Windows.h>
#include <reference_ptr.hpp>
#include <stack>
#include "GlobalSkinUtil.h"

#define USING_CONFIG_FILE
namespace GlobalSkin
{
	// 注意，不要在这里增加虚函数
	struct CCtrlParameter
	{
	public:
		virtual ~CCtrlParameter(){}
		WNDPROC		m_pPreviousProc;  // 系统的处理过程
	};
	class CSkinConfig;
	class CGlobalUiManager;
	namespace DynamicParam
	{
		class CScrollBarCtrlSkin;
		class CMenubarCtrlSkin;
	}
	class CCtrlSkin : public CReferenceObject
	{
		friend class  CRefPtr<CCtrlSkin>;
	public:
		
		/** 
		* @brief 添加按钮控件
		* @param 窗口句柄
		* @return 如果窗口是此类皮肤，则添加成功，否则失败
		*/
		bool	AddControl( HWND hWnd, WNDPROC pProc, WNDPROC* pOldProc = NULL );


		/** 
		* @brief 删除一个控件
		*/
		bool	RemoveControl( HWND hWnd );

		
		/** 
		 * @brief 设置当前按钮
		 */
		void SetCurrentWindow( HWND hWnd );
		void ResetCurrentWindow( );
		virtual void OnFinishProc( ) = 0;

		virtual bool	CheckHwnd( 
			HWND hWnd, PCTSTR lpszWndClassName, CCtrlParameter*& pParam ) = 0;

		virtual bool	RemoveHwnd( HWND hWnd, WNDPROC& pProc ) = 0;

		/** 
		 * @brief 检查是否是此类型窗口
		 */
		virtual bool	CheckOwner( HWND hWnd, CCtrlParameter*& pParam ) = 0;

		/** 
		 * @brief 窗口过程处理
		 */
		virtual LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam ) = 0;
		
		
		/*!
		 * @brief 加载皮肤配置文件
		 * @param 皮肤配置参数，如果为null,则使用默认的方式加载
		 * @return 
		 * @note
		 */
		virtual void LoadSkin( const CSkinConfig* pConfig = NULL ) = 0;
	protected:
	
		virtual bool GetPreviousWndProc( WNDPROC& pProc ) const = 0;
		/** 
		 * @brief 旧的窗口过程
		 */
		LRESULT	OnPreviousWndProc( HWND hWnd, UINT nMsg, WPARAM wParam ,LPARAM lParam );

		/** 
		 * @brief 使用备份的参数调用旧的窗口过程
		 */
		LRESULT	OnAutoDefaultWndProc( );
	
		virtual ~CCtrlSkin( );

		inline HWND GetCurHwnd( ) const
		{ 
			if( m_stackWnd.empty() )
			{
				ShowErrorMsg( );
				return NULL;
			}
#ifdef _DEBUG
			if( m_stackWnd.size() > 1 )
			{
				std::size_t i = m_stackWnd.size();
				i = i;
			}
#endif
			return m_stackWnd.top( );
		}
	public:
		void SetUiManager( CGlobalUiManager* pManager );
		DynamicParam::CScrollBarCtrlSkin& GetScrollBarCtrlSkin( );
		DynamicParam::CMenubarCtrlSkin& GetMenuBarCtrlSkin( );
	protected:
		std::stack<HWND>	m_stackWnd;
		//HWND				m_hWnd;
		CGlobalUiManager*	m_pManager;
	};

	typedef  CRefPtr<CCtrlSkin> CCtrlSkinPtr;
}

