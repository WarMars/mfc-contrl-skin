#pragma  once
#include <Windows.h>
#include <reference_ptr.hpp>
#include <stack>
#include "GlobalSkinUtil.h"

#define USING_CONFIG_FILE
namespace GlobalSkin
{
	// ע�⣬��Ҫ�����������麯��
	struct CCtrlParameter
	{
	public:
		virtual ~CCtrlParameter(){}
		WNDPROC		m_pPreviousProc;  // ϵͳ�Ĵ������
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
		* @brief ��Ӱ�ť�ؼ�
		* @param ���ھ��
		* @return ��������Ǵ���Ƥ��������ӳɹ�������ʧ��
		*/
		bool	AddControl( HWND hWnd, WNDPROC pProc, WNDPROC* pOldProc = NULL );


		/** 
		* @brief ɾ��һ���ؼ�
		*/
		bool	RemoveControl( HWND hWnd );

		
		/** 
		 * @brief ���õ�ǰ��ť
		 */
		void SetCurrentWindow( HWND hWnd );
		void ResetCurrentWindow( );
		virtual void OnFinishProc( ) = 0;

		virtual bool	CheckHwnd( 
			HWND hWnd, PCTSTR lpszWndClassName, CCtrlParameter*& pParam ) = 0;

		virtual bool	RemoveHwnd( HWND hWnd, WNDPROC& pProc ) = 0;

		/** 
		 * @brief ����Ƿ��Ǵ����ʹ���
		 */
		virtual bool	CheckOwner( HWND hWnd, CCtrlParameter*& pParam ) = 0;

		/** 
		 * @brief ���ڹ��̴���
		 */
		virtual LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam ) = 0;
		
		
		/*!
		 * @brief ����Ƥ�������ļ�
		 * @param Ƥ�����ò��������Ϊnull,��ʹ��Ĭ�ϵķ�ʽ����
		 * @return 
		 * @note
		 */
		virtual void LoadSkin( const CSkinConfig* pConfig = NULL ) = 0;
	protected:
	
		virtual bool GetPreviousWndProc( WNDPROC& pProc ) const = 0;
		/** 
		 * @brief �ɵĴ��ڹ���
		 */
		LRESULT	OnPreviousWndProc( HWND hWnd, UINT nMsg, WPARAM wParam ,LPARAM lParam );

		/** 
		 * @brief ʹ�ñ��ݵĲ������þɵĴ��ڹ���
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

