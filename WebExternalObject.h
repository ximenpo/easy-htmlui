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
		DISPATCH_PROP(101,L"Caption",	do_GetCaption, do_SetCaption)
		DISPATCH_FUNCTION(201,L"ResizeTo",		do_ResizeTo)
		DISPATCH_FUNCTION(202,L"ResizeBy",		do_ResizeBy)
		DISPATCH_FUNCTION(203,L"MoveTo",		do_MoveTo)
		DISPATCH_FUNCTION(204,L"MoveBy",		do_MoveBy)
		DISPATCH_FUNCTION(205,L"MoveCenter",	do_MoveCenter)
		DISPATCH_FUNCTION(301,L"ExecCmd",		do_ExecCmd)
		DISPATCH_FUNCTION(401,L"LoadTextFile",	do_LoadTextFile)
		DISPATCH_FUNCTION(402,L"SaveTextFile",	do_SaveTextFile)
		DISPATCH_ITEMS_END()

private:
	void	do_AlwaysTrue(_variant_t& ret);
	void	do_AlwaysFalse(_variant_t& ret);
	
	void	do_GetCaption(_variant_t& ret);
	void	do_SetCaption(_variant_t caption);

	void	do_ExecCmd(_variant_t cmdline, _variant_t wnd_show, _variant_t& ret);
	void	do_LoadTextFile(_variant_t file, _variant_t& ret);
	void	do_SaveTextFile(_variant_t file, _variant_t content, _variant_t& ret);
	void	do_ResizeTo(_variant_t w, _variant_t h, _variant_t& ret);
	void	do_ResizeBy(_variant_t cx, _variant_t cy, _variant_t& ret);
	void	do_MoveTo(_variant_t x, _variant_t y, _variant_t& ret);
	void	do_MoveBy(_variant_t cx, _variant_t cy, _variant_t& ret);
	void	do_MoveCenter(_variant_t& ret);
};

