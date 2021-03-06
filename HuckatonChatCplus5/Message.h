#pragma once
#include <string>

class Message
{
	static int num;		//уникальный номер, который получает id
	static int messageCounter;
	int id;
	int writerID;
	int targetID;
	std::string text;
public:
	Message();
	Message(int writer, std::string text);//сообщение в чат
	Message(int writer, int target, std::string text);//личное сообщение

	bool searchByTarget(int);
	bool searchByWriter(int);
	int getWriter();
	int getTarget();
	int getID();
	std::string getText();

};