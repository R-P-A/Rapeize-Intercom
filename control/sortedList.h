/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
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
#include "myString.h"

using namespace std;

class SortedList {
	private:
		Node<Model*>* head;
		Node<Model*>* findNode(int id);

	public:
		SortedList();
		~SortedList();

		/**
		 *	Insert a Model in the list sorted. If the Model id already exists
		 *	in the list returns false.
		 *	@param newModel		The new Model to be inserted.
		 *	@return	Wheter the Model was inserted correctly.
		 */
		bool insert(Model* newModel);

		/**
		 *	Remove a Model in the list with this id.
		 *	@param id 	The id of the Model to be removed.
		 *	@return	Wheter the Model was removed correctly.
		 */
		bool remove(int id);

		/**
		 *	Edit a Model in the list with this id.
		 *	@param modifiedModel 	The new Model that substitute the data in
		 *							the old Model which shares the same id.
		 *	@return	Wheter the Model was removed correctly.
		 */
		bool edit(Model* modifiedModel);

		/**
		 *	Find a Model in the list with this id and returns it.
		 *	@param id 	The id of the Model to be returned.
		 *	@return	The pointer to the Model desired. NULL if the Model don't exist.
		 */
		Model* find(int id);

		/**
		 *	Print in a string all the ids of the Models in the list separated by \n.
		 *	@return	Return the string with the Models' ids.
		 */
		string listAll();
};

#endif		  // SORTEDLIST
