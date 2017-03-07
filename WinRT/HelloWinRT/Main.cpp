#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

using namespace Windows::Networking;
using namespace Windows::Networking::Connectivity;



int main()
{
    init_apartment();
    
    for (HostName const & name : NetworkInformation::GetHostNames())
    {
        printf("%ls\n", name.ToString().c_str());
    }
}
