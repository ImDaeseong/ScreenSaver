#include "stdafx.h"
#include "scrnsavescr.h"
#include "scrnsavescrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CscrnsavescrDlg::CscrnsavescrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CscrnsavescrDlg::IDD, pParent)
{
}

void CscrnsavescrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CscrnsavescrDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CscrnsavescrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CscrnsavescrDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CscrnsavescrDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CscrnsavescrDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

BOOL CscrnsavescrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Init();

	return TRUE; 
}

void CscrnsavescrDlg::OnDestroy() 
{
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	processcheck.StopProcessCheck();

	CDialog::OnDestroy();
}
void CscrnsavescrDlg::OnPaint()
{
	CPaintDC dc(this);
}

void CscrnsavescrDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{		
		KillTimer(1);

		//�������� ���μ��� üũ
		processcheck.RunProcessCheck();
	}
	else if(nIDEvent == 2)
	{	
		KillTimer(2);

		//��ũ�� ���̹� �۵� ���ɿ��� Ȯ�� �� ����
		if(scr.isScrnsave())
		{
			scr.StartScrn();

			SetTimer(3, 10000, NULL);
		}
	}
	else if(nIDEvent == 3)
	{
		KillTimer(3);
		
		//��ũ�� ���̹� ���Ḧ ���� ���콺 ������
		//MoveCursor;	
		
		//��ũ�� ���̹� ���̱�
		scr.StopScrn();
	}

	CDialog::OnTimer(nIDEvent);
}

void CscrnsavescrDlg::OnBnClickedButton1()
{
	//���μ��� üũ ����
	processcheck.StopProcessCheck();	
}

void CscrnsavescrDlg::OnBnClickedButton2()
{
	//���μ��� üũ ����
	processcheck.RunProcessCheck();
}

//��ũ�� ���̹� ��� ���� 
void CscrnsavescrDlg::OnBnClickedButton3()
{
	// ��ũ�� ���̹� ����
	VERIFY(SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, 0, 0));

	//��ũ�� ���̹� ���
	scr.setScrnsave(1, 0, 5);	

	SetTimer(2, 1000, NULL);	
}

//��ũ�� ���̹� ��� ����
void CscrnsavescrDlg::OnBnClickedButton4()
{
	// ��ũ�� ���̹� ���� ����
	VERIFY(SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, FALSE, 0, 0));

	//��ũ�� ���̹� �̻��
	scr.setScrnsave(0, 0, 1);

	SetTimer(2, 1000, NULL);
}

void CscrnsavescrDlg::Init()
{
	//����
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);
	//ShowWindow(SW_HIDE);
	//MoveWindow(-3333, -3333, 1, 1);

	//���μ��� üũ ������ �ʱ�ȭ
	processcheck.SetParent(this); 
	
	SetTimer(1, 100, NULL);
}

void CscrnsavescrDlg::MoveCursor()
{
	//��ũ�� ���̹� ���Ḧ ���� ���콺 ������
	CPoint pt;
	GetCursorPos(&pt);
	int nX = pt.x;
	int nY = pt.y;
				
	CRect rc;
	::GetWindowRect(GetDesktopWindow()->m_hWnd, &rc);
				
	int x = rc.right  - rc.left;
	int y = rc.bottom - rc.top;
	GetDesktopWindow()->PostMessage(WM_MOUSEMOVE, 0L, MAKELPARAM(x, y));	
}