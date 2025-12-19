#ifndef AUTH_H
#define AUTH_H

#include <iostream>
using namespace std;

int signUp(string enteredName, string enteredEmail, string enteredPassword, string confimPassWord);
int signIn(string enteredEmail, string passWord);
int uidGenerator();

#endif