#pragma once
#include <string>

using namespace std;

/*
  проверяет, что строка начинается с шаблона
*/
bool startWith(string tmpl, string& s);

/*
  проверяет, что строка начинается с шаблона
  версия для c-style строки (нужно для оптимизации других функций)
*/
bool startWith(string tmpl, const char* s);

/*
  находит позицию начиная с которой встречается шаблон. Возвращает -1 если шаблона нет.
*/
int findFirst(string tmpl, string& s);

/*
  делит строку на подстроку до шаблона (которую возвращает) и после (до которой обрезает переданную по ссылке)
*/
string splitBy(string tmpl, string& s);

/*
  удаляет строку до шаблона. При несовпадении очищает строку полностью.
*/
void skipuntil(string tmpl, string& s);

/*
  возвращает участок строки от шаблона from до шаблона to
*/
string segment(string from, string to, string s);