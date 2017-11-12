/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
 *	@version 1.0 
 *	
 *	@brief Student class which represents a generic student.
 */

#ifndef STUDENT
#define STUDENT

#include <iostream>
#include <exception>
#include "model.h"
#include "myString.h"

using namespace std;

class Student : public Model {
	private:
		string name;
		float grade1;
		float grade2;
		string creationTime;
		string modificationTime;
		
	public:
		Student();
		Student(int id);
		~Student();

		string getName();
		void setName(string value);

		float getGrade1();
		/** @return Whether set was successfull if the grade is within limits (0-10). */
		bool setGrade1(float value);

		float getGrade2();
		/** @return Whether set was successfull if the grade is within limits (0-10). */
		bool setGrade2(float value);

		string getCreationTime();
		void setCreationTime(string value);

		string getModificationTime();
		void setModificationTime(string value);

		/** @return Average of grades. */
		float getFinalGrade();

		/** @return Every variable in a beutiful way. */
		string toString();
};

#endif		  // STUDENT
