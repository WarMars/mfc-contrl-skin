
// testskinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testskin.h"
#include "testskinDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestskinDlg �Ի���


#include <string>

CtestskinDlg::CtestskinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestskinDlg::IDD, pParent)
	,m_staticGdiPlus( Gdiplus::Image::FromFile(
	_T("E:\\printer\\PrintClient\\Debug\\ui\\image\\login\\prefix_password.png")) )
	, m_bRadio1Checked(false)
	, m_fTest(0)
	, m_fTest1(0)
{
	std::string str = "iu37G+6O/dldLgxDQWZfld4yopCaS0fjdnl5PfUqUEW1i83WkevEPzK9PPRTkfQe/UQJvj8yktwBDEdXRn2d7QlFtXOCIR93a+i5EKiwdbAKJAkkqW/lSFgTZIWxBv6u+WetYOJTlntIRqOMQXcBFgQ19i0qF9ysRLXFPzctkz0o7MIwN3RghcjVNudty4Zw+VFh3eMKfJPNBoMenQI4V4er/nFv1FA6qhv4XgHZso5s5wapT5MJg6EnzA5xSydtc2qLB2VI9Y2vpur9kfKM20DBNfKzf9Av/b2EgYcLUxs9fbSGTOiyk6g3GRpaRCnAH/RBpZxeKP2vwbtf2fWlmg==";
	std::size_t nSize = str.size();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestskinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEST_GDIPLUS, m_staticGdiPlus);
	DDX_Text(pDX, IDC_EDIT2, m_fTest);
	DDV_MinMaxFloat(pDX, m_fTest1, -9999999.9, 999999.9);
}

BEGIN_MESSAGE_MAP(CtestskinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestskinDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CtestskinDlg ��Ϣ�������

BOOL CtestskinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	CWnd* pWnd = GetDlgItem( IDOK );
	CRect rectClient,rectWindow;
	pWnd ->GetClientRect( rectClient );
	pWnd ->GetWindowRect( rectWindow );
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	m_wndToolTips.Create(this);
	m_wndToolTips.AddTool((CTabCtrl*)GetDlgItem( IDC_TAB1 ), _T("���,tooltips") );
	m_wndToolTips.AddTool((CTabCtrl*)GetDlgItem( IDC_TAB1 ), _T("���,xxtooltips") );
	m_wndToolTips.SetTipBkColor(RGB(255,255,0) );
	m_wndToolTips.SetTipTextColor( RGB(0,255,0) );
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CTabCtrl* pTabCtrl = (CTabCtrl*)GetDlgItem( IDC_TAB1 );
	pTabCtrl ->InsertItem( 0,_T("��Ŀ0") );
	pTabCtrl ->InsertItem( 1,_T("��Ŀ1") );
	pTabCtrl ->InsertItem( 2,_T("��Ŀ2") );
	do
	{
		static UINT indicators[]=
		{
			IDS_SYSTEM_TIME,
			IDS_DATETIME_FORMAT
		};
#if 0
		m_wndStatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW,
			CRect(0,0,0,0), this, 0);
		int iPaneDim[3] = {100,200,-1};
		m_wndStatusBar.SetParts(3,iPaneDim);
		m_wndStatusBar.SetText(_T("aaaaa"),0,0);
		m_wndStatusBar.SetText(_T("bbbbb"),1,0);
		m_wndStatusBar.SetText(_T("ccccc"),2,0);
		int partArray[255] = {0};
		int nParts = m_wndStatusBar.GetParts(255,partArray);
		int ns = 0;
#else
		if( !m_wndStatusBar.Create(this)
			||
			!m_wndStatusBar.SetIndicators(
			indicators,sizeof(indicators)/sizeof(UINT)) )
		{
			m_wndStatusBar.GetCount( );
			AfxMessageBox( _T("Can't create status bar\n") );
			break;
			//return FALSE;
		}
		CRect rectClient;
		GetClientRect( rectClient );
		//���״̬����Ϣ
		m_wndStatusBar.MoveWindow(
			1,rectClient.bottom-20,rectClient.right,20);
		m_wndStatusBar.SetPaneInfo(
			1,m_wndStatusBar.GetDlgCtrlID(),SBPS_NORMAL,30);
		//m_wndStatusBar.SetIndicators();CStatusBarCtrl
#endif
	}while(false);
	do 
	{
		if (!m_wndToolBar.CreateEx(this,
			TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | 
			CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | 
			CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1) )||
			!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
		{
			TRACE0("δ�ܴ���������\n");
			break;
		}
		m_wndToolBar.SetWindowText( _T("���Թ�����") );
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST,   AFX_IDW_CONTROLBAR_LAST,   0); 
	} while (false);
	CProgressCtrl* pCtrl = (CProgressCtrl*)GetDlgItem( IDC_PROGRESS1 );
	pCtrl ->SetRange(1,100);
	pCtrl ->SetPos( 50 );
	//m_layout.Attach( this );
	//m_layout.SetAlignment( HCENTER | VCENTER );
	//m_layout.AddChild( GetDlgItem(IDC_EDIT1) );
	//m_layout.AddChild( GetDlgItem(IDC_BUTTON1) );
	//m_layout.AddChild( GetDlgItem(IDC_SPIN1) );
	//m_layout.AddChild( GetDlgItem(IDC_SLIDER1) );
	//m_layout.AddChild( GetDlgItem(IDC_SLIDER2) );
	//m_layout.AddChild( GetDlgItem(IDC_PROGRESS1) );
	//m_layout.AddChild( GetDlgItem(IDC_RADIO1) );
	//m_layout.AddChild( GetDlgItem(IDC_RADIO2) );
	//m_layout.AddChild( GetDlgItem(IDC_TREE1) );
	//m_layout.AddChild( GetDlgItem(IDC_TAB1) );
	//m_layout.AddChild( GetDlgItem(IDOK) );
	//m_layout.AddChild( GetDlgItem(IDCANCEL) );
	//m_staticGdiPlus
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtestskinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestskinDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		dc.DrawText( _T("�ú�ѧϰ����������"), -1,
			CRect(0,0,100,100 ), DT_VCENTER | DT_CENTER | DT_SINGLELINE |DT_NOCLIP);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestskinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestskinDlg::OnBnClickedButton1()
{
	//CtestskinDlg dlg;
	//dlg.DoModal();
	ASSERT(false);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CtestskinDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CtestskinDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CtestskinDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch( pMsg ->message )
	{
	case WM_MOUSEMOVE:
		m_wndToolTips.RelayEvent( pMsg );
		break;
	default:
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CtestskinDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

//	CDialogEx::OnOK();
}


void CtestskinDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}
