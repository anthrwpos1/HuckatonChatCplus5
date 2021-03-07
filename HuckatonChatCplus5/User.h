#pragma once
#include <string>

using namespace std;

class User
{
	static int userCounter;
	int _id;
	string _login;
	string _username;
	long long _passwordHash;
public:
	User();
	User(string username, long long passHash);
	int checklogin(string login, long long passHash);
	string getuserName();
	int getUserID();
};

long long getHash(string);