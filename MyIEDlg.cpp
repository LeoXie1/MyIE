// MyIEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyIE.h"
#include "MyIEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyIEDlg dialog

CMyIEDlg::CMyIEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyIEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyIEDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyIEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyIEDlg)
	DDX_Control(pDX, IDC_IE_CTRL, m_ctrlWeb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyIEDlg, CDialog)
	//{{AFX_MSG_MAP(CMyIEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BACK, OnBtnBack)
	ON_BN_CLICKED(IDC_BTN_FWD, OnBtnFwd)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_HOME, OnBtnHome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyIEDlg message handlers

BOOL CMyIEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ctrlWeb.Navigate("www.google.com", NULL, NULL, NULL, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyIEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyIEDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyIEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CMyIEDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMyIEDlg)
	ON_EVENT(CMyIEDlg, IDC_IE_CTRL, 105 /* CommandStateChange */, OnCommandStateChangeIeCtrl, VTS_I4 VTS_BOOL)
	ON_EVENT(CMyIEDlg, IDC_IE_CTRL, 250 /* BeforeNavigate2 */, OnBeforeNavigate2IeCtrl, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMyIEDlg::OnCommandStateChangeIeCtrl(long Command, BOOL Enable) 
{
	// TODO: Add your control notification handler code here
	switch(Command)
	{
	case 1:
		{
			GetDlgItem(IDC_BTN_FWD)->EnableWindow(Enable);
			break;
		}
	case 2:
		{
			GetDlgItem(IDC_BTN_BACK)->EnableWindow(Enable);
			break;
		}
	}
}



void CMyIEDlg::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	m_ctrlWeb.Refresh();
}
BOOL CMyIEDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			char szURL[512] = {0};
			GetDlgItem(IDC_INPUT_URL)->GetWindowText(szURL, sizeof(szURL));

			m_ctrlWeb.Navigate(szURL, NULL, NULL, NULL, NULL);
			SetLocationURL(m_ctrlWeb.GetLocationURL());
//			MessageBox(szURL, NULL, MB_OK);
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CMyIEDlg::OnBtnFwd() 
{
	// TODO: Add your control notification handler code here
	m_ctrlWeb.GoForward();
}

void CMyIEDlg::OnBtnBack() 
{
	// TODO: Add your control notification handler code here
	m_ctrlWeb.GoBack();
}

void CMyIEDlg::OnBtnHome() 
{
	// TODO: Add your control notification handler code here
	m_ctrlWeb.Navigate("http://blog.csdn.net/skiing_886", NULL, NULL, NULL, NULL);
}

void CMyIEDlg::SetLocationURL(CString &strURL)
{
	GetDlgItem(IDC_INPUT_URL)->SetWindowText((LPSTR)(LPCTSTR)strURL);
}

void CMyIEDlg::OnBeforeNavigate2IeCtrl(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	// TODO: Add your control notification handler code here
	
}
