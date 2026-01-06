#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main(int arguments, char *arg[])
{
    if (arguments != 2)
    {
        return -6;
    }
    int userID = stoi(arg[1]);
    vector<string> exchangeVector;
    ifstream readExchangeHistoryFile;
    readExchangeHistoryFile.open("exchangeHistory.txt");
    if (readExchangeHistoryFile.is_open())
    {
        string line;
        while (getline(readExchangeHistoryFile, line))
        {
            int uid;
            char separator;
            stringstream ss(line);
            ss >> uid >> separator;
            if (uid == userID)
            {
                exchangeVector.push_back(line);
            }
        }
        readExchangeHistoryFile.close();
    }
    for (string x : exchangeVector)
    {
        int uid;
        string currency;
        string exchangedAmount;
        string time;
        char separator;
        stringstream ss(x);
        ss >> uid >> separator;
        getline(ss, currency, '|');
        getline(ss, exchangedAmount, '|');
        getline(ss, time);
        cout << uid << '|' << currency << '|' << exchangedAmount << '|' << time << endl;
    }

    return 0;
}