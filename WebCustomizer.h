#pragma once

#include	"simple-win32/atl/IEHostWindow.h"

class WebCustomizer :
	public IEHostWindow
{
public:
	WebCustomizer(void);
	~WebCustomizer(void);

public:
	DECLARE_POLY_AGGREGATABLE(WebCustomizer);

private:
	virtual HRESULT STDMETHODCALLTYPE		ResizeBorder(
		_In_ LPCRECT prcBorder,
		_Inout_ IOleInPlaceUIWindow* pUIWindow,
		_In_ BOOL fFrameWindow);
	virtual HRESULT STDMETHODCALLTYPE		GetOptionKeyPath(
		/* [out] */ LPOLESTR __RPC_FAR *pchKey,
		/* [in] */ DWORD dw);
};

