#pragma once

class CScreenSaverDlg : public CDialog
{
public:
	CScreenSaverDlg(CWnd* pParent = NULL);	

	enum { IDD = IDD_SCREENSAVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	CString GetModulePath();
	void ExecuteScreenSaver();
	void CheckMouseKeyboard(BOOL bMove);
	void CheckMousePoint();
	void InitMousePoint();

	CPoint m_pOldPoint;
	int m_nScreenSaverCount;
};
