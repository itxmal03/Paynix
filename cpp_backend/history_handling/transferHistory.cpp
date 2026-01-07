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
    if (arguments == 7)
    {
        int userID = stoi(arg[1]);
        string transferredCurrency = arg[2];
        string method = arg[3];
        string accountNumber = arg[4];
        string accountHolderName = arg[5];
        double sentAmount = stod(arg[6]);
        string time = currentDateTime();
        ofstream transferHistoryFile;
        transferHistoryFile.open("transferHistory.txt", ios::app);
        if (transferHistoryFile.is_open())
        {
            transferHistoryFile << userID << '|' << transferredCurrency << '|' << method << '|' << accountNumber << '|' << accountHolderName << '|' << fixed << setprecision(0) << sentAmount << '|' << time << endl;
            transferHistoryFile.close();
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
