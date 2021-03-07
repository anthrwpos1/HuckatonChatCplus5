#include "Message.h"
int Message::num = 0;
int Message::messageCounter = 0;
//сообщение в чат
Message::Message() : id(num), writerID(0), targetID(0), text("") 
{
} 
Message::Message(int writer, std::string text) : id(++num), writerID(writer), targetID(-1), text(text)
{   
    messageCounter++;
}
//личное сообщение
Message::Message(int writer, int target, std::string text) : id(++num), writerID(writer), targetID(target), text(text)
{
    messageCounter++;
}

bool Message::searchByTarget(int n) {
    return (targetID == n); 
}

bool Message::searchByWriter(int n) {
    return (writerID == n); 
}

int Message::getWriter() {
    return writerID;
}

int Message::getTarget() {
    return targetID;
}

std::string Message::getText() {
    return text;
}

int Message::getID() {
    return id;
}