
#include "std_lib_facilities.h"

class Token{
    public:
        char kind;
        double value;
};

Token get_token();

vector<Token> tok; //put tokens here;

int main()
{
    while(cin){
        Token t = get_token();
        tok.push_back(t);
    }

    keep_window_open();
    return 0;
}