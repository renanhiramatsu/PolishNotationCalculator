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
 
 */

#include <iostream>
#include <string>
#include "calculator.h"

//    TODO: EXCEPTION OF DIVIDING BY 0

using namespace std;



/*
Infix to postfix conversion in C++
Input Postfix expression must be in a desired format.
Operands and operator, both must be single character.
Only '+'  ,  '-'  , '*', '/' and '$' (for exponentiation)  operators are expected.
*/
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
        cout << "Enter a mathematical expression: ";
        getline(cin, userInput);

        cout << "Infix to postfix: " << endl;
        postfix = ob.inFixToPostfix(userInput);
        cout << postfix << endl;
        cout << "Result: " << ob.evalPostFix(userInput) << endl;

        cout << "Infix to prefix: " << endl;
        prefix = ob.inFixToPrefix(userInput);
        cout << prefix << endl;

        
        cout << "press 'q' to quit and 'c' to continue: ";
        cin >> input;
        cin.ignore();

        if (tolower(input) == 'q')
            cont = false;

    } while (cont != false);

    

    system("pause");

}
