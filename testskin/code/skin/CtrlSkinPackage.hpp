#pragma once

#include "CtrlSkin.h"
#include <map>

namespace GlobalSkin
{

	/** 
	 * @brief 将同种类型的控件皮肤打包：使用一套资源参数绘制
	 * @note 需要重写的函数:
		①功能：返回控件的窗口类名称
		virtual LPCTSTR GetHwndClassName( ) = 0;
		②功能：接管之前创建参数
		CParamReference* OnPreTakeOverSkin( HWND hWnd ) = 0;
		③功能：控件消息处理
		LRESULT	OnWndProc( UINT nMsg, WPARAM wParam, LPARAM lParam ) = 0;
	 */
	template <typename T>
	class CCtrlSkinPackage : public CCtrlSkin
	{
	protected:
		typedef CClassReference<T>		CParamReference;
		typedef CRefPtr<CParamReference>	CParamReferencePtr;
	public:
		inline CCtrlSkinPackage( ) { }

		/** 
		 * @override
		 */
		inline bool	CheckHwnd( 
			HWND hWnd, PCTSTR lpszWndClassName, CCtrlParameter*& pParam )
		{
			// 过滤按钮类型
			if( 0 != _tcsicmp( lpszWndClassName,  GetHwndClassName() ) )
			{
				return false;
			}

			std::map<HWND,CParamReferencePtr>::iterator itFound = 
				m_mapCtrlParameterPack.find(hWnd);
			if( m_mapCtrlParameterPack.end( ) != itFound )
			{//存在，跳过
				return true;
			}
			CParamReference* pParamRef = OnPreTakeOverSkin( hWnd );
			if( NULL == pParamRef )
			{
				return false;
			}
			pParam = pParamRef;
			m_mapCtrlParameterPack.insert( 
				std::pair<HWND,CParamReferencePtr>(hWnd,pParamRef) );
			return true;
		}

		/** 
		 * @override
		 */
		inline bool	RemoveHwnd( HWND hWnd, WNDPROC& pProc )
		{
			// 查找
			std::map<HWND,CParamReferencePtr>::iterator itFound = 
				m_mapCtrlParameterPack.find(hWnd);
			if( m_mapCtrlParameterPack.end( ) == itFound )
			{
				return false;
			}
			CParamReferencePtr pOldProc = itFound ->second;
			pProc = pOldProc ->m_pPreviousProc;
			// 删除
			m_mapCtrlParameterPack.erase( itFound );

			return true;
		}
		
		/** 
		 * @override
		 */
		inline bool CheckOwner( HWND hWnd, CCtrlParameter*& pParam )
		{
			CParamReferencePtr pStatus;
			if( FindWnd(hWnd,pStatus ) )
			{
				SetCurrentWindow( hWnd );
				SetCurrentProc( pStatus );
				pParam = pStatus.get( );
				return true;
			}
			return false;
		}

		/** 
		 * @brief 设置当前的窗口过程
		 */
		inline void SetCurrentProc( CParamReferencePtr proc )
		{
			m_pCurParam = proc;
		}

		/** 
		 * @brief 查找窗口过程
		 */
		inline bool	FindWnd( HWND hWnd,CParamReferencePtr& pProc )
		{
			//map查找
			std::map<HWND,CParamReferencePtr>::iterator itFound 
				= m_mapCtrlParameterPack.find(hWnd);
			if( itFound == m_mapCtrlParameterPack.end() )
			{
				return false;
			}
			pProc = itFound->second;
			return true;
		}
		
		bool GetPreviousWndProc( WNDPROC& pProc ) const
		{
			if( IsNull( ) )
			{
				return false;
			}
			pProc = GetCurParam( )->m_pPreviousProc;
			return true;
		}
	protected:
		~CCtrlSkinPackage( )
		{
			// 清除之前的恢复
			for( std::map<HWND,CParamReferencePtr>::iterator it = 
				m_mapCtrlParameterPack.begin();
				it != m_mapCtrlParameterPack.end(); ++it )
			{
				const CParamReferencePtr& pOldProc = it ->second;
#ifdef _WIN64
				SetWindowLongPtr( it ->first, GWLP_WNDPROC,
					(LONG_PTR)( pOldProc ->m_pPreviousProc) );
#else
				SetWindowLong( it ->first, GWL_WNDPROC, 
					(LONG)( pOldProc ->m_pPreviousProc)  );
#endif
			}
			m_mapCtrlParameterPack.clear();
		}
		
		/** 
		 * @brief 获取当前的窗口类名
		 */
		virtual LPCTSTR GetHwndClassName( ) = 0;

		/** 
		 * @brief 接管控件皮肤之前
		 */
		virtual CParamReference* OnPreTakeOverSkin( HWND hWnd ) = 0;

		bool	IsNull( ) const { return !m_pCurParam; }
		bool	IsValid( ) const { return !IsNull();}
		inline CParamReferencePtr& GetCurParam( ){ return m_pCurParam; }
		inline const CParamReferencePtr& GetCurParam( ) const{ return m_pCurParam; }
	protected:

		CParamReferencePtr				m_pCurParam;
		std::map<HWND,CParamReferencePtr>	m_mapCtrlParameterPack;
	};
}
