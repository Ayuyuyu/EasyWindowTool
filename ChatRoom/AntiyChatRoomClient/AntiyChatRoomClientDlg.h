
// AntiyChatRoomClientDlg.h : 头文件
//

#pragma once
#include "AntiyConnetDlg.h"
#include "afxwin.h"

// CAntiyChatRoomClientDlg 对话框
class CAntiyChatRoomClientDlg : public CDialog
{
// 构造
public:
	CAntiyChatRoomClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CAntiyChatRoomClientDlg();

// 对话框数据
	enum { IDD = IDD_ANTIYCHATROOMCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CAntiyConnetDlg *m_Connectdlg;
	
public:
	int ShowServerMSG(string strtmp);
	void AppendTextToEditCtrl(CEdit& edit, CString strText);
	int StartConnect(CString strServerIP,int nPort,CString strClientName);
	int SendData(string strSendMSG);
	static UINT  myAcceptThread(LPVOID   param);
public:
	SOCKET Clientsocket;
	string strUserName;
	string strUserIP;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	CString m_SendToChatRoom;
	//CString m_RecvFChatRoom;
	afx_msg void OnBnClickedButton2();
	CListBox m_listbox;
	//CEdit m_textbox;
	afx_msg LRESULT  OnConnectMessage(WPARAM wParam,LPARAM lParam);
	CEdit m_TextSend;
	CListBox m_chatbox;
	int nstr;
	afx_msg void OnLbnSelchangeList2();
};
