#include "Message.h"
int Message::num = 0;
int Message::messageCounter = 0;
//сообщение в чат
Message::Message() : _id(num), _writer(""), _targetID(0), _text("") 
{
} 
Message::Message(std::string writer, std::string text) : _id(++num), _writer(writer), _targetID(-1), _text(text)
{   
    messageCounter++;
}
//личное сообщение
Message::Message(std::string writer, int target, std::string text) : _id(++num), _writer(writer), _targetID(target), _text(text)
{
    messageCounter++;
}

bool Message::searchByTarget(int n) {
    return (_targetID == n); 
}

std::string Message::getWriter() {
    return _writer;
}

int Message::getTarget() {
    return _targetID;
}

std::string Message::getText() {
    return _text;
}

int Message::getID() {
    return _id;
}