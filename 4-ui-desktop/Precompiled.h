#pragma once

#define NOMINMAX

#include <wrl.h>
#include <algorithm>
#include <d2d1_1.h>
#include <d3d11_1.h>
#include <uianimation.h>
#include <wincodec.h>

#if WINAPI_FAMILY_APP == WINAPI_FAMILY

    #include <windows.ui.xaml.media.dxinterop.h>

#endif

#if WINAPI_FAMILY_DESKTOP_APP == WINAPI_FAMILY

    #include <atlbase.h>
    #include <atlwin.h>

#endif
