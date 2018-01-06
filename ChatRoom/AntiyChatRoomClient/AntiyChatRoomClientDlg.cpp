
// AntiyChatRoomClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AntiyChatRoomClient.h"
#include "AntiyChatRoomClientDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAntiyChatRoomClientDlg 对话框




CAntiyChatRoomClientDlg::CAntiyChatRoomClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntiyChatRoomClientDlg::IDD, pParent)
	, m_SendToChatRoom(_T(""))
	//, m_RecvFChatRoom(_T(""))
{
	m_Connectdlg = NULL;
	nstr = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CAntiyChatRoomClientDlg::~CAntiyChatRoomClientDlg()
{
	closesocket(Clientsocket);
	WSACleanup();
	if (NULL != m_Connectdlg)   
	{   
		// 删除非模态对话框对象   
		delete m_Connectdlg;   
	} 
}

void CAntiyChatRoomClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_SendToChatRoom);
	//DDX_Text(pDX, IDC_EDIT1, m_RecvFChatRoom);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	//DDX_Control(pDX, IDC_EDIT1, m_textbox);
	DDX_Control(pDX, IDC_EDIT2, m_TextSend);
	DDX_Control(pDX, IDC_LIST2, m_chatbox);
}

BEGIN_MESSAGE_MAP(CAntiyChatRoomClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CAntiyChatRoomClientDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CAntiyChatRoomClientDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CAntiyChatRoomClientDlg::OnBnClickedButton2)
	ON_MESSAGE(WM_CONNECT_MSG,&CAntiyChatRoomClientDlg::OnConnectMessage)
	ON_LBN_SELCHANGE(IDC_LIST2, &CAntiyChatRoomClientDlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CAntiyChatRoomClientDlg 消息处理程序

BOOL CAntiyChatRoomClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAntiyChatRoomClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAntiyChatRoomClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAntiyChatRoomClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

char* ExportUnicodeToAnsi( const wchar_t* szStr )  
{  
	int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );  
	if (nLen == 0)  
	{  
		return NULL;  
	}  
	char* pResult = new char[nLen];  
	WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );  
	return pResult;  
}

wchar_t * ExportANSIToUnicode( const char* str ) 
{ 
	int textlen ; 
	wchar_t * result; 
	textlen = MultiByteToWideChar( CP_ACP, 0, str,-1, NULL,0 ); 
	result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
	memset(result,0,(textlen+1)*sizeof(wchar_t)); 
	MultiByteToWideChar(CP_ACP, 0,str,-1,(LPWSTR)result,textlen ); 
	return result; 
} 

int CAntiyChatRoomClientDlg::ShowServerMSG(string strtmp)
{
	CString strEdit(strtmp.c_str());  //转换
	//int nLength = m_listbox.GetWindowTextLength();
	//m_listbox.SetSel(nLength, nLength);
	m_chatbox.InsertString(nstr,strEdit);
	m_chatbox.PostMessage(WM_VSCROLL, SB_BOTTOM, 0) ;   //发送消息滚动条自动
	nstr++;
	return 1;
}


int CAntiyChatRoomClientDlg::StartConnect(CString strServerIP,int nPort,CString strClientName)
{
	CT2CA CStringToAscii(strServerIP);
	string strIP (CStringToAscii);
	CT2CA CStringToAscii2(strClientName);
	string strName (CStringToAscii2);

	SOCKADDR_IN addrserver;
	strUserName = strName;
	strUserIP = strIP;
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的
	wVersionRequested = MAKEWORD( 2, 2 );	// 请求1.1版本的WinSock库

	if (WSAStartup( wVersionRequested, &wsaData ) != 0)
	{
		MessageBox(_T("WSAStartup failed"));
		return -1;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 2 ) {
		// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本
		// 否则的话，调用WSACleanup()清除信息，结束函数
		WSACleanup( );
		return -2; 
	}
	//Create a socket
	Clientsocket = socket(AF_INET, SOCK_STREAM, 0);
	if( Clientsocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("创建套接字失败！"));
		WSACleanup();		//解除与Socket库的绑定并且释放Socket库所占用的系统资源
		return -3;
	}

	addrserver.sin_addr.S_un.S_addr = inet_addr(strIP.c_str()); 
	addrserver.sin_family = AF_INET;
	addrserver.sin_port = htons( nPort );

	//Connect to remote server
	if (connect(Clientsocket , (SOCKADDR *)&addrserver , sizeof(SOCKADDR)) < 0)
	{
		WSACleanup();
		return -3;
	}
	//_beginthreadex(NULL, 0, myAcceptThread, this, 0, NULL);
	AfxBeginThread(myAcceptThread,this);
	return 1;
}


int CAntiyChatRoomClientDlg::SendData(string strSendMSG)
{	
	
	string sTemp = strUserName +"("+strUserIP+")"+"："+ strSendMSG+"\n";

	if( send(Clientsocket ,sTemp.c_str() ,sTemp.size() , 0) < 0)
	{
		MessageBox(_T("Send Failed"));
		return -1;
	}
}

UINT  CAntiyChatRoomClientDlg::myAcceptThread(LPVOID  param)
{
	char server_reply[2000]= {};
	memset(server_reply,0,2000);
	int recv_size;
	CAntiyChatRoomClientDlg *pDlg=(CAntiyChatRoomClientDlg*)param;//获得对话框指针
	while((recv_size = recv(pDlg->Clientsocket, server_reply , 2000 , 0)) != SOCKET_ERROR)
	{ 
		
		//server_reply[recv_size] = '\0';
		//CString strTmp;
		
		string strTmp ="\n"+string(server_reply)+"\n";
		//strTmp.Format(_T("\n%s\n"),server_reply);  // ASCII 转Unicode
		
		pDlg->ShowServerMSG(server_reply);
		memset(server_reply,0,2000);
	}
	return 1;
}

// Send Data
void CAntiyChatRoomClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CT2CA CStringToAscii(m_SendToChatRoom);

	string sResultedString (CStringToAscii);
	SendData(sResultedString);
	m_TextSend.SetWindowText(_T(""));
}

void CAntiyChatRoomClientDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CAntiyChatRoomClientDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//CChatConnect p_cc;
	//CConnectDLG md;
	//md.DoModal();
	
	if (NULL == m_Connectdlg)   
	{   
		// 创建非模态对话框实例   
		m_Connectdlg = new CAntiyConnetDlg();   
		m_Connectdlg->Create(IDD_DIACONNECT, this);   
	}   
	// 显示非模态对话框   
	m_Connectdlg->ShowWindow(SW_SHOW);   
	
	
}

afx_msg LRESULT CAntiyChatRoomClientDlg::OnConnectMessage(WPARAM wParam, LPARAM lParam)  
{  
	LoadingInfo *p_linfo;
	if (wParam == NULL)
	{
		return -1;
	}
	p_linfo = (LoadingInfo*)wParam;
	int nC = StartConnect(p_linfo->strIp,p_linfo->nPort,p_linfo->strName);
	if (nC > 0)
	{
		CString strConInfo;
		strConInfo.Format(_T("已连接:%s:%d"),p_linfo->strIp,p_linfo->nPort);
		SetDlgItemText(IDC_STATIC_CON,strConInfo);
	}

	return 0;  
}  
void CAntiyChatRoomClientDlg::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
}
