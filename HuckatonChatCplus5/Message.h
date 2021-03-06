#pragma once
#include <string>

class Message
{
	static int messageCounter;
	int id;
	int writerID;
	int targetID;
	std::string text;
public:
	Message(int writer, std::string text);//��������� � ���
	Message(int writer, int target, std::string text);//������ ���������
	bool searchByTarget(int);
	bool searchByWriter(int);
	int getWriter();
	std::string getText();
};