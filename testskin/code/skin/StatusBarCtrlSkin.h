#pragma  once
#include "CtrlSkinPackage.hpp"
#include "gdiobj_ptr.hpp"


///
/// @brief ״̬����ȫ��Ƥ������
///
namespace GlobalSkin
{
	
	///
	/// @brief ״̬����Ŀǰ��֧�ֹ������Ի���
	///
	struct sStatusBarCtrlParameter:public sCtrlParameter
	{

	};

	///
	/// @brief ״̬����ʵ��
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
		
		/* ������ͼ */
		CBitmapRefPtr		m_pBmpBk;
		
		/* ����ı���ͼ */
		CBitmapRefPtr		m_pBmpItemBk;
	};

}

