#include "auth.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
  return 0 => if function execution successfull i.e required action done.
  return -1 => if file opening error!
  return 2 => if invalid email or password for signin
  return 3 => if passwords doesn't matched in signup
  return 4 => if account already exists
  return 5 => if unexpected behavoir
*/

struct userCredentials
{
    string userName, email, passWord, confirmPassword;
};

int signIn(string enteredEmail, string enteredPassword)
{
    userCredentials user;
    user.email = enteredEmail;
    user.passWord = enteredPassword;

    ifstream readfile;
    string line;
    bool userFound = false;
    readfile.open("users.txt");
    if (readfile.is_open())
    {
        while (getline(readfile, line))
        {
            string name, email, password;
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, email, '|');
            getline(ss, password, '|');

            if (email == user.email && password == user.passWord)
            {
                userFound = true;
                return 0; // if sigin is successful!
            }
        }
        readfile.close();
    }
    else
    {
        return -1; // if file opening error!
    }
    if (!userFound)
    {
        return 2; // if entered creds does not match !
    }
    return 5; // unexpected behaviour
}

int uidGenerator()
{
    int lastUid = 0;
    ifstream file;
    file.open("users.txt");
    if (file.is_open())
    {
        string readLine;
        while (getline(file, readLine))
        {
            if (readLine.empty())
            {
                continue;
            }
            int uid;
            char seperater;
            stringstream ss(readLine);
            ss >> uid >> seperater;
            if (uid > lastUid)
            {
                lastUid = uid;
            }
        }
        file.close();
        return lastUid + 1;
    }
    else
    {
        return -1; // file opening error
    }
    return 0;
}

int signUp(string enteredName, string enteredEmail, string enteredPassword, string enteredConfirmPassword)
{
    userCredentials user;
    user.email = enteredEmail;
    user.passWord = enteredPassword;
    user.confirmPassword = enteredConfirmPassword;
    user.userName = enteredName;
    int newUid = uidGenerator();

    if (user.passWord != user.confirmPassword)
    {
        return 3; // if Passwords doesn't matched!
    }

    ifstream readfile;
    string line;
    bool userFound = false;
    readfile.open("users.txt");
    if (readfile.is_open())
    {
        while (getline(readfile, line))
        {
            string name, email, password;
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, email, '|');
            getline(ss, password, '|');

            if (email == user.email)
            {
                userFound = true;
                return 4; // if Account already exists
            }
        }
        readfile.close();
    }
    else
    {
        return -1; // if File opening error!
    }

    if (!userFound)
    {
        ofstream file;
        file.open("users.txt", ios::app);
        if (file.is_open())
        {
            file << newUid << "|" << user.userName << "|" << user.email << "|" << user.passWord << endl;
            file.close();
            return 0; //  if Sign Up successfull!";
        }
        else
        {
            return -1; // File opening error!
        }
    }
    return 5; // unexpected behaviour
}