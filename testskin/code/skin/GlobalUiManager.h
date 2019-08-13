#pragma once
#include "CtrlSkin.h"
#include <vector>
// 全局的皮肤管理器实现

namespace GlobalSkin
{ 
	class CSkinConfig;
	class CGlobalUiManager
	{
		friend LRESULT CALLBACK WndHookProc(int , WPARAM , LPARAM );
		friend LRESULT CALLBACK ControlSkinProc( HWND, UINT, WPARAM, LPARAM );
	public:
		inline static CGlobalUiManager* GetPtr( ){ return s_pSkinManager; }
	public:
		CGlobalUiManager( const CSkinConfig* pConfig = NULL );
		CGlobalUiManager( const CSkinConfig& config );
		~CGlobalUiManager( );

		bool Add( HWND hWnd,WNDPROC* pOldProc = NULL);
		bool Remove( HWND hWnd );
		DynamicParam::CScrollBarCtrlSkin* GetScrollBarCtrlSkin( );
		DynamicParam::CMenubarCtrlSkin*	GetMenuBarCtrlSkin( );	
	protected:

		/** 
		 * @brief 安装皮肤
		 */
		void InstallSkin( const CSkinConfig* pConfig = NULL );

		/** 
		 * @brief 卸载皮肤
		 */
		void UninstallSkin( );

		LRESULT HandleWndProc( HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam );
	private:
		static	CGlobalUiManager*	  s_pSkinManager;
		std::vector<CCtrlSkinPtr>	  m_vectorCtrlSkins;
		HHOOK						  m_pPreviosHook;

		SimplePtr<DynamicParam::CScrollBarCtrlSkin> m_pScrollBarCtrlSkin;
		SimplePtr<DynamicParam::CMenubarCtrlSkin>	  m_pMenuBarCtrlSkin;
	};

}