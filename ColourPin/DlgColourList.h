#pragma once
#include "afxbutton.h"


// CDlgColourList 对话框

class CDlgColourList : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgColourList)

public:
	CDlgColourList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgColourList();

// 对话框数据
	enum { IDD = IDD_COLOURLIST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetListBtnColour(DWORD rgb[3]);
	void MovePOS();
	void SetListColour(DWORD ColourList[9][3]);
	void CopyClip(CString strBuf);
public:
	CMFCButton mBtnColList0;
	CMFCButton mBtnColList1;
	CMFCButton mBtnColList2;
	CMFCButton mBtnColList3;
	CMFCButton mBtnColList4;
	CMFCButton mBtnColList5;
	CMFCButton mBtnColList6;
	CMFCButton mBtnColList7;
	CMFCButton mBtnColList8;
	DWORD ColourListSave[9][3];

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
