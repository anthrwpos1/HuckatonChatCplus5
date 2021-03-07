#pragma once
#include <string>

class Message
{
	static int num;		//���������� �����, ������� �������� id
	static int messageCounter;
	int _id;
	std::string _writer;
	int _targetID;
	std::string _text;
public:
	Message();
	Message(std::string writer, std::string text);//��������� � ���
	Message(std::string writer, int target, std::string text);//������ ���������

	bool searchByTarget(int);
	std::string getWriter();
	int getTarget();
	int getID();
	std::string getText();

};