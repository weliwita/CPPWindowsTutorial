#include "Library.h"
#include <windows.h>

#define TRACE OutputDebugString

struct Hen : IHen
{
	unsigned m_count;
	Hen() : m_count(0)
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

	void __stdcall AddRef()
	{
		++m_count;
	}

	void __stdcall Release()
	{
		if (0 == --m_count){
			delete this;
		}
	}
};

IHen * __stdcall CreateHen()
{
    IHen * result = new Hen;
	result->AddRef();
	return result;
}
