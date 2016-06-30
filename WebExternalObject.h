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
		DISPATCH_FUNCTION(101,L"CenterWindow",	do_CenterWindow)
		DISPATCH_FUNCTION(102,L"ResizeWindowTo",do_ResizeWindowTo)
		DISPATCH_FUNCTION(103,L"ResizeWindowBy",do_ResizeWindowBy)
		DISPATCH_FUNCTION(104,L"MoveWindowTo",	do_MoveWindowTo)
		DISPATCH_FUNCTION(105,L"MoveWindowBy",	do_MoveWindowBy)
		DISPATCH_FUNCTION(201,L"ExecCmd",		do_ExecCmd)
		DISPATCH_FUNCTION(301,L"LoadTextFile",	do_LoadTextFile)
		DISPATCH_FUNCTION(302,L"SaveTextFile",	do_SaveTextFile)
		DISPATCH_ITEMS_END()

private:
	void	do_AlwaysTrue(_variant_t& ret);
	void	do_AlwaysFalse(_variant_t& ret);

	void	do_CenterWindow(_variant_t& ret);
	void	do_ExecCmd(_variant_t cmdline, _variant_t wnd_show, _variant_t& ret);
	void	do_LoadTextFile(_variant_t file, _variant_t& ret);
	void	do_SaveTextFile(_variant_t file, _variant_t content, _variant_t& ret);
	void	do_ResizeWindowTo(_variant_t w, _variant_t h, _variant_t& ret);
	void	do_ResizeWindowBy(_variant_t cx, _variant_t cy, _variant_t& ret);
	void	do_MoveWindowTo(_variant_t x, _variant_t y, _variant_t& ret);
	void	do_MoveWindowBy(_variant_t cx, _variant_t cy, _variant_t& ret);
};

