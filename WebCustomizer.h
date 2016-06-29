#pragma once

#include	"simple-win32/atl/IEHostWindow.h"

class WebExternalObject;

class WebCustomizer :
	public IEHostWindow
{
public:
	WebCustomizer(void);
	~WebCustomizer(void);

private:
	WebExternalObject*	m_pExternal;

public:
	DECLARE_POLY_AGGREGATABLE(WebCustomizer);


};

