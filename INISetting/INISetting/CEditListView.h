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
	CEdit * m_edit;		//指向编辑框，初值为NULL
	BOOL * m_isedit;	//允许进行编辑的列，初值为NULL
	int m_item;			//当前编辑的行号，初值为-1
	int m_subitem;		//当前编辑的列号，初值为-1
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};

