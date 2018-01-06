
// ColourPinDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "PinButton.h"
#include "afxbutton.h"
#include "DlgColourList.h"
#include "ColourBase.h"

// CColourPinDlg 对话框
class CColourPinDlg : public CDialogEx
{
// 构造
public:
	CColourPinDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COLOURPIN_DIALOG };

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
	afx_msg void OnBnClickedButtonColourChose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
protected:
	afx_msg LRESULT OnUserPointColour(WPARAM wParam, LPARAM lParam);
public:
	void SetBtnShowColour(COLORREF col);
	void MoveColorDialog(CRect rt_colourDlg);
public:
	CMFCButton mColourShow;
	CPinButton mColourPin;
	CButton mColourChose;
	CEdit mEditRGB;
	CEdit mEditHEX;
	CBitmap bmp;
	BOOL bListDlgShow;
	CDlgColourList *m_pDlgList;
	CColourBase m_ColourBase;
	afx_msg void OnDestroy();
	afx_msg void OnMove(int x, int y);
};
