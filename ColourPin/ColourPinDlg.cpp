
// ColourPinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColourPin.h"
#include "ColourPinDlg.h"
#include "afxdialogex.h"

#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColourPinDlg 对话框




CColourPinDlg::CColourPinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColourPinDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDlgList = nullptr;
}

void CColourPinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PIN, mColourPin);
	DDX_Control(pDX, IDC_BUTTON_COLOUR_CHOSE, mColourChose);
	DDX_Control(pDX, IDC_BUTTON_SHOWCOLOUR, mColourShow);
	DDX_Control(pDX, IDC_EDIT_RGB, mEditRGB);
	DDX_Control(pDX, IDC_EDIT_HEX, mEditHEX);
}

BEGIN_MESSAGE_MAP(CColourPinDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COLOUR_CHOSE, &CColourPinDlg::OnBnClickedButtonColourChose)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_USER_POINT_COLOUR, &CColourPinDlg::OnUserPointColour)
	ON_WM_DESTROY()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CColourPinDlg 消息处理程序

BOOL CColourPinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	mColourShow.SetFaceColor(RGB(255,255,255));
	//bmp.LoadBitmap(IDB_BITMAP);	
	// TODO: 在此添加额外的初始化代码
	//mColourPin.SetBitmap(bmp);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CColourPinDlg::OnPaint()
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
HCURSOR CColourPinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CColourPinDlg::OnUserPointColour(WPARAM wParam, LPARAM lParam)
{
	COLORREF col = (COLORREF)wParam;
	SetBtnShowColour(col);
	return 0;
}

void CColourPinDlg::OnBnClickedButtonColourChose()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog *m_pColorDlg = new CColorDialog();
	COLORREF color;  

	if (m_pColorDlg != NULL && IDOK == m_pColorDlg->DoModal())                  // 启动调色板  
	{  
		color = m_pColorDlg->GetColor();                // 获得选取的颜色  

		SetBtnShowColour(color);
		UpdateData(FALSE);  
	}  
}


void CColourPinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnSysCommand(nID, lParam);

}

void CColourPinDlg::SetBtnShowColour(COLORREF col)
{
	int n_colorR,n_colorG,n_colorB;
	n_colorR = GetRValue(col);
	n_colorG = GetGValue(col);
	n_colorB = GetBValue(col);

	DWORD rgb[3] = {n_colorR,n_colorG,n_colorB};
	CString strRGB,strHEX;
	strRGB.Format(_T("%d,%d,%d"),n_colorR,n_colorG,n_colorB);
	strHEX = m_ColourBase.RGBto16(rgb);
	mEditRGB.SetWindowText(strRGB);
	mEditHEX.SetWindowText(strHEX);
	mColourShow.SetFaceColor(RGB(n_colorR,n_colorG,n_colorB));
	if (m_pDlgList == nullptr)
	{
		m_pDlgList = new CDlgColourList();
		m_pDlgList->Create(IDD_COLOURLIST_DIALOG,this);       //创建对话框
		m_pDlgList->ShowWindow(SW_SHOW);                //显示对话框
	}

	m_pDlgList->SetListBtnColour(rgb);

}

void CColourPinDlg::MoveColorDialog(CRect rt_colourDlg)
{
	CRect rt_pinDlg;
	GetWindowRect(rt_pinDlg);
}



void CColourPinDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}


void CColourPinDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	if (m_pDlgList)
	{
		m_pDlgList->MovePOS();
	}
}
