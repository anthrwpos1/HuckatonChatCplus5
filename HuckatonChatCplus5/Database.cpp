#include "Database.h"
#include "ChatException.h"
#include "Parsing.h"
#include "Saver.h"
#include "Loader.h"
#include <memory>

//#include <iostream>

int Database::searchUserByName(string username)
{
	int size = _users.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (_users[i].getuserName() == username) return _users[i].getUserID();
	}
	throw ChatException("user " + username + " doesn't exists");
	return -1;
}

string Database::searchUserByID(int userID)
{
	int size = _users.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (_users[i].getUserID() == userID) return _users[i].getuserName();
	}
	throw ChatException("user doesn't exists");
	return "";
}

Database::Database() : _users(DynamicArray<User>()), _messages(DynamicArray<Message>())
{
	Loader<int> counters("statics.bin");
	int *temp = nullptr;
	if (counters.read(temp) > 0) User::setCounter(*temp);
	if (counters.read(temp) > 0) Message::setCounter(*temp);
	Loader<User> users("users.bin");
	User *utemp = nullptr;
	while (users.read(utemp) > 0) _users.put(*utemp);
	Loader<Message> messages("messages.bin");
	Message *mtemp = new Message();
	while (messages.read(mtemp) > 0) _messages.put(*mtemp);
}

int Database::addUser(string username, string password)
{
	if (!correctName(username)) throw ChatException("incorrect username " + username);
	int size = _users.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (_users[i].getuserName() == username) throw ChatException("user with name " + username + " already exists");
	}
	User newUser = User(username, getHash(password));
	_users.put(newUser);
	return newUser.getUserID();
}

int Database::checkPassword(string username, string password)
{
	int result = -1;
	int size = _users.getSize();
	long long passHash = getHash(password);
	for (int i = 0; i < size; ++i)
	{
		result = _users[i].checklogin(username, passHash);
		if (result != -1) return result;
	}
	return result;
}

void Database::addChatMessage(string sender, string text)
{
	_messages.put(Message(sender, text));
}

void Database::addPrivateMessage(string sender, string target, string message)
{
	int targetID = searchUserByName(target);
	_messages.put(Message(sender, targetID, message));
}

DynamicArray<string> Database::getChatMessages()
{
	DynamicArray<string> strings = DynamicArray<string>();
	int size = _messages.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (_messages[i].getDest() == -1)
		{
			strings.put("<" + _messages[i].getSender() + ">: " + _messages[i].getText());
		}
	}
	return strings;
}

DynamicArray<Message> Database::getPrivateMessage(int userID)
{
	DynamicArray<Message> strings = DynamicArray<Message>();
	int size = _messages.getSize();
	//int userID = searchUserByName(username);
	for (int i = 0; i < size; ++i)
	{
		if (_messages[i].getDest() == userID) strings.put(_messages[i]);
	}
	return strings;
}

void Database::saveState()
{
	Saver<int> counters("statics.bin");
	counters.write(User::getCounter());
	counters.write(Message::getCounter());
	Saver<User> users("users.bin");
	int size = _users.getSize();
	for (int i = 0; i < size; ++i)
	{
		users.write(_users[i]);
	}
	Saver<Message> messages("messages.bin");
	size = _messages.getSize();
	for (int i = 0; i < size; ++i)
	{
		messages.write(_messages[i]);
	}
}