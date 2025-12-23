#include "auth.h"  

#include <iostream>
using namespace std;

int main(int arguments, char *arg[])
{
    if (arguments == 6)
    {
        return signUp(arg[2], arg[3], arg[4], arg[5]);
    }
    else if (arguments == 4)
    {
        return signIn(arg[2], arg[3]);
    }

    return 9; // invalid arguments/unexpected behaviour!
}
