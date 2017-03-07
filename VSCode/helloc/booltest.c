#include <stdio.h>

#ifndef __cplusplus
    typedef char bool; // define a type / create an alias/ compiler know the data type bool, can be used as parameter,
    #define true 1 // define a macro / compiler dont know true, but same as 1, so 1 and true can used interchangebly.
    #define false 0
#endif

int main(){
    bool c2f = true;

    double c = 34;
    double f = 0;

    if(c2f){
        f= c * 9/5 +32;
    }else{
        c= (f-32)*5/9;
    }

    printf("%f c = %f F\n",c,f);

    return 0;
}

