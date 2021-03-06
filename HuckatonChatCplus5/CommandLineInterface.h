#pragma once
#include <string>
#include "Database.h"

using namespace std;

class CommandLineInterface
{
	int currentLoginID = -1;
	string username = "";
	string password;
	Database db;
	bool correctName(string s);
public:
	void parseCommand();
	void parseLogin(string);
	void callLogin();
	void callLogout();
};