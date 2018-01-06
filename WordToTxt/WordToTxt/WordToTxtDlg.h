
// WordToTxtDlg.h : 头文件
//

#pragma once
#include "CApplication.h"
#include "CDocuments.h"
#include "CDocument0.h"
#include "CSection.h"
#include "CRange.h"
#include <fstream>
#include <vector>

using namespace std;

// CWordToTxtDlg 对话框
class CWordToTxtDlg : public CDialogEx
{
// 构造
public:
	CWordToTxtDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WORDTOTXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenWord();
	afx_msg void OnBnClickedConvert();
	afx_msg void OnBnClickedOpenPath();
	int ReadDocPath(CString  strDoc);
	char* UnicodeToANSI( const wchar_t* str );  
	int FindDocFile(CString strFoldername);

public:
	CApplication    m_oApp;    
	CDocuments      m_oDocs;     
	CDocument0      m_oDoc;
	CSection		m_oSel;
	CRange			m_oRange;
	CString strFilePath;
	CString strFileName;
	CString txt;
	vector<CString> v_mDocPath;
	vector<CString> v_mDocName;
	
	afx_msg void OnDestroy();
};
