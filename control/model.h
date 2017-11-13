/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief This model contains only a id to be used in the SortedList class in conjunction with Node.
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
		 *	Constructor that initializes the model with id = 0.
		 */
		Model();

		/**
		 *	Constructor that initializes the model with an id.
		 */
		Model(unsigned long int value);

		/**
		 *	@return	The id.
		 */
		unsigned long int getId();
		
		/**
		 *	@param value The number to set the id.
		 */
		void setId(unsigned long int value);
};

#endif	// MODEL
