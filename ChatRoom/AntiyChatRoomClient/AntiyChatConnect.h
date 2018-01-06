#pragma once
#include<Winsock2.h>
#include <iostream>


#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;

class CAntiyChatRoomClientDlg;

class CChatConnect
{
public:
	CChatConnect(void);
	~CChatConnect(void);
public:
	int StartConnect(CString strServerIP,int nPort,CString strClientName);
	int SendData(CString strSendMSG);
public:
	WSADATA wsa;
	SOCKET Clientsocket;
	CString strUserName;
	
};
