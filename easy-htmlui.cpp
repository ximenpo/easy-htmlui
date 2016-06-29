// easy-htmlui.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "easy-htmlui.h"

#include <fstream>

#include "DlgMain.h"

static	bool	_Initialize()
{
	bool	is_debug	= false;
#ifndef	NDEBUG
	is_debug	= true;
#endif

	char buf[1024]	= {0};

	//	root dir
	{
		if(is_debug) {
			::SetCurrentDirectoryW(L"example");
		}else{
			GetModuleFileNameA(0, buf, sizeof(buf) - 1);
			std::string		path(buf);
			path	= path.substr(0, path.find_last_of("."));
			if(!PathIsDirectoryA(path.c_str())) {
				path	= path.substr(0, path.find_last_of("/\\"));
			}
			::SetCurrentDirectoryA(path.c_str());
		}
		::GetCurrentDirectoryA(sizeof(buf) - 1, buf);
		g_workdir.assign(buf);
	}

	//	config
	{
		std::ifstream	ifs("config.ini");
		if(!ifs || !stringify_from_ini_stream(g_config, ifs)){
			return	false;
		}
	}

	return	true;
}

int APIENTRY	_tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	g_instace	= hInstance;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if(!_Initialize()){
		return	EXIT_FAILURE;
	}

	CoInitialize(NULL);
	g_module.Init(NULL, hInstance);

	{
		MainDialog	dlg;
		dlg.Create(NULL);
		g_wnd_main	= dlg.m_hWnd;

		MSG msg;
		while (dlg.IsWindow() && GetMessage(&msg, NULL, 0, 0))
		{
			//	hack for webbrowser's TAB/RETURN/DELETE
			if(		msg.message >= WM_KEYFIRST
				&&	msg.message <= WM_KEYLAST
				&&	dlg.PreProcessKeyboardMessage(&msg)
				){
					continue;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	g_module.Term();
	CoUninitialize();

	return (int) EXIT_SUCCESS;
}
