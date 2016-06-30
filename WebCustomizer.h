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
	virtual HRESULT STDMETHODCALLTYPE		GetOptionKeyPath(
		/* [out] */ LPOLESTR __RPC_FAR *pchKey,
		/* [in] */ DWORD dw);
};

