#pragma once
#include <string>
#include "Database.h"

using namespace std;

class CommandLineInterface
{
	int _currentLoginID = -1;
	string _username = "";
	string _password;
	string _PMTarget = "";
	Database _db;
	bool _exit = false;
	void parseLogin(string&);
	void parsePM(string&);
	void parseGetPM();
	void callRegister();
	void callLogin();
	void callLogout();
	void callExit();
	void callPM(string);
	void callGetPM();
	void showChatMsgs();
public:
	void parseCommand();
	bool shouldExit();
};