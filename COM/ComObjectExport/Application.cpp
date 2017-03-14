#include "Library.h"

int main()
{
    IHen * hen = CreateHen();
    
    hen->Cluck();
    hen->Roost();
    
    delete hen; // fails due to lack of virtual dtor among other things
}
