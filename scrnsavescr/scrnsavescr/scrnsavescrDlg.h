#pragma once

class CscrnsavescrDlg : public CDialog
{
public:
	CscrnsavescrDlg(CWnd* pParent = NULL);	

	enum { IDD = IDD_SCRNSAVESCR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	


// Implementation
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	ProcessCheck processcheck;
	Screenscr scr;	

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

private:
	void Init();
	void MoveCursor();
};
