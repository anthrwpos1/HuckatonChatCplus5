#pragma once
#include "DynamicArray.h"
#include "User.h"
#include "Message.h"
#include <string>

class Database
{
	DynamicArray<User> users;
	DynamicArray<Message> messages;
public:
	Database();
	void addUser(string username, string password);
	void deleteUser(string);
	bool checkPassword(string username, string password);
	void addChatMessage(string);
	void addPrivateMessage(string sender, string target, string message);
	DynamicArray<Message> getChatMessages(int num);//показать num последних сообщений
	DynamicArray<Message> getChatMessages();//показать все сообщения
	DynamicArray<Message> getPrivateMessage(string username);//показать личные сообщения пользователю username
};