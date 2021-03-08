#pragma once
#include <string>

class Message
{
	static int num;		//���������� �����, ������� �������� id
	static int messageCounter;
	int _id;
	std::string _sender;
	int _destID;
	std::string _text;
public:
	Message();
	Message(std::string writer, std::string text);//��������� � ���
	Message(std::string writer, int target, std::string text);//������ ���������

	bool searchByTarget(int);
	std::string getSender();
	int getDest();
	int getID();
	std::string getText();

};