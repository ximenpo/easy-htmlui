#pragma once

#include "simple-win32/dispatch_impl.h"

class WebExternalObject :
	public DispatchImpl
{
public:
	WebExternalObject(void);
	~WebExternalObject(void);

private:
	DISPATCH_ITEMS_BEGIN(WebExternalObject)
		DISPATCH_FUNCTION(101,L"CenterWindow", do_CenterWindow)
		DISPATCH_FUNCTION(102,L"ExecCmd", do_ExecCmd)
		DISPATCH_ITEMS_END()

private:
	void	do_AlwaysTrue(_variant_t& ret);
	void	do_AlwaysFalse(_variant_t& ret);

	void	do_CenterWindow(_variant_t& ret);
	void	do_ExecCmd(_variant_t cmdline, _variant_t wnd_show, _variant_t& ret);
};

