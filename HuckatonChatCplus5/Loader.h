#pragma once
#include <fstream>
template <typename T>
class Loader
{
	ifstream _descriptor;
	void* _tempobject;		//место в куче для временного хранения вычитываемого объекта
	int _tosize;
public:
	Loader(string filename) : _descriptor(filename, ofstream::binary), _tempobject(NULL), _tosize(0)//открытие файла
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
	/*
	  функция загрузки объекта из файла. Возвращает по ссылке указатель 
	  на участок памяти выделенный под временное хранение загружаемых объектов.
	  Объект полученный по этой ссылке должен быть скопирован для постоянного
	  использования в другое место, так как при последующем чтении по этому-же
	  адресу будут записаны другие объекты, а при уничтожении объекта загрузчика
	  указатель станет невалиден.
	*/
	int read(T*& obj)
	{
		int size = 0;
		char* sizeBytes = (char*)&size;
		obj = nullptr;
		_descriptor.read(sizeBytes, sizeof(size));	//вычитываем размер объекта
		if (_descriptor.tellg() == -1) return 0;	//дескриптор становится -1 при ошибках чтения
		if (!_tempobject)
		{
			_tosize = size + size / 2;
			_tempobject = malloc(_tosize);			//если память еще не выделена - выделяем, с запасом, чтобы лишний раз не перевыделять
			
		}
		if (size > _tosize)
		{
			_tosize = size + size / 2;
			_tempobject = realloc(_tempobject, _tosize);	//если объект оказался больше выделенного ранее места - перевыделяем (тоже с запасом)
		}
		char* bytes = (char*) _tempobject;
		_descriptor.read(bytes, size);						//читаем объект
		if (_descriptor.tellg() == -1)
		{
			return -1;
		}
		obj = (T*)bytes;
		return size;
	}
	~Loader()
	{
		_descriptor.close();
		free(_tempobject);
	}
};