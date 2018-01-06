
// INISettingDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <map>
#include "SimpleIni.h"
using namespace std;
// CINISettingDlg 对话框

typedef struct _info{
	CListCtrl * m_list;
	int col;
	bool asc;
}INFO;

class CINISettingDlg : public CDialogEx
{
// 构造
public:
	CINISettingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_XSJ_TESTDEMO_MAINDIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonOpenini();
	afx_msg void OnClickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnSetfocusListIniInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboDropbox();		//下拉框选中
	afx_msg void OnBnClickedButtonSaveini();		//保存list
	afx_msg void OnKillfocusEditList();
	//afx_msg void OnBnClickedButtonTestExport();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnColumnclickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult);


	DECLARE_MESSAGE_MAP()
public:
	int ReadMyIni(CString strPath);
	int Init();
public:
	CListCtrl m_Listini;
	CEdit m_EditList;
	CButton m_BtnOpenini;
	CSimpleIniA ini;
	CComboBox m_ComboBoxSec;
	//CButton m_BtnTestStatus;
	//CButton m_BtnLineStatus;
	CStatic m_staticExport;
	//CButton m_btnCancleExport;
	CStatic m_staticPort;

public:
	CString strIniPath;
	CString strSecChoce;			//当前combox选中项目
	//map<CString,CString> m_mapReadIni;
	int n_Row,n_Col;
	bool asc;

	CFont fontTip,fontTitle,fontPort;
	CBrush brushTip,brushTitle,brushPort;
	BOOL bIsSortPortStart;  //是否打开的是sortPortStart
	BOOL bLineStatus; //线体状态
	//BOOL bPortTEST;  //强制确定按钮状态
	BOOL bIsClickSortPort; //是否选中格口信息
	
};
