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
    vector<string> transactionsVector;
    ifstream readAddBalanceHistoryFile;
    readAddBalanceHistoryFile.open("addBalanceHistory.txt");
    if (readAddBalanceHistoryFile.is_open())
    {
        string line;
        while (getline(readAddBalanceHistoryFile, line))
        {
            int uid;
            char separator;
            stringstream ss(line);
            ss >> uid >> separator;
            if (uid == userID)
            {
                transactionsVector.push_back(line);
            }
        }
        readAddBalanceHistoryFile.close();
    }
    for (string x : transactionsVector)
    {
        int uid;
        string currency;
        string amount;
        string method;
        string tid;
        string time;
        char separator;
        stringstream ss(x);
        ss >> uid >> separator;
        getline(ss, currency, '|');
        getline(ss, amount, '|');
        getline(ss, method, '|');
        getline(ss, tid, '|');
        getline(ss, time);
        cout << uid << '|' << currency << '|' << amount << '|' << method << '|' << tid << '|' << time << endl;
    }

    return 0;
}