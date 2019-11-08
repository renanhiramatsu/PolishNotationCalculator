#include <iostream>
#include <string>
#include "calculator.h"


using namespace std;

// This will go to our calculator class, but I was testing in main first

int evaluatePrecedence(char c)
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


void inFixToPostFix(std::string s)
{

	StackADT<char> strOb;
	strOb.push('N');
	int l = s.length();
	//StackADT<string> tempString;
	std::string tempString;

	for (int i = 0; i < l; i++)
	{
		// If the char found is an operand, add it to tempString
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			tempString += s[i];

		// If the char found is '(', push to stack
		else if (s[i] == '(')
			strOb.push('(');

		// If the scanned character is an ‘)’, pop and to output tempString from the stack 
		// until ‘(‘ is found. 
		else if (s[i] == ')')
		{
			while (strOb.peek() != 'N' && strOb.peek() != '(')
			{
				char c = strOb.peek();
				strOb.pop();
				tempString += c;
			}
			if (strOb.peek() == '(')
			{
				char c = strOb.peek();
				strOb.pop();
			}
		}

		//If an operator is scanned 
		else {
			while (strOb.peek() != 'N' && evaluatePrecedence(s[i]) <= evaluatePrecedence(strOb.peek()))
			{
				char c = strOb.peek();
				strOb.pop();
				tempString += c;
			}
			strOb.push(s[i]);
		}

	}
	//Pop all the remaining elements from the stack 
	while (strOb.peek() != 'N')
	{
		char c = strOb.peek();
		strOb.pop();
		tempString += c;
	}

	cout << tempString << endl;

}


int main(){


	string exp = "x/y*z%k*z";
	inFixToPostFix(exp);			// I think stack has a problem and it's not printing some operators

	system("pause");

}