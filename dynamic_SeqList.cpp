#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<string>

struct __TrueType
{
	bool Get()
	{
		return true;
	}
};

struct __FalseType
{
	bool Get()
	{
		return false;
	}
};

template <class T>
struct TypeTraits
{
	typedef __FalseType   __IsPODType;
};

template <>
struct TypeTraits< bool>
{
	typedef __TrueType     __IsPODType;
};

template <>
struct TypeTraits< char>
{
	typedef __TrueType     __IsPODType;
};

template <>
struct TypeTraits< unsigned char >
{
	typedef __TrueType     __IsPODType;
};

template <>
struct TypeTraits< short>
{
	typedef __TrueType     __IsPODType;
};

template <>
struct TypeTraits< unsigned short >
{
	typedef __TrueType     __IsPODType;
};

template <>
struct TypeTraits<int>
{
	typedef __TrueType __IsPODType;
};

template<class T>
void _Memcpy(T& dest, const T& src, size_t size, __TrueType)	//基本类型
{
	cout << "IsPOD::" << typeid(T).name() << endl;
	memcpy(dest, src, sizeof(T)*size);
}

template<class T>
void _Memcpy(T& dest, const T& src, size_t size, __FalseType)
{
	cout << "IsNotPOD::" << typeid(T).name() << endl;
	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

template<class T>
class SeqList
{
public:
	SeqList()
		:_size(0)
		, _capacity(0)
		, _array(NULL)
	{}

	SeqList<T>(const SeqList<T>& s)
	{
		_array = new T[s._size];
		if (TypeTraits <T>::__IsPODType().Get())
		{
			_Memcpy(_array, s._array, s._size, TypeTraits<T>::__IsPODType());
		}
		else
		{
			_Memcpy(_array, s._array, s._size, TypeTraits<T>::__IsPODType());
		}
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	SeqList<T>& operator= (SeqList<T> s)
	{
		swap(_array, s._array);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
		}
	}

	void _CheckCapacity(size_t n)
	{
		if (n > _capacity)
		{
			_capacity = 2 * _capacity + 3;
			T* tmp = new T[_capacity];
			if (_array != NULL)
			{
				if (TypeTraits <T>::__IsPODType().Get())
				{
					_Memcpy(tmp, _array, _size, TypeTraits <T>::__IsPODType());
				}
				else
				{
					_Memcpy(tmp, _array, _size, TypeTraits <T>::__IsPODType());
				}
			}
			delete[] _array;
			_array = NULL;
			_array = tmp;
		}
	}

	void PushBack(const T& x);
	void PopBack();
	void PrintSeqList();

private:
	size_t _size;
	size_t _capacity;
	T* _array;
};


template<class T>
void SeqList<T>::PushBack(const T& x)
{
	_CheckCapacity(_size + 1);
	_array[_size++] = x;
}

template<class T>
void SeqList<T>::PopBack()
{
	if (_size == 0)
	{
		return;
	}
	else
	{
		--_size;
	}
}

template<class T>
void SeqList<T>::PrintSeqList()
{
	for (int i = 0; i < _size; i++)
	{
		cout << _array[i] << "  ";
	}
	cout << endl;
}


//int的测试函数
//void Test()
//{
//	SeqList<int> s1;
//	s1.PushBack(1);
//	s1.PushBack(2);
//	s1.PushBack(3);
//	s1.PushBack(4);
//	s1.PushBack(5);
//	s1.PrintSeqList();

//  s2.PopBack();
//  s2.PrintSeqList();
//}

//string的测试函数
void Test()
{
	SeqList<string> s2;
	s2.PushBack("hello ");
	s2.PushBack("world ");
	s2.PushBack("I ");
	s2.PushBack("love ");
	s2.PushBack("IT");
	s2.PrintSeqList();

	s2.PopBack();
	s2.PrintSeqList();
}


int main()
{
	Test();
	system("pause");
	return 0;
}