#ifndef __TEXPRESSION_H__
#define __TEXPRESSION_H__

#include <iostream>
#include <string>
#include <ctype.h>
#include "tstack.h"

//using namespace std;

class TExpression
{
protected:
	std::string Infix;
	std::string Postfix;
	std::string Operations = "+-*/()";
	int Priority[6] = { 3,3,2,2,1,1 };
public:
	TExpression(string exp = "1+1");     // конструктор с параметром
	~TExpression();
	string GetInfix() { return Infix; }
	string GetPostfix() { return Postfix; }
	void SetExpression(std::string exp); //получить выражение
	bool HasLetters(std::string exp);
	bool IsCorrect(std::string exp);     //проверка правильности
	void ToPostfix();                    //перевод в польскую запись
	double Calculate();                  // вычисление
	double StringToInt(std::string str);
};

TExpression::TExpression(std::string exp)
{
	if (!IsCorrect(exp)) throw "Error";
	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] != ' ')
			Infix += exp[i];
	}
	if (Infix.length() < 1) throw "Error";
}

TExpression::~TExpression()
{
}

void TExpression::SetExpression(std::string exp)
{
	if (!IsCorrect(exp)) throw "Error";
	std::string temp;
	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] != ' ')
			temp += exp[i];
	}
	if (temp.length() < 1) throw "Error";
	Infix = temp;
}

bool TExpression::HasLetters(std::string exp) // проверить, есть ли буквы
{
	for (int i = 0; i < exp.length(); i++)  
	{
		if (isalpha(exp[i]))
			return true;
	}
	return false;
}

bool TExpression::IsCorrect(std::string exp)
{
	std::string US = "!@#№;$%:^&?.,<>{}[]|_="; // Unacceptable Symbols
	int Pars = 0;  // parenthesis ()
	int Ops = 0;   // operations
	int len = exp.length();
	if (HasLetters(exp)) return false;
	for (int i = 0; i < len; i++)
	{
		if (US.find(exp[i]) != string::npos)
			return false;
		if (exp[i] == '(')
			Pars++;
		if (exp[i] == ')')
			Pars--;
		if (Operations.find(exp[i]) != string::npos)
			Ops++;
		else
			Ops = 0;
		if (Ops > 1)
			return false;
	}
	if (Pars != 0)
		return false;
	return true;
}

void TExpression::ToPostfix()
{
	Postfix.clear();
	TStack<char> Stack(MAX_STACK_SIZE);		
	int len = Infix.length();
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (Infix[i] != Operations[j])
				Postfix += Infix[i];
		}
		if ((Infix[i] >= '0') && (Infix[i] <= '9'))
		{
			if (i != len)
			{
				if ((Infix[i + 1] < '0') || (Infix[i + 1] > '9'))
					Postfix += ';';
			}
			else
				Postfix += ';';
		}
		if (Infix[i] == '(')
			Stack.Push(Infix[i]);
		if (Infix[i] == ')')
		{
			char topelem = Stack.Pop();
			while (topelem != '(')
			{
				Postfix += topelem;
				topelem = Stack.Pop();
			}
		}
		for (int k = 0; k < 4; k++)
		{
			if (Infix[i] == Operations[k])
			{
				if (Stack.IsEmpty())
					Stack.Push(Infix[i]);
				else
				{
					int ind1 = Operations.find(Infix[i]);
					while (!Stack.IsEmpty())
					{
						char lastelem = Stack.Pop();
						if (lastelem == '(')
						{
							Stack.Push(lastelem);
							break;
						}
						int ind2 = Operations.find(lastelem);
						if (Priority[ind2] <= Priority[ind1])
							Postfix += lastelem;
						else
						{
							Stack.Push(lastelem);
							break;
						}
					}
					Stack.Push(Infix[i]);
				}
			}
		}
		while (!Stack.IsEmpty())
			Postfix += Stack.Pop();
	}
}

double TExpression::Calculate()
{
	std::string str;
	ToPostfix();
	int len = Postfix.length();
	TStack<double> Stack(MAX_STACK_SIZE);
    double result = 0;
	for (int i = 0; i < len; i++) 
	{
		switch (Postfix[i])
		{
		case '+':
		{
			int p = Stack.Pop();
			result = Stack.Pop() + p;
			Stack.Push(result);
		}
		case '-':
		{
			int p = Stack.Pop();
			result = Stack.Pop() - p;
			Stack.Push(result);
		}
		case '*':
		{
			int p = Stack.Pop();
			result = Stack.Pop() * p;
			Stack.Push(result);
		}
		case '/':
		{
			int p = Stack.Pop();
			if (p == 0) throw "Error! Division by zero";
			result = Stack.Pop() / p;
			Stack.Push(result);
		}
		default:
		{
			while (Postfix[i] != ';')
			{
				str += Postfix[i];
				i++;
			}
		//	double res = StringToInt(str);
			double res = stoi(str);
			Stack.Push(res);
		}
		}
	}
	return Stack.GetTop();
}

double TExpression::StringToInt(std::string str)
{
	int temp = 0;
	int i = 0;
	while ((str[i] >= 0x30) && (str[i] <= 0x39))
	{
		temp = temp + (str[i] & 0x0F);
		temp = temp * 10;
		i++;
	}
	temp = temp / 10;
	return(temp);
}

#endif