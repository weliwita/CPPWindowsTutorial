#include "Library.h"
#include <windows.h>

#define TRACE OutputDebugString

struct Hen : IHen2, IOfflineChicken
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

	//
	//IHen2
	//
	void __stdcall Forage()
	{
		TRACE("Forage!\n");
	}

	//
	//Offline Chicken
	//
	void __stdcall Load(char const * /*file*/)
	{
		//TRACE("Forage!\n");
	}
	void __stdcall Save(char const * /*file*/)
	{
		//("Forage!\n");
	}




	//
	// IObject
	//
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

	void * __stdcall As(char const * type)
	{
		if (0 == strcmp(type, "IHen2") || 
			0 == strcmp(type, "IHen") ||
			0 == strcmp(type, "IObject"))
		{
			AddRef();
			return static_cast<IHen2 *>(this);
		}

		else if (0 == strcmp(type, "IOfflineChicken")){
			AddRef();
			return static_cast<IOfflineChicken *>(this);
		}
		else{
			return 0;
		}
	}
};

IHen * __stdcall CreateHen()
{
    IHen * result = new Hen;
	result->AddRef();
	return result;
}
