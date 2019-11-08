#include "linkedList.h"

template <class T>
class StackADT : protected linkedList<T>
{
private:

	T top;	// Index to top of stack
	linkedList<T> ob; // Creates stack from base class

public:
	StackADT<T>();

	bool isEmpty();
	void push(const T &newEntry);
	void pop();
	void emptyStack();
	T peek();

};


//***************************************************************************************
//				ListQueue
// pre-> receives nothing
// this functions is the default constructor and it creates a stack of linkedlist objects 
// returns nothing
// post-> creates a stack list
//****************************************************************************************
template <class T>
StackADT<T>::StackADT() {
	ob.createList("none");
}


//***************************************************************************************
//					isEmpty() const
//  pre->receives nothing
//	this function returns whether or not the queue is empty
//  post-> returns either true if empty or false if has elements 
//****************************************************************************************
template <class T>
bool StackADT <T>::isEmpty()
{
	return ob.dataCount();
}


//***************************************************************************************
//					push(const T&)
// pre->receives a value of type T 
// the function adds the desired value and pushes it to the stack
// post-> push a new entry to the top of the stack
//		  returns nothing 
//****************************************************************************************

template <class T>
void StackADT <T>::push(const T &newEntry)
{
	ob.addData(newEntry, ob);
	top = newEntry;
}


//***************************************************************************************
//					pop()
// pre -> receives nothing
//  this function removes a value from the stack and decreases the index of top
// pos-> a entry from the top of the stack is removed
//		 returns nothing 
//****************************************************************************************

template <class T>
void StackADT <T>::pop()
{
	if (isEmpty()) {
		ob.removeData(top);
		top = ob.getNext();
	}
	else {
		std::cout << "Stack is empty!" << std::endl;
	}
}



//***************************************************************************************
//					emptyStack()	
//  pre-> receives nothing
//  this function empties everything from the stack
// pos-> the stack is empty
//		  returns nothing
//****************************************************************************************
template <class T>
void StackADT<T>::emptyStack()
{
	if (isEmpty()) {
		ob.emptyList();
	}
	else
		std::cout << "Stack is already empty!" << std::endl;
}



//***************************************************************************************
//					peek()
//  pre-> receives nothing
//  this function finds the top of the stack
//  pos-> returns a value of type T which is the top of the qtack
//****************************************************************************************
template <class T>
T StackADT <T>::peek()
{
	if (isEmpty()) {
		return top;
	}
}

