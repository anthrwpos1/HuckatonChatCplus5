#include "Database.h"
#include "ChatException.h"
#include "Parsing.h"
#include "Saver.h"
#include "Loader.h"
#include <memory>

#include <iostream>

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
	try 
	{
		Loader loader("data.bin");													//открываем файл
		int temp = 0;
		int size = 0;
		if (loader.readStatic(temp) > 0) User::setCounter(temp);					//вычитываем статические переменные
		else throw ChatException("user counter not loaded, using defaults");
		if (loader.readStatic(temp) > 0) Message::setCounter(temp);
		else throw ChatException("message counter not loaded, using defaults");
		if (loader.readStatic(temp) > 0) size = temp;								//вычитываем число юзеров
		else throw ChatException("users num not loaded, using defaults");
		User *utemp = nullptr;
		for (int i = 0; i < size; ++i)
		{
			if (loader.readDynamic(utemp) > 0) _users.put(*utemp);					//вычитываем самих юзеров
			else throw ChatException("error loading user, using defaults");
		}
		if (loader.readStatic(temp) > 0) size = temp;								//вычитываем число сообщений
		else throw ChatException("messages num not loaded, using defaults");
		Message *mtemp = nullptr;
		for (int i = 0; i < size; ++i)
		{
			if (loader.readDynamic(mtemp) > 0) _messages.put(*mtemp);				//вычитываем сами сообщения
			else throw ChatException("error loading messages, using defaults");
		}
	}
	catch (ChatException e)						//если на каком-то этапе что-то не получилось, инициализируем пустой чат
	{
		std::cout << e.what() << std::endl;		//выводим что не получилось
		User::setCounter(1);
		Message::setCounter(0);
		_users = DynamicArray<User>();
		_messages = DynamicArray<Message>();
	}
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
			strings.put("<" + _messages[i].getSender() + ">:" + _messages[i].getText());
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
	Saver saver("data.bin");					//открываем файл
	saver.writeStatic(User::getCounter());		//записываем статические переменные
	saver.writeStatic(Message::getCounter());
	int size = _users.getSize();				//записываем число юзеров
	saver.writeStatic(size);
	for (int i = 0; i < size; ++i)
	{
		saver.writeDynamic(_users[i]);			//записываем самих юзеров
	}
	size = _messages.getSize();					//записываем число сообщений
	saver.writeStatic(size);
	for (int i = 0; i < size; ++i)
	{
		saver.writeDynamic(_messages[i]);		//записываем сами сообщения
	}
}