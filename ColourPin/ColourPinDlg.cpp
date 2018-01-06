
// ColourPinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColourPin.h"
#include "ColourPinDlg.h"
#include "afxdialogex.h"

#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColourPinDlg �Ի���




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


// CColourPinDlg ��Ϣ�������

BOOL CColourPinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	mColourShow.SetFaceColor(RGB(255,255,255));
	//bmp.LoadBitmap(IDB_BITMAP);	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//mColourPin.SetBitmap(bmp);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CColourPinDlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog *m_pColorDlg = new CColorDialog();
	COLORREF color;  

	if (m_pColorDlg != NULL && IDOK == m_pColorDlg->DoModal())                  // ������ɫ��  
	{  
		color = m_pColorDlg->GetColor();                // ���ѡȡ����ɫ  

		SetBtnShowColour(color);
		UpdateData(FALSE);  
	}  
}


void CColourPinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
		m_pDlgList->Create(IDD_COLOURLIST_DIALOG,this);       //�����Ի���
		m_pDlgList->ShowWindow(SW_SHOW);                //��ʾ�Ի���
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
	// TODO: �ڴ˴������Ϣ����������
}


void CColourPinDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
	if (m_pDlgList)
	{
		m_pDlgList->MovePOS();
	}
}
