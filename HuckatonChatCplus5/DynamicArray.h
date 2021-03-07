#pragma once
#include <exception>

template <typename T>
class DynamicArray
{
private:
	const int initialSize = 2;
	T* _array;
	int _size;
	int _lastElement;
	void resize(int newsize)//увеличить размер хранилища
	{
		T* newArray = new T[newsize];
		for (int i = 0; i < _size; ++i)
		{
			newArray[i] = _array[i];
		}
		delete[] _array;
		_array = newArray;
		_size = newsize;
	}
public:
	DynamicArray() : _array(new T[initialSize]), _size(initialSize), _lastElement(0)
	{}

	DynamicArray(const DynamicArray& other) : _array(new T[other._size]), _size(other._size), _lastElement(other._lastElement)
	{
		for (int i = 0; i < _lastElement; ++i)
		{
			_array[i] = other._array[i];
		}
	}

	DynamicArray(DynamicArray&& other) : _array(other._array), _size(other._size), _lastElement(other._lastElement)
	{
		other._array = nullptr;
		other._size = 0;
		other._lastElement = 0;
	}

	DynamicArray& operator=(const DynamicArray& other) = delete;

	DynamicArray& operator=(const DynamicArray&& other) = delete;

	void put(T element)
	{
		if (_lastElement == _size) resize(_size + _size / 2);
		_array[_lastElement++] = element;
	}

	T& operator[](int index)
	{
		if (index >= _lastElement) throw std::exception("out of bound");
		return _array[index];
	}

	int getSize()
	{
		return _lastElement;
	}

	~DynamicArray()
	{
		if (_size) delete[] _array;
	}
};