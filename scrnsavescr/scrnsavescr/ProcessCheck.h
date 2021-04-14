#pragma once

class CscrnsavescrDlg;
class ProcessCheck
{
protected:
	CscrnsavescrDlg * m_pParent;

public:
	ProcessCheck(void);
	~ProcessCheck(void);

	void SetParent(CscrnsavescrDlg *pParent);
	bool RunProcessCheck();
	void StopProcessCheck();	

private:

	static UINT _stdcall ProcessThread(PVOID pParam);
	bool Thread_Start();
	bool Thread_Stop();	
	UINT uthread;	

	void RunProcessing();
};
