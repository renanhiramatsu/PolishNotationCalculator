#pragma once

template <typename T>
class linkNode {
private:
	T data;
	linkNode<T>* next = nullptr;
public:
	T getData();
	linkNode<T>*  getNext();
	void setData(T);
	void setNext(linkNode<T>*);

};
template <typename T>
T linkNode<T>::getData() {
	return data;
}

template <typename T>
linkNode<T>* linkNode<T>::getNext() {
										// THROWING EXEPCTION of NULLPTR
		return next;
}
template <typename T>
void  linkNode<T> ::setData(T val) {
	data = val;
}

template <typename T>
void linkNode<T> ::setNext(linkNode<T>* pointer) {
	next = pointer;
}