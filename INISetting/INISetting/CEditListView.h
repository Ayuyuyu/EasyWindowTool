#pragma once
#include "afxcmn.h"
#include "resource.h"
class CEditListView :
	public CListCtrl
{
public:
	CEditListView(void);
	~CEditListView(void);
public:
	CEdit * m_edit;		//ָ��༭�򣬳�ֵΪNULL
	BOOL * m_isedit;	//������б༭���У���ֵΪNULL
	int m_item;			//��ǰ�༭���кţ���ֵΪ-1
	int m_subitem;		//��ǰ�༭���кţ���ֵΪ-1
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};

