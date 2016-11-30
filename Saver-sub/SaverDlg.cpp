#include "stdafx.h"
#include "Saver.h"
#include "SaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSaverDlg::CSaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaverDlg::IDD, pParent)
{	
	InitMousePoint();
}

void CSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebBrowser);
}

BEGIN_MESSAGE_MAP(CSaverDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CSaverDlg::OnDestroy()
{
	CDialog::OnDestroy();

	KillTimer(1);
}

BOOL CSaverDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_SYSKEYDOWN || pMsg->message == WM_KEYDOWN)
	{
		PostMessage(WM_QUIT, 0, 0);
		PostQuitMessage(0);
	}   
	return CDialog::PreTranslateMessage(pMsg);
}

void CSaverDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	PostMessage(WM_QUIT, 0, 0);
	PostQuitMessage(0);
	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CSaverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDialogLocation();

	SetTimer(1, 500, NULL);

	return TRUE;  
}

void CSaverDlg::OnPaint()
{
	CPaintDC dc(this);
}

void CSaverDlg::InitMousePoint()
{
	POINT point;
	GetCursorPos(&point);
	m_pOldPoint.x = point.x;
	m_pOldPoint.y = point.y;
}

void CSaverDlg::CheckMousePoint()
{
	POINT point;
	GetCursorPos(&point);

	if (m_pOldPoint.x != 0 && m_pOldPoint.y != 0 &&  m_pOldPoint.x != point.x && m_pOldPoint.y != point.y)
	{		
		m_pOldPoint.x = point.x;
		m_pOldPoint.y = point.y;

		PostMessage(WM_QUIT, 0, 0);
		PostQuitMessage(0);
	}
	else
	{
		m_pOldPoint.x = point.x;
		m_pOldPoint.y = point.y;
	}
}

void CSaverDlg::InitDialogLocation()
{
	int nScreenSizeX = GetSystemMetrics(SM_CXSCREEN);
	int nScreenSizeY = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(&wndTopMost, 0, 0, nScreenSizeX, nScreenSizeY, SWP_NOZORDER);	
	SetWindowPos(&wndTopMost, 0, 0, nScreenSizeX, nScreenSizeY, SWP_NOMOVE | SWP_NOSIZE);
	
	CString strUR;
    strURL.Format("%s\\htm\\index.html", GetModulePath());

	Navigate(strURL);	

	m_WebBrowser.MoveWindow(0, 0, nScreenSizeX, nScreenSizeY);
}

void CSaverDlg::Navigate(CString strUrl)
{
	VARIANT vtHeader, vtTarget, vtEmpty; 
	CString strHeader, strTarget; 
	
    strHeader = "Content-Type: application/x-www-form-urlencoded\r\n"; 
	
    strTarget = "_parent"; 

	::VariantInit(&vtHeader); 
	::VariantInit(&vtTarget); 
	::VariantInit(&vtEmpty); 
	
	vtHeader.vt = VT_BSTR; 
	
	vtHeader.bstrVal = strHeader.AllocSysString(); 
	
	vtTarget.vt = VT_BSTR; 
	
	vtTarget.bstrVal = strTarget.AllocSysString(); 
	
    m_WebBrowser.Navigate(strUrl, &vtEmpty, &vtTarget, &vtEmpty, &vtHeader);

	SysFreeString(vtHeader.bstrVal);
	SysFreeString(vtTarget.bstrVal);
}

CString CSaverDlg::GetModulePath()
{
	char cTemp[MAX_PATH];
	char *spzRealDirEnd;
	CString strModulePath;

	GetModuleFileName(NULL, cTemp, MAX_PATH);  
	spzRealDirEnd = strrchr(cTemp, '\\');
	*spzRealDirEnd = '\0';
	strModulePath = (CString)cTemp;
	return strModulePath;
}

void CSaverDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		CheckMousePoint();
	}
		
	CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CSaverDlg, CDialog)
	ON_EVENT(CSaverDlg, IDC_EXPLORER1, 259, CSaverDlg::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

void CSaverDlg::HideBrowserBorder()
{		
    IHTMLDocument2* phtmldoc2 = NULL;   
	IHTMLElement* phtmlElement = NULL;   
	IDispatch* pdisp = NULL;   
	pdisp = m_WebBrowser.GetDocument();  

	if (pdisp != NULL)
	{
		pdisp->QueryInterface(IID_IHTMLDocument2, (void**) &phtmldoc2);   
		pdisp->Release();
	}   

	if (phtmldoc2 != NULL)
	{
		phtmldoc2->get_body(&phtmlElement);   
		phtmldoc2->Release();
	}   

	if (phtmlElement != NULL)
	{
		IHTMLStyle* phtmlStyle = NULL;   
		phtmlElement->get_style(&phtmlStyle);   

		if (phtmlStyle != NULL)
		{
			phtmlStyle->put_overflow(L"hidden");   
			phtmlStyle->put_border(L"none");  

			phtmlStyle->Release();   
			phtmlElement->Release();
		}
	}   	  
}

void CSaverDlg::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	//HideBrowserBorder();

	//IDispatch *pDisp2 = m_WebBrowser.GetDocument();
	//CString strOption = _T("no" );   // yes no auto
	//if (pDisp2 != NULL)
	//{
	//	IHTMLDocument2* pHTMLDocument2;
	//	HRESULT hr;
	//	hr = pDisp2->QueryInterface(IID_IHTMLDocument2, (void**)&pHTMLDocument2);

	//	if (hr == S_OK)
	//	{
	//		IHTMLElement *pIElement;
	//		hr = pHTMLDocument2->get_body(&pIElement);


	//		IHTMLBodyElement *pIBodyElement;
	//		hr = pIElement->QueryInterface(IID_IHTMLBodyElement, (void**)&pIBodyElement);


	//		BSTR bstr;
	//		bstr = strOption.AllocSysString();
	//		pIBodyElement->put_scroll(bstr);
 //		}
	//	pDisp2->Release ();
	//}  
}
