#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main()
{
	DynamicArray<float> test = DynamicArray<float>();
	try {
		for (int i = 0; i < 2000000; ++i)
		{
			float arg = (i - 1000000.0) / 1000000.0;
			test.put(exp(-arg * arg));
		}
		cout << test[1000000] << " " << test.getSize();
	}
	catch (exception &e)
	{
		e.what();
	}
	catch (...)
	{
		cout << "unkn error" << endl;
	}
	return 0;
}