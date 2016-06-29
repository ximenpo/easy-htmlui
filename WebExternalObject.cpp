#include "StdAfx.h"
#include "WebExternalObject.h"

#include "easy-htmlui.h"

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