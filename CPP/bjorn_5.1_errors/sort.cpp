#include "std_lib_facilities.h"

int main()
{
    vector<string> words {"test","broccoli"};
    for(string x:words){
        cout << x << " ";
    }
    sort(words.begin(), words.end());
    for(string x:words){
        cout << x << " ";
    }
    keep_window_open();
    return 0;
}