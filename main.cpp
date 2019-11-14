#if 0

double evaluatePrefix(string expression)

{

	StackADT<double> ob; // Stack object



	for (int j = expression.size() - 1; j >= 0; j--) {



		// Push operand to stack

		// To convert expression[j] to digit subtract 

		// '0' from expression[j]. 

		if (isdigit(expression[j]))

			ob.push(expression[j] - '0');



		else {



			// finds operator

			// and pops from object

			double exp1 = ob.peek();

			ob.pop();

			double exp2 = ob.peek();

			ob.pop();



			// Use switch case to operate on exp1 

			// and exp2 and perform exp1 O exp2. 

			switch (expression[j]) {

			case '+':

				ob.push(exp1 + exp2);

				break;

			case '-':

				ob.push(exp1 - exp2);

				break;

			case '*':

				ob.push(exp1 * exp2);

				break;

			case '/':

				ob.push(exp1 / exp2);

				break;

			case '%':

				// ob.push(exp1 % exp2);				TODO

				break;

			}

		}

	}



	return ob.peek();		// Returns result of prefix expression

}

#endif



/*
	Renan Silva Hiramatsu
	Amber Low
 this lab demonstrates the conversion of postfix and prefix notation
 from a user input and evaluates the expression

 do
	ask user input expression
	convert expression to postfix notation and evaluate
	display
	convert expression to prefix notation and evaluate
	display
	ask user if they want to continue
 while(user wants to continue)

	infix (2 + 30) / 10 * 2
	postfix 2 30 + 10 / 2 *

 */

#include <iostream>
#include <string>
#include "calculator.h"

 //    TODO: EXCEPTION OF DIVIDING BY 0

using namespace std;



#include<iostream>
#include<string>

using namespace std;
int main() {

	char input;
	Calculator ob;
	string userInput;
	bool cont = true;
	string postfix, prefix;
	do
	{
		try {
			cout << "Enter a mathematical expression: ";
			getline(cin, userInput);


			int l = userInput.length();
			for (int i = 0; i < l; i++) {			// negative values are considered illegal
				if (userInput[i] == '~')			// if encountered, throw an exception
					throw - 1;
			}
			cout << "Your expression in postfix notation: " << endl;
			postfix = ob.infixToPostfix(userInput);
			cout << postfix << endl;
			cout << "Result: " << ob.evalPostFix(postfix) << endl;

			cout << "Your expression in prefix notation: " << endl;
			//prefix = ob.infixToPrefix(userInput);
			//cout << prefix << endl;


			cout << "press 'q' to QUIT and any other letter/number to CONTINUE: ";
			cin >> input;
			cin.ignore();

			if (tolower(input) == 'q')
				cont = false;
		}
		catch (int) {
			cout << "negatative inputs are invalid" << endl;		// catches exception and displays a message
			cout << "please try again" << endl;						// allows user to try again
		}
	} while (cont != false);





	system("pause");

}
