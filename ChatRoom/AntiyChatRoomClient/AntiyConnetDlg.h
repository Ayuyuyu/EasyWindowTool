#pragma once



class LoadingInfo
{
public:
	CString strIp;
	int nPort;
	CString strName;
};

// CAntiyConnetDlg �Ի���

class CAntiyConnetDlg : public CDialog
{
	DECLARE_DYNAMIC(CAntiyConnetDlg)

public:
	CAntiyConnetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAntiyConnetDlg();

// �Ի�������
	enum { IDD = IDD_DIACONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	CString m_IP;
	int m_Port;
	CString m_Name;
};
