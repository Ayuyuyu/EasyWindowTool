// DlgColourList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColourPin.h"
#include "DlgColourList.h"
#include "afxdialogex.h"
#include "ColourBase.h"

// CDlgColourList �Ի���

IMPLEMENT_DYNAMIC(CDlgColourList, CDialogEx)

CDlgColourList::CDlgColourList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgColourList::IDD, pParent)
{

}

CDlgColourList::~CDlgColourList()
{
}

void CDlgColourList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST0, mBtnColList0);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST1, mBtnColList1);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST2, mBtnColList2);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST3, mBtnColList3);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST4, mBtnColList4);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST5, mBtnColList5);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST6, mBtnColList6);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST7, mBtnColList7);
	DDX_Control(pDX, IDC_MFCBUTTON_LIST8, mBtnColList8);
}


BEGIN_MESSAGE_MAP(CDlgColourList, CDialogEx)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgColourList ��Ϣ�������
void CDlgColourList::SetListBtnColour(DWORD rgb[3])
{
	CColourBase m_ColourBase;
	MovePOS();

	m_ColourBase.RGBTurnToList(rgb);
	memset(ColourListSave,0,sizeof(ColourListSave));
	memcpy(ColourListSave,m_ColourBase.RGBList,sizeof(ColourListSave));
	SetListColour(ColourListSave);
}


void CDlgColourList::MovePOS()
{
	CRect rt_p,rt_c,rt_new;
	this->GetParent()->GetWindowRect(rt_p);
	GetWindowRect(rt_c);
	//rt_p.left + (rt_p.right - rt_p.left)/2
	int DlgListHeight = rt_c.Height();
	int DlgListWidth = rt_c.Width();
	rt_new.top = rt_p.bottom;
	rt_new.bottom = rt_new.top + DlgListHeight;
	rt_new.left = rt_p.left + (rt_p.right - rt_p.left)/2 - DlgListWidth/2;
	rt_new.right = rt_new.left + DlgListWidth;
	MoveWindow(rt_new,TRUE);
}

void CDlgColourList::SetListColour(DWORD ColourList[9][3])
{
	mBtnColList0.SetFaceColor(RGB(ColourList[0][0],ColourList[0][1],ColourList[0][2]));
	mBtnColList1.SetFaceColor(RGB(ColourList[1][0],ColourList[1][1],ColourList[1][2]));
	mBtnColList2.SetFaceColor(RGB(ColourList[2][0],ColourList[2][1],ColourList[2][2]));
	mBtnColList3.SetFaceColor(RGB(ColourList[3][0],ColourList[3][1],ColourList[3][2]));
	mBtnColList4.SetFaceColor(RGB(ColourList[4][0],ColourList[4][1],ColourList[4][2]));
	mBtnColList5.SetFaceColor(RGB(ColourList[5][0],ColourList[5][1],ColourList[5][2]));
	mBtnColList6.SetFaceColor(RGB(ColourList[6][0],ColourList[6][1],ColourList[6][2]));
	mBtnColList7.SetFaceColor(RGB(ColourList[7][0],ColourList[7][1],ColourList[7][2]));
	mBtnColList8.SetFaceColor(RGB(ColourList[8][0],ColourList[8][1],ColourList[8][2]));
}

int CDlgColourList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//mBtnColList0.EnableWindow(FALSE);
	return 0;
}

void CDlgColourList::CopyClip(CString strBuf)
{
	if (this->OpenClipboard())   //����ܴ򿪼�����  
	{  
		::EmptyClipboard();  //��ռ����壬ʹ�ô��ڳ�Ϊ�������ӵ����  
		HGLOBAL hClip;  
		hClip = ::GlobalAlloc(GMEM_MOVEABLE, (strBuf.GetLength() * 2) + 2); //�ж�Ҫ���ı����ݣ������ڴ�ʱ�����һ���ַ�  
		TCHAR *pBuf;  
		pBuf = (TCHAR *)::GlobalLock(hClip);//����������  
		_tcscpy(pBuf,strBuf);
		::GlobalUnlock(hClip);//�������������  
		::SetClipboardData(CF_UNICODETEXT, hClip);//���ı����ݷ��͵�������  CF_UNICODETEXTΪUnicode����  
		::CloseClipboard();//�رռ�����  
	} 
}


void CDlgColourList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���44
	CString strBuf;
	int x = point.x;
	int nBtnPos = x/66;
	strBuf.Format(_T("%d,%d,%d"),ColourListSave[nBtnPos][0],ColourListSave[nBtnPos][1],ColourListSave[nBtnPos][2]);
	CopyClip(strBuf);

	CDialogEx::OnLButtonDown(nFlags, point);
}
