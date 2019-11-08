#pragma once
#include "linkNode.h"
#include <string>

template <typename T>
class linkedList {
private:
	int count;
	linkNode<T> *head;
	linkNode<T> *tail;
	std::string sortType; // increase, decrease, or none

public:
	linkedList();
	void createList(std::string);			//creates a new linkedList
	void addData(T, linkedList<T>);			//adds a node onto the linkedList
	void removeData(T);						//removed a node from linkedList
	bool findData(T);						//searches for a specific node from linkedList (i think its bool??)
	int dataCount();						//counts the amount of nodes in linkedlist
	void emptyList();						//empties the entire linkedlist
	void displayData();						//displays all nodes 
	bool operator != (T);
	int getNext();

};


template <typename T>
int linkedList<T>::getNext() {
	int nxt = head->data;
	return nxt;
}

//default constructor
template <typename T>
linkedList<T>::linkedList() : head(nullptr), tail(nullptr), count(0), sortType("") {};


//*******************************************************************
//						createList
// receives nothing
// similar to default constructor. Creates a new list with one node
// initialized to null and count to 0
//	returns nothing
//********************************************************************
template <typename T>
void linkedList<T>::createList(std::string type) {
	head = nullptr;
	tail = head;
	count = 0;
	sortType = type;
	std::cout << "list created!" << std::endl;
}


//*******************************************************************
//						addData
// recieves a type T data
// adds the data into the linkedlist
// returns nothing 
//********************************************************************
template <typename T>
void linkedList<T>::addData(T d, linkedList<T> obj) {
	linkNode<T>* newNode = new linkNode<T>;
	newNode->data = d;
	newNode->next = nullptr;

	// if the list is empty, set it as the head
	if (head == nullptr)
	{
		head = newNode;
		tail = head;
		head->next = nullptr;
		count++;
	}

	// if not empty:
	else
	{
		linkNode<T>* temp = head;
		linkNode<T>* preNode = nullptr;

		//specific for unsorted linkedlists
		if (obj.sortType == "none")
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;				//just add node last
			}
			temp->next = newNode;
			count++;				//increase count
		}

		//specific for increasing sorted linkedlist
		if (obj.sortType == "increase")
		{
			//if first node is larger than the node being added, prepend
			if (head->data > newNode->data)
			{
				newNode->next = temp;
				head = newNode;
				count++;
				return;
			}
			//else, loop till at appropiate node
			while (temp->next != nullptr && temp->data < newNode->data)
			{
				preNode = temp;
				temp = temp->next;
			}
			if (temp->data > newNode->data)
			{
				preNode->next = newNode;
				newNode->next = temp;
				count++;
			}
			else
			{
				temp->next = newNode;
				count++;
			}
		}

		//specific for decreasing sorted linkedlists
		if (obj.sortType == "decrease")
		{

			//if the first node is smaller than new node, prepend
			if (head->data < newNode->data)
			{
				newNode->next = temp;
				head = newNode;
				count++;
				return;
			}

			//else, loop till appropiate node
			while (temp->next != nullptr && temp->data > newNode->data)
			{
				preNode = temp;
				temp = temp->next;
			}
			if (temp->data < newNode->data)
			{
				preNode->next = newNode;
				newNode->next = temp;
				count++;
			}
			else
			{
				temp->next = newNode;
				count++;
			}
		}
	}
}

template <typename T>
bool linkedList<T>::operator != (T d) {
	if (this->removeData(d) != removeData(d))
		return true;
	else
		return false;
};


//*******************************************************************
//							removeData
// receives a type T data
// finds the data that user specifies and removes the node
// returns nothing
//********************************************************************
template <typename T>
void linkedList<T>::removeData(T d) {
	linkNode<T>* iter = head;
	linkNode<T>* preNode = nullptr;

	//if list is empty, nothng to remove
	if (head == nullptr)
	{
		std::cout << "List is empty. Nothing to remove" << std::endl;
		return;
	}

	// if data desired to remove is first then this executes
	if (iter->data == d)
	{
		iter = head->next;
		delete head;
		head = iter;
		std::cout << "Removed! " << std::endl;
		count--;
		return;
	}

	//else loop until data is equal to desired removal data
	else
	{
		while (iter->data != d && iter->next != nullptr)
		{
			preNode = iter;
			iter = iter->next;
		}

		//if loops successfully, remove
		if (iter->data == d)
		{
			preNode->next = iter->next;
			delete iter;
			count--;
			std::cout << d << " has been removed. " << std::endl;
		}

		// else its not in the list 
		else
		{
			std::cout << "The element you wanted to delete is not part of the list" << std::endl;
		}
	}
}


//*******************************************************************
//							findData
// recieves a type T data
// the function tries to find the desired data in the linkedlist
//
//********************************************************************
template <typename T>
bool linkedList<T>::findData(T d) {
	linkNode<T>* iter = head;
	bool found = false;
	//if first element is the one you're searching for 
	if (head->data == d)
	{
		found = true;
	}

	//loop through until you find the element 
	while (iter->next != nullptr)
	{
		if (iter->data == d)
		{
			found = true;

		}
		iter = iter->next;
	}

	return found;
}


//*******************************************************************
//						dataCount
// recieves nothing
// returns the total count of the linkedlist
// returns an integer for the count
//********************************************************************
template <typename T>
int linkedList<T>::dataCount() {
	return count;
}


//*******************************************************************
//						emptyList
// receives nothing
// empties the entire list
// returns nothing 
//********************************************************************
template <typename T>
void linkedList<T>::emptyList() {
	linkNode<T>* iter = head;
	linkNode<T>* next;
	while (iter != NULL)
	{
		next = iter->next;
		delete iter;
		iter = next;
	}
	head = nullptr;
	count = 0;
	sortType = "";
	std::cout << "Your list has been emptied..." << std::endl;
}


//*******************************************************************
//							displayData
//	receives nothing
// displays all of the data within the linkedlist
// returns nothing 
//********************************************************************
template <typename T>
void linkedList<T>::displayData() {
	linkNode<T>* iter = head;

	// if list is empty:
	if (!head)
	{
		std::cout << "Nothing to display (empty list) " << std::endl;
		return;
	}

	//if there is only one node:
	if (iter->next == nullptr)
	{
		std::cout << iter->data << " ";
	}

	//else loop while print 
	else
	{
		while (iter != nullptr)
		{
			std::cout << iter->data << " ";
			iter = iter->next;
		}
	}
	std::cout << std::endl;
}

