// easy-htmlui.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "easy-htmlui.h"

#include "DlgMain.h"

static	bool	_Initialize()
{
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
		dlg.DoModal();
	}

	g_module.Term();
	CoUninitialize();

	return (int) EXIT_SUCCESS;
}
