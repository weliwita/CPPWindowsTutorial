#include "Library.h"
#include <wrl.h>

using namespace Microsoft::WRL;

struct ComException
{
    HRESULT error;

    ComException(HRESULT hr) : error(hr) {}
};

inline void HR(HRESULT hr)
{
    if (S_OK != hr)
    {
        throw ComException(hr);
    }
}

static ComPtr<IHen> CreateHen()
{
    ComPtr<IHen> hen;
    HR(CreateHen(hen.GetAddressOf()));
    return hen;
}

int main()
{
    ComPtr<IHen> hen = CreateHen();

    hen->Cluck();

    ComPtr<IHen2> hen2;

    if (S_OK == hen.CopyTo(hen2.GetAddressOf()))
    {
        hen2->Forage();
    }

    ComPtr<IOfflineChicken> offline;
    
    if (S_OK == hen.CopyTo(offline.GetAddressOf()))
    {
        offline->Save("filename");
    }
}
