#include <iostream>
#include <string>
#include "calculator.h"

//	TODO: EXCEPTION OF DIVIDING BY 0


using namespace std;


int main(){

	Calculator ob;
	string userInput;
	while (userInput != "q")
	{
	cout << "Enter a mathematical expression: ";
	getline(cin, userInput);

	cout << "Infix to postfix: " << endl;
	cout << ob.inFixToPostfix(userInput) << endl;


	cout << "Infix to prefix: " << endl;
	cout << ob.inFixToPrefix(userInput) << endl;


	}

	
	
	system("pause");

}