#pragma once

#include <wrl.h>
#include <algorithm>
#include <d2d1_1.h>
#include <d3d11_1.h>

#if WINAPI_FAMILY_DESKTOP_APP == WINAPI_FAMILY
#include <atlbase.h>
#include <atlwin.h>
#endif

#pragma comment(lib, "d2d1")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")

#pragma warning(disable: 4706)
#pragma warning(disable: 4127)

namespace wrl = Microsoft::WRL;
namespace d2d = D2D1;

#ifdef __cplusplus_winrt

namespace win
{
    using namespace Platform;
    using namespace Windows::ApplicationModel::Core;
    using namespace Windows::UI::Core;
    using namespace Windows::Graphics::Display;
}

#endif

#if WINAPI_FAMILY_PHONE_APP != WINAPI_FAMILY
#define ASSERT(expression) _ASSERTE(expression)
#else
#if _DEBUG
#define ASSERT(expression) { if (!(expression)) throw win::Exception::CreateException(E_FAIL); }
#else
#define ASSERT(expression) ((void)0)
#endif
#endif

#ifdef _DEBUG

#define VERIFY(expression) ASSERT(expression)
#define HR(expression) ASSERT(S_OK == (expression))

inline void TRACE(WCHAR const * const format, ...)
{
    va_list args;
    va_start(args, format);

    WCHAR output[512];
    vswprintf_s(output, format, args);

    OutputDebugString(output);

    va_end(args);
}

#else

#define VERIFY(expression) (expression)

#ifdef __cplusplus_winrt

inline void HR(HRESULT const hr)
{
    if (S_OK != hr) throw win::Exception::CreateException(hr);
}

#else

struct ComException
{
    HRESULT const hr;
    ComException(HRESULT const value) : hr(value) {}
};

inline void HR(HRESULT const hr)
{
    if (S_OK != hr) throw ComException(hr);
}

#endif

#define TRACE __noop

#endif

inline wrl::ComPtr<ID2D1Factory1> CreateFactory()
{
    D2D1_FACTORY_OPTIONS fo = {};

    #ifdef _DEBUG
    fo.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
    #endif

    wrl::ComPtr<ID2D1Factory1> factory;

    HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                         fo,
                         factory.GetAddressOf()));

    return factory;
}


#if WINAPI_FAMILY_DESKTOP_APP == WINAPI_FAMILY

template <typename T>
struct DesktopWindow :
    CWindowImpl<DesktopWindow<T>, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW | WS_VISIBLE>>
{
    DECLARE_WND_CLASS_EX(nullptr, 0, -1);

    BEGIN_MSG_MAP(c)
        MESSAGE_HANDLER(WM_PAINT, PaintHandler)
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

    LRESULT DestroyHandler(UINT, WPARAM, LPARAM, BOOL &)
    {
        PostQuitMessage(0);
        return 0;
    }

    void Render()
    {
        if (!m_target)
        {
            // create device and target

            static_cast<T *>(this)->CreateDeviceResources();
            static_cast<T *>(this)->CreateDeviceSizeResources();
        }
    }

    void ReleaseDevice()
    {
        // release device 

        static_cast<T *>(this)->ReleaseDeviceResources();
    }

    void Run()
    {
        m_factory = CreateFactory();
        static_cast<T *>(this)->CreateDeviceIndependentResources();

        RECT bounds = { 10, 10, 1010, 750 };
        VERIFY(__super::Create(nullptr, bounds, L"Direct2D"));

        MSG message = {};

        while (BOOL result = GetMessage(&message, 0, 0, 0))
        {
            if (-1 != result)
            {
                DispatchMessage(&message);
            }
        }
    }

    void CreateDeviceIndependentResources() {}
    void CreateDeviceResources() {}
    void CreateDeviceSizeResources() {}
    void ReleaseDeviceResources() {}

    wrl::ComPtr<ID2D1Factory1> m_factory;
    wrl::ComPtr<ID2D1DeviceContext> m_target;
};

#endif
