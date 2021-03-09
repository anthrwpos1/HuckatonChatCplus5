#pragma once
#include <fstream>

class Saver
{
	ofstream _descriptor;
	bool _staticSegment;
	const char* ds = "Dynamic segment";
	const char* ss = "Static segment-";
public:
	Saver(string filename) : _descriptor(filename, ofstream::binary), _staticSegment(false)
	{	}
	/*
		�������� ������ ���������� �����
		���������� ������-������ ������������� ��������
		��� �������� ����������� ������ ��� ������
		����� �����-����� ������ � ���� ������.
	*/
	template <typename T>
	void writeDynamic(const T& obj)
	{
		_staticSegment = false;
		char* bytes = (char*)&obj;
		int size = sizeof(obj);
		char* sizebytes = (char*)&size;
		_descriptor.write(ds, 16);
		_descriptor.write(sizebytes, sizeof(size));
		_descriptor.write(bytes, size);
	}
	/*
		�������� ������ ������������ �����
		��� ������ ������ ���������� �����-������ ������������ ��������
		��� �������� ����������� ������ ��� ������
		����� ������ ��� ������������ - ���� ������
	*/
	template <typename T>
	void writeStatic(const T& obj)
	{
		char* bytes = (char*)&obj;
		int size = sizeof(obj);
		if (!_staticSegment)
		{
			_descriptor.write(ss, 16);
			_staticSegment = true;
		}
		_descriptor.write(bytes, size);
	}
	~Saver()
	{
		_descriptor.close();
	}
};