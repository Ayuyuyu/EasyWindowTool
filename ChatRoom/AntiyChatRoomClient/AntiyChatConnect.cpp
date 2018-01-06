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
	WSADATA wsaData;	// ��ṹ�����ڽ���Wjndows Socket�Ľṹ��Ϣ��
	wVersionRequested = MAKEWORD( 2, 2 );	// ����1.1�汾��WinSock��
	
    if (WSAStartup( wVersionRequested, &wsaData ) != 0)
    {
		MessageBox(NULL,"WSAStartup failed",NULL,NULL);
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