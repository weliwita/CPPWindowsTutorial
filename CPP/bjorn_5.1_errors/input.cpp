
#include "std_lib_facilities.h"

int main()
{
    vector<string> words {"test","broccoli"};
    string current;
    while(cin>>current){
        bool found= false;

        for(string x:words){
            if(x==current){
               found = true;
                break;
            }
            
        }

        if(found){
            cout << "dont like: " << current;
        }else{
            cout << "you typed" << current;
        }
      
    }
    keep_window_open();
    return 0;
}