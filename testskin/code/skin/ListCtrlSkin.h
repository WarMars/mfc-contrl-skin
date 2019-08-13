#pragma once
#include "CtrlWithScrollBar.h"

namespace GlobalSkin
{
	struct sListCtrlParameter : public sCtrlWithScrollBar
	{

	};
	/** 
	 * @brief list�ؼ�Ƥ��
	 */
	class CListCtrlSkin:public CCtrlWithScrollBar<sListCtrlParameter>
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
