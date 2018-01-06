#include "StdAfx.h"
#include "AntiyChatConnect.h"




CChatConnect::CChatConnect()
{

	//Clientsocket = NULL;
}

CChatConnect::~CChatConnect(void)
{
}


int CChatConnect::StartConnect(CString strServerIP,int nPort,CString strClientName)
{
	SOCKADDR_IN addrserver;
   char server_reply[2000];
    int recv_size;
	//strUserName = strClientName;
	WORD wVersionRequested;
	WSADATA wsaData;	// 这结构是用于接收Wjndows Socket的结构信息的
	wVersionRequested = MAKEWORD( 2, 2 );	// 请求1.1版本的WinSock库
	
    if (WSAStartup( wVersionRequested, &wsaData ) != 0)
    {
		MessageBox(NULL,"WSAStartup failed",NULL,NULL);
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

	addrserver.sin_addr.S_un.S_addr = inet_addr(strServerIP.GetBuffer(strServerIP.GetLength())); 
    addrserver.sin_family = AF_INET;
    addrserver.sin_port = htons( nPort );
 
    //Connect to remote server
    if (connect(Clientsocket , (SOCKADDR *)&addrserver , sizeof(SOCKADDR)) < 0)
    {
        return -3;
    }
    //AfxBeginThread(acceptconnect,this);	
    //Receive a reply from the server
    while((recv_size = recv(Clientsocket, server_reply , 2000 , 0)) != SOCKET_ERROR)
    { 
		server_reply[recv_size] = '\0';
		CString strTmp ="\n"+CString(server_reply)+"\n";
		//MessageBox(NULL,strTmp,NULL,NULL);
		CAntiyChatRoomClientDlg m_pClientDlg;
		m_pClientDlg.ShowServerMSG(strTmp);
	}
	return 1;
}


int CChatConnect::SendData(CString strSendMSG)
{	
	CString sTemp = strUserName +">>"+ strSendMSG+"\n";

	if( send(Clientsocket , sTemp.GetBuffer(sTemp.GetLength()),sTemp.GetLength() , 0) < 0)
	{
		cout<<"Send failed"<<endl;
		return -1;
	}

}