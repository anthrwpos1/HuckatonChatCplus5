#include "Database.h"
#include "ChatException.h"
#include "Parsing.h"
#include <memory>

int Database::searchUserByName(string username)
{
	int size = _users.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (_users[i].getuserName() == username) return _users[i].getUserID();
	}
	throw ChatException("user " + username + "doesn't exists");
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
	int senderID = searchUserByName(sender);
	_messages.put(Message(senderID, text));
}

void Database::addPrivateMessage(string sender, string target, string message)
{
	int senderID = searchUserByName(sender);
	int targetID = searchUserByName(target);
	_messages.put(Message(senderID, targetID, message));
}

DynamicArray<string> Database::getChatMessages()
{
	DynamicArray<string> strings = DynamicArray<string>();
	int size = _messages.getSize();
	for (int i = 0; i < size; ++i)
	{
		if (_messages[i].getTarget() == -1)
		{
			string senderName = searchUserByID(_messages[i].getWriter());
			strings.put("<" + senderName + ">: " + _messages[i].getText());
		}
	}
	return strings;
}

DynamicArray<Message> Database::getPrivateMessage(string username)
{
	DynamicArray<Message> strings = DynamicArray<Message>();
	int size = _messages.getSize();
	int userID = searchUserByName(username);
	for (int i = 0; i < size; ++i)
	{
		if (_messages[i].getTarget() == userID) strings.put(_messages[i]);
	}
	return strings;
}
