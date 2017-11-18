/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief Create a doubly linked list which is sorted by id.
 *
 *	@section DESCRIPTION
 *	
 *	The doubly linked list accepts a data type Model which has only an id.
 *	The list is always sorted based on this id number. The insert function
 *	always sort the Model in the list.
 */

#ifndef SORTEDLIST
#define SORTEDLIST

#include <iostream>
#include <exception>
#include "model.h"
#include "node.h"

using namespace std;

class SortedList {
	private:
		/**
		 *	The first node of the list.
		 */
		Node<Model*>* head;

		/**
		 *	Find a node in the list and returns the pointer to it.
		 *	@param newModel The id of the node to be found.
		 */
		Node<Model*>* searchNode(unsigned long int id);

	public:
		SortedList();

		~SortedList();

		/**
		 *	Insert a Model in the list sorted.
		 *	@param newModel The new Model to be inserted.
		 *	@throw const char* "Inserted NULL Model".
		 *	@throw const char* "Id already exists".
		 */
		void insert(Model* newModel);

		/**
		 *	Read a Model in the list with this id and returns it.
		 *	@param id The id of the Model to be returned.
		 *	@return	The pointer to the Model desired. NULL if the Model don't exist.
		 */
		Model* search(unsigned long int id);

		/**
		 *	Update a Model in the list with this id.
		 *	@param modifiedModel The new Model that substitute the data in the old Model which shares the same id.
		 *	@throw const char* "Id not found".
		 */
		void update(Model* modifiedModel);

		/**
		 *	Remove a Model in the list with this id.
		 *	@param id The id of the Model to be removed.
		 *	@throw const char* "Id not found".
		 */
		void remove(unsigned long int id);

		/**
		 *	Print in a string all the ids of the Models in the list separated by \n.
		 *	@return	Return the string with the Models' ids.
		 */
		string listAll();
};

#endif		  // SORTEDLIST
