
// INISetting.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CINISettingApp:
// �йش����ʵ�֣������ INISetting.cpp
//

class CINISettingApp : public CWinApp
{
public:
	CINISettingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CINISettingApp theApp;