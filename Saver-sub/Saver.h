#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

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