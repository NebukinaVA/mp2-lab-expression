#ifndef __TEXPRESSION_H__
#define __TEXPRESSION_H__

#include <iostream>
#include <string>
#include "tstack.h"

class TExpression
{
protected:
	std::string Infix;
	std::string Postfix;
	std::string Operations = "+-*/";
	int Priority[6] = { 2,2,1,1 };
public:
	TExpression(std::string exp = "1+1");     // конструктор с параметром
	~TExpression();
	std::string GetInfix() { return Infix; }
	std::string GetPostfix() { return Postfix; }
	void SetExpression(std::string exp); //получить выражение
	bool HasLetters(std::string exp);
	bool IsCorrect(std::string exp);     //проверка правильности
	void ToPostfix();                    //перевод в польскую запись
	double Calculate();                  // вычисление
};

TExpression::TExpression(std::string exp)
{
	if (!IsCorrect(exp)) throw "Error";
	int len = exp.length();
	for (int i = 0; i < len; i++)
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

bool TExpression::HasLetters(std::string exp) 
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
	std::string US = "!@#В№;$%:^&?.,<>{}[]|_="; // Unacceptable Symbols
	int Pars = 0;  // parenthesis ()
	int Ops = 0;   // operations
	int len = exp.length();
	if (HasLetters(exp)) return false;
	for (int i = 0; i < len; i++)
	{
		if (US.find(exp[i]) != std::string::npos)
			return false;
		if (exp[i] == '(')
			Pars++;
		if (exp[i] == ')')
			Pars--;
		if (Operations.find(exp[i]) != std::string::npos)
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
	if(!Postfix.empty())
		Postfix.erase();
	std::string temp = "+-*/()";
	TStack<char> Stack(MAX_STACK_SIZE);
	int len = Infix.length();
	for (int i = 0; i < len; i++)
	{
		if (temp.find(Infix[i]) == std::string::npos)
			Postfix += Infix[i];
		if ((Infix[i] >= '0') && (Infix[i] <= '9'))
			if (i != len)
			{
				if ((Infix[i + 1] < '0') || (Infix[i + 1] > '9'))
					Postfix += ';';
			}
			else
				Postfix += ';';
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
		if (Operations.find(Infix[i]) != std::string::npos)
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

double TExpression::Calculate()
{
	ToPostfix();
	int len = Postfix.length();
	TStack<char> Ops;
	TStack<double> Nums;
    double result = 0;
	for (int i = 0; i < len; i++)
	{
		if (Operations.find(Postfix[i]) != std::string::npos)
			Ops.Push(Postfix[i]);
		else 
		{
	        std::string str;
			while (Postfix[i] != ';')
			{
				str += Postfix[i];
				i++;
			}
			double number = std::stoi(str);
			Nums.Push(number);
		}
	}
	while(!Ops.IsEmpty()) 
	{
		switch (Ops.Pop())
		{
		case '+':
		{
			double p = Nums.Pop();
			result = Nums.Pop() + p;
			Nums.Push(result);
			Ops.Pop();
		}
		case '-':
		{
			double p = Nums.Pop();
			result = Nums.Pop() - p;
			Nums.Push(result);
			Ops.Pop();

		}
		case '*':
		{
			double p = Nums.Pop();
			result = Nums.Pop() * p;
			Nums.Push(result);
			Ops.Pop();
		}
		case '/':
		{
			double p = Nums.Pop();
			if (p == 0) throw "Error! Division by zero";
			result = Nums.Pop() / p;
			Nums.Push(result);
			Ops.Pop();
		}
		}
	}
	
	return Nums.GetTop();
}


#endif