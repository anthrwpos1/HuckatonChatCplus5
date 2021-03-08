#include "Message.h"
int Message::num = 0;
//сообщение в чат
Message::Message() : _id(num), _sender(""), _destID(0), _text("") 
{
} 
Message::Message(std::string writer, std::string text) : _id(++num), _sender(writer), _destID(-1), _text(text)
{	}

//личное сообщение
Message::Message(std::string writer, int target, std::string text) : _id(++num), _sender(writer), _destID(target), _text(text)
{	}

bool Message::searchByTarget(int n) {
    return (_destID == n); 
}

std::string Message::getSender() {
    return _sender;
}

int Message::getDest() {
    return _destID;
}

std::string Message::getText() {
    return _text;
}

int Message::getCounter()
{
	return num;
}

void Message::setCounter(int x)
{
	num = x;
}

int Message::getID() {
    return _id;
}