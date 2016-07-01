#include "StdAfx.h"
#include "DlgMain.h"

#include "WebCustomizer.h"
#include "WebExternalObject.h"

#include "simple/string.h"

MainDialog::MainDialog(void)
	:	m_pWeb(NULL)
	,	m_pExternalObject(new WebExternalObject(this))
	,	m_hIcon(NULL)
{
#ifdef	NDEBUG
	//	will error if DEP enabled.
	WebCustomizer::patch_atl_creator_CAxHostWindow(&WebCustomizer::_CreatorClass::CreateInstance);
#endif

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

	this->ShowWindow(SW_HIDE);

	RECT rc_client;
	GetClientRect(&rc_client);

	if(NULL != m_hIcon) {
		this->SetIcon(m_hIcon, TRUE);
		this->SetIcon(m_hIcon, FALSE);
	}

	//	Title
	{
		SetWindowTextA(m_hWnd, g_config.get_value("config/title", "0").c_str());
	}

	//	Resizable
	bool resizable;
	{
		string_tobool(g_config.get_value("config/resizable", "0"), resizable);
		if(resizable){
			this->ModifyStyle(DS_MODALFRAME, WS_THICKFRAME, 0);
		}else{
			this->ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, DS_MODALFRAME, 0);
		}
	}

	//	Size
	{
		SIZE	size;
		if(string_tonumbers(g_config.get_value("config/default_size", ""), size.cx, size.cy)){
			variant_t	v;
			m_pExternalObject->ResizeTo(size.cx, size.cy, v);
		}
		this->CenterWindow();
	}

	//	IE Control
	{
		m_ctrlWeb	= GetDlgItem(IDC_WEB);
		m_ctrlWeb.QueryControl(__uuidof(IWebBrowser2), (void**)&m_pWeb);
		m_ctrlWeb.MoveWindow(&rc_client, TRUE);

		{
			m_ctrlWeb.SetExternalDispatch(m_pExternalObject);
			m_pWeb->put_Resizable(resizable ? ATL_VARIANT_TRUE : ATL_VARIANT_FALSE);
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
	RECT rc_client;
	GetClientRect(&rc_client);

	if(m_ctrlWeb.m_hWnd){
		m_ctrlWeb.MoveWindow(&rc_client, TRUE);
	}

	return 0;
}


LRESULT MainDialog::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	this->do_CloseWindow();
	return 0;
}
