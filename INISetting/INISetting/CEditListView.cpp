#include "StdAfx.h"
#include "CEditListView.h"


CEditListView::CEditListView(void)
{
	m_edit = NULL;//编辑框的指针，初始为NULL，表示无编辑框

	m_isedit = NULL;//标志哪些列可编辑的标志维数组，初始为NULL

	m_item = -1;//当前编辑的行号，初值为-1

	m_subitem = -1;//当前编辑的列号，初值为-1
}


CEditListView::~CEditListView(void)
{
}
BEGIN_MESSAGE_MAP(CEditListView, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CEditListView::OnNMClick)
END_MESSAGE_MAP()


void CEditListView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;  
	CRect rc;  
	int m_Row = pNMListView->iItem;//获得选中的行  
	int m_Col = pNMListView->iSubItem;//获得选中列  
	GetClientRect(&rc);

	if   (pNMListView->iSubItem != 0) //如果选择的是子项;  
	{  
		RECT m_itemrect,m_r;
		GetItemRect(m_item ,&m_itemrect,2);
		GetItemRect(0 ,&m_r,2);
		//CRect rect(x,y,cx,cy);
		m_edit=new CEdit();
		m_edit->Create (WS_CHILD|WS_VISIBLE|WS_BORDER,m_r,this,1);
		CString str=GetItemText (pNMListView->iItem,pNMListView->iSubItem);   //获取list当前项 并设置
		m_edit->UpdateData(0);
		m_edit->SetWindowText(str); 
		DWORD dwSel = m_edit->GetSel();   
		m_edit->SetSel(HIWORD(dwSel), -1);   
		m_edit->ShowWindow (SW_SHOW);//显示编辑框。
		m_edit->SetFocus ();


	} 
	*pResult = 0;
}
