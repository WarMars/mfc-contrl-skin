#pragma  once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"


///
/// @brief 状态栏的全局皮肤绘制
///
namespace GlobalSkin
{
	
	///
	/// @brief 状态栏的目前仅支持滚动条自绘制
	///
	struct sStatusBarCtrlParameter:public sCtrlParameter
	{

	};

	///
	/// @brief 状态栏的实现
	///
	class CStatusBarCtrlSkin:public CCtrlSkinPackage<sStatusBarCtrlParameter>
	{
	public:
		CStatusBarCtrlSkin( );

		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CStatusBarCtrlSkin( );
		/** 
		 * @brief overide
		 */
		LPCTSTR GetHwndClassName( );
		
		/** 
		 * @brief overide
		 */
		CParamReference* OnPreTakeOverSkin( HWND hWnd );
		
		/** 
		 * @brief overide
		 */
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam );
	

		void OnPaint( );
		BOOL OnEraseBkgnd( HDC hdc );
		LRESULT OnSetText(WPARAM wParam, LPARAM lParam );

		void DrawStatusBar( HDC hdc );

	private:
		
		/* 背景贴图 */
		CBitmapRefPtr		m_pBmpBk;
		
		/* 子项的背景图 */
		CBitmapRefPtr		m_pBmpItemBk;
	};

}

