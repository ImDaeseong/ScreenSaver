#include "stdafx.h"
#include "Saver.h"
#include "SaverDlg.h"
#include<afxocc.h>
#include "custsite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CSaverApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CSaverApp::CSaverApp()
{	
}

CSaverApp theApp;

BOOL CSaverApp::InitInstance()
{
	m_hMutex = ::CreateMutex(NULL, FALSE, "SaverInstance");
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
		return FALSE;

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	RegisterWin();	

	CCustomOccManager *pMgr = new CCustomOccManager;
	m_pDispOM = new CImpIDispatch;
	AfxEnableControlContainer(pMgr);

	CSaverDlg dlg;
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

int CSaverApp::ExitInstance() 
{	
	return CWinApp::ExitInstance();
}

void CSaverApp::RegisterWin()
{
	WNDCLASS wndclass;
	::GetClassInfo(AfxGetInstanceHandle(), "#32770", &wndclass);
	CString strClassName = "Saver";
	wndclass.lpszClassName = strClassName;
	BOOL bSuccess;
	bSuccess = AfxRegisterClass(&wndclass);
}

BOOL CSaverApp::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{    
		if (pMsg->wParam == VK_F1)
		{
			return TRUE;
		}
	}	
	else if (pMsg->message == WM_SYSKEYDOWN)
	{
		if (pMsg->wParam == VK_F4)
		{
			return TRUE;
		}
	}
	return CWinApp::PreTranslateMessage(pMsg);
}