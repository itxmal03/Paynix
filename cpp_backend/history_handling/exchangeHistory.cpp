#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

string currentDateTime()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    ostringstream oss;
    oss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int main(int arguments, char *arg[])
{
    if (arguments == 4)
    {
        int userID = stoi(arg[1]);
        string toexchangeCurrency = arg[2];
        double exchangedAmount = stod(arg[3]);
        string time = currentDateTime();
        ofstream exchangeHistoryFile;
        exchangeHistoryFile.open("exchangeHistory.txt", ios::app);
        if (exchangeHistoryFile.is_open())
        {
            exchangeHistoryFile << userID << '|' << toexchangeCurrency << '|' << fixed << setprecision(0) << exchangedAmount << '|' << time << endl;
            exchangeHistoryFile.close();
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -6; // no of arguments is not correct
    }

    return 0;
}
