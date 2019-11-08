#include "linkedList.h"

template <class T>
class ListQueue : protected linkedList <T>
{
private:
	linkedList<T> list;	// List of queue items
	T front, rear;

public:
	ListQueue();

	bool isEmpty();
	void enqueue(const T& newEntry);
	void dequeue();
};



//***************************************************************************************
//				ListQueue
// pre-> receives nothing
// this functions is the default constructor and it creates a queue of linkedlist objects 
// returns nothing
// post-> creates a queue list
//****************************************************************************************
template <class T>
ListQueue <T>::ListQueue()
{
	list.createList("none");
}



//***************************************************************************************
//					isEmpty() const
//  pre->receives nothing
//	this function returns whether or not the queue is empty
//  post-> returns either true if empty or false if has elements 
//****************************************************************************************
template <class T>
bool ListQueue <T>::isEmpty()
{
	return list.dataCount();
}



//***************************************************************************************
//					enqueue(const T&)
// pre->receives a constant type T object 
// this function adds the the desired value into the queue
// pos-> a new entry has been added onto queue 
 //		 returns true if the value was successfully added 
//****************************************************************************************
template <class T>
void ListQueue <T>::enqueue(const T& newEntry)
{
	if (!isEmpty()) {
		list.addData(newEntry, list);
		front = newEntry;
	}
	else {
		list.addData(newEntry, list);
		rear = newEntry;
		//*front = list->head;
	}

	std::cout << front << " is front" << std::endl;
	std::cout << rear << " is rear" << std::endl;

}



//***************************************************************************************
//					dequeue()
// pre -> recieves nothing
// this functions deletes an value from the queue
// pos-> the front entry has been deleted
//       returns true if the value was successfully deleted
//***************************************************************************************

template <class T>
void ListQueue <T>::dequeue()
{
	T temp;
	if (isEmpty()) {
		temp = list.getNext();
		list.removeData(front);
		front = temp;
	}
	else {
		std::cout << "List is empty!" << std::endl;
	}

}


