#include "stackADT.h"

class Calculator //: public StackADT<T>
{
private:
    std::string inFix, postFix;

public:
    Calculator() {};                                     // default constructor
    std::string inFixToPostfix(std::string str);        // converts expression to postfix
    std::string inFixToPrefix(std::string infix);       // converts expression to prefix
    int checkPrecedence(char c);                        // determines PMMDAS precedence
    bool isOperator(char c);                           // determines if character is bool/char
    double evalPostFix(std::string postfix);           // evaluate the expression from postfix

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
    if (c == '%' || c == ' ') // PMMDAS is module higher than */? idk lol
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
bool Calculator::isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}


//******************************************************************
//            std::string infixToPostFix(std::string)
// pre: receives the user expression
// pos: returns the expression converted into postfix
// this function converts the user's expression into postfix and returns
// it back to the main function
//*******************************************************************
//std::string Calculator::inFixToPostfix(std::string str)
//{
//
//    StackADT<char> strOb;    // Creates the stack
//    strOb.push('B');        // create a dummy value for the top
//    int l = str.length();
//    std::string tempStr;
//
//    for (int i = 0; i < l; i++)
//    {
//        // If the char found is an operand, add it to tempStr
//        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 0 && str[i] <= 9) || (str[i] == ' '))
//            tempStr += str[i];
//
//        // If the char found is '(', push to stack
//        else if (str[i] == '(')
//            strOb.push('(');
//
//        // If the scanned character is an ‘)’, pop and to output tempStr from the stack
//        // until ‘(‘ is found.
//        else if (str[i] == ')')
//        {
//            while (strOb.peek() != 'B' && strOb.peek() != '(')
//            {
//                char c = strOb.peek();
//                strOb.pop();
//                tempStr += c;
//            }
//            if (strOb.peek() == '(')
//            {
//                char c = strOb.peek();
//                strOb.pop();
//            }
//        }
//
//        //If an operator is scanned
//        else {
//
//            while (strOb.peek() != 'B' && checkPrecedence(str[i]) <= checkPrecedence(strOb.peek()))
//            {
//                tempStr += strOb.peek();
//                strOb.pop();
//            }
//            strOb.push(str[i]);
//        }
//    }
//    //Pop all the remaining elements from the stack
//    while (strOb.peek() != 'B')
//    {
//        char c = strOb.peek();
//        strOb.pop();
//        tempStr += c;
//    }
//
//    return tempStr;
//}



//******************************************************************
//          std::string inFixToPrefix(std::String)
// pre: receives the user input expression
// pos: returns the prefix notated expression
// this function converts the user's expression into prefix notation
// and returns it back to the main
//*******************************************************************
std::string Calculator::inFixToPrefix(std::string infix)
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
    while (!operators.isEmpty()) {
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
//            std::string infixToPostFix(std::string)
// pre: receives the user expression
// pos: returns the expression converted into postfix
// this function converts the user's expression into postfix and returns
// it back to the main function
//*******************************************************************
std::string Calculator::inFixToPostfix(std::string infix)
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

            if (isOperator(char_stack.peek())) {
                while (checkPrecedence(infix[i])
                    <= checkPrecedence(char_stack.peek())) {
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
//          double evalPostFix(std::string)
// pre: receives the user's expression
// pos: returns a double value for the result of the expression
// This function calculates the result of the expression given by the
// user and returns it back to the main
//*******************************************************************
double Calculator::evalPostFix(std::string preStr)
{
    std::string posStr;
    for (int i = 0; i < preStr.length(); i++)
{
        // Getting rid of spaces
        if (preStr[i] != ' ')
            posStr += preStr[i];
    }
    // Evaluation of parenthesis
    std::string newStr = "";
    for (int i = 0; i < posStr.length(); i++){
        if (posStr[i] == '(')    {
            int iter = 1;
            std::string tempStr;
            i++;
            while (true){
                if (posStr[i] == '(')
                    iter++;
                else if (posStr[i] == ')')    {
                    iter--;
                    if (iter == 0)    {
                        i++;
                        break;
                    }
                }
                    tempStr += posStr[i];
                    i++;
            }
            newStr += std::to_string(evalPostFix(tempStr));
        }
        newStr += posStr[i];
    }

    for (int i = 0; i < newStr.length(); i++){
        if (newStr[i] == '+')
            return evalPostFix(newStr.substr(0, i)) + evalPostFix(newStr.substr(i + 1, newStr.length() - i - 1));

        else if (newStr[i] == '-')
            return evalPostFix(newStr.substr(0, i)) - evalPostFix(newStr.substr(i + 1, newStr.length() - i - 1));
    }

    for (int i = 0; i < newStr.length(); i++){
        if (newStr[i] == '*')
            return evalPostFix(newStr.substr(0, i)) * evalPostFix(newStr.substr(i + 1, newStr.length() - i - 1));
        
        else if (newStr[i] == '/')
            return evalPostFix(newStr.substr(0, i)) / evalPostFix(newStr.substr(i + 1, newStr.length() - i - 1));
    }

    return std::stod(newStr.c_str());
}

