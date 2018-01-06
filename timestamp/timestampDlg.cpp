
// timestampDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "timestamp.h"
#include "timestampDlg.h"
#include "afxdialogex.h"
#include "define.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtimestampDlg 对话框




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


// CtimestampDlg 消息处理程序

BOOL CtimestampDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtimestampDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtimestampDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtimestampDlg::OnBnClickedButtonConvert2time()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editUnixTimestampReady.GetWindowText(strUnixTimestampReady);
	DWORD  dwUnixTimestampReady = _ttol(strUnixTimestampReady);
	strTimeResult = mtime.ConvertTimeStamp2Time(dwUnixTimestampReady);
	m_editTimeResult.SetWindowText(strTimeResult);
}


void CtimestampDlg::OnBnClickedButtonNowRenew()
{
	// TODO: 在此添加控件通知处理程序代码
	dwNowTimestamp = mtime.GetNowTimeStamp();
	strNowTimestamp.Format(__T("%d"),dwNowTimestamp);
	m_editNowTimestamp.SetWindowText(strNowTimestamp);
	KillTimer(TIMER_NOWTIME);
	SetTimer(TIMER_NOWTIME,1000,0);
}


void CtimestampDlg::OnBnClickedButtonConvert2timestamp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editTimeReady.GetWindowText(strTimeReady);
	DWORD dwTimeResult = mtime.ConvertTime2TimeStamp(strTimeReady);
	strUnixTimestampResult.Format(__T("%d"),dwTimeResult);
	m_editUnixTimestampResult.SetWindowText(strUnixTimestampResult);
}


void CtimestampDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
