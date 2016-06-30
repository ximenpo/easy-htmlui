#include "StdAfx.h"
#include "WebCustomizer.h"

#include "easy-htmlui.h"

WebCustomizer::WebCustomizer(void)
{
}


WebCustomizer::~WebCustomizer(void)
{
}

HRESULT STDMETHODCALLTYPE WebCustomizer::GetOptionKeyPath(
	/* [out] */ LPOLESTR __RPC_FAR *pchKey,
	/* [in] */ DWORD dw)
{
	*pchKey	= AtlAllocTaskOleString(L"SOFTWARE\\Simple\\easy-htmlui\\IE");
	return	S_OK;
}