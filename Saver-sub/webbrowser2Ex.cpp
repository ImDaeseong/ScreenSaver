#include "stdafx.h"
#include "Resource.h"
#include "webbrowser2Ex.h"

CWebBrowser2Ex::CWebBrowser2Ex()
{
}

CWebBrowser2Ex::~CWebBrowser2Ex()
{
}

BEGIN_MESSAGE_MAP(CWebBrowser2Ex, CWebBrowser2)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BOOL CWebBrowser2Ex::PreTranslateMessage(MSG* pMsg) 
{
	 switch(pMsg->message) 
	 {
        case WM_LBUTTONUP:
			OnLButtonUp(NULL, NULL);
            break;
        default :
            break;
    }
	return CWnd::PreTranslateMessage(pMsg);
}

void CWebBrowser2Ex::OnLButtonUp(UINT nFlags, CPoint point)
{
	//
	CWnd::OnLButtonUp(nFlags, point);
}

void CWebBrowser2Ex::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CWnd::OnLButtonDown(nFlags, point);
}
	
