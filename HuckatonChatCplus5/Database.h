#pragma once
#include "DynamicArray.h"
#include "User.h"
#include "Message.h"
#include <string>

class Database
{
	DynamicArray<User> _users;
	DynamicArray<Message> _messages;
	int searchUserByName(string);
	string searchUserByID(int);
public:
	Database();
	int addUser(string username, string password);
	void deleteUser(string);
	int checkPassword(string username, string password);
	void addChatMessage(string sender, string);
	void addPrivateMessage(string sender, string target, string message);
	DynamicArray<string> getChatMessages(int num);//показать num последних сообщений
	DynamicArray<string> getChatMessages();//показать все сообщения
	DynamicArray<Message> getPrivateMessage(string username);//показать личные сообщения пользователю username
};