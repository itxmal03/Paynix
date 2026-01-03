#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream file("session.txt");
    if (!file.is_open())
    {
        return 1; // file not opened ! / no session exist
    }
    string line;
    getline(file, line);
    file.close();
    if (line.empty()) 
    {
        return 1; // no session exist
    }

    return 0; // session exists
}