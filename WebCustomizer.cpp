#include "StdAfx.h"
#include "WebCustomizer.h"

#include "WebExternalObject.h"

WebCustomizer::WebCustomizer(void)
	:	m_pExternal(new WebExternalObject())
{
	this->SetExternalDispatch(m_pExternal);
}


WebCustomizer::~WebCustomizer(void)
{
	delete	m_pExternal;
}
