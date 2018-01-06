// INISettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "INISetting.h"
#include "INISettingDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CINISettingDlg �Ի���




CINISettingDlg::CINISettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CINISettingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Init(); //��ʼ������
}

void CINISettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INI_INFO, m_Listini);
	DDX_Control(pDX, IDC_BUTTON_OPENINI, m_BtnOpenini);
	DDX_Control(pDX, IDC_EDIT_LIST, m_EditList);
	DDX_Control(pDX, IDC_COMBO_DROPBOX, m_ComboBoxSec);
}

BEGIN_MESSAGE_MAP(CINISettingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENINI, &CINISettingDlg::OnBnClickedButtonOpenini)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INI_INFO, &CINISettingDlg::OnClickListIniInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_DROPBOX, &CINISettingDlg::OnCbnSelchangeComboDropbox)
	ON_BN_CLICKED(IDC_BUTTON_SAVEINI, &CINISettingDlg::OnBnClickedButtonSaveini)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST, &CINISettingDlg::OnKillfocusEditList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_INI_INFO, &CINISettingDlg::OnColumnclickListIniInfo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


int CINISettingDlg::Init()
{
	strIniPath = _T("");
	strSecChoce = _T("");
	asc =true;
	n_Row = -1;
	n_Col = -1;
	bIsSortPortStart = FALSE;
	bLineStatus = TRUE;
	//bPortTEST = TRUE;
	bIsClickSortPort = FALSE;

	return 1;
}

// CINISettingDlg ��Ϣ�������

BOOL CINISettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
	m_Listini.GetClientRect(&rect);   

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_Listini.SetExtendedStyle(m_Listini.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  
	m_Listini.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/2, 0);   
	m_Listini.InsertColumn(1, _T("��ֵ"), LVCFMT_CENTER, rect.Width()/2, 1);   
	
	brushTitle.CreateSolidBrush(RGB(50,180,200));
	fontTitle.CreatePointFont(100,_T("΢���ź�"),NULL);//
	brushTip.CreateSolidBrush(RGB(0, 0, 255));//��ˢ
	fontTip.CreatePointFont(80,_T("΢���ź�"), NULL);//
	brushPort.CreateSolidBrush(RGB(220,55,20));
	fontPort.CreatePointFont(100,_T("΢���ź�"),NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CINISettingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CINISettingDlg::OnPaint()
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
HCURSOR CINISettingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CINISettingDlg::OnBnClickedButtonOpenini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bIsSortPortStart = FALSE;


	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.ini)||All Files (*.*)|*.*||"), NULL);  

	if (dlgFile.DoModal())  
	{  
		strIniPath = dlgFile.GetPathName();  
		//strFileName = dlgFile.GetFileTitle();
		if (strIniPath.GetLength() > 0 && strIniPath.Find(_T(".ini")) > 0)
		{
			SetDlgItemText(IDC_EDIT_OPENPATH,strIniPath);
			ReadMyIni(strIniPath);
		}
		else
		{
			MessageBox(_T("��ѡ����ȷ��ini�ļ���"));
			m_Listini.DeleteAllItems();
			m_ComboBoxSec.ResetContent();			//���combox
		}
	}  

}



void CINISettingDlg::OnClickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;  
	CRect rc;  
	n_Row = pNMListView->iItem;		//���ѡ�е���  
	n_Col = pNMListView->iSubItem;//���ѡ����  

	if (pNMListView->iSubItem == 0 && bIsSortPortStart)		//�����sortportstart.ini 
	{
		CString strStatictmp;		//��̬�ı���ʾ��Ϣ
		strStatictmp.Format(_T("��ǰѡ������Ϊ��%s"),m_Listini.GetItemText(n_Row,n_Col));
		m_staticExport.SetWindowText(strStatictmp);
		bIsClickSortPort = TRUE;
	}
  if   (pNMListView->iSubItem > 0) //���ѡ���������;  ��ѡ��
	{  
		m_Listini.GetSubItemRect(n_Row,n_Col,LVIR_LABEL,rc);					//��������RECT��  
		m_EditList.SetParent(&m_Listini);														//ת������Ϊ�б���е�����  
		m_EditList.MoveWindow(rc);																//�ƶ�Edit��RECT���ڵ�λ��;  
		m_EditList.SetWindowText(m_Listini.GetItemText(n_Row,n_Col));		//���������е�ֵ����Edit�ؼ��У�  
		m_EditList.ShowWindow(SW_SHOW);												//��ʾEdit�ؼ���  
		m_EditList.SetFocus();																		//����Edit����  
		m_EditList.ShowCaret();																		//��ʾ���  
		m_EditList.SetSel(-1);																		//������ƶ������  
		//strNowListEditSave = m_Listini.GetItemText(n_Row,n_Col);
	}  
	else
	{
		return;
	}
	*pResult = 0;
}


/*
//���浱ǰ���úõ���ֵ��list�б���
void CINISettingDlg::OnSetfocusListIniInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	CString str;
	m_EditList.GetWindowText(str);
	m_Listini.SetItemText(n_Row, n_Col, str); 
	if (str == strNowListEditSave)
	{
	//	return;
	}

	m_EditList.ShowWindow(SW_HIDE);
	m_EditList.SetWindowText(_T(""));
		Invalidate();  
	*pResult = 0;
}
*/

/*	���ܣ���Ӧcomboxѡ��Ч��
*/
void CINISettingDlg::OnCbnSelchangeComboDropbox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (strSecChoce.GetLength()  < 0)				//ѡ����Ŀ
	{
		return;
	}

	int i = 0;
	m_EditList.ShowWindow(SW_HIDE);		//���ر༭��
	m_Listini.DeleteAllItems();		//���list
	//m_mapReadIni.clear();			//���map

	CSimpleIniA::TNamesDepend keys;
	
	m_ComboBoxSec.GetLBText(m_ComboBoxSec.GetCurSel(),strSecChoce);		//��ȡ��ǰcomboxѡ��ֵ
	ini.GetAllKeys(CW2A(strSecChoce),keys);														//��ȡ��ǰsections ������key��ֵ
	//const char* mz = keys[0].pItem;
	CSimpleIniA::TNamesDepend::iterator it_key = keys.begin();  
	for(;it_key!=keys.end();it_key++)  
	{  
		const char* szTmp = it_key->pItem;//key
		CString strTemp(szTmp);
		TCHAR szNum[256] = {0};
		GetPrivateProfileString(strSecChoce.GetBuffer(strSecChoce.GetLength()),strTemp.GetBuffer(strTemp.GetLength()),_T(""),szNum,sizeof(szNum),strIniPath);
		m_Listini.InsertItem(i,strTemp);																//��ʾ��list��
		m_Listini.SetItemText(i,1,szNum);
		i++;
	}  
	/*
	map<CString, CString>::iterator  iter;
	int i = 0;
	for(iter = m_mapReadIni.begin(); iter != m_mapReadIni.end(); iter++)			//����
	{
		m_Listini.InsertItem(i,iter->first);
		m_Listini.SetItemText(i,1,iter->second);
		i++;
	} 
	*/
}

/*
���ܣ����水ť
*/
void CINISettingDlg::OnBnClickedButtonSaveini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nListCount = m_Listini.GetItemCount();
	if (nListCount <= 0)
	{
		return;
	}
	for (int i = 0 ; i < nListCount; i++)
	{
		CString strKeyName = m_Listini.GetItemText(i,0);  //��һ��
		CString strValue = m_Listini.GetItemText(i,1);		//�ڶ���
		WritePrivateProfileString(strSecChoce,strKeyName,strValue,strIniPath);			//��ʱֻ�����޸ĵڶ���ֵ
	}
	MessageBox(_T("����ɹ�"));
}


/*
���ܣ�EDITʧȥ����
*/
void CINISettingDlg::OnKillfocusEditList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString str;
	m_EditList.GetWindowText(str);
	m_Listini.SetItemText(n_Row, n_Col, str);			//��ȡEDIT�ϵ�ֵ��List

	m_EditList.ShowWindow(SW_HIDE);
	m_EditList.SetWindowText(_T(""));
}


/* ���ܣ���ȡINI�����ļ���ϸ��Ϣ
*   ���룺strPath ����ini·��
*	���� �� >0 Ϊ����
*/
int CINISettingDlg::ReadMyIni(CString strPath)
{
	if (strPath.GetLength() <= 0)
	{
		return -1;
	}
	m_Listini.DeleteAllItems();
	m_ComboBoxSec.ResetContent();			//���combox

	//ini.SetUnicode();
	ini.Reset();   //����� ��Ȼsections�ᴢ��ܶ�
	ini.LoadFile(strPath);
	//const char * pVal = ini.GetValue(("AssLine"), "key3", "default");
	CSimpleIniA::TNamesDepend sections;
	sections.clear();
	ini.GetAllSections(sections);
	CSimpleIniA::TNamesDepend::iterator it_sec = sections.begin();  
	for (;it_sec != sections.end();it_sec++)
	{
		CString strTemp_sec(it_sec->pItem);
		m_ComboBoxSec.AddString(strTemp_sec);	//��combox�����ַ���Ϊsections�б�
	}
	CString strShowtmp;
	m_ComboBoxSec.SetCurSel(0);
	OnCbnSelchangeComboDropbox();
	return 1;
}

//¥��ʹ�õĻص�����
static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CString text1,text2,strT;
	INFO* info = (INFO*)lParamSort;

	strT = info->m_list->GetItemText((int)lParam1, info->col);
	text1.Format(_T("%s"), strT.Mid(8));		//������sortPortStart.ini��Ч
	text1.Trim();

	strT = info->m_list->GetItemText((int)lParam2, info->col);
	text2.Format(_T("%s"),  strT.Mid(8));
	text2.Trim();

	int i = 0;
	if (info->asc)
		i = _ttoi(text1.GetBuffer())> _ttoi(text2.GetBuffer());
	else
		i = _ttoi(text1.GetBuffer()) < _ttoi(text2.GetBuffer());

	return i;
}

/*
��Ӧ���LIst��ͷ����Ϣ��������Ҫ�ж�sortPortStart.ini������
*/
void CINISettingDlg::OnColumnclickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult)    //���sortPortStart.ini ������
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (!bIsSortPortStart)  //û���ҵ�
	{
		return;
	}
	static int iSorted = -1; //�����к�
	if (pNMLV->iSubItem != 0)   //ֻΪ��һ��
	{
		*pResult = 0;
		return;
	}

	if (pNMLV->iSubItem == iSorted)
		asc = !asc;

	CListCtrl* m_ListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_INI_INFO);

	INFO info;
	info.col = iSorted = 0;//ֻ��Ե�һ������
	info.m_list = m_ListCtrl;
	info.asc = asc;

	m_ListCtrl->SortItemsEx((PFNLVCOMPARE)MyCompareProc, (LPARAM)&info);
	*pResult = 0;
}




HBRUSH CINISettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEST_EXPORT)
	{
		pDC->SetBkColor(RGB(50,180,200));//����ɫ
		pDC->SetTextColor(RGB(255, 255, 255));//����
		pDC->SelectObject(&fontTitle);//����Ϊ15�����壬�����п�
		return brushTitle;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP1)
	{
		//pDC->SetBkColor(RGB(220,55,20));//����ɫ
		pDC->SetTextColor(RGB(65, 180, 100));//����
		pDC->SelectObject(&fontTitle);//����Ϊ15�����壬�����п�
		return hbr;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_PORT)
	{
		pDC->SetBkColor(RGB(220,55,20));
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SelectObject(&fontPort);
		return brushPort;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


