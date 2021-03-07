#pragma once
#include <string>
#include "Database.h"

using namespace std;

class CommandLineInterface
{
	int _currentLoginID = -1;
	string _username = "";
	string _password;
	Database _db;
	bool _exit = false;
public:
	void parseCommand();
	void parseLogin(string&);
	void callRegister();
	void callLogin();
	void callLogout();
	void callExit();
	void showChatMsgs();
	bool shouldExit();
};