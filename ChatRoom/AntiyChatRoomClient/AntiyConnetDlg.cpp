// AntiyConnetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AntiyChatRoomClient.h"
#include "AntiyConnetDlg.h"


// CAntiyConnetDlg �Ի���

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


// CAntiyConnetDlg ��Ϣ�������

void CAntiyConnetDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ��ø����ڵľ��  
	HWND hWnd = this->GetParent()->GetSafeHwnd();  
	int i = m_IP.GetLength();
	if (m_IP.GetLength()<8 || m_Port<= 0)
	{
		AfxMessageBox(_T("��������"));
		return;
	}
	if (m_Name.GetLength() < 1)
	{
		AfxMessageBox(_T("��������ȷ������"));
		return;
	}
	LoadingInfo m_linfo;
	m_linfo.strIp = m_IP;
	m_linfo.nPort = m_Port;
	m_linfo.strName = m_Name;
	// �򸸴��ڷ�����Ϣ  
	if (hWnd == NULL) return (void)MessageBox(_T("��ø����ھ��ʧ�ܣ�"));  
	::SendNotifyMessage(hWnd,WM_CONNECT_MSG,(WPARAM)&m_linfo,NULL); 
	OnCancel();
}

void CAntiyConnetDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
