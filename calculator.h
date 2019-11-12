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


std::string Calculator::inFixToPostfix(std::string str)
{

	StackADT<char> strOb;	// Creates the stack
	strOb.push('B');												//TODO
	int l = str.length();
	std::string tempStr;

	for (int i = 0; i < l; i++)
	{
		// If the char found is an operand, add it to tempStr
		if (str[i] == ' ')
		{
			std::cout << "found space!" << std::endl;
		}
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 0 && str[i] <= 9))
			tempStr += str[i];

		// If the char found is '(', push to stack
		else if (str[i] == '(')
			strOb.push('(');

		// If the scanned character is an �)�, pop and to output tempStr from the stack 
		// until �(� is found. 
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

std::string Calculator::inFixToPrefix(std::string infix)
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

	std::string prefix = inFixToPostfix(infix);

	// Reverse postfix 
	reverse(prefix.begin(), prefix.end());

	return prefix;
}
