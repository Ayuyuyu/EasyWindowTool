#pragma once



class LoadingInfo
{
public:
	CString strIp;
	int nPort;
	CString strName;
};

// CAntiyConnetDlg 对话框

class CAntiyConnetDlg : public CDialog
{
	DECLARE_DYNAMIC(CAntiyConnetDlg)

public:
	CAntiyConnetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAntiyConnetDlg();

// 对话框数据
	enum { IDD = IDD_DIACONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	CString m_IP;
	int m_Port;
	CString m_Name;
};
