
// INISettingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <map>
#include "SimpleIni.h"
using namespace std;
// CINISettingDlg �Ի���

typedef struct _info{
	CListCtrl * m_list;
	int col;
	bool asc;
}INFO;

class CINISettingDlg : public CDialogEx
{
// ����
public:
	CINISettingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XSJ_TESTDEMO_MAINDIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonOpenini();
	afx_msg void OnClickListIniInfo(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnSetfocusListIniInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboDropbox();		//������ѡ��
	afx_msg void OnBnClickedButtonSaveini();		//����list
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
	CString strSecChoce;			//��ǰcomboxѡ����Ŀ
	//map<CString,CString> m_mapReadIni;
	int n_Row,n_Col;
	bool asc;

	CFont fontTip,fontTitle,fontPort;
	CBrush brushTip,brushTitle,brushPort;
	BOOL bIsSortPortStart;  //�Ƿ�򿪵���sortPortStart
	BOOL bLineStatus; //����״̬
	//BOOL bPortTEST;  //ǿ��ȷ����ť״̬
	BOOL bIsClickSortPort; //�Ƿ�ѡ�и����Ϣ
	
};
