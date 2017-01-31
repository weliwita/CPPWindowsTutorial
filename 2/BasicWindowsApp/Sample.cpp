#include "Precompiled.h"

using namespace D2D1;
using namespace Microsoft::WRL;

struct SampleWindow : CWindowImpl<SampleWindow, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW | WS_VISIBLE>>
{
    ComPtr<ID2D1Factory> m_factory;
    ComPtr<ID2D1HwndRenderTarget> m_dc;

    DECLARE_WND_CLASS_EX(L"window", CS_HREDRAW | CS_VREDRAW, -1);

    BEGIN_MSG_MAP(Window)
        MESSAGE_HANDLER(WM_PAINT, PaintHandler)
        MESSAGE_HANDLER(WM_SIZE, SizeHandler)
        MESSAGE_HANDLER(WM_DISPLAYCHANGE, DisplayChangeHandler)
        MESSAGE_HANDLER(WM_DESTROY, DestroyHandler)
    END_MSG_MAP()

    LRESULT PaintHandler(UINT, WPARAM, LPARAM, BOOL &)
    {
        PAINTSTRUCT ps;
        VERIFY(BeginPaint(&ps));

        Render();

        EndPaint(&ps);
        return 0;
    }

    LRESULT SizeHandler(UINT, WPARAM, LPARAM lparam, BOOL &)
    {
        if (m_dc)
        {
            if (S_OK != m_dc->Resize(SizeU(LOWORD(lparam), HIWORD(lparam))))
            {
                m_dc.Reset();
            }

            Invalidate();
        }

        return 0;
    }

    LRESULT DisplayChangeHandler(UINT, WPARAM, LPARAM, BOOL &)
    {
        Invalidate();
        return 0;
    }

    LRESULT DestroyHandler(UINT, WPARAM, LPARAM, BOOL &)
    {
        PostQuitMessage(0);
        return 0;
    }

    void Create()
    {
        VERIFY(__super::Create(nullptr, 0, L"Title"));

        D2D1_FACTORY_OPTIONS fo = {};

        #ifdef DEBUG
        fo.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
        #endif

        HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                             fo,
                             m_factory.GetAddressOf()));

        CreateDeviceIndependentResources();
    }

    void Invalidate()
    {
        VERIFY(__super::Invalidate(false));
    }

    void Render()
    {
        if (!m_dc)
        {
            RECT rect;
            VERIFY(GetClientRect(&rect));

            auto size = SizeU(rect.right,
                              rect.bottom);

            HR(m_factory->CreateHwndRenderTarget(RenderTargetProperties(),
                                                 HwndRenderTargetProperties(m_hWnd, size),
                                                 m_dc.GetAddressOf()));

            CreateDeviceResources();
        }

        if (!(D2D1_WINDOW_STATE_OCCLUDED & m_dc->CheckWindowState()))
        {
            m_dc->BeginDraw();

            Draw();

            if (D2DERR_RECREATE_TARGET == m_dc->EndDraw())
            {
                m_dc.Reset();
                Invalidate();
            }
        }
    }

    void CreateDeviceResources()
    {
    }

    void CreateDeviceIndependentResources()
    {
    }

    void Draw()
    {
        m_dc->Clear(ColorF(0.26f, 0.56f, 0.87f));
    }
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    SampleWindow window;
    window.Create();

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
