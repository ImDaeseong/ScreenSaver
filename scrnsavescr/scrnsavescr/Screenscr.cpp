#include "StdAfx.h"
#include "Screenscr.h"


BOOL CALLBACK StopScrenProc(HWND hwnd, LPARAM lParam)
{
  if(IsWindowVisible(hwnd))
      PostMessage(hwnd, WM_CLOSE, 0, 0);

  return TRUE;
}

Screenscr::Screenscr(void)
{
}

Screenscr::~Screenscr(void)
{
}

BOOL Screenscr::StartScrn()
{
	/*
	CString strAppExe;
	strAppExe.Format("%s\\scrnsave.scr", GetSystemFolder());
	if(!::PathFileExists(strAppExe)) 
		return FALSE;

	HINSTANCE hInstance = ::ShellExecute(NULL, "open", strAppExe, NULL, NULL, SW_SHOW);
	*/

	HDESK hdesk = NULL;
	hdesk = OpenDesktop(_T("Screen-saver"), 0, FALSE, DESKTOP_READOBJECTS | DESKTOP_WRITEOBJECTS);
	if (hdesk == NULL)
	{
		PostMessage(GetDesktopWindow(), WM_SYSCOMMAND, SC_SCREENSAVE, 0L);
	}

	return TRUE;
}

BOOL Screenscr::StopScrn()
{
   HDESK hdesk = NULL;
   hdesk = OpenDesktop(_T("Screen-saver"), 0, FALSE, DESKTOP_READOBJECTS | DESKTOP_WRITEOBJECTS);
   if (hdesk)
   {
      EnumDesktopWindows(hdesk, StopScrenProc, 0);
      CloseDesktop(hdesk);
   }

   return TRUE;
}

void Screenscr::setScrnsave(int nActive, int nSaverIsSecure, int nScreenSaveTimeOut)
{
	CString sActive, sSaverIsSecure, ScreenSaveTimeOut;

	sActive.Format("%d", nActive);//1:사용 0:미사용
	sSaverIsSecure.Format("%d", nSaverIsSecure);//1:사용 0:미사용(1이면 암호 입력창 호출됨)
	ScreenSaveTimeOut.Format("%d", (nScreenSaveTimeOut * 60));// 분을 초로 등록해야 함
	
	SetScreenSaveActive(sActive);
	SetScreenSaverIsSecure(sSaverIsSecure);
	SetScreenSaveTimeOut(ScreenSaveTimeOut);
}

BOOL Screenscr::isScrnsave()
{
	BOOL bScrn = false;
	int nActive = GetScreenSaveActive();
	int nSecure = GetScreenSaverIsSecure();

	if(nActive == 1)//&& nSecure == 1)
	{
		bScrn = true;
	}

	return bScrn;
}

int Screenscr::GetScreenSaveActive()
{
	char szBuffer [MAX_PATH + 1] = {0, };
	DWORD dwCount = 0;

	CRegKey regKey;

	if (regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop"), KEY_READ) != ERROR_SUCCESS)
	{
		regKey.Close();
		return 0;
	}

	dwCount = REG_BUFF_SIZE + 1;
	
	if (ERROR_SUCCESS != regKey.QueryStringValue("ScreenSaveActive", szBuffer, &dwCount))
	{
		regKey.Close();
		return 0;
	}

	regKey.Close();

	int nState = atoi(szBuffer);
	return nState;
}

int Screenscr::GetScreenSaverIsSecure()
{
	char szBuffer [MAX_PATH + 1] = {0, };
	DWORD dwCount = 0;

	CRegKey regKey;

	if (regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop"), KEY_READ) != ERROR_SUCCESS)
	{
		regKey.Close();
		return 0;
	}

	dwCount = REG_BUFF_SIZE + 1;
	
	if (ERROR_SUCCESS != regKey.QueryStringValue("ScreenSaverIsSecure", szBuffer, &dwCount))
	{
		regKey.Close();
		return 0;
	}

	regKey.Close();

	int nState = atoi(szBuffer);
	return nState;
}

int Screenscr::GetScreenSaveTimeOut()
{
	char szBuffer [MAX_PATH + 1] = {0, };
	DWORD dwCount = 0;

	CRegKey regKey;
	
	if (regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop"), KEY_READ) != ERROR_SUCCESS)
	{
		regKey.Close();
		return 0;
	}

	dwCount = REG_BUFF_SIZE + 1;
	
	if (ERROR_SUCCESS != regKey.QueryStringValue("ScreenSaveTimeOut", szBuffer, &dwCount))
	{
		regKey.Close();
		return 0;
	}

	regKey.Close();

	int nState = atoi(szBuffer);
	return nState;
}

CString Screenscr::GetScreenSaverPath()
{
	char szBuffer [MAX_PATH + 1] = {0, };
	DWORD dwCount = 0;

	CRegKey regKey;

	if (regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop"), KEY_READ) != ERROR_SUCCESS)
	{
		regKey.Close();
		return "";
	}

	dwCount = REG_BUFF_SIZE + 1;
	
	if (ERROR_SUCCESS != regKey.QueryStringValue("SCRNSAVE.EXE", szBuffer, &dwCount))
	{
		regKey.Close();
		return "";
	}

	regKey.Close();

	return (CString)szBuffer;
}

void Screenscr::SetScreenSaveActive(CString strValue)
{
	CRegKey regKey;
	
	if ( regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop")) == ERROR_SUCCESS )
	{
		if (ERROR_SUCCESS == regKey.SetStringValue("ScreenSaveActive", strValue, REG_SZ) )
		{
		}	
	}
	regKey.Close();
}
	
void Screenscr::SetScreenSaverIsSecure(CString strValue)
{
	CRegKey regKey;
	
	if ( regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop")) == ERROR_SUCCESS )
	{
		if (ERROR_SUCCESS == regKey.SetStringValue("ScreenSaverIsSecure", strValue, REG_SZ) )
		{
		}	
	}
	regKey.Close();
}

void Screenscr::SetScreenSaveTimeOut(CString strValue)
{
	CRegKey regKey;
	
	if ( regKey.Open(HKEY_CURRENT_USER, _T("Control Panel\\Desktop")) == ERROR_SUCCESS )
	{
		if (ERROR_SUCCESS == regKey.SetStringValue("ScreenSaveTimeOut", strValue, REG_SZ) )
		{
		}	
	}
	regKey.Close();
}

CString Screenscr::GetSystemFolder()
{
	char szPath[MAX_PATH];

	::SHGetSpecialFolderPath(NULL, szPath, CSIDL_SYSTEM, FALSE);

	return (CString)szPath;
}

CString Screenscr::GetFileName(CString strFilename)
{	
	int nFindExt = 0;
	int i = 0;
	for (i = 0; i < strFilename.GetLength(); )
	{
		nFindExt = strFilename.Find('\\', nFindExt);
		if (nFindExt == -1) break;
		nFindExt++;
		i = nFindExt;
	}

	if (i > 0)
		return strFilename.Mid(i, strFilename.GetLength());
	else
		return strFilename;
}