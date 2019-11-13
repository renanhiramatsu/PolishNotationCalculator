#include <iostream>
#include <string>
#include "calculator.h"

//	TODO: EXCEPTION OF DIVIDING BY 0


using namespace std;



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
		cout << "Result: " << ob.evalPostFix(userInput) << endl;

		cout << "Infix to prefix: " << endl;
		cout << ob.inFixToPrefix(userInput) << endl;


		cout << "press 'q' to quit and 'c' to continue: ";
		cin >> input;
		cin.ignore();

		if (tolower(input) == 'q')
			cont = false;

	} while (cont != false);

	

	system("pause");

}