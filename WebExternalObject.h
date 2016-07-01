#pragma once

#include "simple-win32/dispatch_impl.h"

class	MainDialog;

class WebExternalObject :
	public DispatchImpl
{
public:
	WebExternalObject(MainDialog* main_dlg);
	~WebExternalObject(void);

public:
	void	GetCaption(_variant_t& ret);
	void	SetCaption(_variant_t caption);

	void	ExecCmd(_variant_t cmdline, _variant_t wnd_show, _variant_t& ret);
	void	LoadTextFile(_variant_t file, _variant_t& ret);
	void	SaveTextFile(_variant_t file, _variant_t content, _variant_t& ret);
	void	ResizeTo(_variant_t w, _variant_t h, _variant_t& ret);
	void	ResizeBy(_variant_t cx, _variant_t cy, _variant_t& ret);
	void	MoveTo(_variant_t x, _variant_t y, _variant_t& ret);
	void	MoveBy(_variant_t cx, _variant_t cy, _variant_t& ret);
	void	MoveCenter(_variant_t& ret);
	void	MaximizeWindow(_variant_t& ret);
	void	RestoreWindow(_variant_t& ret);
	void	MinimizeWindow(_variant_t& ret);

private:
	DISPATCH_ITEMS_BEGIN(WebExternalObject)
		DISPATCH_PROP(101,		L"Caption",			GetCaption,		SetCaption)
		DISPATCH_FUNCTION(201,	L"ResizeTo",		ResizeTo)
		DISPATCH_FUNCTION(202,	L"ResizeBy",		ResizeBy)
		DISPATCH_FUNCTION(203,	L"MoveTo",			MoveTo)
		DISPATCH_FUNCTION(204,	L"MoveBy",			MoveBy)
		DISPATCH_FUNCTION(205,	L"MoveCenter",		MoveCenter)
		DISPATCH_FUNCTION(211,	L"MaximizeWindow",	MaximizeWindow)
		DISPATCH_FUNCTION(212,	L"RestoreWindow",	RestoreWindow)
		DISPATCH_FUNCTION(213,	L"MinimizeWindow",	MinimizeWindow)
		DISPATCH_FUNCTION(301,	L"ExecCmd",			ExecCmd)
		DISPATCH_FUNCTION(401,	L"LoadTextFile",	LoadTextFile)
		DISPATCH_FUNCTION(402,	L"SaveTextFile",	SaveTextFile)
		DISPATCH_ITEMS_END()

private:
	MainDialog*		m_dlg;

private:
	void	do_AlwaysTrue(_variant_t& ret);
	void	do_AlwaysFalse(_variant_t& ret);
};

