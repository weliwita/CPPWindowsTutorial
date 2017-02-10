#include "Precompiled.h"

#include <atlbase.h>
#include <atlwin.h>

struct SampleWindow : 
    CWindowImpl<SampleWindow, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW | WS_VISIBLE>>
{
    DECLARE_WND_CLASS_EX(L"window", CS_HREDRAW | CS_VREDRAW, -1);

    BEGIN_MSG_MAP(SampleWindow)
                MESSAGE_HANDLER(WM_PAINT, PaintHandler)
                MESSAGE_HANDLER(WM_DESTROY, DestroyHandler)
    END_MSG_MAP()

    LRESULT PaintHandler(UINT, WPARAM, LPARAM, BOOL &)
    {
        PAINTSTRUCT ps;
        VERIFY(BeginPaint(&ps));
        
        TRACE(L"Paint!\n");

        EndPaint(&ps);
        return 0;
    }

    LRESULT DestroyHandler(UINT, WPARAM, LPARAM, BOOL &)
    {
        PostQuitMessage(0);
        return 0;
    }


};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    SampleWindow window;

    VERIFY(window.Create(nullptr, 0, L"title"));

    MSG message;
    BOOL result;

    while (result = GetMessage(&message, 0, 0, 0))
    {
        if (-1 != result)
        {
            DispatchMessage(&message);
        }
    }
}
