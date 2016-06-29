// stdafx.cpp : 只包括标准包含文件的源文件
// easy-htmlui.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

HINSTANCE		g_instace;
HWND			g_wnd_main;
stringify_data	g_config;
std::string		g_workdir;

//////////////////////////////////////////////////////////////////
//	ATL Module
CComModule		g_module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
