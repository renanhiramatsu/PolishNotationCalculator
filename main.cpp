#include <iostream>
#include <string>
#include "calculator.h"

//	TODO: EXCEPTION OF DIVIDING BY 0


using namespace std;
const char* expressionToParse = "1+2";

char peek()
{
	return *expressionToParse;
}

char get()
{
	return *expressionToParse++;
}

int expression();

int number()
{
	int result = get() - '0';
	while (peek() >= '0' && peek() <= '9')
	{
		result = 10 * result + get() - '0';
	}
	return result;
}

int factor()
{


	if (peek() >= '0' && peek() <= '9')
		return number();
	else if (peek() == '(')
	{
		get(); // '('
		int result = expression();
		get(); // ')'
		return result;
	}
	else if (peek() == '-')
	{
		get();
		return -factor();
	}
	return 0; // error
}

int term()
{
	int result = factor();
	while (peek() == '*' || peek() == '/')
		if (get() == '*')
			result *= factor();
		else
			result /= factor();
	return result;
}

int expression()
{
	int result = term();
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += term();
		else
			result -= term();
	return result;
}


int main() {
	char input;
	Calculator ob;
	string userInput;
	bool cont = true;
	string postfix, prefix;
	do
	{
		cout << "Enter a mathematical expression: ";
		getline(cin, userInput);

		cout << "Infix to postfix: " << endl;
		postfix = ob.inFixToPostfix(userInput);
		cout << postfix << endl;
		//cout << "Result: " << ob.evalPostFix(postfix) << endl;

		cout << "Infix to prefix: " << endl;
		cout << ob.inFixToPrefix(userInput) << endl;


		cout << "press 'q' to quit and 'c' to continue: ";
		cin >> input;
		cin.ignore();

		if (tolower(input) == 'q')
			cont = false;

	} while (cont != false);


	cout << expression();


	system("pause");

}