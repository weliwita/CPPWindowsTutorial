#include "windows.h"
#define TRACE OutputDebugString


struct ComException
{
	HRESULT error;

	ComException(HRESULT const hr) :error(hr){

	}
};

inline void HR(HRESULT const hr){
	if (S_OK != hr){
		throw ComException(hr);
	}
}

int main(){
	HRESULT hr = S_FALSE;
	/*if (SUCCEEDED(hr)){
		TRACE("succeeded\n");

	}

	if (FAILED(hr)){
		TRACE("failed\n");
	}*/

	if (S_OK == hr){
		TRACE("succeeded\n");
	}
	else{
		TRACE("failed\n");
	}
	
}