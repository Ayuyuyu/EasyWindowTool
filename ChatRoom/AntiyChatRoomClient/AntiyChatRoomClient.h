
// AntiyChatRoomClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include <string>
using namespace std;
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#define WM_CONNECT_MSG WM_USER+0x01001  


// CAntiyChatRoomClientApp:
// �йش����ʵ�֣������ AntiyChatRoomClient.cpp
//

class CAntiyChatRoomClientApp : public CWinAppEx
{
public:
	CAntiyChatRoomClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAntiyChatRoomClientApp theApp;