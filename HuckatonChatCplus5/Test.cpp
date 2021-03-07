#include <iostream>
#include <string>
#include "DynamicArray.h"
#include "Parsing.h"

using namespace std;

bool commandProcessing();
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
		
	}
	if (command == "exit") return false;
	string info = "unknown command: " + command;
	throw exception(info.c_str());
}