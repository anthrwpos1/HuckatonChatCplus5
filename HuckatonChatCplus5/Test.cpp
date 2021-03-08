#include <iostream>
#include "CommandLineInterface.h"

using namespace std;

int main()
{
	CommandLineInterface cli{};
	cout << "chat ver. 1.0" << endl;
	while (!cli.shouldExit())
	{
		try
		{
			cli.parseCommand();
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}