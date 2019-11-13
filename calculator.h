#include "stackADT.h"

class Calculator //: public StackADT<T>
{
private:
	std::string inFix, postFix;

public:
	Calculator() {};
	std::string inFixToPostfix(std::string s);
	int checkPrecedence(char c);
	std::string inFixToPrefix(std::string infix);
	bool isOperator(char c);
	double evalPostFix(std::string postfix);

};

int Calculator::checkPrecedence(char c)
{
	if (c == '%') // PMMDAS is module higher than */? idk lol
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

bool Calculator::isOperator(char c)
{
	return (!isalpha(c) && !isdigit(c));
}


std::string Calculator::inFixToPrefix(std::string str)
{

	StackADT<char> strOb;	// Creates the stack
	strOb.push('B');												//TODO
	int l = str.length();
	std::string tempStr;

	for (int i = 0; i < l; i++)
	{
		// If the char found is an operand, add it to tempStr
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 0 && str[i] <= 9) || (str[i] == ' '))
			tempStr += str[i];

		// If the char found is '(', push to stack
		else if (str[i] == '(')
			strOb.push('(');

		// If the scanned character is an ‘)’, pop and to output tempStr from the stack 
		// until ‘(‘ is found. 
		else if (str[i] == ')')
		{
			while (strOb.peek() != 'B' && strOb.peek() != '(')
			{
				char c = strOb.peek();
				strOb.pop();
				tempStr += c;
			}
			if (strOb.peek() == '(')
			{
				char c = strOb.peek();
				strOb.pop();
			}
		}

		//If an operator is scanned 
		else {

			while (strOb.peek() != 'B' && checkPrecedence(str[i]) <= checkPrecedence(strOb.peek()))
			{
				tempStr += strOb.peek();
				strOb.pop();
				//cout << .peek now is: " << strOb.peek() << endl;
			}
			strOb.push(str[i]);

		}

	}
	//Pop all the remaining elements from the stack 
	while (strOb.peek() != 'B')
	{
		char c = strOb.peek();
		strOb.pop();
		tempStr += c;
	}

	return tempStr;
}

std::string Calculator::inFixToPostfix(std::string infix)
{
	/* Reverse String
	 * Replace ( with ) and vice versa
	 * Get Postfix
	 * Reverse Postfix  *  */
	int l = infix.size();

	// Reverse infix 
	reverse(infix.begin(), infix.end());

	// Replace ( with ) and vice versa 
	for (int i = 0; i < l; i++) {

		if (infix[i] == '(') {
			infix[i] = ')';
			i++;
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
			i++;
		}
	}

	std::string prefix = inFixToPrefix(infix);

	// Reverse postfix 
	reverse(prefix.begin(), prefix.end());

	return prefix;
}





double Calculator::evalPostFix(std::string postfix) {
	StackADT<int> intStack;
	int l = postfix.length();
	for (int i = 0; i < l; i++) {
		if (!isOperator(postfix[i]))
		{
			intStack.push(postfix[i]);
		}
		else
		{
			int a, b;
			if (isOperator(postfix[i]))
			{
				std::cout << static_cast<int>(intStack.peek());
				a = intStack.peek();
				intStack.pop();
				std::cout << intStack.peek();

				b = intStack.peek();
				if (postfix[i] == '-')
				{
					intStack.push(a - b);
				}
				if (postfix[i] == '+')
				{
					intStack.push(a + b);
				}
				if (postfix[i] == '/')
				{
					if (a != 0 && b != 0)
						intStack.push(a / b);
					else {
						std::cout << "divide by zero error! " << std::endl;
						return NULL;
					}
				}
				if (postfix[i] == '*')
				{
					intStack.push(a * b);
				}
				if (postfix[i] == '%')
				{
					intStack.push(a % b);
				}

			}
		}
	}
	return intStack.peek();
}
