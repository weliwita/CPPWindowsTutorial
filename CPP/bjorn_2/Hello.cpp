
#include "std_lib_facilities.h"

int main()
{
    cout << "Please Enter your first and last names followed by number to get sqrt.\n";
    string first;
    string last;
    int age;
    cin >> first >> last >> age;
    double sqrt1 = sqrt(double(age));
    cout << first << " " << last << "\n";
    cout << "squire root is " << sqrt1 << " \n";
    keep_window_open();
    return 0;
}