#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream file;
    file.open("session.txt", ios::trunc);
    if (file.is_open())
    {
        file.close();
        return 0;
    }

    return -1; // file opening error
}