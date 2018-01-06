// AntiyConnetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AntiyChatRoomClient.h"
#include "AntiyConnetDlg.h"


// CAntiyConnetDlg 对话框

IMPLEMENT_DYNAMIC(CAntiyConnetDlg, CDialog)

CAntiyConnetDlg::CAntiyConnetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntiyConnetDlg::IDD, pParent)
	, m_IP(_T(""))
	, m_Port(0)
	, m_Name(_T(""))
{

}

CAntiyConnetDlg::~CAntiyConnetDlg()
{
}

void CAntiyConnetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_IP);
	DDX_Text(pDX, IDC_EDIT2, m_Port);
	DDX_Text(pDX, IDC_EDIT3, m_Name);
}


BEGIN_MESSAGE_MAP(CAntiyConnetDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAntiyConnetDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CAntiyConnetDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAntiyConnetDlg 消息处理程序

void CAntiyConnetDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 获得父窗口的句柄  
	HWND hWnd = this->GetParent()->GetSafeHwnd();  
	int i = m_IP.GetLength();
	if (m_IP.GetLength()<8 || m_Port<= 0)
	{
		AfxMessageBox(_T("输入有误"));
		return;
	}
	if (m_Name.GetLength() < 1)
	{
		AfxMessageBox(_T("请输入正确的名字"));
		return;
	}
	LoadingInfo m_linfo;
	m_linfo.strIp = m_IP;
	m_linfo.nPort = m_Port;
	m_linfo.strName = m_Name;
	// 向父窗口发送消息  
	if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));  
	::SendNotifyMessage(hWnd,WM_CONNECT_MSG,(WPARAM)&m_linfo,NULL); 
	OnCancel();
}

void CAntiyConnetDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
