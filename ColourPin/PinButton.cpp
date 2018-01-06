// PinButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColourPin.h"
#include "PinButton.h"
#include "define.h"

// CPinButton

IMPLEMENT_DYNAMIC(CPinButton, CButton)

CPinButton::CPinButton()
{
}

CPinButton::~CPinButton()
{
}


BEGIN_MESSAGE_MAP(CPinButton, CButton)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CPinButton ��Ϣ�������




void CPinButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//AfxMessageBox(L"R");
	CButton::OnRButtonDown(nFlags, point);
}


void CPinButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnRButtonUp(nFlags, point);
}


void CPinButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//AfxMessageBox(L"L");
	SetCapture();
	//SetClassLong(this->GetParent()->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(NULL , IDC_CROSS));
	::SetCursor( ::LoadCursor( NULL, IDC_CROSS )  );
	SetTimer(TIMER_POINT_COLOUR,200,0);
	//CURSORINFO isf;
	//isf.cbSize=sizeof CURSORINFO;
	//GetCursorInfo(&isf);
	//SetCursor(this->LoadStandardCursor(IDC_CROSS));
	//CButton::OnLButtonDown(nFlags, point);
}


void CPinButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(TIMER_POINT_COLOUR);
	//AfxMessageBox(L"LU");
	ReleaseCapture();
	//SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR , (LONG)LoadCursor(NULL , IDC_ARROW));
	CButton::OnLButtonUp(nFlags, point);
}



void CPinButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)      
	{      
	case TIMER_POINT_COLOUR:         
		{
			
			CPoint pt;
			GetCursorPos(&pt);
			
			 HDC hDC = ::GetDC(NULL);
			COLORREF clr = ::GetPixel(hDC, pt.x, pt.y); 
			CString strpo;
			strpo.Format(L"%d,%d -- %d\n",pt.x,pt.y,clr);
			OutputDebugString(strpo);
			HWND Hmodle = this->GetParent()->GetSafeHwnd();
			::SendMessage(Hmodle,WM_USER_POINT_COLOUR,(WPARAM)clr,NULL);
		}
		break;      
	default:      
		break;      
	}      
	CButton::OnTimer(nIDEvent);
}


