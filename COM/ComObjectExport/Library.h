#pragma once

struct IHen
{
    virtual void __stdcall Cluck() = 0;
    virtual void __stdcall Roost() = 0;
};

IHen * __stdcall CreateHen();
