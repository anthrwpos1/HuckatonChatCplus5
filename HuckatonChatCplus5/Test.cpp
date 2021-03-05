#include <iostream>
#include <string>
#include "DynamicArray.h"
#include "Parsing.h"

using namespace std;

bool commandProcessing();
bool correctName(string s);
bool isLetter(char c);
bool isDigit(char c);

int main()
{
	cout << "chat ver. 0.03" << endl;
	while (true)
	{
		try
		{
			if (!commandProcessing()) break;
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}

bool commandProcessing()
{
	string s;
	getline(cin, s);
	string command = splitBy(" ", s);
	if (command == "logout")
	{
		if (s.empty())
		{
			cout << "logged out!" << endl;
			return true;
		}
		else
		{
			string info = "illegal parameter(s): " + s;
			throw exception(info.c_str());
		}
	}
	if (command == "login")
	{
		string username;
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
		if (!correctName(username))
		{
			string info = "incorrect username: " + username;
			throw exception(info.c_str());
		}
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
		if (s.empty())
		{
			cout << "logged in as " << username << " and password " << password << endl;
			return true;
		}
		else
		{
			string info = "illegal parameter(s): " + s;
			throw exception(info.c_str());
		}
	}
	if (command == "exit") return false;
	string info = "unknown command: " + command;
	throw exception(info.c_str());
}

bool correctName(string s)
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

bool isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}

bool isLetter(char c)
{
	return (c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z');
}