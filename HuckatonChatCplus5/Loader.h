#pragma once
#include <fstream>

template <typename T>
class Loader
{
	ifstream _descriptor;
	void* _tempobject;
	int _tosize;
public:
	Loader(string filename) : _descriptor(filename, ofstream::binary), _tempobject(NULL), _tosize(0)
	{	}
	void seekfromEnd(int pos)
	{
		_descriptor.seekg(pos, ifstream::end);
	}
	void seekfromBeg(int pos)
	{
		_descriptor.seekg(pos, ifstream::beg);
	}
	long getSize()
	{
		long cur = _descriptor.tellg();
		_descriptor.seekg(0, ifstream::end);
		long size = _descriptor.tellg();
		_descriptor.seekg(cur, ifstream::beg);
		return size;
	}
	int read(T*& obj)
	{
		int size = 0;
		char* sizeBytes = (char*)&size;
		obj = nullptr;
		_descriptor.read(sizeBytes, sizeof(size));
		if (_descriptor.tellg() == -1) return 0;
		if (!_tempobject)
		{
			_tempobject = malloc(size);
			_tosize = size;
		}
		if (size > _tosize)
		{
			_tempobject = realloc(_tempobject, size);
			_tosize = size;
		}
		char* bytes = (char*) _tempobject;
		if (_descriptor.tellg() == -1)
		{
			return -1;
		}
		_descriptor.read(bytes, size);
		obj = (T*)bytes;
		return size;
	}
	~Loader()
	{
		_descriptor.close();
		free(_tempobject);
	}
};