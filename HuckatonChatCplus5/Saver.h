#pragma once
#include <fstream>

template <typename T>
class Saver
{
	ofstream _descriptor;
public:
	Saver(string filename) : _descriptor(filename, ofstream::binary)
	{	}
	void write(const T& obj)
	{
		char* bytes = (char*)&obj;
		int size = sizeof(obj);
		char* sizebytes = (char*)&size;
		_descriptor.write(sizebytes, sizeof(size));
		_descriptor.write(bytes, size);
	}
	~Saver()
	{
		_descriptor.close();
	}
};