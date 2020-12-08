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
	bool IsCorrect(std::string exp);     //проверка правильности
	void ToPostfix();                    //перевод в польскую запись
	double Calculate();                  // вычисление
};

TExpression::TExpression(std::string exp)
{
	int len = exp.length();
	for (int i = 0; i < len; i++)
	{
		if (exp[i] != ' ')
			Infix += exp[i];
	}
	if (!IsCorrect(Infix)) throw "Error";
	if (Infix.length() < 1) throw "Error";
}

TExpression::~TExpression()
{
}

void TExpression::SetExpression(std::string exp)
{
	std::string temp;
	int len = exp.length();
	for (int i = 0; i < len; i++)
	{
		if (exp[i] != ' ')
			temp += exp[i];
	}
	if (!IsCorrect(temp)) throw "Error";
	if (temp.length() < 1) throw "Error";
	Infix = temp;
}

bool TExpression::IsCorrect(std::string exp)
{
	int Cond = 0;      // condition
	int Pars = 0;      // parenthesis ()
	int i = 0;
	while ((Cond != 3) && (Cond != 4))
	{
		switch (Cond)
		{
		case 0:
		{
			Cond = 3;
			if (exp[i] == '\0')
				Cond = 2;
			if (exp[i] == '(')
			{
				Pars++;
				Cond = 0;
			}
			if ((exp[i] >= '0') && (exp[i] <= '9'))
			{
				Cond = 1;
				int dot = 0;
				while (((exp[i + 1] >= '0') && (exp[i + 1] <= '9')) || (exp[i + 1] == '.'))
				{
					i++;
					if (exp[i] == '.') 
					{ 
						dot++;
						if (exp[i + 1] == '.') dot--; 
					}
				}
				if ((dot > 1) || (exp[i] == '.')) Cond = 3;
			}
			break;
		}
		case 1:
		{
			Cond = 3;
			if (exp[i] == '\0')
				Cond = 2;
			if (exp[i] == ')')
			{
				Pars--;
				Cond = 1;
				if (Pars < 0) Cond = 3;
			}
			if (Operations.find(exp[i]) != std::string::npos)
			{
				Cond = 0;
				if (exp[i + 1] == '\0') Cond = 3;
			}
			break;
		}
		case 2:
		{
			Cond = 3;                // ERROR
			if (Pars == 0) Cond = 4; // SUCCESS
			break;
		}
		default: break;
		}
		i++;
	}
	if (Cond == 4) return true;
	return false;
}

void TExpression::ToPostfix()
{
	if(!Postfix.empty())
		Postfix.erase();
	std::string temp = "+-*/()";
	TStack<char> Stack;
	int len = Infix.length();
	for (int i = 0; i < len; i++)
	{
		if (temp.find(Infix[i]) == std::string::npos)
			Postfix += Infix[i];
		if ((Infix[i] >= '0') && (Infix[i] <= '9'))
			if (i != len - 1)
			{
				if (((Infix[i + 1] < '0') || (Infix[i + 1] > '9')) && (Infix[i + 1] != '.'))
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
	TStack<double> Stack;
	double result = 0;
	for (int i = 0; i < len; i++)
	{
		if (Operations.find(Postfix[i]) != std::string::npos)
		{
			switch (Postfix[i])
			{
			case '+':
			{
				double p = Stack.Pop();
				result = Stack.Pop() + p;
				Stack.Push(result);
				break;
			}
			case '-':
			{
				double p = Stack.Pop();
				result = Stack.Pop() - p;
				Stack.Push(result);
				break;

			}
			case '*':
			{
				double p = Stack.Pop();
				result = Stack.Pop() * p;
				Stack.Push(result);
				break;
			}
			case '/':
			{
				double p = Stack.Pop();
				if (p == 0) throw "Error! Division by zero";
				result = Stack.Pop() / p;
				Stack.Push(result);
				break;
			}
			}
		}
		else
		{
			std::string str;
			while (Postfix[i] != ';')
			{
				str += Postfix[i];
				i++;
			}
			double number = std::stod(str);
			Stack.Push(number);
		}
	}
	return Stack.GetTop();
}


#endif