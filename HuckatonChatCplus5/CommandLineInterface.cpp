#include "CommandLineInterface.h"
#include "CLIException.h"
#include "Parsing.h"
#include "Database.h"
#include <iostream>
#include <string>

using namespace std;

void CommandLineInterface::parseCommand()
{
	string s;
	if(_currentLoginID != -1)
	{
		cout << "[" << _username << "] ";
		getline(cin, s);
	}
	else getline(cin, s);
	if (startWith("!", s))
	{
		string command = splitBy(" ", s);
		if (command == "!login")
		{
			parseLogin(s);
			if (!s.empty()) throw CLIException("illegal parameter(s): " + s);
			callLogin();
			showCountPM(_username);
			showChatMsgs();
		}
		else if (command == "!logout")
		{
			if (!s.empty()) throw CLIException("illegal parameter(s): " + s);
			if (_currentLoginID == -1) throw CLIException("already logged out");
			callLogout();
		}
		else if (command == "!exit")
		{
			if (!s.empty()) throw CLIException("illegal parameter(s): " + s);
			callExit();
		}
		else if (command == "!register")
		{
			parseLogin(s);
			if (!s.empty()) throw CLIException("illegal parameter(s): " + s);
			callRegister();
			showChatMsgs();
		}
		else if (command == "!pm")
		{
			if (_currentLoginID == -1) throw CLIException("Please log in to write to other users!");
			parsePM(s);
			callPM(s);
		}
		else if (command == "!getPM")
		{
			if (_currentLoginID == -1) throw CLIException("Please log in to receive messages!");
			parseGetPM();
			callGetPM();
		}
		else throw CLIException("unknown command: " + command);
	}
	else
	{
		if (_currentLoginID == -1) throw CLIException("Please log in to write to the chat!");
		if (!s.empty())
		{
			_db.addChatMessage(_username, s);
			cout << "<" << _username << "> : " << s << endl;
		}
	}
}

void CommandLineInterface::parseLogin(string& s)
{
	if (s.empty())
	{
		cout << "enter username" << endl;
		getline(cin, s);
		_username = splitBy(" ", s);
	}
	else
	{
		_username = splitBy(" ", s);
	}
	if (!correctName(_username)) throw CLIException("incorrect username: " + _username);
	if (s.empty())
	{
		cout << "enter password" << endl;
		getline(cin, s);
		_password = splitBy(" ", s);
	}
	else
	{
		_password = splitBy(" ", s);
	}
}

void CommandLineInterface::parsePM(string& s)
{
	if (startWith("(", s))
	{
		skipuntil("(", s);
		string target = splitBy(")", s);
		if (!correctName(target))
		{
			throw CLIException("incorrect user name " + target);
		}
		_PMTarget = target;
	}
	else
	{
		string target;
		cout << "enter user name who received message" << endl;
		getline(cin, target);
		if (!correctName(target))
		{
			throw CLIException("incorrect user name " + target);
		}
		_PMTarget = target;
	}
}

void CommandLineInterface::parseGetPM()
{
	//TODO можно что нибудь придумать
}

void CommandLineInterface::callRegister()
{
	_currentLoginID = _db.addUser(_username, _password);
	_password = "";
}

void CommandLineInterface::callLogin()
{
	_currentLoginID = _db.checkPassword(_username, _password);
	_password = "";
	if (_currentLoginID == -1) throw CLIException("Login/password incorrect");
}

void CommandLineInterface::callLogout()
{
	_currentLoginID = -1;
	_username = "";
}

void CommandLineInterface::callExit()
{
	_exit = true;
}

void CommandLineInterface::callPM(string message)
{
	_db.addPrivateMessage(_username, _PMTarget, message);
}

void CommandLineInterface::callGetPM()
{
	DynamicArray<Message> msgs = _db.getPrivateMessage(_username);
	cout << "private messages:" << endl;
	for (int i = 0; i < msgs.getSize(); ++i)
	{
		cout << "<" << msgs[i].getWriter() << ">: " << msgs[i].getText() << endl;
	}
	cout << "---" << endl;
}

void CommandLineInterface::showChatMsgs()
{
	DynamicArray<string> chatmsgs = _db.getChatMessages();
	cout << "chat messages:" << endl;
	for (int i = 0; i < chatmsgs.getSize(); ++i)
	{
		cout << chatmsgs[i] << endl;
	}
	cout << "---" << endl;
}

bool CommandLineInterface::shouldExit()
{
	return _exit;
}

void CommandLineInterface::showCountPM(string target) {
	DynamicArray<Message> pm = _db.getPrivateMessage(target);
	int countpm = pm.getSize();
	if(countpm)	cout << "You have " << pm.getSize() << " private message." << endl;
}