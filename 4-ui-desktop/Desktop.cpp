#include "Precompiled.h"
#include "Common.h"

struct SampleWindow : DesktopWindow<SampleWindow>
{
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	SampleWindow window;
	window.Run();
}