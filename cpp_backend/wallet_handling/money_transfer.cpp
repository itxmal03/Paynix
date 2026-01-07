#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

double transactionFee(bool type, double amountToTransfer);

int main(int arguments, char *arg[])
{
    if (arguments == 4)
    {
        bool pkrBalanceTransfer = false;
        int userID = stoi(arg[1]);
        int balanceType = stoi(arg[2]);
        if (balanceType == 1)
        {
            pkrBalanceTransfer = true;
        }
        double amountToBeTransferred = stod(arg[3]);

        ifstream readWalletFile;
        vector<string> linesV;
        string line;
        readWalletFile.open("wallet.txt");

        if (readWalletFile.is_open())
        {
            while (getline(readWalletFile, line))
            {
                linesV.push_back(line);
            }

            for (string &x : linesV)
            {
                int uid;
                char separator;
                double totalPkrBalance, totalUsdBalance;
                stringstream ss(x);
                ss >> uid >> separator >> totalPkrBalance >> separator >> totalUsdBalance;

                if (uid == userID)
                {
                    if (pkrBalanceTransfer)
                    {
                        double fee = transactionFee(true, amountToBeTransferred);

                        if ((amountToBeTransferred + fee) <= totalPkrBalance)
                        {
                            totalPkrBalance = totalPkrBalance - amountToBeTransferred - fee;

                            ostringstream oss;
                            oss << uid << '|' << fixed << setprecision(1)
                                << totalPkrBalance << '|' << setprecision(1)
                                << totalUsdBalance;
                            x = oss.str();
                            break;
                        }
                        else
                        {
                            return -7; // insufficient balance
                        }
                    }
                    else 
                    {
                        double fee = transactionFee(false, amountToBeTransferred);

                        if ((amountToBeTransferred + fee) <= totalUsdBalance)
                        {
                            totalUsdBalance = totalUsdBalance - amountToBeTransferred - fee;

                            ostringstream oss;
                            oss << uid << '|' << fixed << setprecision(1)
                                << totalPkrBalance << '|' << setprecision(1)
                                << totalUsdBalance;
                            x = oss.str();
                            break;
                        }
                        else
                        {
                            return -7; // insufficient balance
                        }
                    }
                }
            }

            readWalletFile.close();
        }

        ofstream rewriteWalletFile;
        rewriteWalletFile.open("wallet.txt", ios::trunc);
        if (rewriteWalletFile.is_open())
        {
            for (string x : linesV)
            {
                rewriteWalletFile << x << endl;
            }
            rewriteWalletFile.close();
        }
        else
        {
            return -1; // file opening error
        }
    }
    else
    {
        return -6; // number of arguments is not correct
    }

    return 0;
}

double transactionFee(bool type, double amountToTransfer)
{
    if (type)
    {
        if (amountToTransfer < 5000)
        {
            return 0;
        }
        else if (amountToTransfer < 10000)
        {
            return 10;
        }
        else if (amountToTransfer < 100000)
        {
            return 100;
        }
        else if (amountToTransfer < 1000000)
        {
            return 500;
        }
        else if (amountToTransfer < 10000000)
        {
            return 1000;
        }
        else if (amountToTransfer < 100000000)
        {
            return 2000;
        }
    }
    else
    {
        if (amountToTransfer < 50)
        {
            return 0;
        }
        else if (amountToTransfer < 100)
        {
            return 3;
        }
        else if (amountToTransfer < 100000)
        {
            return 10;
        }
        else if (amountToTransfer < 1000000)
        {
            return 50;
        }
        else if (amountToTransfer < 10000000)
        {
            return 100;
        }
        else if (amountToTransfer < 100000000)
        {
            return 200;
        }
    }
    return 0;
}
