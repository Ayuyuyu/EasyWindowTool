
// timestampDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "timestamp.h"
#include "timestampDlg.h"
#include "afxdialogex.h"
#include "define.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtimestampDlg �Ի���




CtimestampDlg::CtimestampDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtimestampDlg::IDD, pParent)
	, strNowTimestamp(_T(""))
	, strUnixTimestampReady(_T(""))
	, strTimeResult(_T(""))
	, strTimeReady(_T(""))
	, strUnixTimestampResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtimestampDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOWTIMESTAMP, m_editNowTimestamp);
	DDX_Text(pDX, IDC_EDIT_NOWTIMESTAMP, strNowTimestamp);
	DDX_Control(pDX, IDC_BUTTON_NOW_RENEW, m_btnNowReNew);
	DDX_Control(pDX, IDC_EDIT_UNIX_TIMESTAMP_READY, m_editUnixTimestampReady);
	DDX_Text(pDX, IDC_EDIT_UNIX_TIMESTAMP_READY, strUnixTimestampReady);
	DDX_Control(pDX, IDC_BUTTON_CONVERT2TIME, m_btnConvert2Time);
	DDX_Control(pDX, IDC_EDIT_TIME_RESULT, m_editTimeResult);
	DDX_Text(pDX, IDC_EDIT_TIME_RESULT, strTimeResult);
	DDX_Control(pDX, IDC_EDIT_TIME_READY, m_editTimeReady);
	DDX_Text(pDX, IDC_EDIT_TIME_READY, strTimeReady);
	DDX_Control(pDX, IDC_BUTTON_CONVERT2TIMESTAMP, m_btnConvert2Timestamp);
	DDX_Control(pDX, IDC_EDIT_UNIX_TIMESTAMP_RESULT, m_editUnixTimestampResult);
	DDX_Text(pDX, IDC_EDIT_UNIX_TIMESTAMP_RESULT, strUnixTimestampResult);
}

BEGIN_MESSAGE_MAP(CtimestampDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONVERT2TIME, &CtimestampDlg::OnBnClickedButtonConvert2time)
	ON_BN_CLICKED(IDC_BUTTON_NOW_RENEW, &CtimestampDlg::OnBnClickedButtonNowRenew)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT2TIMESTAMP, &CtimestampDlg::OnBnClickedButtonConvert2timestamp)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CtimestampDlg ��Ϣ�������

BOOL CtimestampDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtimestampDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtimestampDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtimestampDlg::OnBnClickedButtonConvert2time()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_editUnixTimestampReady.GetWindowText(strUnixTimestampReady);
	DWORD  dwUnixTimestampReady = _ttol(strUnixTimestampReady);
	strTimeResult = mtime.ConvertTimeStamp2Time(dwUnixTimestampReady);
	m_editTimeResult.SetWindowText(strTimeResult);
}


void CtimestampDlg::OnBnClickedButtonNowRenew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dwNowTimestamp = mtime.GetNowTimeStamp();
	strNowTimestamp.Format(__T("%d"),dwNowTimestamp);
	m_editNowTimestamp.SetWindowText(strNowTimestamp);
	KillTimer(TIMER_NOWTIME);
	SetTimer(TIMER_NOWTIME,1000,0);
}


void CtimestampDlg::OnBnClickedButtonConvert2timestamp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_editTimeReady.GetWindowText(strTimeReady);
	DWORD dwTimeResult = mtime.ConvertTime2TimeStamp(strTimeReady);
	strUnixTimestampResult.Format(__T("%d"),dwTimeResult);
	m_editUnixTimestampResult.SetWindowText(strUnixTimestampResult);
}


void CtimestampDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)      
	{      
	case TIMER_NOWTIME:         
		{
			dwNowTimestamp++;
			strNowTimestamp.Format(__T("%d"),dwNowTimestamp);
			m_editNowTimestamp.SetWindowText(strNowTimestamp);
			
		}
		break;      
	default:      
		break;      
	}      
	CDialogEx::OnTimer(nIDEvent);
}
