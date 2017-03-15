#include "Library.h"
#include <crtdbg.h>

#define ASSERT _ASSERTE

template <typename T>
class ComPtr
{

private:
	T * m_ptr;

public:
	ComPtr() : m_ptr(0) 
	{
	
	}

	~ComPtr()
	{
		if (m_ptr)
		{
			m_ptr->Release();
		}
	}

	T * operator ->() const
	{
		ASSERT(m_ptr);
		return m_ptr;
	}

	T ** GetAddressOf()
	{
		ASSERT(!m_ptr);
		return &m_ptr;
	}
};


int main()
{
	ComPtr<IHen> hen;


	if (S_OK != CreateHen(hen.GetAddressOf()))
	{
		return 0;
	}
    
    hen->Cluck();


	ComPtr<IHen2> hen2;


	if (S_OK == hen->QueryInterface((hen2.GetAddressOf())))
	{
		hen2->Forage();
		
	}


	ComPtr<IOfflineChicken> offline;

	if (S_OK == hen->QueryInterface((offline.GetAddressOf())))
	{
		offline->Save("filename");
		
	}

   
}
