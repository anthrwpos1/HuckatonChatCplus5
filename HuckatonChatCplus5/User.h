#pragma once
#include <string>

using namespace std;

class User
{
	static int userCounter;
	int id;
	string login;
	string username;
	long long passwordHash;
public:
	User(string username, long long passHash);
	bool search(int);
	bool checklogin(string login, long long passHash);
	string getuserName();
};

long long getHash(string);