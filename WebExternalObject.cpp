#include "StdAfx.h"
#include "WebExternalObject.h"

#include <fstream>

#include "easy-htmlui.h"

#include "simple/string.h"
#include "simple-win32/exec.h"
#include "simple-win32/res.h"

WebExternalObject::WebExternalObject(void)
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

void	WebExternalObject::do_CenterWindow(_variant_t& ret)
{
	CWindow	wnd(g_wnd_main);
	wnd.CenterWindow();
}

void	WebExternalObject::do_ExecCmd(_variant_t cmdline, _variant_t wnd_show, _variant_t& ret)
{
	CComBSTR	scmd(cmdline.bstrVal);
	WORD		nshow	= wnd_show;
	ret	=	(FALSE != ExecApp(scmd, nshow));
}

void	WebExternalObject::do_LoadTextFile(_variant_t file, _variant_t& ret)
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

	CComBSTR	str(string_ansi_to_wchar(std::string(data.get(), size)));
	ret	= str.Detach();
}

void	WebExternalObject::do_SaveTextFile(_variant_t file, _variant_t content, _variant_t& ret)
{
	std::wstring	sfile(file.bstrVal), scontent(content.bstrVal);
	std::ofstream	os(string_wchar_to_ansi(sfile));
	if(os){
		os << string_wchar_to_ansi(scontent);
	}

	ret	= os.good();
}

void	WebExternalObject::do_ResizeWindowTo(_variant_t w, _variant_t h, _variant_t& ret)
{
	RECT	rc_wnd, rc_client;
	CWindow	wnd(g_wnd_main);
	wnd.GetWindowRect(&rc_wnd);
	wnd.GetClientRect(&rc_client);
	const int	OX	= (rc_wnd.right - rc_wnd.left) - (rc_client.right - rc_client.left);
	const int	OY	= (rc_wnd.bottom - rc_wnd.top) - (rc_client.bottom - rc_client.top);

	rc_wnd.right	= rc_wnd.left + LONG(w) + OX;
	rc_wnd.bottom	= rc_wnd.top + LONG(h) + OY;
	wnd.MoveWindow(&rc_wnd, TRUE);

	ret	= true;
}

void	WebExternalObject::do_ResizeWindowBy(_variant_t cx, _variant_t cy, _variant_t& ret)
{
	RECT	rc;
	CWindow	wnd(g_wnd_main);
	wnd.GetWindowRect(&rc);
	rc.right	+= LONG(cx);
	rc.bottom	+= LONG(cy);
	wnd.MoveWindow(&rc, TRUE);

	ret	= true;
}

void	WebExternalObject::do_MoveWindowTo(_variant_t x, _variant_t y, _variant_t& ret)
{
	RECT	rc;
	CWindow	wnd(g_wnd_main);
	wnd.GetWindowRect(&rc);
	OffsetRect(&rc, LONG(x) - rc.left, LONG(y) - rc.top);
	wnd.MoveWindow(&rc, TRUE);

	ret	= true;
}

void	WebExternalObject::do_MoveWindowBy(_variant_t cx, _variant_t cy, _variant_t& ret)
{
	RECT	rc;
	CWindow	wnd(g_wnd_main);
	wnd.GetWindowRect(&rc);
	OffsetRect(&rc, cx, cy);
	wnd.MoveWindow(&rc, TRUE);

	ret	= true;
}
