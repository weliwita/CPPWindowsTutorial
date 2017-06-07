#include "Precompiled.h"

#pragma comment(lib, "rpcrt4.lib")

int main(){
	GUID guid;
	ASSERT(RPC_S_OK == UuidCreate(&guid));
	HR(CoCreateGuid(&guid));

	unsigned short * rpc_string;
	ASSERT(RPC_S_OK == UuidToString(&guid, &rpc_string));
	TRACE(L"%s\n", rpc_string);

	wchar_t ole_string[39];
	ASSERT(StringFromGUID2(guid, ole_string, _countof(ole_string)));
	TRACE(L"%s\n", ole_string);

	std::wstring std_string(ole_string + 1, _countof(ole_string) - 3);
	TRACE(L"%s\n", std_string.c_str());

	GUID guid2;
	ASSERT(RPC_S_OK == UuidFromString(rpc_string, &guid2));

	HR(CLSIDFromString(ole_string, &guid2));

	ASSERT(RPC_S_OK == UuidFromString(reinterpret_cast<unsigned short *>(const_cast<wchar_t *>(std_string.c_str())), &guid2));

	ASSERT(RPC_S_OK == RpcStringFree(&rpc_string));

}