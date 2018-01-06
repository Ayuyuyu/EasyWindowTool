
// timestampDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "GetTimeStamp.h"

// CtimestampDlg 对话框
class CtimestampDlg : public CDialogEx
{
// 构造
public:
	CtimestampDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TIMESTAMP_DIALOG };

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
	CTimeStamp mtime;
	DWORD dwNowTimestamp;
public:
	CEdit m_editNowTimestamp;			//当前时间戳 edit
	CButton m_btnNowReNew;				//当前时间戳刷新 btn
	CEdit m_editUnixTimestampReady;	//时间戳 待转换 edit
	CButton m_btnConvert2Time;			//转换到时间	btn
	CEdit m_editTimeResult;					//转换到时间结果 edit
	CEdit m_editTimeReady;					//时间 待转换 edit
	CButton m_btnConvert2Timestamp;		//转换到时间戳 btn
	CEdit m_editUnixTimestampResult;    //转换到时间戳结果 edit

public:
	CString strNowTimestamp;				//当前时间戳
	CString strUnixTimestampReady;		//时间戳 待转换
	CString strTimeResult;						//转换到时间结果
	CString strTimeReady;						//时间 待转换 
	CString strUnixTimestampResult;		//转换到时间戳结果
	afx_msg void OnBnClickedButtonConvert2time();
	afx_msg void OnBnClickedButtonNowRenew();
	afx_msg void OnBnClickedButtonConvert2timestamp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
