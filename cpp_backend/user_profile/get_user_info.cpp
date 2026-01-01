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
                cout << email << endl;
                readUserFile.close();
            }
        }
    }
    else
    {
        return -1; // file opening error!
    }
    ifstream readWalletFile;
    readWalletFile.open("wallet.txt");
    if (readWalletFile.is_open())
    {
        int userId;
        char separator;
        string pkrBalance, usdBalance, line;
        while (getline(readWalletFile, line))
        {
            stringstream ss(line);
            ss >> userId >> separator;
            getline(ss, pkrBalance, '|');
            getline(ss, usdBalance, '|');
            if (userId == currentUser)
            {
                cout << pkrBalance << endl;
                cout << usdBalance << endl;
                readWalletFile.close();
            }
        }
    }
    else
    {
        return -4;
    }

    return 0;
}