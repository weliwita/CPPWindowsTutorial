#pragma once
#include <unknwn.h>



struct __declspec(uuid("35B60A55-8F41-4231-BA7F-10EFB95CEBC9"))
IHen:IUnknown
{
    virtual void __stdcall Cluck() = 0;
    virtual void __stdcall Roost() = 0;
};

struct __declspec(uuid("CCCB9EAF-6856-4D0D-A8A4-048FDCDEB6D8"))
IHen2 : IHen
{
	virtual void __stdcall Forage() = 0;
};

struct __declspec(uuid("A2C0CE9D-9C82-47B3-9DA4-2957F5B751F7"))
IOfflineChicken : IUnknown
{
	virtual void _stdcall Load(char const * file) = 0;
	virtual void _stdcall Save(char const * file) = 0;
};


HRESULT __stdcall CreateHen(IHen ** hen);

