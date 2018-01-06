// INISettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "INISetting.h"
#include "INISettingDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CINISettingDlg 对话框




CINISettingDlg::CINISettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CINISettingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Init(); //初始化函数
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

// CINISettingDlg 消息处理程序

BOOL CINISettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	m_Listini.GetClientRect(&rect);   

	// 为列表视图控件添加全行选中和栅格风格   
	m_Listini.SetExtendedStyle(m_Listini.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  
	m_Listini.InsertColumn(0, _T("名称"), LVCFMT_CENTER, rect.Width()/2, 0);   
	m_Listini.InsertColumn(1, _T("数值"), LVCFMT_CENTER, rect.Width()/2, 1);   
	
	brushTitle.CreateSolidBrush(RGB(50,180,200));
	fontTitle.CreatePointFont(100,_T("微软雅黑"),NULL);//
	brushTip.CreateSolidBrush(RGB(0, 0, 255));//画刷
	fontTip.CreatePointFont(80,_T("微软雅黑"), NULL);//
	brushPort.CreateSolidBrush(RGB(220,55,20));
	fontPort.CreatePointFont(100,_T("微软雅黑"),NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CINISettingDlg::OnPaint()
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
HCURSOR CINISettingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CINISettingDlg::OnBnClickedButtonOpenini()
{
	// TODO: 在此添加控件通知处理程序代码
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
			MessageBox(_T("请选择正确的ini文件！"));
			m_Listini.DeleteAllItems();
			m_ComboBoxSec.ResetContent();			//清空combox
		}
	}  

}



void CINISettingDlg::OnClickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;  
	CRect rc;  
	n_Row = pNMListView->iItem;		//获得选中的行  
	n_Col = pNMListView->iSubItem;//获得选中列  

	if (pNMListView->iSubItem == 0 && bIsSortPortStart)		//如果是sortportstart.ini 
	{
		CString strStatictmp;		//静态文本显示信息
		strStatictmp.Format(_T("当前选择格口项为：%s"),m_Listini.GetItemText(n_Row,n_Col));
		m_staticExport.SetWindowText(strStatictmp);
		bIsClickSortPort = TRUE;
	}
  if   (pNMListView->iSubItem > 0) //如果选择的是子项;  若选中
	{  
		m_Listini.GetSubItemRect(n_Row,n_Col,LVIR_LABEL,rc);					//获得子项的RECT；  
		m_EditList.SetParent(&m_Listini);														//转换坐标为列表框中的坐标  
		m_EditList.MoveWindow(rc);																//移动Edit到RECT坐在的位置;  
		m_EditList.SetWindowText(m_Listini.GetItemText(n_Row,n_Col));		//将该子项中的值放在Edit控件中；  
		m_EditList.ShowWindow(SW_SHOW);												//显示Edit控件；  
		m_EditList.SetFocus();																		//设置Edit焦点  
		m_EditList.ShowCaret();																		//显示光标  
		m_EditList.SetSel(-1);																		//将光标移动到最后  
		//strNowListEditSave = m_Listini.GetItemText(n_Row,n_Col);
	}  
	else
	{
		return;
	}
	*pResult = 0;
}


/*
//保存当前设置好的数值到list列表中
void CINISettingDlg::OnSetfocusListIniInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	
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

/*	功能：响应combox选中效果
*/
void CINISettingDlg::OnCbnSelchangeComboDropbox()
{
	// TODO: 在此添加控件通知处理程序代码
	if (strSecChoce.GetLength()  < 0)				//选中项目
	{
		return;
	}

	int i = 0;
	m_EditList.ShowWindow(SW_HIDE);		//隐藏编辑框
	m_Listini.DeleteAllItems();		//清空list
	//m_mapReadIni.clear();			//清空map

	CSimpleIniA::TNamesDepend keys;
	
	m_ComboBoxSec.GetLBText(m_ComboBoxSec.GetCurSel(),strSecChoce);		//获取当前combox选中值
	ini.GetAllKeys(CW2A(strSecChoce),keys);														//获取当前sections 下所有key的值
	//const char* mz = keys[0].pItem;
	CSimpleIniA::TNamesDepend::iterator it_key = keys.begin();  
	for(;it_key!=keys.end();it_key++)  
	{  
		const char* szTmp = it_key->pItem;//key
		CString strTemp(szTmp);
		TCHAR szNum[256] = {0};
		GetPrivateProfileString(strSecChoce.GetBuffer(strSecChoce.GetLength()),strTemp.GetBuffer(strTemp.GetLength()),_T(""),szNum,sizeof(szNum),strIniPath);
		m_Listini.InsertItem(i,strTemp);																//显示到list中
		m_Listini.SetItemText(i,1,szNum);
		i++;
	}  
	/*
	map<CString, CString>::iterator  iter;
	int i = 0;
	for(iter = m_mapReadIni.begin(); iter != m_mapReadIni.end(); iter++)			//遍历
	{
		m_Listini.InsertItem(i,iter->first);
		m_Listini.SetItemText(i,1,iter->second);
		i++;
	} 
	*/
}

/*
功能：保存按钮
*/
void CINISettingDlg::OnBnClickedButtonSaveini()
{
	// TODO: 在此添加控件通知处理程序代码
	int nListCount = m_Listini.GetItemCount();
	if (nListCount <= 0)
	{
		return;
	}
	for (int i = 0 ; i < nListCount; i++)
	{
		CString strKeyName = m_Listini.GetItemText(i,0);  //第一列
		CString strValue = m_Listini.GetItemText(i,1);		//第二列
		WritePrivateProfileString(strSecChoce,strKeyName,strValue,strIniPath);			//暂时只允许修改第二个值
	}
	MessageBox(_T("保存成功"));
}


/*
功能：EDIT失去焦点
*/
void CINISettingDlg::OnKillfocusEditList()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	m_EditList.GetWindowText(str);
	m_Listini.SetItemText(n_Row, n_Col, str);			//获取EDIT上的值到List

	m_EditList.ShowWindow(SW_HIDE);
	m_EditList.SetWindowText(_T(""));
}


/* 功能：读取INI配置文件详细信息
*   输入：strPath 输入ini路径
*	返回 ： >0 为正常
*/
int CINISettingDlg::ReadMyIni(CString strPath)
{
	if (strPath.GetLength() <= 0)
	{
		return -1;
	}
	m_Listini.DeleteAllItems();
	m_ComboBoxSec.ResetContent();			//清空combox

	//ini.SetUnicode();
	ini.Reset();   //清空下 不然sections会储存很多
	ini.LoadFile(strPath);
	//const char * pVal = ini.GetValue(("AssLine"), "key3", "default");
	CSimpleIniA::TNamesDepend sections;
	sections.clear();
	ini.GetAllSections(sections);
	CSimpleIniA::TNamesDepend::iterator it_sec = sections.begin();  
	for (;it_sec != sections.end();it_sec++)
	{
		CString strTemp_sec(it_sec->pItem);
		m_ComboBoxSec.AddString(strTemp_sec);	//向combox输入字符，为sections列表
	}
	CString strShowtmp;
	m_ComboBoxSec.SetCurSel(0);
	OnCbnSelchangeComboDropbox();
	return 1;
}

//楼下使用的回调函数
static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CString text1,text2,strT;
	INFO* info = (INFO*)lParamSort;

	strT = info->m_list->GetItemText((int)lParam1, info->col);
	text1.Format(_T("%s"), strT.Mid(8));		//仅仅对sortPortStart.ini有效
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
响应点击LIst表头的消息。这里主要判断sortPortStart.ini的排序
*/
void CINISettingDlg::OnColumnclickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult)    //针对sortPortStart.ini 的排序
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (!bIsSortPortStart)  //没有找到
	{
		return;
	}
	static int iSorted = -1; //排序列号
	if (pNMLV->iSubItem != 0)   //只为第一列
	{
		*pResult = 0;
		return;
	}

	if (pNMLV->iSubItem == iSorted)
		asc = !asc;

	CListCtrl* m_ListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_INI_INFO);

	INFO info;
	info.col = iSorted = 0;//只针对第一列排序
	info.m_list = m_ListCtrl;
	info.asc = asc;

	m_ListCtrl->SortItemsEx((PFNLVCOMPARE)MyCompareProc, (LPARAM)&info);
	*pResult = 0;
}




HBRUSH CINISettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEST_EXPORT)
	{
		pDC->SetBkColor(RGB(50,180,200));//背景色
		pDC->SetTextColor(RGB(255, 255, 255));//文字
		pDC->SelectObject(&fontTitle);//文字为15号字体，华文行楷
		return brushTitle;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP1)
	{
		//pDC->SetBkColor(RGB(220,55,20));//背景色
		pDC->SetTextColor(RGB(65, 180, 100));//文字
		pDC->SelectObject(&fontTitle);//文字为15号字体，华文行楷
		return hbr;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_PORT)
	{
		pDC->SetBkColor(RGB(220,55,20));
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SelectObject(&fontPort);
		return brushPort;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


