#include "stdafx.h"
#include "ScreenSaver.h"
#include "ScreenSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CScreenSaverApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CScreenSaverApp::CScreenSaverApp()
{	
}

CScreenSaverApp theApp;

BOOL CScreenSaverApp::InitInstance()
{	
	HANDLE hMutex = ::CreateMutex(NULL, FALSE, "ScreenSaverInstance");
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
		return FALSE;

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	CScreenSaverDlg dlg;
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

BOOL CScreenSaverApp::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{    
		CScreenSaverDlg* pDlg = (CScreenSaverDlg*)AfxGetMainWnd();
		pDlg->CheckMouseKeyboard(TRUE);	
	}	
	
	return CWinAppEx::PreTranslateMessage(pMsg);
}
