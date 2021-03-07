#include "CommandLineInterface.h"
#include "Parsing.h"
#include "CLIException.h"
#include <iostream>

using namespace std;

void CommandLineInterface::parseCommand()
{
	string s;
	getline(cin, s);
	string command = splitBy(" ", s);
	//TODO: add particular commands parsing call
}

void CommandLineInterface::parseLogin(string s)
{
	if (s.empty())
	{
		cout << "enter username" << endl;
		getline(cin, s);
		username = splitBy(" ", s);
	}
	else
	{
		username = splitBy(" ", s);
	}
	if (!correctName(username)) throw CLIException("incorrect username: " + username);
	string password;
	if (s.empty())
	{
		cout << "enter password" << endl;
		getline(cin, s);
		password = splitBy(" ", s);
	}
	else
	{
		password = splitBy(" ", s);
	}
	if (!s.empty()) throw CLIException("illegal parameter(s): " + s);
}

void CommandLineInterface::callLogin()
{
	currentLoginID = db.checkPassword(username, password);
	password = "";
	if (currentLoginID == -1) throw CLIException("Login/password incorrect");
	DynamicArray<string> chatmsgs = db.getChatMessages();
	cout << "chat messages:" << endl;
	for (int i = 0; i < chatmsgs.getSize(); ++i)
	{
		cout << chatmsgs[i] << endl;
	}
	cout << "---" << endl;

}

void CommandLineInterface::callLogout()
{
	currentLoginID = -1;
	username = "";
}

bool CommandLineInterface::correctName(string s)
{
	if (s.empty()) return false;
	if (!isLetter(s[0])) return false;
	for (string::iterator it = s.begin(); it != s.end(); ++it)
	{
		char c = (*it);
		if ((!isDigit(c)) && (!isLetter(c)) && (c != '_')) return false;
	}
	return true;
}