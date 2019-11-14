#include "stackADT.h"
#include "queueADT.h"


class Calculator //: public StackADT<T>
{
private:
    std::string inFix, postFix;

public:
    Calculator() {};                                        // default constructor
    //std::string inFixToPostfix(std::string str);
    //std::string inFixToPrefix(std::string infix);
    int checkPrecedence(char c);                             // determines PMMDAS precedence
    bool isOperator(char c);                                // determines if character is bool/char
    std::string infixToPostfix(std::string infix);            // converts expression to postfix
    std::string infixToPrefix(std::string infix);             // converts expression to prefix

    double evalPostFix(std::string expression);
    double postCalculation(char operation, double operand1, double operand2);
    bool isNum(char C);
    double evalPreFix(std::string prefix);
    double evaluatePrefix(std::string expression);



};

//******************************************************************
//              int checkPrecendence(char)
// pre: receives a character from the user input expression
// pos: returns an integer either 3,2,1,-1 depending on the ranking for the
//      operator
// this program determines the precedence of the operator and returns an
// integer which will used later when converting pre- and pos- fix
//*******************************************************************
int Calculator::checkPrecedence(char c)
{
    if(c == ' ')
        return 4;
    if (c == '%' ) // PMMDAS is module higher than */? idk lol
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}


//******************************************************************
//                   bool isOperator(char)
// pre: receives a character from the user's expression
// pos: returns either true or false
// this function receives the character and checks whether it is an
// operator or not. true = isoperator, false = digit/char
//*******************************************************************
bool Calculator::isOperator(char c) {
    return (!isalpha(c) && !isdigit(c));
}



//******************************************************************
//            std::string infixToPostFix(std::string)
// pre: receives the user expression
// pos: returns the expression converted into postfix
// this function converts the user's expression into postfix and returns
// it back to the main function
//*******************************************************************
std::string Calculator::infixToPostfix(std::string infix)
{
    infix = '(' + infix + ')';
    int l = infix.size();
    StackADT<char> char_stack;
    std::string output;



    for (int i = 0; i < l; i++) {

        // If the scanned character is an
        // operand, add it to output.
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (infix[i] == '(')
            char_stack.push('(');

        // If the scanned character is an
        // ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (infix[i] == ')') {

            while (char_stack.peek() != '(') {
                output += char_stack.peek();
                char_stack.pop();
            }

            // Remove '(' from the stack
            char_stack.pop();
        }

        // Operator found
        else {
            if (isOperator(char_stack.peek()))
            {
                while (checkPrecedence(infix[i]) <= checkPrecedence(char_stack.peek()))
                {
                    output += char_stack.peek();
                    char_stack.pop();
                }
                // Push current Operator on stack
                char_stack.push(infix[i]);
            }
        }
    }
    return output;
}


//******************************************************************
//          std::string inFixToPrefix(std::String)
// pre: receives the user input expression
// pos: returns the prefix notated expression
// this function converts the user's expression into prefix notation
// and returns it back to the main
//*******************************************************************
std::string Calculator::infixToPrefix(std::string infix)
{
    // stack for operators.
    StackADT<char> operators;

    // stack for operands.
    StackADT<std::string> operands;

    for (int i = 0; i < infix.length(); i++) {

        // If current character is an
        // opening bracket, then
        // push into the operators stack.
        if (infix[i] == '(') {
            if (infix[i] != ' ')
                operators.push(infix[i]);
        }

        // If current character is a
        // closing bracket, then pop from
        // both stacks and push result
        // in operands stack until
        // matching opening bracket is
        // not found.
        else if (infix[i] == ')') {
            while (!operators.isEmpty() &&
                operators.peek() != '(') {

                // operand 1
                std::string op1 = operands.peek();
                operands.pop();

                // operand 2
                std::string op2 = operands.peek();
                operands.pop();

                // operator
                char op = operators.peek();
                operators.pop();

                // Add operands and operator
                // in form operator +
                // operand1 + operand2.
                std::string tmp = op + op2 + op1;
                operands.push(tmp);
            }

            // Pop opening bracket from
            // stack.
            operators.pop();
        }

        // If current character is an
        // operand then push it into
        // operands stack.
        else if (!isOperator(infix[i])) {
            operands.push(std::string(1, infix[i]));
        }

        // If current character is an
        // operator, then push it into
        // operators stack after popping
        // high priority operators from
        // operators stack and pushing
        // result in operands stack.
        else {
            while (!operators.isEmpty() &&
                checkPrecedence(infix[i]) <=
                checkPrecedence(operators.peek())) {

                std::string op1 = operands.peek();
                operands.pop();

                std::string op2 = operands.peek();
                operands.pop();

                char op = operators.peek();
                operators.pop();

                std::string tmp = op + op2 + op1;
                operands.push(tmp);
            }

            operators.push(infix[i]);
        }
    }

    // Pop operators from operators stack
    // until it is empty and add result
    // of each pop operation in
    // operands stack.
    while (operators.isEmpty()) {
        std::string op1 = operands.peek();
        operands.pop();

        std::string op2 = operands.peek();
        operands.pop();

        char op = operators.peek();
        operators.pop();

        std::string tmp = op + op2 + op1;
        operands.push(tmp);
    }

    // Final prefix expression is
    // present in operands stack.
    return operands.peek();
}

//******************************************************************
//                 double evalPostFix(std::String)
// pre: receives the user input expression in postfix notation
// pos: returns a double value representing the result
// This function takes in the expression and evaluates it. The result
// is then returned back to the main
//*******************************************************************
double Calculator::evalPostFix(std::string expression)
{
    // StackADT from previous LAB
    StackADT<double> S;

    for (int i = 0; i < expression.length(); i++) {

        // Skip whitespace char
        if (expression[i] == ' ' || expression[i] == ',') continue;

        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (isOperator(expression[i])) {
            double operand2 = S.peek(); S.pop();
            double operand1 = S.peek(); S.pop();
            double result = postCalculation(expression[i], operand1, operand2);
            S.push(result);
        }
        else if (isNum(expression[i])) {
            int operand = 0;
            while (i < expression.length() && isNum(expression[i])) {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            i--;

            S.push(operand);
        }
    }

    return S.peek();    // Returns the result of postfix evaluation
}


//******************************************************************
//         int postCalculation(char, int, int)
// pre: recieves a char operation, and two integers for operands
// pos: returns a double value
// this function take in two operands along with the operator calculates
// the value. Returns that value back to be entered back to stack
//*******************************************************************
double Calculator::postCalculation(char operation, double operand1, double operand2)
{
    if (operation == '+') return operand1 + operand2;
    else if (operation == '-') return operand1 - operand2;
    else if (operation == '*') return operand1 * operand2;
    else if (operation == '/')
    {
        if ( operand2 > 0)
            return operand1 / operand2;
        else{
            std::cout << " divide by zero error... " << std::endl;
            return -1;
        }
    }
    else if (operation == '%')
    {
        if ( operand2 != 0)
             return (static_cast<int>(operand1) % static_cast<int>(operand2));
        else{
            std::cout <<"arrived" << std::endl;

            std::cout << " divide by zero error... " << std::endl;
            return -1;
        }
    }
    else std::cout << "Unexpected Error \n";
    return -1;
}


//******************************************************************
//                         bool isNum(char)
// pre: receives a character from the expression
// pos: returns either true or false
// The function takes in a character and determines whether it is a
// number or not.
//*******************************************************************
// Function to verify whether a character is numeric digit.
bool Calculator::isNum(char c)
{
    if (c >= '0' && c <= '9') return true;
    return false;
}




//******************************************************************
//          double evalPreFix(std::String)
// pre: receives the user input expression in prefix notation
// pos: returns a double value  of the expression
// this function evaluates the prefix notated expression and returns the
// result back into the main
// *******************************************************************
//double Calculator::evalPreFix(std::string prefix) {
//    int l = prefix.length();
//    StackADT<int> intobj;
//    StackADT<char> charObj;
//    for (int i = l; i > 0; i--) {
//        if (isdigit(prefix[i]))
//            intobj.push(prefix[i]);
//        else{
//            if(isOperator(prefix[i]))
//        }
//            }
//    return 0;
//}


//******************************************************************
//             double evaluatePrefix(std::String)
// pre: receives the prefix notated epxression
// pos: returns a double value
// this function takes in the prefix notated expression, evaluates
// it and returns to main.
//*******************************************************************
double Calculator::evaluatePrefix(std::string expression){

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
                if(exp2 > 0)
                    ob.push(exp1 / exp2);
                else
                    std:: cout << "divide by zero error" << std::endl;
                break;
            case '%':
                if(exp2 > 0)
                    ob.push(static_cast<int>(exp1) % static_cast<int>(exp2));
                else
                    std::cout << "divide by zero error" << std::endl;
                break;
            }
        }
    }
    return ob.peek();        // Returns result of prefix expression
}
