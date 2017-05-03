#include "pch.h"
#include "Implements.h"
#include <wrl\client.h>
#include <windows.applicationmodel.core.h>

using namespace Microsoft::WRL;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::UI::Core;

struct Exception
{
	HRESULT Result;

	explicit Exception(HRESULT const result) noexcept :
	Result(result)
	{}
};

void Check(HRESULT const result)
{
	if (result != S_OK)
	{
		throw Exception(result);
	}
}

class App : public Implements<IFrameworkViewSource, IFrameworkView>
{
	ComPtr<ICoreWindow> m_window;

public:

	virtual HRESULT __stdcall CreateView(IFrameworkView ** view) noexcept override
	{
		*view = this;
		(*view)->AddRef();
		return S_OK;
	}

	virtual HRESULT __stdcall SetWindow(ICoreWindow * window) noexcept override
	{
		m_window = window;
		return S_OK;
	}

	virtual HRESULT __stdcall Run() noexcept override
	{
		HRESULT hr = m_window->Activate();

		if (hr != S_OK)
		{
			return hr;
		}

		ComPtr<ICoreDispatcher> dispatcher;
		hr = m_window->get_Dispatcher(dispatcher.GetAddressOf());

		if (hr != S_OK)
		{
			return hr;
		}

		return dispatcher->ProcessEvents(CoreProcessEventsOption_ProcessUntilQuit);
	}

	virtual HRESULT __stdcall Initialize(ICoreApplicationView *) noexcept override
	{
		return S_OK;
	}

	virtual HRESULT __stdcall Load(HSTRING) noexcept override
	{
		return S_OK;
	}

	virtual HRESULT __stdcall Uninitialize() noexcept override
	{
		return S_OK;
	}
};

class StringReference
{
	HSTRING m_string;
	HSTRING_HEADER m_header;

public:

	StringReference(StringReference const &) = delete;
	StringReference & operator=(StringReference const &) = delete;

	StringReference(wchar_t const * const value, unsigned const length)
	{
		Check(WindowsCreateStringReference(value,
			length,
			&m_header,
			&m_string));
	}

	template <unsigned Count>
	StringReference(wchar_t const (&value)[Count]) :
		StringReference(value, Count - 1)
	{}

	HSTRING Get() const noexcept
	{
		return m_string;
	}
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	Check(RoInitialize(RO_INIT_MULTITHREADED));

	// CoreApplication::Run(ref new App);

	ComPtr<ICoreApplication> app;

	StringReference name(L"Windows.ApplicationModel.Core.CoreApplication");

	Check(RoGetActivationFactory(name.Get(),
		__uuidof(app),
		reinterpret_cast<void **>(app.GetAddressOf())));

	ComPtr<IFrameworkViewSource> source;
	source.Attach(new App);

	Check(app->Run(source.Get()));
}
