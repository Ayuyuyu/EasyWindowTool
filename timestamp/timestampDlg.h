
// timestampDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "GetTimeStamp.h"

// CtimestampDlg �Ի���
class CtimestampDlg : public CDialogEx
{
// ����
public:
	CtimestampDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TIMESTAMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTimeStamp mtime;
	DWORD dwNowTimestamp;
public:
	CEdit m_editNowTimestamp;			//��ǰʱ��� edit
	CButton m_btnNowReNew;				//��ǰʱ���ˢ�� btn
	CEdit m_editUnixTimestampReady;	//ʱ��� ��ת�� edit
	CButton m_btnConvert2Time;			//ת����ʱ��	btn
	CEdit m_editTimeResult;					//ת����ʱ���� edit
	CEdit m_editTimeReady;					//ʱ�� ��ת�� edit
	CButton m_btnConvert2Timestamp;		//ת����ʱ��� btn
	CEdit m_editUnixTimestampResult;    //ת����ʱ������ edit

public:
	CString strNowTimestamp;				//��ǰʱ���
	CString strUnixTimestampReady;		//ʱ��� ��ת��
	CString strTimeResult;						//ת����ʱ����
	CString strTimeReady;						//ʱ�� ��ת�� 
	CString strUnixTimestampResult;		//ת����ʱ������
	afx_msg void OnBnClickedButtonConvert2time();
	afx_msg void OnBnClickedButtonNowRenew();
	afx_msg void OnBnClickedButtonConvert2timestamp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
