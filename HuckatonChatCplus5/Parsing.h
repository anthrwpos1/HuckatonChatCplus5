#pragma once
#include <string>

using namespace std;

/*
  ���������, ��� ������ ���������� � �������
*/
bool startWith(string tmpl, string& s);

/*
  ���������, ��� ������ ���������� � �������
  ������ ��� c-style ������ (����� ��� ����������� ������ �������)
*/
bool startWith(string tmpl, const char* s);

/*
  ������� ������� ������� � ������� ����������� ������. ���������� -1 ���� ������� ���.
*/
int findFirst(string tmpl, string& s);

/*
  ����� ������ �� ��������� �� ������� (������� ����������) � ����� (�� ������� �������� ���������� �� ������)
*/
string splitBy(string tmpl, string& s);

/*
  ������� ������ �� �������. ��� ������������ ������� ������ ���������.
*/
void skipuntil(string tmpl, string& s);

/*
  ���������� ������� ������ �� ������� from �� ������� to
*/
string segment(string from, string to, string s);