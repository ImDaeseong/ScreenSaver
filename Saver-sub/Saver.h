#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

class CSaverApp : public CWinAppEx
{
public:
	CSaverApp();

	HANDLE m_hMutex;
	class CImpIDispatch* m_pDispOM;

	void RegisterWin();

public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};

extern CSaverApp theApp;