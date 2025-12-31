#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int arguments, char *arg[])
{
    if (arguments != 2)
    {
        return -2; // uid not provided
    }

    int currentUser = stoi(arg[1]);
    ifstream readUserFile;
    readUserFile.open("users.txt");
    if (readUserFile.is_open())
    {

        string line;
        while (getline(readUserFile, line))
        {
            int uid;
            string userName, email, password;
            char separater;
            stringstream ss(line);
            ss >> uid >> separater;
            getline(ss, userName, '|');
            getline(ss, email, '|');
            if (uid == currentUser)
            {
                cout << userName << endl;
                cout << email;
                readUserFile.close();
                return 0;
            }
        }
    }
    else
    {
        return -1; // file opening error!
    }
    return 5; // unexpected error
}