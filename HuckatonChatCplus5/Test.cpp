#include <iostream>
#include <string>
#include "DynamicArray.h"
#include "Parsing.h"

using namespace std;

int main()
{
	string s = "newstring";
	cout << segment("w", "ing", s) << endl;
	cout << s << endl;
	return 0;
}