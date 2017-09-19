#include "Precompiled.h"
#include "handle.h"

using namespace KennyKerr;

typedef invalid_handle Transaction;

static Transaction CreateTransaction(){
	return Transaction(CreateTransaction(nullptr,
		nullptr,
		TRANSACTION_DO_NOT_PROMOTE,
		0,
		0,
		INFINITE,
		nullptr));
}


struct RegistryKeyTraits
{
	typedef HKEY pointer;
	static pointer invalid() throw()
	{
		return nullptr;
	}

	static void close(pointer value) throw()
	{
		HANDLE_VERIFY_(ERROR_SUCCESS, RegCloseKey(value));
	}
};

typedef unique_handle<RegistryKeyTraits> RegistryKey;

RegistryKey CreateRegistryKey(HKEY key,
	wchar_t const * path,
	Transaction const & transaction,
	REGSAM access)
{
	HKEY handle = nullptr;

	auto result = RegCreateKeyTransacted(key,
		path,
		0, // reserved
		nullptr, // class
		REG_OPTION_NON_VOLATILE,
		access,
		nullptr, // default security descriptor
		&handle,
		nullptr, // disposition
		transaction.get(),
		nullptr); // reserved

	if (ERROR_SUCCESS != result)
	{
		SetLastError(result);
	}

	return RegistryKey(handle);
}

RegistryKey OpenRegistryKey(HKEY key,
	wchar_t const * path,
	Transaction const & transaction,
	REGSAM access)
{
	HKEY handle = nullptr;

	auto result = RegOpenKeyTransacted(key,
		path,
		0, // reserved
		access,
		&handle,
		transaction.get(),
		nullptr); // reserved

	if (ERROR_SUCCESS != result)
	{
		SetLastError(result);
	}

	return RegistryKey(handle);
}

HRESULT	__stdcall DllRegisterServer()
{
	auto transaction = CreateTransaction();
	if (!transaction){
		return HRESULT_FROM_WIN32(GetLastError());
	}
	//un-register
	if (!CommitTransaction(transaction.get())){
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

HRESULT	__stdcall DllUnregisterServer()
{
	return S_OK;
}