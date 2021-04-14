#include "stdafx.h"
#include "scrnsavescr.h"
#include "scrnsavescrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CscrnsavescrApp, CWinAppEx)
END_MESSAGE_MAP()

CscrnsavescrApp::CscrnsavescrApp()
{
}

CscrnsavescrApp theApp;

BOOL CscrnsavescrApp::InitInstance()
{	
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	CscrnsavescrDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}
