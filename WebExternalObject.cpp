#include "StdAfx.h"
#include "WebExternalObject.h"

#include <fstream>

#include "easy-htmlui.h"
#include "DlgMain.h"

#include "simple/string.h"
#include "simple-win32/exec.h"
#include "simple-win32/res.h"

WebExternalObject::WebExternalObject(MainDialog* main_dlg)
	:	m_dlg(main_dlg)
	,	m_exec_result(0)
{
}


WebExternalObject::~WebExternalObject(void)
{
}

void	WebExternalObject::do_AlwaysTrue(_variant_t& ret)
{
	ret	= true;
}

void	WebExternalObject::do_AlwaysFalse(_variant_t& ret)
{
	ret	= false;
}

void	WebExternalObject::GetCaption(_variant_t& ret)
{
	CComBSTR	caption;
	m_dlg->GetWindowTextW(&caption);

	ret	= caption;
}

void	WebExternalObject::SetCaption(_variant_t caption)
{
	CComBSTR	scmd(caption.bstrVal);
	m_dlg->SetWindowTextW(scmd);
}

void	WebExternalObject::GetExecErrMsg(_variant_t& ret)
{
	ret	= m_exec_error.c_str();
}

void	WebExternalObject::GetExecResult(_variant_t& ret)
{
	ret	= m_exec_result;
}

void	WebExternalObject::Run(_variant_t cmdline, _variant_t wnd_show, _variant_t& ret)
{
	CComBSTR	scmd(cmdline.bstrVal);
	WORD		nshow	= wnd_show;
	ret	=	(FALSE != Exec_Cmd(scmd, nshow));
}

void	WebExternalObject::Exec(_variant_t cmdline, _variant_t timeout, _variant_t& ret)
{
	CComBSTR	scmd(cmdline.bstrVal);
	std::string	api_error, std_output;
	DWORD		u32_FirstConvert	= 0;

	m_exec_error.clear();
	m_exec_result	= Exec_App(
		string_wchar_to_ansi(scmd.operator LPWSTR()),
		u32_FirstConvert,	// IN
		g_workdir.c_str(),
		NULL,
		TRUE,
		DWORD(timeout),
		&api_error,
		&std_output,
		&m_exec_error
		);

	ret	=	std_output.c_str();
}

void	WebExternalObject::LoadTextFile(_variant_t file, _variant_t& ret)
{
	ret	= "";
	std::wstring	sfile(file.bstrVal);

    size_t	size	= 0;
    if(!Res_LoadFile(string_wchar_to_ansi(sfile), NULL, size)) {
        return;
    }
    std::auto_ptr<char>	data(new char[size]);
    if(!Res_LoadFile(string_wchar_to_ansi(sfile), data.get(), size)) {
        return;
    }

	CComBSTR	str(std::string(data.get(), size).c_str());
	ret	= str;
}

void	WebExternalObject::SaveTextFile(_variant_t file, _variant_t content, _variant_t& ret)
{
	std::wstring	sfile(file.bstrVal), scontent(content.bstrVal);
	std::ofstream	os(string_wchar_to_ansi(sfile));
	if(os){
		os << string_wchar_to_ansi(scontent);
	}

	ret	= os.good();
}

void	WebExternalObject::ResizeTo(_variant_t w, _variant_t h, _variant_t& ret)
{
	RECT	rc_wnd, rc_client;
	m_dlg->GetWindowRect(&rc_wnd);
	m_dlg->GetClientRect(&rc_client);

	const LONG	OW	= (rc_wnd.right - rc_wnd.left) - (rc_client.right - rc_client.left);
	const LONG	OH	= (rc_wnd.bottom - rc_wnd.top) - (rc_client.bottom - rc_client.top);

	rc_wnd.right	= rc_wnd.left	+ LONG(w)	+ OW;
	rc_wnd.bottom	= rc_wnd.top	+ LONG(h)	+ OH;
	m_dlg->MoveWindow(&rc_wnd, TRUE);

	ret	= true;
}

void	WebExternalObject::ResizeBy(_variant_t cx, _variant_t cy, _variant_t& ret)
{
	RECT	rc;
	m_dlg->GetWindowRect(&rc);
	rc.right	+= LONG(cx);
	rc.bottom	+= LONG(cy);
	m_dlg->MoveWindow(&rc, TRUE);

	ret	= true;
}

void	WebExternalObject::MoveTo(_variant_t x, _variant_t y, _variant_t& ret)
{
	RECT	rc;
	m_dlg->GetWindowRect(&rc);
	OffsetRect(&rc, LONG(x) - rc.left, LONG(y) - rc.top);
	m_dlg->MoveWindow(&rc, TRUE);

	ret	= true;
}

void	WebExternalObject::MoveBy(_variant_t cx, _variant_t cy, _variant_t& ret)
{
	RECT	rc;
	m_dlg->GetWindowRect(&rc);
	OffsetRect(&rc, cx, cy);
	m_dlg->MoveWindow(&rc, TRUE);

	ret	= true;
}

void	WebExternalObject::MoveCenter(_variant_t& ret)
{
	m_dlg->CenterWindow();
}

void	WebExternalObject::MaximizeWindow(_variant_t& ret)
{
	m_dlg->ShowWindow(SW_MAXIMIZE);
	ret	= true;
}

void	WebExternalObject::RestoreWindow(_variant_t& ret)
{
	m_dlg->ShowWindow(SW_RESTORE);
	ret	= true;
}

void	WebExternalObject::MinimizeWindow(_variant_t& ret)
{
	m_dlg->ShowWindow(SW_MINIMIZE);
	ret	= true;
}
