/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief Node for the SortedList class with generic data.
 *
 *	@section DESCRIPTION
 *	
 *	A header file for the SortedList class that contains a Node
 *	with generic type of data. It contains two pointers, one for
 *	the next node and one for the previous node.
 *
 *	@tparam Any data type.
 */

#ifndef NODE
#define NODE

#include <iostream>
#include <exception>

using namespace std;

template <class type>
class Node {
	private:
		/**
		 *	The data contained in the node.
		 */
		type data;

		/**
		 *	The pointer to the next node.
		 */
		Node<type>* next;

		/**
		 *	The pointer to the next node.
		 */
		Node<type>* prev;

	public:
		/**
		 *	The constructor that initiates the node data to 0.
		 */
		Node() {
			data = 0;
			next = NULL;
			prev = NULL;
		}

		/**
		 *	The constructor that initiates the node data to with the data given.
		 */
		Node(type data) {
			this->data = data;
			next = NULL;
			prev = NULL;
		}
		
		/**
		 *	The destructor that deletes the data.
		 */
		~Node () {
			delete data;
		}
		
		/**
		 *	Get the data.
		 *	@return	The data.
		 */
		type getData() {
			return data;
		}
		
		/**
		 *	Set the data to the value given.
		 *	@param value The value to set the data.
		 */
		void setData(type data) {
			this->data = data;
		}
		
		/**
		 *	Get the pointer to the next node.
		 *	@return	The pointer to the next node.
		 */
		Node<type>* getNext() {
			return next;
		}
		
		/**
		 *	Sets the next node but also sets the previous node of the next node
		 *	for usage in doubly linked list.
		 *	@param The pointer to the node to be set as next.
		 */
		void setNext(Node<type>* next) {
			this->next = next;
			if (next != NULL) {
				next->prev = this;
			}
		}
		
		/**
		 *	Get the pointer to the previous node.
		 *	@return	The pointer to the previous node.
		 */
		Node<type>* getPrev() {
			return prev;
		}
		
		/**
		 *	Sets the previous node but also sets the next node of the previous node
		 *	for usage in doubly linked list.
		 *	@param The pointer to the node to be set as previous.
		 */
		void setPrev(Node<type>* prev) {
			this->prev = prev;
			if (prev != NULL) {
				prev->next = this;
			}
		}
		
};

#endif		  // NODE
