#include "stackADT.h"
//
//
//class Calculator : public StackADT<T>
//{
//private:
//	std::string inFix, postFix;
//
//public:
//	Calculator() {};
//	void inFixToPostfix(std::string s);
//
//};
//
//void Calculator::infixToPostfix(std::string s)
//{
//
//
//
//	std::stack<char> st;
//	st.push('N');
//	int l = s.length();
//	std::string ns;
//	for (int i = 0; i < l; i++)
//	{
//		// If the scanned character is an operand, add it to output std::string. 
//		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
//			ns += s[i];
//
//		// If the scanned character is an ‘(‘, push it to the stack. 
//		else if (s[i] == '(')
//
//			st.push('(');
//
//		// If the scanned character is an ‘)’, pop and to output std::string from the stack 
//		// until an ‘(‘ is encountered. 
//		else if (s[i] == ')')
//		{
//			while (st.top() != 'N' && st.top() != '(')
//			{
//				char c = st.top();
//				st.pop();
//				ns += c;
//			}
//			if (st.top() == '(')
//			{
//				char c = st.top();
//				st.pop();
//			}
//		}
//
//		//If an operator is scanned 
//		else {
//			while (st.top() != 'N' && prec(s[i]) <= prec(st.top()))
//			{
//				char c = st.top();
//				st.pop();
//				ns += c;
//			}
//			st.push(s[i]);
//		}
//
//	}
//	//Pop all the remaining elements from the stack 
//	while (st.top() != 'N')
//	{
//		char c = st.top();
//		st.pop();
//		ns += c;
//	}
//
//	cout << ns << endl;
//
//}