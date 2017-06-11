#include "Library.h"
#include <windows.h>
#include <crtdbg.h>
#include <iostream>

#define ASSERT _ASSERTE
//#define printf OutputDebugString

struct Hen : IHen2, IOfflineChicken
{
	long m_count;
	Hen() : m_count(0)
    {
		printf("Cheep!\n");
		
    }
    
    ~Hen()
    {
		printf("Chicken soup!\n");
    }

    void __stdcall Cluck()
    {
		printf("Cluck!\n");
    }
    
    void __stdcall Roost()
    {
        printf("Zzzzz!\n");
    }

	//
	//IHen2
	//
	void __stdcall Forage()
	{
		printf("Forage!\n");
	}

	//
	//Offline Chicken
	//
	void __stdcall Load(char const * /*file*/)
	{
		//printf("Forage!\n");
	}
	void __stdcall Save(char const * /*file*/)
	{
		//("Forage!\n");
	}




	//
	// IUnknown
	//
	ULONG __stdcall AddRef()
	{
		return _InterlockedIncrement(&m_count);
	}

	ULONG __stdcall Release()
	{
		ULONG const result = _InterlockedDecrement(&m_count);

		if (0 == result){
			delete this;
		}

		return result;
	}

	HRESULT __stdcall QueryInterface(IID const & id, void ** result)
	{
		ASSERT(result);

		if (id == __uuidof(IHen2) ||
			id == __uuidof(IHen) ||
			id == __uuidof(IUnknown))
		{
			*result = static_cast<IHen2 *>(this);
		}
		else if (id == __uuidof(IOfflineChicken)){
			*result = static_cast<IOfflineChicken *>(this);
		}
		else{
			*result = 0;
			return E_NOINTERFACE;
		}


		static_cast<IUnknown *>(*result)->AddRef();
		return S_OK;
		
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
