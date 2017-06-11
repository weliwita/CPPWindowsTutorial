#pragma once

#include <unknwn.h>


struct IObject
{
	virtual void __stdcall AddRef() = 0;
	virtual void __stdcall Release() = 0;
	virtual void * __stdcall As(char const * type) = 0;
};

struct __declspec(uuid("7fa1fd7e-ac45-4b2e-acd9-0cd824417adb")) IHen : IUnknown
{
    virtual void __stdcall Cluck() = 0;
    virtual void __stdcall Roost() = 0;
};

//extending IHen

struct  __declspec(uuid("c712d745-c0a8-45be-bcec-7815112dd8f7")) IHen2 :IHen
{
	virtual void __stdcall Forage() = 0;
};

struct  __declspec(uuid("01e53037-6010-4da3-a539-a6c70677d8ea")) IOfflineChicken : IUnknown
{
	virtual void __stdcall Load(char const * file) = 0;
	virtual void __stdcall Save(char const * file) = 0;
};

HRESULT __stdcall CreateHen(IHen ** hen);
