#pragma once
namespace Ui
{
#define COLOR_CHECK_BK			RGB(230,247,247)
#define COLOR_DARK				RGB(0,79,148)
#define COLOR_LIGHT				RGB(186,227,249)
#define COLOR_WHITE				RGB(254,251,234)
#define COLOR_STATE_BK			RGB(151,222,255)
#define COLOR_MAINFRM_TOP		RGB(1,173,255)
#define COLOR_MAINFRM_BODY		RGB(243,250,250)
#define COLOR_MENUBUTTON_NORMAL COLOR_DARK //RGB(157,197,219)
#define COLOR_MENUBUTTON_PRESS	RGB(255,252,240)
#define COLOR_LABEL_TEXT		RGB(89,89,90)
#define COLOR_EDIT_TEXT			RGB(74,74,74)
#define COLOR_EDIT_NORMAL		RGB(186,227,249)
#define COLOR_EDIT_FOCUSED		RGB(151,222,225)
#define COLOR_GRID_ODD			RGB(126,206,244)
#define COLOR_GRID_EVEN			RGB(186,227,249)
#define COLOR_GRID_LINE			RGB(243,250,255)
#define COLOR_ERROR_TEXT		RGB(255,0,0)
#define SetGridItemFormat( grid,row,col ) \
	grid.SetItemBkColour(row, col, 0==(col)%2? COLOR_GRID_EVEN:COLOR_GRID_ODD );\
	grid.SetItemFormat( row,col, DT_CENTER|DT_SINGLELINE|DT_VCENTER)

//void InitFont( int nFontSize = 24,const CString& strFamily = _T("微软雅黑") );
HBRUSH	GetNormalEditBrush( );
HBRUSH  GetFocusedEditBrush( );
int GetVerticalBorderSpacing( );
int GetHorizontalBorderSpacing( );
int GetVerticalSpacing( );
int GetHorizontalSpacing( );
CFont*  GetEditFont( CWnd* pWnd );
class CUiDefines
{
public:
	CUiDefines(void);
	~CUiDefines(void);
};

//////////////////////////////基本信息
#define TIPS_F_HEADER_SPACE   _T("正面所有喷头间距")
#define TIPS_F_GROUP_SPACE    _T("正面喷头组之间的距离")
#define TIPS_F_COLOR_SPACE    _T("不确定")
#define TIPS_F_SUBMIT		  _T("提交正面参数,下次打印时生效")

#define TIPS_B_HEADER_SPACE   _T("背面所有喷头间距")
#define TIPS_B_GROUP_SPACE    _T("背面喷头组之间的距离")
#define TIPS_B_COLOR_SPACE    _T("不确定")
#define TIPS_B_SUBMIT		  _T("提交背面参数,下次打印时生效")

#define TIPS_LOGIC_LENGTH	  _T("理论长度,一般固定为2032")
#define TIPS_REAL_LENGTH	  _T("实际一页的长度,使用【长度校准】测试图")
#define TIPS_CODER_INVERSE    _T("如果打印速度出乎意料地大,请勾选,观察速度是否正常")
#define TIPS_FLASH_PRINT      _T("放置喷头由于长时间不喷墨而堵塞。启动闪喷候需要等待选择的时间后才开始第一次")
#define TIPS_POLYCHROME       _T("通过延迟反面打印,使正反面重合。此值越大,反面开始打印的越晚")
//////////////////////////////设备调试
#define TIPS_OPEN_ODD_HEADER   _T("每组喷头内,奇数编号的喷头启动")
#define TIPS_OPEN_EVEN_HEADER  _T("每组喷头内,偶数编号的喷头启动")
#define TIPS_AUTO_CODER		   _T("开始打印后,使用内部编码器“模拟”的速度打印")
#define TIPS_DEBUG_SUBMIT      _T("提交当前界面的所有数据,在下次启动打印时生效")
#define TIPS_DEBUG_TAB		   _T("第一个为正面,第二个为反面,如果只有一个,则当前配置的为单面")
#define TIPS_HEADER_VOLTAGE    _T("①光电距离暂时不用,请使用默认值100;") \
							   _T("②波形文件为服务器中的路径,错误或未设置则不打印;") \
							   _T("③电压:值越大墨量,为0则对应的喷头不打印;") \
							   _T("④反向:打印方向反转")
#define TIPS_OVERLAP_INFO	   _T("关闭喷头喷孔数目,暂无对应的测试图.")\
							   _T("例外:正反面各自的第一个重叠位是【左右偏移】,24/1mm" )
#define TIPS_HEADER_OFFSET	   _T("使用“套色测试”或“套色检查”测试图.") \
							   _T("①组内偏移:喷头之间的上下偏移量.测试图的大黑条;") \
							   _T("②喷头内偏移.测试图中的细条;PWM是1/8线宽")

/////////////////////////////打印任务///////////////////
#define TIPS_TASK_LIST		   _T("所有打印任务,点击标题刷新此表")
#define TIPS_PRINT_TASK		   _T("当前选中的打印任务,在打印开始后会依次 ")
//循环打印复选框
#define TIPS_PRINT_CIRCLE_CHECK _T("循环打印【打印队列】中的任务,此时打印列表中的【需打印数】会自动设置为1.")
//循环次数
#define TIPS_PRINT_CIRCLE_EDIT  _T("仅在【循环打印】勾选时有效,当打印次数过高(如千万)时可能会有错误.")
//本间隔
#define TIPS_PRINT_BOOK_SPACE  _T("【需打印数】或【循环次数】高于1时,在打印过程中,已经打印次数增加时,增加的空白页数目.")
//纸张信息
#define TIPS_PAPER_INFO	_T("纸张信息的名字(对于每个打印作业设置),输入新的数值,点击提交会记录")
//黑条高度
#define TIPS_BLACK_HEIGHT _T("每一页中黑条的高度值")
//打印质量
#define TIPS_PRINT_QUALITY _T("喷头喷墨量的大小:超精细>精细>正常。注意：【超精细】可能由于墨量过大导致断纸。")
//镂空
#define TIPS_HOLLOW	_T("镂空")
//正面偏移
#define TIPS_FRONT_OFFSET _T("正面左右偏移的点数,24个点/毫米")
//背面偏移
#define TIPS_BACK_OFFSET  _T("背面左右偏移的点数,24个点/毫米")
//套印微调
#define TIPS_POLYCHROME_OFFSET	_T("对于每个作业的套印微调,正值大会使反面打印提前,负值会延后")
//页间隔
#define TIPS_PAGE_SPACE			_T("2页之间的间隔")
//纸张信息-提交
#define TIPS_PAPERINFO_SUBMIT	_T("提交当前作业以及配置参数")

///////////////////////////////控制窗口
#define TIPS_CUR_BOOK				_T("当前打印的本数")
#define TIPS_CUR_PAGE				_T("当前打印的页数")
#define TIPS_RUNTIME_POLYCHROME		_T("打印中‘正反套印’调整值")
#define TIPS_BUTTON_RUNTIME_POLY	_T("提交‘实时套印’值")

}
