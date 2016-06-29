#include "StdAfx.h"
#include "WebCustomizer.h"

#include "WebExternalObject.h"

WebCustomizer::WebCustomizer(void)
	:	m_pExternal(new WebExternalObject())
{
	m_pExternal->AddRef();
	this->SetExternalDispatch(m_pExternal);
}


WebCustomizer::~WebCustomizer(void)
{
	this->SetExternalDispatch(NULL);
	delete	m_pExternal;
}
