#include "Library.h"

int main()
{
    IHen * hen = CreateHen();
    
	hen->Cluck();

	{
		IHen * hen2 = hen;
		hen2->AddRef();
		hen2->Roost();
		hen2->Release();
	}
    
	hen->Release();
		; 
}
