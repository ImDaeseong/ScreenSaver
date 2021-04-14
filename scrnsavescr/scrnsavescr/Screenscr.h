#pragma once

#define	REG_BUFF_SIZE	1024

class Screenscr
{
public:
	Screenscr(void);
	~Screenscr(void);

	BOOL StartScrn();
	BOOL StopScrn();
	void setScrnsave(int nActive, int nSaverIsSecure, int nScreenSaveTimeOut);
	BOOL isScrnsave();

private:

	int GetScreenSaveActive();
	int GetScreenSaverIsSecure();
	int GetScreenSaveTimeOut();
	CString GetScreenSaverPath();

	void SetScreenSaveActive(CString strValue);
	void SetScreenSaverIsSecure(CString strValue);
	void SetScreenSaveTimeOut(CString strValue);

	CString GetFileName(CString strFilename);
	CString GetSystemFolder();
};
