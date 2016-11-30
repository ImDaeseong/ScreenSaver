#pragma once

#include "webbrowser2.h"

class CWebBrowser2Ex : public CWebBrowser2
{
public:
	CWebBrowser2Ex();
	virtual ~CWebBrowser2Ex();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};
