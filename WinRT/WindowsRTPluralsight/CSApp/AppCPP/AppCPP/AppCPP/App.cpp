#include "pch.h"
using namespace Platform;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;
ref class App :IFrameworkViewSource, IFrameworkView
{
public:
	virtual IFrameworkView ^ CreateView()
	{
		return this;
	}

	// Inherited via IFrameworkView
	virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView ^applicationView)
	{
		
	}
	virtual void SetWindow(CoreWindow ^window)
	{
		
	}
	virtual void Load(Platform::String ^entryPoint)
	{
		
	}
	virtual void Run()
	{
		CoreWindow ^ window = CoreWindow::GetForCurrentThread();
		window->Activate();

		CoreDispatcher ^ dispatcher = window->Dispatcher;
		dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
	}
	virtual void Uninitialize()
	{
		
	}
};

int main(Array<String ^> ^ args)
{
	CoreApplication::Run(ref new App);
}