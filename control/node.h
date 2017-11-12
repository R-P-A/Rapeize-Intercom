/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
 *	@version 1.0 
 *	
 *	@brief Node for the SortedList class with generic data.
 *
 *	@section DESCRIPTION
 *	
 *	A header file for the SortedList class that contains a Node
 *	with generic type of data. It contains two pointers, one for
 *	the next node and one for the previous node.
 */

#ifndef NODE
#define NODE

#include <iostream>
#include <exception>

using namespace std;

template <class T>
class Node {
	private:
		T data;
		Node<T>* next;
		Node<T>* prev;

	public:
		Node() {
			data = 0;
			next = NULL;
			prev = NULL;
		}
		
		Node(T data) {
			this->data = data;
			next = NULL;
			prev = NULL;
		}
		
		~Node () {
			delete data;
		}
		
		T getData() {
			return data;
		}
		
		void setData(T data) {
			this->data = data;
		}
		
		Node<T>* getNext() {
			return next;
		}
		
		/**
		 *	Sets the next node but also sets the previous node of the next node
		 *	for usage in doubly linked list.
		 */
		void setNext(Node<T>* next) {
			this->next = next;
			if (next != NULL) {
				next->prev = this;
			}
		}
		
		Node<T>* getPrev() {
			return prev;
		}
		
		/**
		 *	Sets the previous node but also sets the next node of the previous node
		 *	for usage in doubly linked list.
		 */
		void setPrev(Node<T>* prev) {
			this->prev = prev;
			if (prev != NULL) {
				prev->next = this;
			}
		}
		
};

#endif		  // NODE
