#pragma once
#include <fstream>
class Loader
{
	ifstream _descriptor;
	void* _tempobject;		//место в куче для временного хранения вычитываемого объекта
	int _tosize;
	int _filesize;
	bool _staticSegment;
	const char* ds = "Dynamic segment";
	const char* ss = "Static segment-";
	const int checkbytes = 16;
public:
	Loader(string filename) : _descriptor(filename, ofstream::binary), _tempobject(NULL), _tosize(0), _staticSegment(false)//открытие файла
	{	
		_descriptor.seekg(0, ifstream::end);
		_filesize = _descriptor.tellg();
		_descriptor.seekg(0, ifstream::beg);
	}
	void seekfromEnd(int pos)
	{
		_descriptor.seekg(pos, ifstream::end);
	}
	void seekfromBeg(int pos)
	{
		_descriptor.seekg(pos, ifstream::beg);
	}
	/*
	  функция загрузки объекта из файла. Возвращает по ссылке указатель 
	  на участок памяти выделенный под временное хранение загружаемых объектов.
	  Объект полученный по этой ссылке должен быть скопирован для постоянного
	  использования в другое место, так как при последующем чтении по этому-же
	  адресу будут записаны другие объекты, а при уничтожении объекта загрузчика
	  указатель станет невалиден.
	*/
	template <typename T>
	int readDynamic(T*& obj)
	{
		_staticSegment = false;
		int size = 0;
		char* sizeBytes = (char*)&size;
		obj = nullptr;
		char test[16];
		_descriptor.read(test, 16);
		if (!check(test, ds)) return -1;
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

	/*
		функция загрузки объекта постоянного размера
		Передает данные по ссылке.
	*/
	template<typename T>
	int readStatic(T& obj)
	{
		int size = sizeof(obj);
		if (!_staticSegment)
		{
			char test[16];
			_descriptor.read(test, 16);
			if (!check(test, ss)) return -1;
			_staticSegment = true;
		}
		char* bytes = (char*)&obj;
		_descriptor.read(bytes, size);						//читаем объект
		if (_descriptor.tellg() == -1)
		{
			return -1;
		}
		return size;
	}
	
	bool check(const char* text1, const char* text2)
	{
		for (int i = 0; i < checkbytes; ++i)
		{
			if (text1[i] != text2[i]) return false;
		}
		return true;
	}

	~Loader()
	{
		_descriptor.close();
		free(_tempobject);
	}
};