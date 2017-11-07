/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
 *	@version 1.0 
 *	
 *	@brief This model contains the id used in the SortedList class.
 */

#ifndef MODEL
#define MODEL

#include <iostream>
#include <exception>

using namespace std;

class Model {
	protected:
		int id;

	public:
		int getId();
		void setId(int value);
};

#endif		  // MODEL
