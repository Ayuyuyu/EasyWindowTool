
// AntiyChatRoomClientDlg.h : ͷ�ļ�
//

#pragma once
#include "AntiyConnetDlg.h"
#include "afxwin.h"

// CAntiyChatRoomClientDlg �Ի���
class CAntiyChatRoomClientDlg : public CDialog
{
// ����
public:
	CAntiyChatRoomClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CAntiyChatRoomClientDlg();

// �Ի�������
	enum { IDD = IDD_ANTIYCHATROOMCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
