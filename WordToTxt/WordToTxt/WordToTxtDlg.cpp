
// WordToTxtDlg.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "WordToTxt.h"
#include "WordToTxtDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWordToTxtDlg 对话框




CWordToTxtDlg::CWordToTxtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWordToTxtDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordToTxtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWordToTxtDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN_WORD, &CWordToTxtDlg::OnBnClickedOpenWord)
	ON_BN_CLICKED(ID_CONVERT, &CWordToTxtDlg::OnBnClickedConvert)
	ON_BN_CLICKED(IDC_OPEN_PATH, &CWordToTxtDlg::OnBnClickedOpenPath)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CWordToTxtDlg 消息处理程序

BOOL CWordToTxtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (CoInitialize(NULL) != 0)    
	{    
		AfxMessageBox(_T("COM库初始化失败！"));    
		exit(1);    
	}    

  
	v_mDocPath.clear();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWordToTxtDlg::OnPaint()
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
HCURSOR CWordToTxtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWordToTxtDlg::OnBnClickedOpenWord()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.doc)|*.docx|All Files (*.*)|*.*||"), NULL);  

	if (dlgFile.DoModal())  
	{  
		strFilePath = dlgFile.GetPathName();  
		strFileName = dlgFile.GetFileTitle();
		//MessageBox(strFile);
		SetDlgItemText(IDC_STATIC_PATH,strFilePath);
	
	}  
}


void CWordToTxtDlg::OnBnClickedConvert()
{
	// TODO: 在此添加控件通知处理程序代码
	if (v_mDocPath.size() != 0 && v_mDocName.size() !=0)
	{
		for (int i = 0;i<v_mDocPath.size();i++)
		{
			ReadDocPath(v_mDocPath[i]);
			if (txt.GetLength() > 0)
			{
				ofstream of;
				CString strtmp;
				strtmp.Format(_T("%s.txt"),v_mDocName[i]);
				of.open(strtmp);
				of<<UnicodeToANSI(txt);
				of.close();	
			}
		}
		MessageBox(_T("批量转换完成"));
	}
	else if (strFilePath.GetLength() != 0)
	{
		ReadDocPath(strFilePath);
		if (txt.GetLength() > 0)
		{
			ofstream of;
			CString strtmp;
			strtmp.Format(_T("%s.txt"),strFileName);
			of.open(strtmp);
			of<<UnicodeToANSI(txt);
			of.close();
			MessageBox(_T("转换完成"));
		}
	}
	else
	{
		MessageBox(_T("请先选择文件或路径"));
	}
	
}



int CWordToTxtDlg::ReadDocPath(CString strDoc)
{
	if (!m_oApp.CreateDispatch(_T("Word.Application"), NULL))    
	{    
		AfxMessageBox(_T("启动Word程序失败！"));    
		return -1;    
	}  
	COleVariant  
		covTrue((short)TRUE),  
		covFalse((short)FALSE),  
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),  
		//covFileName(_T("E:\\temp\\ac\\Debug\\imgreport.dotx"));  
		covFileName(strDoc);  
	
	m_oDocs = m_oApp.get_Documents();
	m_oDoc = m_oDocs.Open(covFileName,covFalse,covTrue,covFalse,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);	
	m_oRange=m_oDoc.Range(covOptional,covOptional);
	txt = m_oRange.get_Text();

	m_oRange.ReleaseDispatch();
	m_oDoc.Close(covOptional,covOptional,covOptional);
	m_oDoc.ReleaseDispatch();
	m_oDocs.ReleaseDispatch();
	m_oApp.Quit(covOptional,covOptional,covOptional);
	m_oApp.ReleaseDispatch();

//	CoUninitialize();
	return 1;
}

char* CWordToTxtDlg:: UnicodeToANSI( const wchar_t* str )   
{   
	char* result;   
	int textlen;   
	textlen = WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL );   
	result =(char *)malloc((textlen+1)*sizeof(char));   
	memset( result, 0, sizeof(char) * ( textlen + 1 ) );   
	WideCharToMultiByte( CP_ACP, 0, str, -1, result, textlen, NULL, NULL );   
	return result;   
} 

int CWordToTxtDlg::FindDocFile(CString strFoldername)
{
	v_mDocPath.clear();
	v_mDocName.clear();
	CString m_cstrFileList;  
	CFileFind tempFind;   
	BOOL bFound; //判断是否成功找到文件  
	strFoldername = strFoldername + _T("\\*.doc*");
	bFound=tempFind.FindFile(strFoldername);   //修改" "内内容给限定查找文件类型  
	CString strTmppath;   //如果找到的是文件夹 存放文件夹路径
	CString strTmpname;
	while(bFound)      //遍历所有文件  
	{   
		bFound=tempFind.FindNextFile(); //第一次执行FindNextFile是选择到第一个文件，以后执行为选择到下一个文件  
		if( tempFind.IsDots())   
			continue; //如果找到的是返回上层的目录 则结束本次查找  
		if(tempFind.IsDirectory())   //找到的是文件夹，则遍历该文件夹下的文件  
		{   
			//strTmp="";   
			strTmppath=tempFind.GetFilePath();  
			FindDocFile(strTmppath);   
		}   
		else   
		{   
			strTmpname = tempFind.GetFileTitle();
			strTmppath=tempFind.GetFilePath(); //保存文件名，包括后缀名  
			// 在此处添加对找到文件的处理  
			//MessageBox(strTmp);
			v_mDocPath.push_back(strTmppath);
			v_mDocName.push_back(strTmpname);
			 
		}   
	}   
	tempFind.Close();   
	
	return 1;
}

void CWordToTxtDlg::OnBnClickedOpenPath()
{
	BROWSEINFO  bi;
	bi.hwndOwner=NULL;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=NULL;
	bi.lpszTitle=NULL;
	bi.ulFlags=0;
	bi.lpfn =NULL;
	bi.iImage =0;
	LPCITEMIDLIST pidl=SHBrowseForFolder(&bi);
	if(!pidl)
		return;
	TCHAR  szDisplayName[255];
	SHGetPathFromIDList(pidl,szDisplayName);
	CString strPath(szDisplayName);
	//MessageBox(strPath,NULL,MB_OK);
	SetDlgItemText(IDC_STATIC_PATH,strPath);
	FindDocFile(strPath);
	// TODO: 在此添加控件通知处理程序代码
}


void CWordToTxtDlg::OnDestroy()
{

	CoUninitialize();
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
