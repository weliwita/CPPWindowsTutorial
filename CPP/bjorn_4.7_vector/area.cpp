
#include "std_lib_facilities.h"
class Bad_area{};

int area(int length, int width){
    if(length<=0 || width<=0) throw Bad_area{};
    return length*width;
}

int main()
{
    try {
        int x = 1;
        int y = 8;
        int areaq = area(x,y);
    }
    catch (Bad_area) {
        cout << "bad arg \n";
    }
    keep_window_open();
    return 0;
}