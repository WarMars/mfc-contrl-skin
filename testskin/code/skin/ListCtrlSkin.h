#pragma once
#include "CtrlWithScrollBar.h"

namespace GlobalSkin
{
	struct CListCtrlParameter : public CCtrlWithScrollBarParameter
	{

	};
	/** 
	 * @brief list�ؼ�Ƥ��
	 */
	class CListCtrlSkin:public CCtrlWithScrollBar<CListCtrlParameter>
	{
	public:
		CListCtrlSkin( );
		void LoadSkin( const CSkinConfig* pConfig );
	protected:
		~CListCtrlSkin( );
		/** 
		 * @brief ��ȡ��ǰ�Ĵ�������
		 */
		LPCTSTR GetHwndClassName( );

		/** 
		 * @brief �ӹܿؼ�Ƥ��֮ǰ
		 */
		bool OnInitSkinParam( HWND hWnd, CParamReference* pParam );

		/** 
		 * @brief ��Ϣ�������
		 */
		LRESULT OnWndOtherProc(UINT msg,WPARAM wp,LPARAM lp);

	};
}
