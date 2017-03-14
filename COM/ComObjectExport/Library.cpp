#include "Library.h"
#include <windows.h>

#define TRACE OutputDebugString

struct Hen : IHen
{
    Hen()
    {
        TRACE("Cheep!\n");
    }
    
    ~Hen()
    {
        TRACE("Chicken soup!\n");
    }

    void __stdcall Cluck()
    {
        TRACE("Cluck!\n");
    }
    
    void __stdcall Roost()
    {
        TRACE("Zzzzz!\n");
    }
};

IHen * __stdcall CreateHen()
{
    return new Hen;
}
