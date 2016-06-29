#include "StdAfx.h"
#include "DlgMain.h"

#include "WebCustomizer.h"

MainDialog::MainDialog(void)
	:	m_pWeb(NULL)
{
	WebCustomizer::patch_atl_creator_CAxHostWindow(&WebCustomizer::_CreatorClass::CreateInstance);
}


MainDialog::~MainDialog(void)
{
	WebCustomizer::unpatch_atl_creator_CAxHostWindow();
}

void	MainDialog::do_CloseWindow(){
	::EndDialog(m_hWnd, 0);
}

LRESULT MainDialog::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	this->do_CloseWindow();
	return 0;
}


LRESULT MainDialog::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
	return	1;
}


LRESULT MainDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	g_wnd_main	= m_hWnd;
	if(!superClass::OnInitDialog(uMsg, wParam, lParam, bHandled)){
		return	FALSE;
	}
	

	RECT rc;
	GetClientRect(&rc);

	//	IE Control
	{
		m_ctrlWeb	= GetDlgItem(IDC_WEB);
		m_ctrlWeb.QueryControl(__uuidof(IWebBrowser2), (void**)&m_pWeb);
		m_ctrlWeb.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);

		{
			CComVariant	sURL("about:blank");
			m_pWeb->Navigate2(&sURL,0,0,0,0);
		}
	}

	ShowWindow(SW_NORMAL);

	return TRUE;
}


LRESULT MainDialog::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	//	IE Control
	{
		if(NULL != m_pWeb){
			m_pWeb->Stop();
			m_pWeb->Release(); 
		}
	}

	bHandled	= FALSE;
	return 0;
}


LRESULT MainDialog::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rc;
	GetClientRect(&rc);

	if(m_ctrlWeb.m_hWnd){
		m_ctrlWeb.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);
	}

	return 0;
}


LRESULT MainDialog::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	this->do_CloseWindow();
	return 0;
}


void __stdcall MainDialog::WindowSetLeftWeb(long Left)
{
	RECT	rc_wnd;
	GetWindowRect(&rc_wnd);
	OffsetRect(&rc_wnd, Left - rc_wnd.left, 0);

	this->MoveWindow(&rc_wnd, FALSE);
}


void __stdcall MainDialog::WindowSetTopWeb(long Top)
{
	RECT	rc_wnd;
	GetWindowRect(&rc_wnd);
	OffsetRect(&rc_wnd, 0, Top - rc_wnd.top);

	this->MoveWindow(&rc_wnd, FALSE);
}


void __stdcall MainDialog::WindowSetWidthWeb(long Width)
{
	RECT	rc_wnd, rc_client;
	GetWindowRect(&rc_wnd);
	GetClientRect(&rc_client);
	const int	nc	= (rc_wnd.right - rc_wnd.left) - (rc_client.right - rc_client.left);

	rc_wnd.right	= rc_wnd.left + Width + nc;

	this->MoveWindow(&rc_wnd, FALSE);
}


void __stdcall MainDialog::WindowSetHeightWeb(long Height)
{
	RECT	rc_wnd, rc_client;
	GetWindowRect(&rc_wnd);
	GetClientRect(&rc_client);
	const int	nc	= (rc_wnd.bottom - rc_wnd.top) - (rc_client.bottom - rc_client.top);

	rc_wnd.bottom	= rc_wnd.top + Height + nc;

	this->MoveWindow(&rc_wnd, FALSE);
}


void __stdcall MainDialog::WindowSetResizableWeb(BOOL Resizable)
{
	if(Resizable){
		this->ModifyStyle(DS_MODALFRAME, WS_THICKFRAME, 0);
	}else{
		this->ModifyStyle(WS_THICKFRAME, DS_MODALFRAME, 0);
	}
}
