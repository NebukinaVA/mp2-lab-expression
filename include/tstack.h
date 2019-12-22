#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>

const int MAX_STACK_SIZE = 10000;

template <class T>
class TStack
{
protected:
	T *pStack;
	int Size;                  // размер стека
	int TopElem;               // номер верхнего элемента
public:
	TStack(int s = MAX_STACK_SIZE);         // конструктор с параметром
	TStack(const TStack &s);   // конструктор копирования
	~TStack();
	TStack& operator= (const TStack &s); // присваивание
	bool IsEmpty();            // узнать, пустой ли стек
	bool IsFull();             // узнать, полон ли стек
	void Clear();              // очистить стек
	void Push(T elem);         // добавить элемент в стек
	T Pop();                // удалить элемент из стека
	T GetTop();
	void Repack();             // перепаковка
	bool operator==(const TStack &s) const;
	bool operator!=(const TStack &s) const;
};

template <class T>
TStack<T>::TStack(int s)  // конструктор с параметром
{
	if ((s < 0) || (s > MAX_STACK_SIZE)) throw "Error";
	TopElem = -1;
	Size = s;
	pStack = new T[Size];
}

template <class T>
TStack<T>::TStack(const TStack<T> &s) // конструктор копирования
{
	Size = s.Size;
	TopElem = s.TopElem;
	pStack = new T[Size];
	for (int i = 0; i < Size; i++)
		pStack[i] = s.pStack[i];
}

template <class T>
TStack<T>::~TStack()
{
	delete[] pStack;
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack &s) //присваивание 
{
	if ((Size != s.Size) || (TopElem != s.TopElem))
	{
		TopElem = s.TopElem;
		Size = s.Size;
		delete[] pStack;
		pStack = new T[Size];
	}
	for (int i = 0; i <= TopElem; i++)
		pStack[i] = s.pStack[i];
	return *this;
}

template <class T> // сравнение
bool TStack<T>::operator==(const TStack &s) const
{
	bool flag = true;
	if ((Size != s.Size) || (TopElem != s.TopElem)) return false;
	for (int i = 0; i <= TopElem; i++)
	{
		if (pStack[i] != s.pStack[i])
		{
			flag = false;
			break;
		}
	}
	return flag;
}

template <class T> // сравнение
bool TStack<T>::operator!=(const TStack &s) const
{
	if (s == *this) return false;
	return true;
}

template <class T> // узнать, пустой ли стек
bool TStack<T>::IsEmpty()
{
	if (TopElem == -1) return true;
	return false;
}

template <class T> // узнать, заполнен ли стек
bool TStack<T>::IsFull()
{
	if (TopElem == Size - 1) return true;
	return false;
}

template <class T>
void TStack<T>::Clear() // очистить стек
{
	TopElem = -1;
}

template <class T> // добавить элемент в стек
void TStack<T>::Push(T elem)
{
	if (IsFull()) Repack();
	TopElem = TopElem + 1;
	pStack[TopElem] = elem;
}

template <class T> // удалить элемент из стека
T TStack<T>::Pop()
{
	if (IsEmpty()) throw "Error";
	TopElem = TopElem - 1;
	return pStack[TopElem + 1];
}

template <class T>
T TStack<T>::GetTop()
{
	return pStack[TopElem];
}


template <class T> // перепаковать стек
void TStack<T>::Repack()
{
	T *ptemp;
	ptemp = new T[Size + 20];
	for (int i = 0; i < Size; i++)
		ptemp[i] = pStack[i];
	TopElem = Size - 1;
	Size = Size + 20;
	delete[] pStack;
	pStack = ptemp;
}



#endif