#include "Library.h"

int main()
{
	IHen * hen;

	if (S_OK != CreateHen(&hen)){
		return 0;
	}

	hen->Cluck();

	IHen2 * hen2;

	if (S_OK == hen->QueryInterface(&hen2)){ //copiler magic to reinterpret this to original
		hen2->Forage();
		hen2->Release();
	}

	
	IOfflineChicken * offline;
	if (S_OK == hen->QueryInterface(&offline)){
		offline->Save("filename");
		offline->Release();
	}
    
	hen->Release(); 
}
