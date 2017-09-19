#pragma once

#include <unknwn.h>

struct __declspec(uuid("85797D2A-945F-49D4-B07D-68D015921109"))
Hen;

struct __declspec(uuid("95797D2A-945F-49D4-B07D-68D015921199"))
IHen : IUnknown
{
	virtual void __stdcall Cluck() = 0;
};

struct __declspec(uuid("75766D2A-945F-49D4-B07D-68D015921199"))
IHatchery : IUnknown
{
	virtual HRESULT __stdcall CreateHen(IHen ** hen) = 0;
};