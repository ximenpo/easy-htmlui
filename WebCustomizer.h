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
	STDMETHOD(ResizeBorder)(
		_In_ LPCRECT prcBorder,
		_Inout_ IOleInPlaceUIWindow* pUIWindow,
		_In_ BOOL fFrameWindow);
};

