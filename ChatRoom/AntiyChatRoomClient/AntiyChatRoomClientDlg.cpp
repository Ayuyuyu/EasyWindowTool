
// AntiyChatRoomClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AntiyChatRoomClient.h"
#include "AntiyChatRoomClientDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAntiyChatRoomClientDlg �Ի���




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
		// ɾ����ģ̬�Ի������   
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


// CAntiyChatRoomClientDlg ��Ϣ�������

BOOL CAntiyChatRoomClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAntiyChatRoomClientDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	CString strEdit(strtmp.c_str());  //ת��
	//int nLength = m_listbox.GetWindowTextLength();
	//m_listbox.SetSel(nLength, nLength);
	m_chatbox.InsertString(nstr,strEdit);
	m_chatbox.PostMessage(WM_VSCROLL, SB_BOTTOM, 0) ;   //������Ϣ�������Զ�
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
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
	wVersionRequested = MAKEWORD( 2, 2 );	// ����1.1�汾��WinSock��

	if (WSAStartup( wVersionRequested, &wsaData ) != 0)
	{
		MessageBox(_T("WSAStartup failed"));
		return -1;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 2 ) {
		// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾
		// ����Ļ�������WSACleanup()�����Ϣ����������
		WSACleanup( );
		return -2; 
	}
	//Create a socket
	Clientsocket = socket(AF_INET, SOCK_STREAM, 0);
	if( Clientsocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
		WSACleanup();		//�����Socket��İ󶨲����ͷ�Socket����ռ�õ�ϵͳ��Դ
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
	
	string sTemp = strUserName +"("+strUserIP+")"+"��"+ strSendMSG+"\n";

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
	CAntiyChatRoomClientDlg *pDlg=(CAntiyChatRoomClientDlg*)param;//��öԻ���ָ��
	while((recv_size = recv(pDlg->Clientsocket, server_reply , 2000 , 0)) != SOCKET_ERROR)
	{ 
		
		//server_reply[recv_size] = '\0';
		//CString strTmp;
		
		string strTmp ="\n"+string(server_reply)+"\n";
		//strTmp.Format(_T("\n%s\n"),server_reply);  // ASCII תUnicode
		
		pDlg->ShowServerMSG(server_reply);
		memset(server_reply,0,2000);
	}
	return 1;
}

// Send Data
void CAntiyChatRoomClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CT2CA CStringToAscii(m_SendToChatRoom);

	string sResultedString (CStringToAscii);
	SendData(sResultedString);
	m_TextSend.SetWindowText(_T(""));
}

void CAntiyChatRoomClientDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CAntiyChatRoomClientDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//CChatConnect p_cc;
	//CConnectDLG md;
	//md.DoModal();
	
	if (NULL == m_Connectdlg)   
	{   
		// ������ģ̬�Ի���ʵ��   
		m_Connectdlg = new CAntiyConnetDlg();   
		m_Connectdlg->Create(IDD_DIACONNECT, this);   
	}   
	// ��ʾ��ģ̬�Ի���   
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
		strConInfo.Format(_T("������:%s:%d"),p_linfo->strIp,p_linfo->nPort);
		SetDlgItemText(IDC_STATIC_CON,strConInfo);
	}

	return 0;  
}  
void CAntiyChatRoomClientDlg::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
