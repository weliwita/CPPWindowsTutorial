#include "Library.h"
#include <windows.h>
#include <crtdbg.h>
#include <memory> // for nothrow

#define TRACE OutputDebugString
#define ASSERT _ASSERTE

struct Hen : IHen2, IOfflineChicken
{
    long m_count;

    Hen() : m_count(0)
    {
        TRACE("Cheep!\n");
    }

    ~Hen()
    {
        TRACE("Chicken soup!\n");
    }

    //
    // IUnknown
    //

    ULONG __stdcall AddRef()
    {
        TRACE("AddRef\n");

        return _InterlockedIncrement(&m_count);
    }

    ULONG __stdcall Release()
    {
        ULONG result = _InterlockedDecrement(&m_count);

        if (0 == result)
        {
            delete this;
        }

        return result;
    }

    HRESULT __stdcall QueryInterface(IID const & id,
                                     void ** result)
    {
        ASSERT(result);

        if (id == __uuidof(IHen2) ||
            id == __uuidof(IHen) ||
            id == __uuidof(IUnknown))
        {
            *result = static_cast<IHen2 *>(this);
        }
        else if (id == __uuidof(IOfflineChicken))
        {
            *result = static_cast<IOfflineChicken *>(this);
        }
        else
        {
            *result = 0;
            return E_NOINTERFACE;
        }

        static_cast<IUnknown *>(*result)->AddRef();
        return S_OK;
    }

    //
    // IHen
    //

    void __stdcall Cluck()
    {
        TRACE("Cluck!\n");
    }
    
    void __stdcall Roost()
    {
        TRACE("Zzzzz!\n");
    }

    //
    // Hen2
    //

    void __stdcall Forage()
    {
        TRACE("Forage!\n");
    }

    //
    // IOfflineChicken
    //

    void __stdcall Load(char const * /*file*/)
    {
        // ...
    }

    void __stdcall Save(char const * /*file*/)
    {
        // ...
    }
};

HRESULT __stdcall CreateHen(IHen ** result)
{
    ASSERT(result);

    *result = new (std::nothrow) Hen;

    if (0 == *result)
    {
        return E_OUTOFMEMORY;
    }

    (*result)->AddRef();
    return S_OK;
}
