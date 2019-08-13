
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




CtestskinDlg::CtestskinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestskinDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestskinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestskinDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestskinDlg::OnBnClickedButton1)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

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
