#include "StdAfx.h"
#include "CEditListView.h"


CEditListView::CEditListView(void)
{
	m_edit = NULL;//�༭���ָ�룬��ʼΪNULL����ʾ�ޱ༭��

	m_isedit = NULL;//��־��Щ�пɱ༭�ı�־ά���飬��ʼΪNULL

	m_item = -1;//��ǰ�༭���кţ���ֵΪ-1

	m_subitem = -1;//��ǰ�༭���кţ���ֵΪ-1
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;  
	CRect rc;  
	int m_Row = pNMListView->iItem;//���ѡ�е���  
	int m_Col = pNMListView->iSubItem;//���ѡ����  
	GetClientRect(&rc);

	if   (pNMListView->iSubItem != 0) //���ѡ���������;  
	{  
		RECT m_itemrect,m_r;
		GetItemRect(m_item ,&m_itemrect,2);
		GetItemRect(0 ,&m_r,2);
		//CRect rect(x,y,cx,cy);
		m_edit=new CEdit();
		m_edit->Create (WS_CHILD|WS_VISIBLE|WS_BORDER,m_r,this,1);
		CString str=GetItemText (pNMListView->iItem,pNMListView->iSubItem);   //��ȡlist��ǰ�� ������
		m_edit->UpdateData(0);
		m_edit->SetWindowText(str); 
		DWORD dwSel = m_edit->GetSel();   
		m_edit->SetSel(HIWORD(dwSel), -1);   
		m_edit->ShowWindow (SW_SHOW);//��ʾ�༭��
		m_edit->SetFocus ();


	} 
	*pResult = 0;
}
