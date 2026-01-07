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
    if (arguments == 6)
    {
        int userID = stoi(arg[1]);
        string balanceType = arg[2];
        double balanceToAdd = stod(arg[3]);
        string method = arg[4];
        string tid = arg[5];
        string time = currentDateTime();
        ofstream addBalanceFile;
        addBalanceFile.open("addBalanceHistory.txt", ios::app);
        if (addBalanceFile.is_open())
        {
            addBalanceFile << userID << '|' << balanceType << '|' << fixed << setprecision(0) << balanceToAdd << '|' << tid << '|' << method << '|' << time << endl;
            addBalanceFile.close();
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
