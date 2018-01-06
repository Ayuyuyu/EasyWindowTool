
// ColourPinDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "PinButton.h"
#include "afxbutton.h"
#include "DlgColourList.h"
#include "ColourBase.h"

// CColourPinDlg �Ի���
class CColourPinDlg : public CDialogEx
{
// ����
public:
	CColourPinDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COLOURPIN_DIALOG };

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
