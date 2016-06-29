#include "StdAfx.h"
#include "WebExternalObject.h"


WebExternalObject::WebExternalObject(void)
{
}


WebExternalObject::~WebExternalObject(void)
{
}

void	WebExternalObject::do_AlwaysTrue(_variant_t& ret)
{
	ret	= true;
}

void	WebExternalObject::do_AlwaysFalse(_variant_t& ret)
{
	ret	= false;
}
