#pragma once
#include "ListBoxCtrlSkin.h"
namespace GlobalSkin
{
	// combobox�������б��Ĭ��ʹ��listbox��Ƥ�����
	class CComboLBoxCtrlSkin:public CListBoxCtrlSkin
	{
	public:
		CComboLBoxCtrlSkin( );

	protected:
		~CComboLBoxCtrlSkin();

		
		/*!
		 * @brief override
		 * @param 
		 * @return 
		 * @note
		 */
		LPCTSTR GetHwndClassName( );
	};


}