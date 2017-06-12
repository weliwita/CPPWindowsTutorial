
#include "std_lib_facilities.h"

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }    
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

class Token_stream {
public: 
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

Token_stream ts;        // provides get() and putback() 

double term();
double primary();

double expression()
{
    double left = term(); //read and evaluate term
    Token t = ts.get(); // next token Please

    while(true)
    {
        //t.kind=='+' || t.kind == '-'
        switch(t.kind)
        {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t); 
                return left;
        }
    }
}

double term()
{
    double left = primary();
    Token t =  ts.get();
    while(true){
        switch(t.kind){
            case '*':
                left *= primary();
                t =  ts.get();
                break;
            case '/':
            {
                double d = primary();
                if(d==0) error("divide by zero");
                left /= d;
                t =  ts.get();
                break;
            }
            // case '%':
            //     left %= primary();
            //     t = get_token();
            //     break;
            default:
                ts.putback(t); 
                return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch(t.kind)
    {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if(t.kind != ')') error("')' exprected");
            return d;
        }
        case '8':
            return t.value;
        default:
            error("primary expected");
    }
}




//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}


Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    } 

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case ';':    // for "print"
    case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/': 
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {    
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}



int main()
{
   double val = 0;
    try{
        while(cin)
        {
            Token t = ts.get();
            if (t.kind == 'q') break; // 'q' for quit
            if (t.kind == ';')        // ';' for "print now"
                cout << "=" << val << '\n';
            else
                ts.putback(t);
            val = expression();
        }
        keep_window_open();
    }catch (exception& e){
        cerr << e.what() << '\n';
         keep_window_open();
         return 1;
    }catch (...){
        cerr << "exception \n";
         keep_window_open();
         return 2;
    }
    return 0;
}