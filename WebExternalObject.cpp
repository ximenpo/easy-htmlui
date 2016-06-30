#include "StdAfx.h"
#include "WebExternalObject.h"

#include "easy-htmlui.h"

#include "simple-win32/exec.h"

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
