#pragma once
#include "ListBoxCtrlSkin.h"
namespace GlobalSkin
{
	// combobox的下拉列表框默认使用listbox的皮肤风格
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