#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 10000;

template <class ValType>
class TStack
{
protected:
	ValType *pStack;
	int Size;                  // размер стека
	int TopElem;               // номер верхнего элемента
public:
	TStack(int s = 6);         // конструктор с параметром
	TStack(const TStack &s);   // конструктор копирования
	~TStack();
	TStack& operator= (const TStack &s); // присваивание
	bool IsEmpty();            // узнать, пустой ли стек
	bool IsFull();             // узнать, полон ли стек
	void Clear();              // очистить стек
	void Push(ValType elem);   // добавить элемент в стек
	void Pop();                // удалить элемент из стека
	TStack LoadStack();        // перенос элементов
	bool operator==(const TStack &s) const;
	bool operator!=(const TStack &s) const;
};

template <class ValType>
TStack<ValType>::TStack(int s)  // конструктор с параметром
{
	if ((s < 0) || (s > MAX_STACK_SIZE)) throw "Error";
	TopElem = -1;
	Size = s;
	pStack = new ValType[Size];
}

template <class ValType>
TStack<ValType>::TStack(const TStack<ValType> &s) // конструктор копирования
{
	Size = s.Size;
	TopElem = s.TopElem;
	pStack = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pStack[i] = s.pStack[i];
}

template <class ValType>
TStack<ValType>::~TStack()
{
	delete[] pStack;
}

template <class ValType>
TStack<ValType>& TStack<ValType>::operator=(const TStack &s) //присваивание 
{
	if ((Size != s.Size) || (TopElem != s.TopElem))
	{
		TopElem = s.TopElem;
		Size = s.Size;
		delete[] pStack;
		pStack = new ValType[Size];
	}
	for (int i = 0; i <= TopElem; i++)
		pStack[i] = s.pStack[i];
	return *this;
}

template <class ValType> // сравнение
bool TStack<ValType>::operator==(const TStack &s) const
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

template <class ValType> // сравнение
bool TStack<ValType>::operator!=(const TStack &s) const
{
	if (s == *this) return false;
	return true;
}

template <class ValType> // узнать, пустой ли стек
bool TStack<ValType>::IsEmpty()
{
	if (TopElem == -1) return true;
	return false;
}

template <class ValType> // узнать, заполнен ли стек
bool TStack<ValType>::IsFull()
{
	if (TopElem == Size - 1) return true;
	return false;
}

template <class ValType>
void TStack<ValType>::Clear() // очистить стек
{
	TopElem = -1;
}

template <class ValType> // добавить элемент в стек
void TStack<ValType>::Push(ValType elem)
{
	if (IsFull()) throw "Error";
	TopElem = TopElem + 1;
	pStack[TopElem] = elem;
}

template <class ValType> // удалить элемент из стека
void TStack<ValType>::Pop()
{
	if (IsEmpty()) throw "Error";
	pStack[TopElem] = '\0';
	TopElem = TopElem - 1;
}


template <class ValType>
TStack<ValType> TStack<ValType>::LoadStack()  // перенос элементов
{
	TStack temp(Size);
	temp.TopElem = TopElem;
	for (int i = 0; i <= TopElem; i++)
		temp.pStack[i] = pStack[TopElem - i];
	return temp;
}


#endif