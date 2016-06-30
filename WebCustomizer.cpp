#include "StdAfx.h"
#include "WebCustomizer.h"

#include "easy-htmlui.h"

WebCustomizer::WebCustomizer(void)
{
}


WebCustomizer::~WebCustomizer(void)
{
}

HRESULT STDMETHODCALLTYPE	WebCustomizer::ResizeBorder(
	_In_ LPCRECT prcBorder,
	_Inout_ IOleInPlaceUIWindow* pUIWindow,
	_In_ BOOL fFrameWindow)
{
	CWindow	main_wnd(g_wnd_main);
	RECT	rc_wnd, rc_client;
	main_wnd.GetWindowRect(&rc_wnd);
	main_wnd.GetClientRect(&rc_client);
	const int	OX	= (rc_wnd.right - rc_wnd.left) - (rc_client.right - rc_client.left);
	const int	OY	= (rc_wnd.bottom - rc_wnd.top) - (rc_client.bottom - rc_client.top);

	rc_wnd.right	= rc_wnd.left + (prcBorder->right - prcBorder->left) + OX;
	rc_wnd.bottom	= rc_wnd.top + (prcBorder->bottom - prcBorder->top) + OY;

	main_wnd.MoveWindow(&rc_wnd, TRUE);
	return	S_OK;
	//return IEHostWindow::ResizeBorder(prcBorder, pUIWindow, fFrameWindow);
}


HRESULT STDMETHODCALLTYPE WebCustomizer::GetOptionKeyPath(
	/* [out] */ LPOLESTR __RPC_FAR *pchKey,
	/* [in] */ DWORD dw)
{
	*pchKey	= AtlAllocTaskOleString(L"SOFTWARE\\Simple\\easy-htmlui\\IE");
	return	S_OK;
}