#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream file;
    file.open("session.txt");
    if (!file.is_open())
    {
        return -1; // file opening error
    }
    string line;
    if (!getline(file, line))
    {
        return -2; // empty file
    }
    int uid;
    stringstream ss(line);
    if (!(ss >> uid))
    {
        return -3; // invalid format or currupted file 
    }
    return uid;
}