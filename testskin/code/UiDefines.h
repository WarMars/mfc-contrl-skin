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

//void InitFont( int nFontSize = 24,const CString& strFamily = _T("΢���ź�") );
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

//////////////////////////////������Ϣ
#define TIPS_F_HEADER_SPACE   _T("����������ͷ���")
#define TIPS_F_GROUP_SPACE    _T("������ͷ��֮��ľ���")
#define TIPS_F_COLOR_SPACE    _T("��ȷ��")
#define TIPS_F_SUBMIT		  _T("�ύ�������,�´δ�ӡʱ��Ч")

#define TIPS_B_HEADER_SPACE   _T("����������ͷ���")
#define TIPS_B_GROUP_SPACE    _T("������ͷ��֮��ľ���")
#define TIPS_B_COLOR_SPACE    _T("��ȷ��")
#define TIPS_B_SUBMIT		  _T("�ύ�������,�´δ�ӡʱ��Ч")

#define TIPS_LOGIC_LENGTH	  _T("���۳���,һ��̶�Ϊ2032")
#define TIPS_REAL_LENGTH	  _T("ʵ��һҳ�ĳ���,ʹ�á�����У׼������ͼ")
#define TIPS_CODER_INVERSE    _T("�����ӡ�ٶȳ������ϵش�,�빴ѡ,�۲��ٶ��Ƿ�����")
#define TIPS_FLASH_PRINT      _T("������ͷ���ڳ�ʱ�䲻��ī�������������������Ҫ�ȴ�ѡ���ʱ���ſ�ʼ��һ��")
#define TIPS_POLYCHROME       _T("ͨ���ӳٷ����ӡ,ʹ�������غϡ���ֵԽ��,���濪ʼ��ӡ��Խ��")
//////////////////////////////�豸����
#define TIPS_OPEN_ODD_HEADER   _T("ÿ����ͷ��,������ŵ���ͷ����")
#define TIPS_OPEN_EVEN_HEADER  _T("ÿ����ͷ��,ż����ŵ���ͷ����")
#define TIPS_AUTO_CODER		   _T("��ʼ��ӡ��,ʹ���ڲ���������ģ�⡱���ٶȴ�ӡ")
#define TIPS_DEBUG_SUBMIT      _T("�ύ��ǰ�������������,���´�������ӡʱ��Ч")
#define TIPS_DEBUG_TAB		   _T("��һ��Ϊ����,�ڶ���Ϊ����,���ֻ��һ��,��ǰ���õ�Ϊ����")
#define TIPS_HEADER_VOLTAGE    _T("�ٹ�������ʱ����,��ʹ��Ĭ��ֵ100;") \
							   _T("�ڲ����ļ�Ϊ�������е�·��,�����δ�����򲻴�ӡ;") \
							   _T("�۵�ѹ:ֵԽ��ī��,Ϊ0���Ӧ����ͷ����ӡ;") \
							   _T("�ܷ���:��ӡ����ת")
#define TIPS_OVERLAP_INFO	   _T("�ر���ͷ�����Ŀ,���޶�Ӧ�Ĳ���ͼ.")\
							   _T("����:��������Եĵ�һ���ص�λ�ǡ�����ƫ�ơ�,24/1mm" )
#define TIPS_HEADER_OFFSET	   _T("ʹ�á���ɫ���ԡ�����ɫ��顱����ͼ.") \
							   _T("������ƫ��:��ͷ֮�������ƫ����.����ͼ�Ĵ����;") \
							   _T("����ͷ��ƫ��.����ͼ�е�ϸ��;PWM��1/8�߿�")

/////////////////////////////��ӡ����///////////////////
#define TIPS_TASK_LIST		   _T("���д�ӡ����,�������ˢ�´˱�")
#define TIPS_PRINT_TASK		   _T("��ǰѡ�еĴ�ӡ����,�ڴ�ӡ��ʼ������� ")
//ѭ����ӡ��ѡ��
#define TIPS_PRINT_CIRCLE_CHECK _T("ѭ����ӡ����ӡ���С��е�����,��ʱ��ӡ�б��еġ����ӡ�������Զ�����Ϊ1.")
//ѭ������
#define TIPS_PRINT_CIRCLE_EDIT  _T("���ڡ�ѭ����ӡ����ѡʱ��Ч,����ӡ��������(��ǧ��)ʱ���ܻ��д���.")
//�����
#define TIPS_PRINT_BOOK_SPACE  _T("�����ӡ������ѭ������������1ʱ,�ڴ�ӡ������,�Ѿ���ӡ��������ʱ,���ӵĿհ�ҳ��Ŀ.")
//ֽ����Ϣ
#define TIPS_PAPER_INFO	_T("ֽ����Ϣ������(����ÿ����ӡ��ҵ����),�����µ���ֵ,����ύ���¼")
//�����߶�
#define TIPS_BLACK_HEIGHT _T("ÿһҳ�к����ĸ߶�ֵ")
//��ӡ����
#define TIPS_PRINT_QUALITY _T("��ͷ��ī���Ĵ�С:����ϸ>��ϸ>������ע�⣺������ϸ����������ī�������¶�ֽ��")
//�ο�
#define TIPS_HOLLOW	_T("�ο�")
//����ƫ��
#define TIPS_FRONT_OFFSET _T("��������ƫ�Ƶĵ���,24����/����")
//����ƫ��
#define TIPS_BACK_OFFSET  _T("��������ƫ�Ƶĵ���,24����/����")
//��ӡ΢��
#define TIPS_POLYCHROME_OFFSET	_T("����ÿ����ҵ����ӡ΢��,��ֵ���ʹ�����ӡ��ǰ,��ֵ���Ӻ�")
//ҳ���
#define TIPS_PAGE_SPACE			_T("2ҳ֮��ļ��")
//ֽ����Ϣ-�ύ
#define TIPS_PAPERINFO_SUBMIT	_T("�ύ��ǰ��ҵ�Լ����ò���")

///////////////////////////////���ƴ���
#define TIPS_CUR_BOOK				_T("��ǰ��ӡ�ı���")
#define TIPS_CUR_PAGE				_T("��ǰ��ӡ��ҳ��")
#define TIPS_RUNTIME_POLYCHROME		_T("��ӡ�С�������ӡ������ֵ")
#define TIPS_BUTTON_RUNTIME_POLY	_T("�ύ��ʵʱ��ӡ��ֵ")

}
