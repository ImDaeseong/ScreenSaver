#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		

class CScreenSaverApp : public CWinAppEx
{
public:
	CScreenSaverApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CScreenSaverApp theApp;