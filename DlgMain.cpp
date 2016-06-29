#include "StdAfx.h"
#include "DlgMain.h"

#include "WebCustomizer.h"
#include "WebExternalObject.h"

#include "simple/string.h"

/////////////////////////////////////////////////////////
static	HWINEVENTHOOK	gs_hookevt_move;
static	void CALLBACK	gs_WinEventProc_Move(
	HWINEVENTHOOK hWinEventHook,
	DWORD         event,
	HWND          hwnd,
	LONG          idObject,
	LONG          idChild,
	DWORD         dwEventThread,
	DWORD         dwmsEventTime
	)
{
	if(NULL != g_wnd_main && hwnd != g_wnd_main){
		HWND	hwndP	= ::GetParent(hwnd);
		if(hwndP != g_wnd_main && ::GetParent(hwndP) == g_wnd_main){
			//	move the main wnd
			RECT	rc;
			::GetWindowRect(hwnd, &rc);
			POINT	pt	= {rc.left, rc.top};
			::ScreenToClient(hwndP, &pt);
			if(0 != pt.x || 0 != pt.y){
				::GetWindowRect(g_wnd_main, &rc);
				::OffsetRect(&rc, pt.x - rc.left, pt.y - rc.top);
				::MoveWindow(g_wnd_main,
					rc.left,
					rc.top,
					rc.right - rc.left,
					rc.bottom - rc.top,
					TRUE
					);
				::GetClientRect(g_wnd_main, &rc);
				::MoveWindow(hwnd, 
					rc.left,
					rc.top,
					rc.right - rc.left,
					rc.bottom - rc.top,
					TRUE
					);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////

MainDialog::MainDialog(void)
	:	m_pWeb(NULL)
	,	m_pExternalObject(new WebExternalObject())
	,	m_hIcon(NULL)
{
	gs_hookevt_move	= ::SetWinEventHook(
		EVENT_OBJECT_LOCATIONCHANGE,
		EVENT_OBJECT_LOCATIONCHANGE,
		0,
		gs_WinEventProc_Move,
		::GetCurrentProcessId(),
		::GetCurrentThreadId(),
		WINEVENT_OUTOFCONTEXT
		);
	WebCustomizer::patch_atl_creator_CAxHostWindow(&WebCustomizer::_CreatorClass::CreateInstance);

	m_hIcon	= (HICON)::LoadImageA(NULL, 
		g_config.get_value("config/icon", "").c_str(),
		IMAGE_ICON,
		0, 0,
		LR_SHARED|LR_DEFAULTSIZE|LR_LOADFROMFILE
		);
}


MainDialog::~MainDialog(void)
{
	delete	m_pExternalObject;
	m_pExternalObject	= NULL;

	WebCustomizer::unpatch_atl_creator_CAxHostWindow();
	if(NULL != gs_hookevt_move){
		::UnhookWinEvent(gs_hookevt_move);
		gs_hookevt_move	= NULL;
	}
}

void	MainDialog::do_CloseWindow()
{
	DestroyWindow();
}

bool MainDialog::PreProcessKeyboardMessage(MSG* msg) {
	switch(msg->wParam) {
	case VK_TAB:
	case VK_DELETE:
	case VK_RETURN:
		{
			// handled later
		}break;
	default:
		{
			return	false;
		}break;
	}

	CComPtr<IDispatch> disp_doc;
	if(FAILED(m_pWeb->get_Document(&disp_doc))) {
		return	false;
	}

	CComQIPtr<IOleInPlaceActiveObject> spInPlace;  
	if(FAILED(disp_doc->QueryInterface(__uuidof(IOleInPlaceActiveObject), (void**)&spInPlace))) {
		return	false;
	}

	return	(spInPlace->TranslateAccelerator(msg) == S_OK); 
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
	if(!superClass::OnInitDialog(uMsg, wParam, lParam, bHandled)){
		return	FALSE;
	}


	RECT rc;
	GetClientRect(&rc);

	if(NULL != m_hIcon) {
		this->SetIcon(m_hIcon, TRUE);
		this->SetIcon(m_hIcon, FALSE);
	}

	//	Resizable
	{
		bool resizable;
		string_tobool(g_config.get_value("config/resizable", "0"), resizable);
		if(resizable){
			this->ModifyStyle(DS_MODALFRAME, WS_THICKFRAME, 0);
		}else{
			this->ModifyStyle(WS_THICKFRAME, DS_MODALFRAME, 0);
		}
	}

	//	IE Control
	{
		m_ctrlWeb	= GetDlgItem(IDC_WEB);
		m_ctrlWeb.QueryControl(__uuidof(IWebBrowser2), (void**)&m_pWeb);
		m_ctrlWeb.MoveWindow(rc.left, rc.top, rc.right, rc.bottom, FALSE);

		{
			m_ctrlWeb.SetExternalDispatch(m_pExternalObject);
			m_pWeb->put_Resizable(ATL_VARIANT_FALSE);
		}

		{
			std::string	url	= g_config.get_value("config/homepage", "");
			if(url.find(":") == std::string::npos) {
				url	= g_workdir + "\\" + url;
			}
			CComVariant	sURL(url.c_str());
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
		m_ctrlWeb.SetExternalDispatch(NULL);
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
