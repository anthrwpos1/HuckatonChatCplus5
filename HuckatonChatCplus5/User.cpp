#include "User.h"

int User::userCounter = 1;

User::User() : _id(0), _login(""), _username(""), _passwordHash(0)
{
}

User::User(string username, long long passHash) :_login(username), _username(username), _passwordHash(passHash), _id(++userCounter)
{
}

int User::checklogin(string login, long long passHash)
{
	if ((_login == login) && (_passwordHash == passHash)) return _id;
	return -1;
}

string User::getuserName()
{
	return _username;
}

int User::getUserID()
{
	return _id;
}

//закос под хеш-функцию
long long getHash(string text)
{
	long long result = 0x8888888888888888LL;
	for (string::iterator it = text.begin(); it != text.end(); ++it)
	{
		result *= *it;
	}
	return result;
}