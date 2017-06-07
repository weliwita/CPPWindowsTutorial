#pragma once

#include <atlbase.h>
#include <string>

#define TRACE ATLTRACE
#define ASSERT ATLASSERT

struct ComException
{
	HRESULT error;

	ComException(HRESULT hr) : error(hr) {}
};

inline void HR(HRESULT hr)
{
	if (S_OK != hr)
	{
		throw ComException(hr);
	}
}