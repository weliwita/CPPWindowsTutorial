#pragma once

#define NOMINMAX

#include <atlbase.h>
#include <atlwin.h>
#include <d2d1.h>
#include <wrl.h>
#include <algorithm>
#include <Wincodec.h>

#pragma comment(lib, "d2d1")

#define ASSERT ATLASSERT
#define VERIFY ATLVERIFY
#define TRACE ATLTRACE

#ifdef DEBUG
#define HR(expression) ASSERT(S_OK == expression)
#else
struct ComException
{
	HRESULT const hr;
	ComException(HRESULT const value) : hr(value) {}
};

inline void HR(HRESULT hr)
{
	if (S_OK != hr) throw ComException(hr);
}
#endif

#pragma warning(disable: 4706)

// Not a good idea to put this in header but helpful for producing concise demo samples.
using namespace Microsoft::WRL;
using namespace D2D1;

template <typename T>
class DesktopWindow : public CWindowImpl<DesktopWindow<T>, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW | WS_VISIBLE>>
{
public:

	DECLARE_WND_CLASS_EX(nullptr, CS_HREDRAW | CS_VREDRAW, -1);

private:

	BEGIN_MSG_MAP(DesktopWindow)
		MESSAGE_HANDLER(WM_PAINT, PaintHandler)
		MESSAGE_HANDLER(WM_SIZE, SizeHandler)
		MESSAGE_HANDLER(WM_MOUSEMOVE, MouseMoveHandler)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, LeftMouseButtonDownHandler)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, RightMouseButtonDownHandler)
		MESSAGE_HANDLER(WM_LBUTTONUP, LeftMouseButtonUpHandler)
		MESSAGE_HANDLER(WM_RBUTTONUP, RightMouseButtonUpHandler)
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
		if (m_target)
		{
			if (S_OK != m_target->Resize(SizeU(LOWORD(lparam), HIWORD(lparam))))
			{
				m_target.Reset();
			}
		}

		return 0;
	}

	LRESULT MouseMoveHandler(UINT, WPARAM wparam, LPARAM lparam, BOOL &)
	{
		if (m_target)
		{
			static_cast<T *>(this)->MouseMoved(GET_X_LPARAM(lparam) * 96.0f / m_dpiX,
				GET_Y_LPARAM(lparam) * 96.0f / m_dpiY, wparam);
		}

		return 0;
	}

	LRESULT LeftMouseButtonDownHandler(UINT, WPARAM wparam, LPARAM lparam, BOOL &)
	{
		if (m_target)
		{
			static_cast<T *>(this)->LeftMouseButtonDown(GET_X_LPARAM(lparam) * 96.0f / m_dpiX,
				GET_Y_LPARAM(lparam) * 96.0f / m_dpiY, wparam);
		}

		return 0;
	}

	LRESULT RightMouseButtonDownHandler(UINT, WPARAM wparam, LPARAM lparam, BOOL &)
	{
		if (m_target)
		{
			static_cast<T *>(this)->RightMouseButtonDown(GET_X_LPARAM(lparam) * 96.0f / m_dpiX,
				GET_Y_LPARAM(lparam) * 96.0f / m_dpiY, wparam);
		}

		return 0;
	}

	LRESULT LeftMouseButtonUpHandler(UINT, WPARAM wparam, LPARAM lparam, BOOL &)
	{
		if (m_target)
		{
			static_cast<T *>(this)->LeftMouseButtonUp(GET_X_LPARAM(lparam) * 96.0f / m_dpiX,
				GET_Y_LPARAM(lparam) * 96.0f / m_dpiY, wparam);
		}

		return 0;
	}

	LRESULT RightMouseButtonUpHandler(UINT, WPARAM wparam, LPARAM lparam, BOOL &)
	{
		if (m_target)
		{
			static_cast<T *>(this)->RightMouseButtonUp(GET_X_LPARAM(lparam) * 96.0f / m_dpiX,
				GET_Y_LPARAM(lparam) * 96.0f / m_dpiY, wparam);
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

	void CreateDeviceIndependentResources()
	{
		// Do nothing - override in derived class to create stuff
	}

	void CreateDeviceResources()
	{
		// Do nothing - override in derived class to create stuff
	}

	void MouseMoved(float, float, WPARAM)
	{
		// Do nothing - override in derived class to create stuff
	}

	void LeftMouseButtonDown(float, float, WPARAM)
	{
		// Do nothing - override in derived class to create stuff
	}

	void RightMouseButtonDown(float, float, WPARAM)
	{
		// Do nothing - override in derived class to create stuff
	}

	void LeftMouseButtonUp(float, float, WPARAM)
	{
		// Do nothing - override in derived class to create stuff
	}

	void RightMouseButtonUp(float, float, WPARAM)
	{
		// Do nothing - override in derived class to create stuff
	}

	void CaptureMouse()
	{
		SetCapture();
	}

	void ReleaseMouse()
	{
		VERIFY(ReleaseCapture());
	}

	bool MouseCaptured()
	{
		return m_hWnd == GetCapture();
	}

	void Render()
	{
		if (!m_target)
		{
			RECT rect;
			VERIFY(GetClientRect(&rect));

			auto size = SizeU(rect.right, rect.bottom);

			HR(m_factory->CreateHwndRenderTarget(RenderTargetProperties(),
				HwndRenderTargetProperties(m_hWnd, size),
				m_target.GetAddressOf()));

			m_target->GetDpi(&m_dpiX, &m_dpiY);

			static_cast<T *>(this)->CreateDeviceResources();
		}

		if (!(D2D1_WINDOW_STATE_OCCLUDED & m_target->CheckWindowState()))
		{
			m_target->BeginDraw();

			static_cast<T *>(this)->Draw();

			if (D2DERR_RECREATE_TARGET == m_target->EndDraw())
			{
				m_target.Reset();
			}
		}
	}

protected:

	ComPtr<ID2D1Factory> m_factory;
	ComPtr<ID2D1HwndRenderTarget> m_target;
	float m_dpiX;
	float m_dpiY;

	void Invalidate()
	{
		VERIFY(InvalidateRect(nullptr, false));
	}

public:

	void Run()
	{
		D2D1_FACTORY_OPTIONS fo = {};

#ifdef DEBUG
		fo.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

		HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
			fo,
			m_factory.GetAddressOf()));

		static_cast<T *>(this)->CreateDeviceIndependentResources();

		VERIFY(__super::Create(nullptr, nullptr, L"Direct2D Fundamentals by Kenny Kerr"));

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

};

struct ComInitialize
{
	ComInitialize()
	{
		HR(CoInitialize(nullptr));
	}
	~ComInitialize()
	{
		CoUninitialize();
	}
};

template <typename T>
void CreateInstance(REFCLSID clsid, ComPtr<T> & ptr)
{
	ASSERT(!ptr);
	HR(CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(T), reinterpret_cast<void **>(ptr.GetAddressOf())));
}
