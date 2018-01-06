
// WordToTxtDlg.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "WordToTxt.h"
#include "WordToTxtDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWordToTxtDlg �Ի���




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


// CWordToTxtDlg ��Ϣ�������

BOOL CWordToTxtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (CoInitialize(NULL) != 0)    
	{    
		AfxMessageBox(_T("COM���ʼ��ʧ�ܣ�"));    
		exit(1);    
	}    

  
	v_mDocPath.clear();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWordToTxtDlg::OnPaint()
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
HCURSOR CWordToTxtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWordToTxtDlg::OnBnClickedOpenWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("����ת�����"));
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
			MessageBox(_T("ת�����"));
		}
	}
	else
	{
		MessageBox(_T("����ѡ���ļ���·��"));
	}
	
}



int CWordToTxtDlg::ReadDocPath(CString strDoc)
{
	if (!m_oApp.CreateDispatch(_T("Word.Application"), NULL))    
	{    
		AfxMessageBox(_T("����Word����ʧ�ܣ�"));    
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
	BOOL bFound; //�ж��Ƿ�ɹ��ҵ��ļ�  
	strFoldername = strFoldername + _T("\\*.doc*");
	bFound=tempFind.FindFile(strFoldername);   //�޸�" "�����ݸ��޶������ļ�����  
	CString strTmppath;   //����ҵ������ļ��� ����ļ���·��
	CString strTmpname;
	while(bFound)      //���������ļ�  
	{   
		bFound=tempFind.FindNextFile(); //��һ��ִ��FindNextFile��ѡ�񵽵�һ���ļ����Ժ�ִ��Ϊѡ����һ���ļ�  
		if( tempFind.IsDots())   
			continue; //����ҵ����Ƿ����ϲ��Ŀ¼ ��������β���  
		if(tempFind.IsDirectory())   //�ҵ������ļ��У���������ļ����µ��ļ�  
		{   
			//strTmp="";   
			strTmppath=tempFind.GetFilePath();  
			FindDocFile(strTmppath);   
		}   
		else   
		{   
			strTmpname = tempFind.GetFileTitle();
			strTmppath=tempFind.GetFilePath(); //�����ļ�����������׺��  
			// �ڴ˴���Ӷ��ҵ��ļ��Ĵ���  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CWordToTxtDlg::OnDestroy()
{

	CoUninitialize();
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}
