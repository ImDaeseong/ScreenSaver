//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#include <mshtml.h>

#pragma once

class CSaverDlg : public CDialog
{
public:
	CSaverDlg(CWnd* pParent = NULL);	

	enum { IDD = IDD_SAVER_DIALOG };
	CWebBrowser2	m_WebBrowser;

	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);

private:
	void InitMousePoint();
	void CheckMousePoint();
	void InitDialogLocation();
	void Navigate(CString strUrl);
	CString GetModulePath();
	void HideBrowserBorder();

	CPoint m_pOldPoint;	
};
