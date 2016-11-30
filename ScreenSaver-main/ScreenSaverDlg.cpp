#include "stdafx.h"
#include "ScreenSaver.h"
#include "ScreenSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CScreenSaverDlg::CScreenSaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenSaverDlg::IDD, pParent)
{
	m_nScreenSaverCount = 0;	
}

void CScreenSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenSaverDlg, CDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CScreenSaverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitMousePoint();

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);
	MoveWindow(-3333, -3333, 1, 1);

	SetTimer(1, 1000, NULL);
	
	return TRUE;  
}

void CScreenSaverDlg::OnPaint()
{
	CPaintDC dc(this);
}

CString CScreenSaverDlg::GetModulePath()
{
	char cTemp[MAX_PATH];
	char *spzRealDirEnd;
	CString strModulePath;

	GetModuleFileName(NULL, cTemp, MAX_PATH);  
	spzRealDirEnd = strrchr(cTemp, '\\');
	*spzRealDirEnd = '\0';
	strModulePath = (CString)cTemp;
	return strModulePath;
}

void CScreenSaverDlg::ExecuteScreenSaver()
{
	HWND hWnd = ::FindWindow("Saver", NULL);
	if (!hWnd)
	{
		CString strFilePath;
		strFilePath.Format("%s\\Saver.exe", GetModulePath());
		ShellExecute(NULL, "open", strFilePath, "", NULL, SW_SHOW);
	}
}

void CScreenSaverDlg::CheckMouseKeyboard(BOOL bMove)
{
	if (!bMove)
	{
		if (m_nScreenSaverCount++ >= 60)
		{
			ExecuteScreenSaver();
			m_nScreenSaverCount = 0;
		}
	}
	else
	{
		m_nScreenSaverCount = 0;
	}
}

void CScreenSaverDlg::CheckMousePoint()
{
	POINT point;
	GetCursorPos(&point);

	if (m_pOldPoint.x != 0 && m_pOldPoint.y != 0 &&  m_pOldPoint.x != point.x && m_pOldPoint.y != point.y)
	{
		CheckMouseKeyboard(TRUE);
		m_pOldPoint.x = point.x;
		m_pOldPoint.y = point.y;
	}
	else
	{
		CheckMouseKeyboard(FALSE);
		m_pOldPoint.x = point.x;
		m_pOldPoint.y = point.y;
	}
}

void CScreenSaverDlg::InitMousePoint()
{
	POINT point;
	GetCursorPos(&point);
	m_pOldPoint.x = point.x;
	m_pOldPoint.y = point.y;
}

void CScreenSaverDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		CheckMousePoint();	
	}

	CDialog::OnTimer(nIDEvent);
}

void CScreenSaverDlg::OnDestroy()
{
	CDialog::OnDestroy();

	KillTimer(1);
}
