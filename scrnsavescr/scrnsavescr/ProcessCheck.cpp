#include "StdAfx.h"
#include "ProcessCheck.h"

static HANDLE m_Thread_event = NULL;
static bool m_bPrcessThread = false;		
static HANDLE m_Thread_result = NULL;

typedef struct _FIND_HWND_PARAM
{
	DWORD dwProcessID;
	HWND hwnd;

} FIND_HWND_PARAM, *LP_FIND_HWND_PARAM;


BOOL CALLBACK FindWindowFromPidProc(HWND hwnd, LPARAM lParam)
{
	DWORD dwProcessID = 0;
	LP_FIND_HWND_PARAM findParam = (LP_FIND_HWND_PARAM)lParam;
	GetWindowThreadProcessId(hwnd, &dwProcessID);

	if(findParam->dwProcessID == dwProcessID)
	{
		findParam->hwnd = ::GetWindow(hwnd, GW_OWNER);
		if(findParam->hwnd == NULL)
			findParam->hwnd = hwnd;
	}

	return TRUE;
}

HWND FindWindowFromProcessId(DWORD dwProcessID)
{
	HWND hwnd = NULL;
	FIND_HWND_PARAM param;
	param.dwProcessID = dwProcessID;
	param.hwnd = NULL;

	::EnumWindows(FindWindowFromPidProc, (LPARAM)&param);

	return param.hwnd;
}

ProcessCheck::ProcessCheck(void)
{

}

ProcessCheck::~ProcessCheck(void)
{
	Thread_Stop();
}

void ProcessCheck::SetParent(CscrnsavescrDlg *pParent)
{
	m_pParent = pParent;
}

bool ProcessCheck::RunProcessCheck()
{
	if(m_bPrcessThread)	
		Thread_Stop();		

	if(!Thread_Start())
		return false;

	return true;
}

void ProcessCheck::StopProcessCheck()
{
	Thread_Stop();
}

bool ProcessCheck::Thread_Start()
{
	if(m_bPrcessThread)
		return false;
	
	m_Thread_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(m_Thread_event == NULL)
	{
		return false;
	}
	
	m_bPrcessThread = true;
	m_Thread_result  = (HANDLE)_beginthreadex(NULL,0,&ProcessCheck::ProcessThread, this, 0,&uthread);
	if(m_Thread_result == 0)
	{
		Thread_Stop();
		return false;
	}

	return true;
}

bool ProcessCheck::Thread_Stop()
{
	if(m_bPrcessThread == false)
		return false;

	m_bPrcessThread = false;
	SetEvent(m_Thread_event);

	if(m_Thread_result)
	{
		WaitForSingleObject(m_Thread_result, 5000);

		CloseHandle(m_Thread_result);
		m_Thread_result = NULL;
	}

	ResetEvent(m_Thread_event);

	if(m_Thread_event)
	{
		CloseHandle(m_Thread_event);
		m_Thread_event = NULL;
	}

	return true;
}

UINT ProcessCheck::ProcessThread(PVOID pParam)
{
	ProcessCheck *pProcess = (ProcessCheck *)pParam;
	DWORD ret;
	CString EventErr;

	while (m_bPrcessThread != false )
	{
		ret = WaitForSingleObject(m_Thread_event, 1000);
		if(ret == WAIT_FAILED)
		{			
			return 0;
		}
		else if(ret == WAIT_ABANDONED)
		{			
			continue;
		}

		pProcess->RunProcessing();

		if(!m_bPrcessThread)
			break;
	}
	_endthreadex(1);
	return 1;
}

void ProcessCheck::RunProcessing()
{
	if(!m_bPrcessThread)
		return;

	HANDLE hProcessSnap = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(hProcessSnap != INVALID_HANDLE_VALUE)
	{
		int nlen = 0, i = 0, ncheck=0;
		if(!Process32First(hProcessSnap, &pe32))
		{
			::CloseHandle(hProcessSnap);
			return;
		}

		do 
		{
			HWND hwnd = FindWindowFromProcessId(pe32.th32ProcessID);
			if(hwnd)
			{
				char className[MAX_PATH + 1] = {0, };
				char wndName[MAX_PATH + 1] = {0, };
				GetClassName(hwnd, className, MAX_PATH + 1);
				//GetWindowText(hwnd, wndName, MAX_PATH + 1);

				DWORD dwResult;
				::SendMessageTimeout(hwnd, WM_GETTEXT, (WPARAM)sizeof(wndName), (LPARAM)wndName, SMTO_NORMAL, 3000, &dwResult);
					
				CString strLog;
				strLog.Format(_T("%ld : %s  : %s  : %s  \r\n"), pe32.th32ProcessID, pe32.szExeFile, className, wndName);
				::OutputDebugString(strLog);
			}
			
		} while (Process32Next(hProcessSnap,&pe32));

		CloseHandle(hProcessSnap);
	}
}
