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
		DISPATCH_ITEMS_END()

private:
	void	do_AlwaysTrue(_variant_t& ret);
	void	do_AlwaysFalse(_variant_t& ret);
};

