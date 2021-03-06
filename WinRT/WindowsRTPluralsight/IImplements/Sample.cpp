#include "Precompiled.h"
#include <windows.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

template <typename ... Interfaces>
class __declspec(novtable) Implements:public interfaces ...
{
	long m_references = 1;

protected:
	virtual ~Implements() noexcept {}

public:
	unsigned long __stdcall AddRef() noexcept
	{
		return InterlockedIncrement(&m_references);
	}

	unsigned long __stdcall Release() noexcept
	{
		unsigned long const count =  InterlockedDecrement(&m_references);
		if (0 == count) {
			delete this;
		}

		return count;
	}

	//todo:https://app.pluralsight.com/player?course=windows-runtime-essentials&author=kenny-kerr&name=windows-runtime-essentials-m3-implements&clip=4&mode=live (recursive query interface)

};


struct __declspec(uuid("c86a7bc1-96a0-4dc9-8987-c2fd7afdfd61")) __declspec(novtable)
IHen : IUnknown
{
    virtual HRESULT __stdcall Cluck() = 0;
};

class Hen : public IHen
{
    long m_references = 1;

public:

    Hen()
    {
        Trace(L"Cheep\n");
    }

    ~Hen()
    {
        Trace(L"Chicken soup\n");
    }

    unsigned long __stdcall AddRef() noexcept
    {
        return InterlockedIncrement(&m_references);
    }

    unsigned long __stdcall Release() noexcept
    {
        unsigned long const count = InterlockedDecrement(&m_references);

        if (0 == count)
        {
            delete this;
        }
        
        return count;
    }

    HRESULT __stdcall QueryInterface(GUID const & id,
                                     void ** object) noexcept
    {
        if (id == __uuidof(IHen) ||
            id == __uuidof(IUnknown))
        {
            *object = static_cast<IHen *>(this);
        }
        else
        {
            *object = nullptr;
            return E_NOINTERFACE;
        }

        static_cast<IUnknown *>(*object)->AddRef();
        return S_OK;
    }

    HRESULT __stdcall Cluck() noexcept
    {
        Trace(L"Cluck\n");
        return S_OK;
    }
};

template <typename T>
ComPtr<T> Make() noexcept
{
    ComPtr<T> result;

    result.Attach(new (std::nothrow) T);

    return result;
}

HRESULT CreateHen(IHen ** hen) noexcept
{
    ComPtr<IHen> temp = Make<Hen>();

    if (!temp)
    {
        *hen = nullptr;
        return E_OUTOFMEMORY;
    }

    *hen = temp.Detach();
    return S_OK;
}

int main()
{
    ComPtr<IHen> hen;

    HRESULT hr = CreateHen(hen.GetAddressOf());

    if (S_OK == hr)
    {
        hen->Cluck();
    }
}
