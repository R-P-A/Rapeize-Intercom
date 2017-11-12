/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief This model contains only a id to be used in the SortedList class.
 */

#ifndef MODEL
#define MODEL

#include <iostream>
#include <exception>

using namespace std;

class Model {
	protected:
		/**
		 *	A number to define a position on the SortedList.
		 */
		unsigned long int id;

	public:
		/**
		 *	Constructor that initializes the model with an id.
		 */
		Model(unsigned long int value);

		/**
		 *	Get the id.
		 *	@return	The id.
		 */
		unsigned long int getId();
		
		/**
		 *	Set the id to the value given.
		 *	@param value The number to set the id.
		 */
		void setId(unsigned long int value);
};

#endif	// MODEL
