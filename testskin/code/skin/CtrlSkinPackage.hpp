#pragma once

#include "CtrlSkin.h"
#include <map>

namespace GlobalSkin
{

	/** 
	 * @brief ��ͬ�����͵Ŀؼ�Ƥ�������ʹ��һ����Դ��������
	 * @note ��Ҫ��д�ĺ���:
		�ٹ��ܣ����ؿؼ��Ĵ���������
		virtual LPCTSTR GetHwndClassName( ) = 0;
		�ڹ��ܣ��ӹ�֮ǰ��������
		CParamReference* OnPreTakeOverSkin( HWND hWnd ) = 0;
		�۹��ܣ��ؼ���Ϣ����
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
			// ���˰�ť����
			if( 0 != _tcsicmp( lpszWndClassName,  GetHwndClassName() ) )
			{
				return false;
			}

			std::map<HWND,CParamReferencePtr>::iterator itFound = 
				m_mapCtrlParameterPack.find(hWnd);
			if( m_mapCtrlParameterPack.end( ) != itFound )
			{//���ڣ�����
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
			// ����
			std::map<HWND,CParamReferencePtr>::iterator itFound = 
				m_mapCtrlParameterPack.find(hWnd);
			if( m_mapCtrlParameterPack.end( ) == itFound )
			{
				return false;
			}
			CParamReferencePtr pOldProc = itFound ->second;
			pProc = pOldProc ->m_pPreviousProc;
			// ɾ��
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
		 * @brief ���õ�ǰ�Ĵ��ڹ���
		 */
		inline void SetCurrentProc( CParamReferencePtr proc )
		{
			m_pCurParam = proc;
		}

		/** 
		 * @brief ���Ҵ��ڹ���
		 */
		inline bool	FindWnd( HWND hWnd,CParamReferencePtr& pProc )
		{
			//map����
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
			// ���֮ǰ�Ļָ�
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
		 * @brief ��ȡ��ǰ�Ĵ�������
		 */
		virtual LPCTSTR GetHwndClassName( ) = 0;

		/** 
		 * @brief �ӹܿؼ�Ƥ��֮ǰ
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
