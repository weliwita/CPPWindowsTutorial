#pragma once

#include <unknwn.h>

struct __declspec(uuid("5C631997-1E44-4FE2-BD44-4BD7DF8FE56F")) IHen : IUnknown
{
    virtual void __stdcall Cluck() = 0;
    virtual void __stdcall Roost() = 0;
};

struct __declspec(uuid("8FEA0426-91CA-4264-AAC5-544A7544E628")) IHen2 : IHen
{
    virtual void __stdcall Forage() = 0;
};

struct __declspec(uuid("A3CF3A88-0D79-4705-A287-A67BC5E4FBA0")) IOfflineChicken : IUnknown
{
    virtual void __stdcall Load(char const * file) = 0;
    virtual void __stdcall Save(char const * file) = 0;
};

HRESULT __stdcall CreateHen(IHen ** hen);
